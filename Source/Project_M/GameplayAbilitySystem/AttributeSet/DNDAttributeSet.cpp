// Fill out your copyright notice in the Description page of Project Settings.


#include "DNDAttributeSet.h"

UDNDAttributeSet::UDNDAttributeSet()
{
	InitStrenght(10.f);
	InitDexterity(10.f);
	InitConstitution(10.f);
	InitIntelligence(10.f);
	InitWisdom(10.f);
	InitCharisma(10.f);
	InitArmorClass(10.f);
}

void UDNDAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Strenght, OldStrength);
}

void UDNDAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Dexterity, OldDexterity);
}

void UDNDAttributeSet::OnRep_Constitution(const FGameplayAttributeData& OldConstitution)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Constitution, OldConstitution);
}

void UDNDAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Intelligence, OldIntelligence);
}

void UDNDAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Wisdom, OldWisdom);
}

void UDNDAttributeSet::OnRep_Charisma(const FGameplayAttributeData& OldCharisma)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, Charisma, OldCharisma);
}

void UDNDAttributeSet::OnRep_ArmorClass(const FGameplayAttributeData& OldArmorClass)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDNDAttributeSet, ArmorClass, OldArmorClass);
}
