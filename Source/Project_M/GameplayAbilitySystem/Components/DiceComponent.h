// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DiceComponent.generated.h"

USTRUCT(BlueprintType)
struct FDiceSet
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 DiceCount = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 DiceSides = 20;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 Modifier = 0; 
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_M_API UDiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDiceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Temel zar ayarlari
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice|Base")
	FDiceSet BaseDice;
	
	//Bonus zar setleri, örneğin yetenekler veya eşyalar tarafından sağlanan ek zarlar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice|Modularity")
	TArray<FDiceSet> BonusDiceSets;
	
	//Toplam sonucu donduren fonksiyon
	UFUNCTION(BlueprintCallable, Category = "Dice")
	int32 RollDice();
	
	//Özel zar setleri ile atma fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Dice")
	int32 RollCustomDice(const TArray<FDiceSet>& DiceSets);
	
private:
	//Tekil zar atma mantigi
	int32 ExecuteRoll(const FDiceSet& DiceSet);

		
};