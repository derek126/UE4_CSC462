// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Client.h"
#include "Packet.h"
#include "Peer.h"

void APeer::BeginPlay()
{
	Super::BeginPlay();

	// Check that this peers know the other peers
	if (Peers.Num() == 0 || Peers.Num() % 2 == 0)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Peers needs to have more than 0 and an odd number of peers."))
	}

	// Make sure we have a reference to the Packet blueprint
	if (!PacketBP)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Client needs to have a packet defined."))
	}
}

void APeer::Receive(FPacketData Data)
{
	if (Data.Type == FPacketType::START_OPERATION)
	{
		if (bIsAlive)
		{
			SendProposals(Data);
		}
		else
		{
			Data.bIsError = true;
			Data.Client->Receive(Data);
		}
	}
	else if (Data.Type == FPacketType::PROPOSE)
	{
		Data.Type = FPacketType::PROPOSE_OK;
		if (bIsAlive) 
		{
			Data.DestinationPeer = Data.Peer;
			SendPacket(Data);
		}
		else
		{
			Data.bIsError = true;
			Data.Peer->Receive(Data);
		}
	}
	else if (Data.Type == FPacketType::ACCEPT)
	{
		Data.Type = FPacketType::ACCEPT_OK;
		if (bIsAlive)
		{
			Data.DestinationPeer = Data.Peer;
			SendPacket(Data);
		}
		else
		{
			Data.bIsError = true;
			Data.Peer->Receive(Data);
		}
	}
	else if (Data.Type == FPacketType::DECIDE)
	{
		Data.Type = FPacketType::DECIDE_OK;
		if (bIsAlive)
		{
			Data.DestinationPeer = Data.Peer;
			SendPacket(Data);
		}
		else
		{
			Data.bIsError = true;
			Data.Peer->Receive(Data);
		}
	}
	else if (Data.Type == FPacketType::PROPOSE_OK)
	{
		P_OK++;
		if (Data.bIsError)
		{
			bNotMajority = true;
		}

		if (P_OK == (Peers.Num() / 2) + 1)
		{
			if (bNotMajority)
			{
				bNotMajority = false;
				Data.bIsError = false;
				SendProposals(Data);
			}
			else
			{
				SendAccepts(Data);
			}
		}
	}
	else if (Data.Type == FPacketType::ACCEPT_OK)
	{
		A_OK++;
		if (Data.bIsError)
		{
			bNotMajority = true;
		}

		if (A_OK == (Peers.Num() / 2) + 1)
		{
			if (bNotMajority)
			{
				bNotMajority = false;
				Data.bIsError = false;
				SendAccepts(Data);
			}
			else
			{
				SendDecides(Data);
			}
		}
	}
	else if (Data.Type == FPacketType::DECIDE_OK)
	{
		D_OK++;
		if (Data.bIsError)
		{
			bNotMajority = true;
		}

		if (D_OK == Peers.Num())
		{
			if (bNotMajority)
			{
				bNotMajority = false;
				Data.bIsError = false;
				SendDecides(Data);
			}
			else
			{
				D_OK = 0;
				Data.SendTo = EPacketSendTo::CLIENT;
				Data.Type = FPacketType::END_OPERATION;
				SendPacket(Data);
			}
		}
	}
}

TArray<int32> APeer::ChooseMajority() const
{
	TArray<int32> Indices;

	while (Indices.Num() != (Peers.Num() / 2) + 1)
	{
		int32 Index = FMath::RandRange(0, Peers.Num() - 1);
		if (!Indices.Contains(Index))
		{
			Indices.Push(Index);
		}
	}

	return Indices;
}

void APeer::SendPacket(struct FPacketData Data)
{
	const FVector MyLocation = GetActorLocation();
	APacket* Packet = GetWorld()->SpawnActor<APacket>(PacketBP, MyLocation, FRotator(0));

	Packet->Send(Data);
}

void APeer::SendProposals(FPacketData Data)
{
	const TArray<int32> Indices = ChooseMajority();

	P_OK = 0;

	Data.Type = FPacketType::PROPOSE;
	for (const int32& Index : Indices)
	{
		Data.DestinationPeer = Peers[Index];
		SendPacket(Data);
	}
}

void APeer::SendAccepts(FPacketData Data)
{
	const TArray<int32> Indices = ChooseMajority();

	A_OK = 0;

	Data.Type = FPacketType::ACCEPT;
	for (const int32& Index : Indices)
	{
		Data.DestinationPeer = Peers[Index];
		SendPacket(Data);
	}
}

void APeer::SendDecides(FPacketData Data)
{
	D_OK = 0;

	Data.Type = FPacketType::DECIDE;
	for (APeer* Peer : Peers)
	{
		Data.DestinationPeer = Peer;
		SendPacket(Data);
	}
}
