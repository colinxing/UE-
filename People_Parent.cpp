// Fill out your copyright notice in the Description page of Project Settings.


#include "People_Parent.h"

// Sets default values
APeople_Parent::APeople_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APeople_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeople_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

