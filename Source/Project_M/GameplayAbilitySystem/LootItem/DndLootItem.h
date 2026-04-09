// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_M/GameplayAbilitySystem/Interfaces/InteractableInterface/DndInteractableInterface.h"
#include "Project_M/GameplayAbilitySystem/Data/DataAssets/DndItemData.h"
#include "DndLootItem.generated.h"

UCLASS()
class PROJECT_M_API ADndLootItem : public AActor, public IDndInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADndLootItem();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category= "Components")
	class UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Loot",meta=(ExposeOnSpawn=true))
	UDndItemData* ItemData;
	
	// Interface fonksiyonlari
	virtual void Interact_Implementation(class ADNDCharacter* InteractorCharacter) override;
	virtual FText GetInteractText_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
