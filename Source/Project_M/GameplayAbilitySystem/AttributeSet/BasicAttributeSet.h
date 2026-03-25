// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"


UCLASS()
class PROJECT_M_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UBasicAttributeSet();
	

	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
