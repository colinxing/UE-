// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"
#include "Track.h"
#include "MyCharacter.generated.h"

UCLASS()
class AIRPORT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category = "Active")
	bool Active;

	UPROPERTY(BlueprintReadWrite, Category = "Active")
	float Duration;

	UPROPERTY(BlueprintReadWrite, Category = "Active")
	float Startoffset;

	UPROPERTY(BlueprintReadWrite, Category = "Active")
	float Alpha;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
	float Num = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
		float XXX;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
		float YYY;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
		float WWW;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
		float HHH;
};
