// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Packet.h"

void APacket::Send(const FPacketData& Data)
{
	this->Data = Data;
	OnSend.Broadcast();
}

void APacket::Arrive()
{
	this->Destroy();
}