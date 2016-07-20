// Copyright 2016 Derek Fletcher, All Rights Reserved.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Client.generated.h"

/**
 * The client what will be issuing requests to paxos peers
 */
UCLASS()
class CSC462_API AClient : public AStaticMeshActor
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 

	AClient();

	/**
	* The function handles the client receiving the packet
	*/
	void Receive(struct FPacketData Data);

protected:

	bool bOperationInProgress = false;

	/**
	* Reference for the packet type to spawn
	*/
	UPROPERTY(EditAnywhere, Category = Paxos)
	TSubclassOf<class APacket> PacketBP;

	/**
	* All of the peers in the simulation
	*/
	UPROPERTY(EditAnywhere, Category = Paxos)
	TArray<class APeer*> Peers;

	/**
	* Begins the process by sending the intitial packet to a paxos peer
	*/
	UFUNCTION(BlueprintCallable, Category = Paxos)
	void StartOperation();
};
