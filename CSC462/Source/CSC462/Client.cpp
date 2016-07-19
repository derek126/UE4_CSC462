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

	if (Peers.Num() == 0 || Peers.Num() % 2 == 0)
	{
		   UE_LOG(LogTemp, Fatal, TEXT("Client needs to have more than 0 and an odd number of peers."))
	}

	if (!PacketBP)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Client needs to have a packet defined."))
	}
}

// Called every frame
void AClient::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AClient::SendPacket(APeer* Peer)
{
	const FVector MyLocation = GetActorLocation();
	APacket* Packet = GetWorld()->SpawnActor<APacket>(PacketBP, MyLocation, FRotator(0));

	FPacketData Data;
	Data.Client = this;
	Data.Peer = Peer;
	Data.Sender = EPacketSender::CLIENT;

	Packet->Send(Data);
}

void AClient::SendPackets()
{
	for (APeer* Peer : Peers) 
	{
		SendPacket(Peer);
	}
}
