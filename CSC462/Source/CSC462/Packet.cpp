// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Packet.h"
#include "Peer.h"
#include "Client.h"

void APacket::Send(const FPacketData& Data)
{
	this->Data = Data;
	OnSend.Broadcast(); // Fire blueprint event
}

void APacket::Arrive()
{
	if (Data.SendTo == EPacketSendTo::PEER)
	{
		Data.DestinationPeer->Receive(Data);
	}
	else
	{
		Data.Client->Receive(Data);
	}

	// Destroy the packet after the data is transferred
	this->Destroy();
}