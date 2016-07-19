// Copyright 2016 Derek Fletcher, All Rights Reserved.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Peer.generated.h"

/**
 * The paxos peer which will contain the paxos protocol,
 * and have some event exposed to UE4 for visualization
 */
UCLASS()
class CSC462_API APeer : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = Paxos)
	bool bIsActive = true;

	/**
	* The function handles the peer receiving the packet
	*/
	void Receive(const struct FPacketData& Data);
};
