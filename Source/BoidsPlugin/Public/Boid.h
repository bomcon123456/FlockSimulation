// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class BOIDSPLUGIN_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Flock(TArray<ABoid*> boids);
	void UpdateBoid(float DeltaTime);
	
	void SetMag(FVector& in, float length);
	void Limit(FVector& in, float length);


	FVector Align(TArray<ABoid*> boids);
	FVector Cohesion(TArray<ABoid*> boids);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		UStaticMeshComponent* m_meshComp;

	FVector m_initialPosition;
	FVector m_velocity;
	FVector m_acceleration;

	float m_maxForce;
	float m_maxSpeed;
	
};
