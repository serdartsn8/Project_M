// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_M/GameplayAbilitySystem/Data/DataAssets/DndItemData.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"
#include "DndInventoryComponent.generated.h"

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

USTRUCT(BlueprintType)
struct FEquippedItemData
{
	GENERATED_BODY()

	// Kusanilan Esya
	UPROPERTY()
	UDndItemData* Item = nullptr;
	
	// GAS'in verdigi ability handle'lari (Eger esya yetenek veriyorsa)
	TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;
	
	// GAS'in verdigi effect handle'lari (Eger esya effect veriyorsa)
	TArray<FActiveGameplayEffectHandle> GrantedEffectHandles;
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_M_API UDndInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDndInventoryComponent();
	
	// Envanterdeki Esya Listesi
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category= "Inventory")
	TArray<UDndItemData*> InventoryItems;

	// Envanterin alabilecegi maximum esya sayisi
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	int32 MaxCapacity = 20;
	
	// Esya eklendiginde/kaldirildiginda tetiklenecek delegate
	UPROPERTY(BlueprintAssignable, Category= "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	
	// Item Ekleme
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UDndItemData* ItemToADD);
	
	// Item Kaldirma
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UDndItemData* ItemToRemove);
	
	// Envanterde belirli bir item var mi?
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UDndItemData* ItemToCheck) const;
	
	// Ekipman Slotlari ve Kusanilan Esya Bilgisi
	UPROPERTY(VisibleAnywhere, Category= "Inventory|Equipment")
	TMap<EEquipmentSlot, FEquippedItemData> EquippedItems;
	
	// Esyayi kusan ve yetenekleri/statlari karaktere ver
	UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
	bool EquipItem(UDndItemData* ItemToEquip);
	
	// Esyayi kuşanmayı kaldır ve verilen yetenekleri/statları geri al
	UFUNCTION(BlueprintCallable, Category = "Inventory|Equipment")
	bool UnequipItem(EEquipmentSlot SlotToUnequip);
	
protected:
	virtual void BeginPlay() override;


};
