// Fill out your copyright notice in the Description page of Project Settings.


#include "DiceComponent.h"

// Sets default values for this component's properties
UDiceComponent::UDiceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDiceComponent::BeginPlay()
{
	Super::BeginPlay();
}

int32 UDiceComponent::RollDice()
{
	//1. Ana zari at
	int32 TotalResult = ExecuteRoll(BaseDice);
	
	//2. Bonus zar setlerini sırayla at ve sonucu ekle
	for (const FDiceSet& BonusSet : BonusDiceSets)
	{
		TotalResult += ExecuteRoll(BonusSet);
	}
	
	//DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Toplam Zar Sonucu: %d"), TotalResult);
	
	return TotalResult;
}

int32 UDiceComponent::RollCustomDice(const TArray<FDiceSet>& DiceSets)
{
	int32 TotalResult = 0;
	
	for (const FDiceSet& DiceSet : DiceSets)
	{
		TotalResult += ExecuteRoll(DiceSet);
	}
	
	//DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Özel Zar Sonucu: %d"), TotalResult);
	
	return TotalResult;
}

int32 UDiceComponent::ExecuteRoll(const FDiceSet& DiceSet)
{
	int32 Result = 0;
	
	for (int32 i = 0; i < DiceSet.DiceCount; i++)
	{
		//1 ile DiceSides arasında rastgele bir sayı üret
		Result += FMath::RandRange(1, DiceSet.DiceSides);
	}
	
	Result += DiceSet.Modifier;
	
	return Result;
	
}

/**
// Called every frame
void UDiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
**/
