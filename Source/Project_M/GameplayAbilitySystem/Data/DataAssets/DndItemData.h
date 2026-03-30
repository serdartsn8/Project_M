// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DndItemData.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Armor,
	Consumable,
	QuestItem,
	Misc
};

UCLASS()
class PROJECT_M_API UDndItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// Temel Bilesenler
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | Base")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | Base")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | Base")
	UTexture2D* ItemIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | Base")
	EItemType ItemType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | Base")
	UStaticMesh* WorldMesh;
	
	// GAS Entegrasyonu
	// Item'in verecegi yetenek
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | GAS")
	TArray<TSubclassOf<class UGameplayAbility>> GrantedAbility;
	
	// Kusanildiginda veya kullanildiginda kullanacagi effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | GAS")
	TArray<TSubclassOf<class UGameplayEffect>> GrantedEffect;
	
	// Item'in Tagleri
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item | GAS")
	FGameplayTagContainer ItemTags;
	
	
};
