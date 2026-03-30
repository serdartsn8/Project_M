// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project_M/GameplayAbilitySystem/AttributeSet/DNDAttributeSet.h"
#include "GameplayTagContainer.h"
#include "DndDiceLibrary.generated.h"


UCLASS()
class PROJECT_M_API UDndDiceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/*
		D&D 5e kurallarına göre Skill Check zarı atar.
	 * @param TargetActor Zar atacak karakter (ASC'ye sahip olmalı)
	 * @param CoreAttribute Zarın bağlı olduğu ana stat (Örn: Strength)
	 * @param SkillTag Kontrol edilecek yetenek (Örn: Skill.Athletics)
	 * @param DifficultyClass (DC) Geçilmesi gereken zorluk derecesi
	 * @param OutNaturalRoll Atılan ham d20 zarı (1-20)
	 * @param OutTotalRoll Zar + Modifier + Proficiency toplamı
	 * @return Zar DC'ye eşit veya büyükse true döner.
 */
	UFUNCTION(BlueprintCallable, Category = "Dnd|Dice System")
	static bool RollSkillCheck(AActor* TargetActor, FGameplayAttribute CoreAttribute, FGameplayTag SkillTag, int32 DifficultyClass, int32& OutNaturalRoll, int32& OutTotalRoll);
	
};
