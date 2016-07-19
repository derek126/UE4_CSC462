// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Packet.h"
#include "Peer.h"

void APacket::Send(const FPacketData& Data)
{
	this->Data = Data;
	OnSend.Broadcast();
}

void APacket::Arrive()
{
	if (Data.Sender == EPacketSender::CLIENT)
	{
		Data.Peer->Receive(Data);
	}

	this->Destroy();
}