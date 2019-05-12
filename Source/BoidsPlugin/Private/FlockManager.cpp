// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockManager.h"
#include "Boid.h"

// Sets default values
AFlockManager::AFlockManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlockManager::BeginPlay()
{
	Super::BeginPlay();
	BeginPlayFunction();
	
}

// Called every frame
void AFlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ABoid* boid : m_boids)
	{
		boid->Flock(m_boids);
		boid->UpdateBoid(DeltaTime);
	}
}

