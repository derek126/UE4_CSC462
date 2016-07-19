// Copyright 2016 Derek Fletcher, All Rights Reserved.

#include "CSC462.h"
#include "Peer.h"

void APeer::Receive(const FPacketData& Data)
{
	if (bIsActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Peer %s received the packet!"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Peer %s is dead!"), *GetName());
	}
}


