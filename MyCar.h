// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCar.generated.h"

UCLASS()
class AIRPORT_API AMyCar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
	float XXX;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
	float YYY;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
	float WWW;

	UPROPERTY(BlueprintReadWrite, Category = "Path spline")
	float HHH;
};
