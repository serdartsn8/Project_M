// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DNDAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECT_M_API UDNDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDNDAttributeSet();
	
	// Base Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Strenght;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Strenght)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Dexterity)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Constitution)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Intelligence)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Wisdom)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Core")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, Charisma)
	
	// Combat Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(UDNDAttributeSet, ArmorClass)
	
	// Replication
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	
	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);
	
	UFUNCTION()
	virtual void OnRep_Constitution(const FGameplayAttributeData& OldConstitution);
	
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	
	UFUNCTION()
	virtual void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom);
	
	UFUNCTION()
	virtual void OnRep_Charisma(const FGameplayAttributeData& OldCharisma);
	
	UFUNCTION()
	virtual void OnRep_ArmorClass(const FGameplayAttributeData& OldArmorClass);
	
};
