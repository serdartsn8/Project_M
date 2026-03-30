// Fill out your copyright notice in the Description page of Project Settings.


#include "DndDiceLibrary.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "Math/UnrealMathUtility.h"

bool UDndDiceLibrary::RollSkillCheck(AActor* TargetActor, FGameplayAttribute CoreAttribute, FGameplayTag SkillTag, int32 DifficultyClass, int32& OutNaturalRoll, int32& OutTotalRoll)
{
	// Karakterin Ability System Component'i var mi?
	if (!TargetActor) return false;
	
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!ASC) return false;
	
	// GAS'tan Core Attribute değerini al (Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma)
	float CoreStatValue = ASC->GetNumericAttribute(CoreAttribute);
	
	// DND modifier formulu (AbilityScore-10)/2
	int32 AbilityModifier = FMath::FloorToInt((CoreStatValue - 10.0f) / 2.0f);
	
	// Proficiency ve Expertise kontrolu (Demo icin PB = +2 sabit)
	int32 ProficiencyBonus = 2;
	int32 TotalSkillBonus = AbilityModifier;
	
	
	if (SkillTag.IsValid())
	{
		FGameplayTag ProficiencyTag = FGameplayTag::RequestGameplayTag(FName(*(SkillTag.ToString() + TEXT(".Proficiency"))), false);
		FGameplayTag ExpertiseTag = FGameplayTag::RequestGameplayTag(FName(*(SkillTag.ToString() + TEXT(".Expertise"))), false);

		if (ProficiencyTag.IsValid() && ASC->HasMatchingGameplayTag(ProficiencyTag))
			TotalSkillBonus += ProficiencyBonus;
		else if (ExpertiseTag.IsValid() && ASC->HasMatchingGameplayTag(ExpertiseTag))
			TotalSkillBonus += (ProficiencyBonus * 2);
	}
	else
	{
		// Attribute ismini otomatik al (Örn: "Dexterity") ve Tag'i oluştur: "Save.Dexterity.Proficiency"
		FString SaveTagName = FString::Printf(TEXT("Save.%s.Proficiency"), *CoreAttribute.GetName());
		FGameplayTag SaveProfTag = FGameplayTag::RequestGameplayTag(FName(*SaveTagName), false);

		// Karakterin bu kurtarma zarına uzmanlığı var mı?
		if (SaveProfTag.IsValid() && ASC->HasMatchingGameplayTag(SaveProfTag))
		{
			TotalSkillBonus += ProficiencyBonus;
		}
	}
	
	// Zar At
	OutNaturalRoll = FMath::RandRange(1,20);
	
	if (OutNaturalRoll == 20)
	{
		OutTotalRoll = OutNaturalRoll + TotalSkillBonus;
		return true; // Natural 20 her zaman basarilidir
	}
	if (OutNaturalRoll == 1)
	{
		OutTotalRoll = OutNaturalRoll + TotalSkillBonus;
		return false; // Natural 1 her zaman basarisizdir
	}
	
	// Sonucu hesapla ve dondur
	OutTotalRoll = OutNaturalRoll + TotalSkillBonus;
	return OutTotalRoll >= DifficultyClass;
	
}


