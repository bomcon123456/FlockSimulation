// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlockManager.generated.h"

class ABoid;

UCLASS()
class BOIDSPLUGIN_API AFlockManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlockManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "BeginPlay")
		void BeginPlayFunction();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Boid")
	TArray<ABoid*> m_boids;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boid")
	int32 m_numberOfBoids;

	
};
