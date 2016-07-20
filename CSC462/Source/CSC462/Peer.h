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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**
	* The function handles the peer receiving the packet
	*/
	void Receive(struct FPacketData Data);

protected:

	/**
	* Is this node alive or dead?
	*/
	UPROPERTY(BlueprintReadWrite, Category = Paxos)
	bool bIsAlive = true;

	/**
	* Reference for the packet type to spawn
	*/
	UPROPERTY(EditAnywhere, Category = Paxos)
	TSubclassOf<class APacket> PacketBP;

	/**
	* All of the other peers in the simulation
	*/
	UPROPERTY(EditAnywhere, Category = Paxos)
	TArray<class APeer*> Peers;

	/**
	* Keep track of how many propose/accept/decide_ok
	*/
	int32 P_OK = 0;
	int32 A_OK = 0;
	int32 D_OK = 0;

	/**
	* Randomly chooses the indices for peers
	*/
	TArray<int32> ChooseMajority() const;

	/**
	* Sends a packet based on the data provided
	*/
	void SendPacket(struct FPacketData Data);

	/**
	* Sends the proposal packets
	*/
	void SendProposals(struct FPacketData Data);

	/**
	* Sends the accept packets
	*/
	void SendAccepts(struct FPacketData Data);

	/**
	* Sends the decide packets
	*/
	void SendDecides(struct FPacketData Data);
};
