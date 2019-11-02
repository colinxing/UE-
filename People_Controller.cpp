// Fill out your copyright notice in the Description page of Project Settings.


#include "People_Controller.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "../MyBlueprintFunctionLibrary.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <vector>
#include <thread>
#include <unordered_set>

std::vector<FVector> PlaneLocs{{-13297, 9120.0, 0},{-12927, -300.0, 0},{-3090, -8120, 0},{-3067, 1200, 0},{-2380, 6670,0}};
std::vector<FRotator> PlaneRots{{-0, 109, 0},{0, 90, 0},{0, -60, 0},{0, -90, 0},{0, -110, 0}};
std::vector<FVector> VehicleLocs;
std::vector<FRotator> VehicleRots;

std::vector<AMyCharacter*> myChars;


UMyBlueprintFunctionLibrary* LoadFile;
FString fileNameWrite = "Output.txt";

// Sets default values
APeople_Controller::APeople_Controller()
{
	FString fromFile;
	FString fileName = "Configuration.txt";
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.f;
	xCord = 0.f;
	yCord = 0.f;

	ourRot.ZeroRotator;

	ourLoc.X = 0.f;
	ourLoc.Y = 0.f;
	ourLoc.Z = 0.f;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (i == 0)
			{
				ourLoc.X = FMath::RandRange(-16000, -10000);
				ourLoc.Y = FMath::RandRange(10000, 12000);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			else if (i == 1)
			{
				ourLoc.X = FMath::RandRange(-14500, -11000);
				ourLoc.Y = FMath::RandRange(1500, 5500);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			else if (i == 2)
			{
				ourLoc.X = FMath::RandRange(-14500, -11000);
				ourLoc.Y = FMath::RandRange(-5000, -2000);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			else if (i == 3)
			{
				ourLoc.X = FMath::RandRange(-5500, -2000);
				ourLoc.Y = FMath::RandRange(-5500, -760);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			else if (i == 4)
			{
				ourLoc.X = FMath::RandRange(-5500, -2000);
				ourLoc.Y = FMath::RandRange(2900, 5000);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			else if (i == 5)
			{
				ourLoc.X = FMath::RandRange(-5500, -2000);
				ourLoc.Y = FMath::RandRange(9900, 12000);
				ourRot.Yaw = FMath::RandRange(0, 359);
			}
			VehicleLocs.push_back(ourLoc);
			VehicleRots.push_back(ourRot);
		}
	}

	ourRot.ZeroRotator;
	ourLoc.X = 0.f;
	ourLoc.Y = 0.f;
	ourLoc.Z = 0.f;
}


void fun(AMyCharacter** t, int a)
{
	if ((*t) == NULL)
		return;
	(*t)->Num = a;
}
int peopleCnt = -1, carCnt = -1, planeCnt = -1, route = -1;
// Called when the game starts or when spawned
void APeople_Controller::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Spawning"));

	FString fromFile;
	FString fileName = "Configuration.txt";
	FString fileNameWrite = "Output.txt";

	if (LoadFile->FileLoadString(fileName, fromFile))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, fromFile);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FPaths::GameDir() + fileName);
	}

	std::string stringFile = std::string(TCHAR_TO_UTF8(*fromFile));
	
	int start = 0;

	for (int i = 0; i < stringFile.length(); i++)
	{
		if (stringFile[i] == ':')
		{
			if (stringFile.substr(start, i - start) == "People")
			{
				for (int j = i + 1; j < stringFile.length(); j++)
				{
					if (stringFile[j] == ';')
					{
						peopleCnt = stoi(stringFile.substr(i + 1, j - i - 1));
						start = j + 1;
						break;
					}
				}
				//if (peopleCnt == -1)
					//peopleCnt = stoi(stringFile.substr(i + 1));
				//break;
			}
			else if (stringFile.substr(start, i - start) == "Car")
			{
				for (int j = i + 1; j < stringFile.length(); j++)
				{
					if (stringFile[j] == ';')
					{
						carCnt = stoi(stringFile.substr(i + 1, j - i - 1));
						start = j + 1;
						break;
					}
				}
			}
			else if (stringFile.substr(start, i - start) == "Airplane")
			{
				for (int j = i + 1; j < stringFile.length(); j++)
				{
					if (stringFile[j] == ';')
					{
						planeCnt = stoi(stringFile.substr(i + 1, j - i - 1));
						start = j + 1;
						break;
					}
				}
			}
			else if (stringFile.substr(start, i - start) == "Route")
			{
				for (int j = i + 1; j < stringFile.length(); j++)
				{
					if (stringFile[j] == ';')
					{
						route = stoi(stringFile.substr(i + 1, j - i - 1));
						start = j + 1;
						break;
					}
				}
			}
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Route is:") + FString::FromInt(route));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Airplane is:") + FString::FromInt(planeCnt));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Car is:") + FString::FromInt(carCnt));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,TEXT("Number is:") + FString::FromInt(peopleCnt));

	FActorSpawnParameters spawnParamsTest;
	spawnParamsTest.Owner = this;
	spawnParamsTest.Instigator = Instigator;

	ourLoc.X = -5210.f;
	ourLoc.Y = -1420.f;

	if(route == 1)
		ACharacter* NewBPP = GetWorld()->SpawnActor<ACharacter>(BPP, ourLoc, ourRot, spawnParamsTest);
	else if (route == 2)
		ACharacter* NewBPP = GetWorld()->SpawnActor<ACharacter>(BPP2, ourLoc, ourRot, spawnParamsTest);
	else if (route == 3)
		ACharacter* NewBPP = GetWorld()->SpawnActor<ACharacter>(BPP3, ourLoc, ourRot, spawnParamsTest);
	else if (route == 4)
		ACharacter* NewBPP = GetWorld()->SpawnActor<ACharacter>(BPP4, ourLoc, ourRot, spawnParamsTest);
	else if (route == 5)
		ACharacter* NewBPP = GetWorld()->SpawnActor<ACharacter>(BPP5, ourLoc, ourRot, spawnParamsTest);

	//ourNewPerson->Num = 1;
	//ourLoc.X = 0.f;
	//ourLoc.Y = 0.f;

	std::unordered_set<int> set;
	for (int i = 0; i < planeCnt; i++)
	{
		int c = rand() % PlaneLocs.size();
		if (set.find(c) != set.end())
		{
			i--;
			continue;
		}

		set.insert(c);
		ourLoc = PlaneLocs[c];
		ourRot = PlaneRots[c];

		AAirplane* ourNewAirplane = GetWorld()->SpawnActor<AAirplane>(Airplane1, ourLoc, ourRot, spawnParamsTest);
	}

	set.clear();
	for (int i = 0; i < carCnt; i++)
	{
		int c = rand() % VehicleLocs.size();
		if (set.find(c) != set.end())
		{
			i--;
			continue;
		}

		set.insert(c);
		ourLoc = VehicleLocs[c];
		ourRot = VehicleRots[c];

		int c2 = rand() % 6;
		if (c2 == 0)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle1, ourLoc, ourRot, spawnParamsTest);
		else if (c2 == 1)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle2, ourLoc, ourRot, spawnParamsTest);
		else if (c2 == 2)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle3, ourLoc, ourRot, spawnParamsTest);
		else if (c2 == 3)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle4, ourLoc, ourRot, spawnParamsTest);
		else if (c2 == 4)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle5, ourLoc, ourRot, spawnParamsTest);
		else if (c2 == 5)
			AMyCar* ourNewVehicle = GetWorld()->SpawnActor<AMyCar>(Vehicle6, ourLoc, ourRot, spawnParamsTest);
	}
	
	set.clear();
	for (int i = 0; i < peopleCnt; i++)
	{
		xCord = generateX();
		yCord = generateY();

		ourLoc.X = xCord;
		ourLoc.Y = yCord;

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;
		
		int routee = rand() % 20;
		if (set.find(routee) != set.end())
		{
			i--;
			continue;
		}
		set.insert(routee);

		int c = rand() % 2;
		if (c == 0)
		{
			AMyCharacter* ourNewPerson = GetWorld()->SpawnActor<AMyCharacter>(ourSpawningPersonTest, ourLoc, ourRot, spawnParamsTest);
			if (ourNewPerson)
				myChars.push_back(ourNewPerson);
			std::thread t(fun, &ourNewPerson, routee);
			t.join();
		}
		else if (c == 1)
		{
			AMyCharacter* ourNewPerson = GetWorld()->SpawnActor<AMyCharacter>(ourSpawningPersonTest2, ourLoc, ourRot, spawnParamsTest);
			std::thread t(fun, &ourNewPerson, routee);
			t.join();
		}
	}

}

// Called every frame
void APeople_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString outPeople = TEXT("");
	float z = 0;

	for (int i = 0; i < myChars.size(); i++)
	{
		if ((int)myChars[i]->XXX == 0 || (int)myChars[i]->YYY == 0 || (int)myChars[i]->WWW <= 20 || (int)myChars[i]->HHH <= 20)
			continue;
		outPeople += TEXT("X:") + FString::FromInt(myChars[i]->XXX) + TEXT("Y:") + FString::FromInt(myChars[i]->YYY) +
			TEXT("W:") + FString::FromInt(myChars[i]->WWW) + TEXT("H:") + FString::FromInt(myChars[i]->HHH) + TEXT("\r");
	}

	LoadFile->FileSaveString(outPeople, fileNameWrite);
}

float APeople_Controller::generateX()
{
	float passBack = 0.f;
	
	passBack = FMath::RandRange(-15050, 2500);
	
	return passBack;
}

float APeople_Controller::generateY()
{
	float passBack = 0.f;

	passBack = FMath::RandRange(-13000, 20000);

	return passBack;
}

