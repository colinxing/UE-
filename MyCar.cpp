// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

//APlayerController* cur;
const APlayerController* PlayerController;
// Sets default values
AMyCar::AMyCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	//cur = new APlayerController();
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
void AMyCar::Tick(float DeltaTime)
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
		PlayerController->ProjectWorldLocationToScreen(OutVertices[BoundsPointItr], ScreenLocation);
		// Add to 2D bounding box
		ActorBox2D += ScreenLocation;// FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
	}

	XXX = ActorBox2D.Min.X;
	YYY = ActorBox2D.Min.Y;
	WWW = ActorBox2D.GetSize().X;
	HHH = ActorBox2D.GetSize().Y;

	//DrawRect(FColor::Red, ActorBox2D.Min.X, ActorBox2D.Min.Y, ActorBox2D.GetSize().X, ActorBox2D.GetSize().Y);
	//outOrigin = ActorBox2D.Min;
	//outSize = ActorBox2D.GetSize();
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Bounding Box:") + FString::FromInt(ActorBox2D.Min.X) + FString::FromInt(ActorBox2D.Min.Y) + FString::FromInt(ActorBox2D.Max.X) + FString::FromInt(ActorBox2D.Max.Y));
}

