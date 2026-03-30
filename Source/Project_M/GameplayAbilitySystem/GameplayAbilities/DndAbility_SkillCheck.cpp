// Fill out your copyright notice in the Description page of Project Settings.


#include "DndAbility_SkillCheck.h"
#include "Project_M/GameplayAbilitySystem/DiceLibrary/DndDiceLibrary.h"
#include "GameFramework/Actor.h"

UDndAbility_SkillCheck::UDndAbility_SkillCheck()
{
	// Yetenek her tetiklendiginde Instance olmasini saglar
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDndAbility_SkillCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// Karakter referansi gecerli mi?
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true,true);
		return;
	}
	
	AActor* Avatar = ActorInfo->AvatarActor.Get();
	
	// DndDiceLibrary'nin dondurecegi veriler icin degiskenler
	int32 NaturalRoll = 0;
	int32 TotalRoll = 0;
	
	// DndDiceLibrary'yi cagir
	bool bSuccess = UDndDiceLibrary::RollSkillCheck(Avatar, TargetAttribute, TargetSkillTag, DifficultyClass, NaturalRoll, TotalRoll);
	
	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Basarili! Natural Roll: %d | Total: %d | DC: %d"), NaturalRoll, TotalRoll, DifficultyClass);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Basarisiz! Natural Roll: %d | Total: %d | DC: %d"), NaturalRoll, TotalRoll, DifficultyClass);
	}
	
	// Yetenek tamamlandi
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	
}
