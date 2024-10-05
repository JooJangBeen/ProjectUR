// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KallariDagger.generated.h"

UCLASS()
class PROJECTUR_API AKallariDagger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKallariDagger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void EclipseDagger_OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void FireInDirection(const FVector& ShootDirection);
	bool GetIsOnGround() { return bIsOnGround; };
	FVector GetHittedGroundPos() { return HittedGroundPos; };


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UStaticMeshComponent> DaggerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UParticleSystemComponent> ProjectileDaggerParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UProjectileMovementComponent> MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<class USphereComponent> CollisionComponent;

private:
	bool bIsOnGround = false;
	FVector HittedGroundPos;
};
