// Fill out your copyright notice in the Description page of Project Settings.

#include "Boid.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABoid::ABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = m_meshComp;	

	m_initialPosition = FVector(0.f);
	m_velocity = FVector(FMath::RandRange(0.f, 100.f), FMath::RandRange(0.f, 100.f), FMath::RandRange(0.f, 100.f));
	SetMag(m_velocity, FMath::RandRange(2.f, 4.f));
		
	m_acceleration = FVector(0.f);
	m_maxForce = 0.2f;
	m_maxSpeed = 4.f;
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABoid::Flock(TArray<ABoid*> boids)
{
	//FVector aligment = Align(boids);
	FVector cohesion = Cohesion(boids);
	//m_acceleration += aligment;	
	m_acceleration += cohesion;
}

void ABoid::UpdateBoid(float DeltaTime)
{
	this->AddActorLocalOffset(m_velocity*DeltaTime);
	m_velocity += m_acceleration * DeltaTime;
	Limit(m_velocity, m_maxSpeed);
	m_acceleration *= 0.f;
}

void ABoid::SetMag(FVector & in, float length)
{
	in.Normalize();
	in *= length;
}

void ABoid::Limit(FVector & in, float length)
{
	if (in.Size() > length)
	{
		SetMag(in, length);
	}
}

FVector ABoid::Align(TArray<ABoid*> boids)
{
	int perceptionRadius = 100;
	int totalBoids = 0;
	FVector steering = FVector();
	for (ABoid* other : boids)
	{
		float distance = FVector::Dist(GetActorLocation(), other->GetActorLocation());
		if (other != this && distance < perceptionRadius)
		{
			steering += other->m_velocity;
			totalBoids++;
		}
	}
	if (totalBoids)
	{
		steering /= totalBoids;
		SetMag(steering, m_maxSpeed);
		steering -= m_velocity;
		Limit(steering, m_maxForce);
	}
	return steering;
}

FVector ABoid::Cohesion(TArray<ABoid*> boids)
{
	int perceptionRadius = 50;
	int totalBoids = 0;
	FVector steering = FVector();
	for (ABoid* other : boids)
	{
		float distance = FVector::Dist(GetActorLocation(), other->GetActorLocation());
		if (other != this && distance < perceptionRadius)
		{
			steering += other->GetActorLocation();
			totalBoids++;
		}
	}
	if (totalBoids)
	{
		steering /= totalBoids;
		steering -= GetActorLocation();
		SetMag(steering, m_maxSpeed);
		steering -= m_velocity;
		Limit(steering, m_maxForce);
	}
	return steering;
}
