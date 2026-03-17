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
	// ABILITIES	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Strength)
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Dexterity)
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Constitution)
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Constitution)
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Intelligence)
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Wisdom)
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Wisdom)
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes", ReplicatedUsing = OnRep_Charisma)
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Charisma)
	
	UBasicAttributeSet();
	
	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Strength, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Dexterity(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Dexterity, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Constitution(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Constitution, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Intelligence, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Wisdom(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Wisdom, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Charisma(FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Charisma, OldValue);
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
