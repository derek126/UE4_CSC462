// Copyright 2016 Derek Fletcher, All Rights Reserved.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Packet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSendPacket);

UENUM(BlueprintType)
enum class EPacketSender : uint8
{
	CLIENT,
	PEER
};

USTRUCT(BlueprintType)
struct FPacketData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	class AClient* Client;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	class APeer* Peer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Paxos)
	EPacketSender Sender;
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

	/**
	* Called via blueprints after pack has arrived
	*/
	UFUNCTION(BlueprintCallable, Category = Paxos)
	void Arrive();

protected:

	UPROPERTY(BlueprintReadOnly, Category = Paxos)
	FPacketData Data;
};
