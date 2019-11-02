// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "../MyBlueprintFunctionLibrary.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

// Sets default values
const APlayerController* PlayerController2;
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController2 = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

const FVector BoundsPointMapping[8] =
{
	FVector(1, 1, 1),
	FVector(1, 1, -1),
	FVector(1, -1, 1),
	FVector(1, -1, -1),
	FVector(-1, 1, 1),
	FVector(-1, 1, -1),
	FVector(-1, -1, 1),
	FVector(-1, -1, -1)
};

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FBox EachActorBounds = this->GetComponentsBoundingBox(true); /* All Components */

 //Center
	const FVector BoxCenter = EachActorBounds.GetCenter();

	//Extents
	const FVector BoxExtents = EachActorBounds.GetExtent();

	FOrientedBox oBox;
	oBox.Center = BoxCenter;
	oBox.ExtentX = BoxExtents.X;
	oBox.ExtentY = BoxExtents.Y;
	oBox.ExtentZ = BoxExtents.Z;
	//oBox.AxisX = AxisX;
	//oBox.AxisY = AxisY;
	//oBox.AxisZ = AxisZ;

	FVector OutVertices[8];
	oBox.CalcVertices(OutVertices);

	// Build 2D bounding box of actor in screen space
	FBox2D ActorBox2D(0);
	for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
	{
		FVector2D ScreenLocation;

		// Project vert into screen space.
		PlayerController2->ProjectWorldLocationToScreen(OutVertices[BoundsPointItr], ScreenLocation);
		// Add to 2D bounding box
		ActorBox2D += ScreenLocation;// FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
	}

	XXX = ActorBox2D.Min.X;
	YYY = ActorBox2D.Min.Y;
	WWW = ActorBox2D.GetSize().X;
	HHH = ActorBox2D.GetSize().Y;

	//XXX = XXX + WWW / 2 - 10;
	//YYY = YYY + HHH / 2 - 10;
	//WWW /= 10;
	//HHH /= 10;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

