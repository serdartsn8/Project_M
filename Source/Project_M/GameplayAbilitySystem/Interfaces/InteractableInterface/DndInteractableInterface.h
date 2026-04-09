// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DndInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDndInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_M_API IDndInteractableInterface
{
	GENERATED_BODY()

public:
	// Interact Function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Category= "Interaction")
	void Interact(class ADNDCharacter* InteractorCharacter);
	
	// UI
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interaction")
	FText GetInteractText();
	
};
