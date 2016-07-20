// Copyright 2016 Derek Fletcher, All Rights Reserved.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Packet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSendPacket);

namespace FPacketType
{
	static const FString START_OPERATION = "START_OPERATION";
	static const FString PROPOSE = "PROPOSE";
	static const FString PROPOSE_OK = "PROPOSE_OK";
	static const FString ACCEPT = "ACCEPT";
	static const FString ACCEPT_OK = "ACCEPT_OK";
	static const FString DECIDE = "DECIDE";
	static const FString DECIDE_OK = "DECIDE_OK";
	static const FString END_OPERATION = "END_OPERATION";
}

UENUM(BlueprintType)
enum class EPacketSendTo : uint8
{
	CLIENT,
	PEER
};

USTRUCT(BlueprintType)
struct FPacketData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	class AClient* Client; // Starting client

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	class APeer* Peer; // The first peer the client sent the packet to

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	class APeer* DestinationPeer; // The current destination of this packet

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	EPacketSendTo SendTo;
};

/**
 * Responsible for carrying information between client and peer
 */
UCLASS()
class CSC462_API APacket : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	/**
	* Event broadcasters to blueprint
	*/
	UPROPERTY(BlueprintAssignable)
	FSendPacket OnSend;

	/**
	* Populate this packet with data and send it to location
	*/
	void Send(const FPacketData& Data);

protected:

	UPROPERTY(BlueprintReadOnly, Category = Paxos)
	FPacketData Data;

	/**
	* Called via blueprints after pack has arrived
	*/
	UFUNCTION(BlueprintCallable, Category = Paxos)
	void Arrive();
};
