// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	if(GetActorQuat().Z == 0)
	{
		rightDirection = true;
	}
	else if(GetActorQuat().Z == 180)
	{
		rightDirection = false;
	}
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyEnemy::MoveEnemy(bool willNotFall, float delta, float speed, float distance, float traceDistanceFall, float traceDistanceFront)
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	
	if(willNotFall)
	{
		if(rightDirection)
		{
			// Checking if actor is about to fall
			FVector StartFall = FVector(GetActorLocation().X, GetActorLocation().Y + distance, GetActorLocation().Z);
			FVector EndFall = StartFall + (-GetActorUpVector() * traceDistanceFall);

			if(!GetWorld()->LineTraceSingleByChannel(OutHit, StartFall, EndFall, ECC_WorldStatic, CollisionParams))
			{
				// Look toward left direction
				DrawDebugLine(GetWorld(), StartFall, EndFall, FColor::Red, false, 1, 0, 5);
				
				FQuat newQuad = FQuat(FRotator(0, 180, 0));
				SetActorRotation(newQuad);
				rightDirection = false;
			}
			else
			{
				// Move towards right direction
				//DrawDebugLine(GetWorld(), StartFall, EndFall, FColor::Green, false, 1, 0, 5);
				FVector newPos = FVector(0, delta * speed, 0);
				AddActorWorldTransform(FTransform(newPos));
			}

			// Checking if actor is colliding with something in right direction
			FVector StartFront = FVector(GetActorLocation().X, GetActorLocation().Y + distance, GetActorLocation().Z); 
			FVector EndFront = StartFront + (GetActorRightVector() * traceDistanceFront);
			DrawDebugLine(GetWorld(), StartFront, EndFront, FColor::Black, false, 1, 0, 5);

			if(GetWorld()->LineTraceSingleByChannel(OutHit, StartFront, EndFront, ECC_WorldStatic, CollisionParams))
			{
				// Look toward left direction
				FQuat newQuad = FQuat(FRotator(0, 180, 0));
				SetActorRotation(newQuad);
				rightDirection = false;
			}

		}
		else if(!rightDirection)
		{
			// Checking if actor is about to fall
			FVector StartFall = FVector(GetActorLocation().X, GetActorLocation().Y - distance, GetActorLocation().Z);
			FVector EndFall = StartFall + (-GetActorUpVector() * traceDistanceFall);
			
			if(!GetWorld()->LineTraceSingleByChannel(OutHit, StartFall, EndFall, ECC_WorldStatic, CollisionParams))
			{
				// Look toward right direction
				DrawDebugLine(GetWorld(), StartFall, EndFall, FColor::Red, false, 1, 0, 5);
				
				FQuat newQuad = FQuat(FRotator(0, 0, 0));
				SetActorRotation(newQuad);
				rightDirection = true;
			}
			else
			{
				// Move towards left direction
				//DrawDebugLine(GetWorld(), StartFall, EndFall, FColor::Green, false, 1, 0, 5);
				FVector newPos = FVector(0, delta * -speed, 0);
				AddActorWorldTransform(FTransform(newPos));
			}

			// Checking if actor is colliding with something in left direction
			FVector StartFront = FVector(GetActorLocation().X, GetActorLocation().Y - distance, GetActorLocation().Z); 
			FVector EndFront = StartFront + (GetActorRightVector() * traceDistanceFront);
			DrawDebugLine(GetWorld(), StartFront, EndFront, FColor::Black, false, 1, 0, 5);

			if(GetWorld()->LineTraceSingleByChannel(OutHit, StartFront, EndFront, ECC_WorldStatic, CollisionParams))
			{
				// Look toward right direction
				FQuat newQuad = FQuat(FRotator(0, 0, 0));
				SetActorRotation(newQuad);
				rightDirection = true;
			}
		}
	}
	else
	{
		if(rightDirection)
		{
			// Move in right direction
			FVector newPos = FVector(0, delta * speed, 0);
			AddActorWorldTransform(FTransform(newPos));

			// Checking if actor colliding with something in right direction
			FVector StartFront = FVector(GetActorLocation().X, GetActorLocation().Y + distance, GetActorLocation().Z); 
			FVector EndFront = StartFront + (GetActorRightVector() * traceDistanceFront);
			DrawDebugLine(GetWorld(), StartFront, EndFront, FColor::Black, false, 1, 0, 5);

			if(GetWorld()->LineTraceSingleByChannel(OutHit, StartFront, EndFront, ECC_WorldStatic, CollisionParams))
			{
				// Look toward left direction
				FQuat newQuad = FQuat(FRotator(0, 180, 0));
				SetActorRotation(newQuad);
				rightDirection = false;
			}
		}
		else
		{
			// Move in left direction
			FVector newPos = FVector(0, delta * -speed, 0);
			AddActorWorldTransform(FTransform(newPos));

			// Checking if actor colliding with something in left direction
			FVector StartFront = FVector(GetActorLocation().X, GetActorLocation().Y - distance, GetActorLocation().Z); 
			FVector EndFront = StartFront + (GetActorRightVector() * traceDistanceFront);
			DrawDebugLine(GetWorld(), StartFront, EndFront, FColor::Black, false, 1, 0, 5);

			if(GetWorld()->LineTraceSingleByChannel(OutHit, StartFront, EndFront, ECC_WorldStatic, CollisionParams))
			{
				// Look toward right direction
				FQuat newQuad = FQuat(FRotator(0, 0, 0));
				SetActorRotation(newQuad);
				rightDirection = true;
			}
		}
	}
}
