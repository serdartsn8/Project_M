// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DndAbility_SkillCheck.generated.h"

UCLASS()
class PROJECT_M_API UDndAbility_SkillCheck : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDndAbility_SkillCheck();
	
	// Yetenek tetiklendiginde calisacak ilk fonksiyon
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	// Hangi Core Stat kullanilacak (Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DND|Skill Check")
	FGameplayAttribute TargetAttribute;
	
	// Hangi skill eklenecek
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DND|Skill Check", meta = (Categories = "Skill"))
	FGameplayTag TargetSkillTag;
	
	// Zorluk Derecesi (Difficulty Class)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "DND|Skill Check")
	int32 DifficultyClass = 10; // Default DC 10
	
};
