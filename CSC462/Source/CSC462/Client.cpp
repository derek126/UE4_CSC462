// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Client.h"
#include "Packet.h"

AClient::AClient()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();

	// Check that the client knows the peers
	if (Peers.Num() == 0 || Peers.Num() % 2 == 0)
	{
		   UE_LOG(LogTemp, Fatal, TEXT("Client needs to have more than 0 and an odd number of peers."))
	}

	// Make sure we have a reference to the Packet blueprint
	if (!PacketBP)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Client needs to have a packet defined."))
	}
}

void AClient::Receive(struct FPacketData Data)
{
	if (Data.Type == FPacketType::END_OPERATION)
	{
		bOperationInProgress = false;
	}
	else if (Data.bIsError && Data.Type == FPacketType::START_OPERATION)
	{
		bOperationInProgress = false;
		StartOperation();
	}
}

void AClient::StartOperation()
{
	if (bOperationInProgress) return;

	int32 Index = FMath::RandRange(0, Peers.Num() - 1);

	const FVector MyLocation = GetActorLocation();
	APacket* Packet = GetWorld()->SpawnActor<APacket>(PacketBP, MyLocation, FRotator(0));

	// Create the start opeation pakcet
	FPacketData Data;
	Data.Client = this;
	Data.Peer = Peers[Index];
	Data.DestinationPeer = Peers[Index];
	Data.SendTo = EPacketSendTo::PEER;
	Data.Type = FPacketType::START_OPERATION;

	Packet->Send(Data);
	bOperationInProgress = true;
}
