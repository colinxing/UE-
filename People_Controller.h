// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Car/MyCar.h"
#include "../Airplane/Airplane.h"
#include "GameFramework/Actor.h"
#include "People_Parent.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "People_Controller.generated.h"

UCLASS()
class AIRPORT_API APeople_Controller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeople_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Hold current alive time
	float currentTime;

	// Generate a new X
	float generateX();

	// Hold the xCord
	float xCord;

	// Generate a new Y
	float generateY();

	// Hold the yCord
	float yCord;

	// Old location
	FTransform oldLocation;

	// Hold our location
	FVector ourLoc;
	
	// Hold our Rotation
	FRotator ourRot;

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Person")
	// "People_parent.h" Hold the blue print object
	//APeople_Parent* ourSpawningPerson;
	TSubclassOf<APeople_Parent> ourSpawningPerson;

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Person2")
	TSubclassOf<ACharacter> ourSpawningPerson2;

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Person3")
	TSubclassOf<APeople_Parent> ourSpawningPerson3;

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Person Test")
	TSubclassOf<AMyCharacter> ourSpawningPersonTest;

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Person Test2")
	TSubclassOf<AMyCharacter> ourSpawningPersonTest2;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle1")
	TSubclassOf<AMyCar> Vehicle1;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle2")
	TSubclassOf<AMyCar> Vehicle2;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle3")
	TSubclassOf<AMyCar> Vehicle3;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle4")
	TSubclassOf<AMyCar> Vehicle4;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle5")
	TSubclassOf<AMyCar> Vehicle5;

	UPROPERTY(EditDefaultsOnly, Category = "Vehicle6")
	TSubclassOf<AMyCar> Vehicle6;

	UPROPERTY(EditDefaultsOnly, Category = "Airplane1")
	TSubclassOf<AAirplane> Airplane1;

	UPROPERTY(EditDefaultsOnly, Category = "BPP")
	TSubclassOf<ACharacter> BPP;

	UPROPERTY(EditDefaultsOnly, Category = "BPP2")
	TSubclassOf<ACharacter> BPP2;

	UPROPERTY(EditDefaultsOnly, Category = "BPP3")
	TSubclassOf<ACharacter> BPP3;

	UPROPERTY(EditDefaultsOnly, Category = "BPP4")
	TSubclassOf<ACharacter> BPP4;

	UPROPERTY(EditDefaultsOnly, Category = "BPP5")
	TSubclassOf<ACharacter> BPP5;
};
