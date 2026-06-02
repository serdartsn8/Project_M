// Fill out your copyright notice in the Description page of Project Settings.


#include "DndAbility_SkillCheck.h"
#include "Project_M/GameplayAbilitySystem/DiceLibrary/DndDiceLibrary.h"
#include "GameFramework/Actor.h"
#include "Project_M/GameplayAbilitySystem/Interfaces/InteractableInterface/DndInteractableInterface.h"

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
	
	// Bu yetenek bir EVENT ile mi tetiklendi
	if (TriggerEventData)
	{
		// Paketteki DC
		DifficultyClass = TriggerEventData->EventMagnitude;
		
		// Paketteki SKILLTAG 
		TargetSkillTag = TriggerEventData->EventTag;
		
		// Paketi kim gonderdi
		InteractionTarget = Cast<AActor>(const_cast<AActor*>(TriggerEventData->Instigator.Get()));	
		
		UE_LOG(LogTemp,Warning,TEXT("Payload Alindi! Istenen Yetenek: %s, DC: %d"), *TargetSkillTag.ToString(), DifficultyClass);
	}
	
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
	
	if (InteractionTarget && InteractionTarget->Implements<UDndInteractableInterface>())
	{
		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Zar Basarili! Objeye 'OnSuccess' mesaji gonderiliyor."));
			// Objenin Blueprint'indeki OnInteractionSuccess Event'ini tetikler
			IDndInteractableInterface::Execute_OnInteractionSuccess(InteractionTarget);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Zar Basarisiz! Objeye 'OnFailed' mesaji gonderiliyor."));
			// Objenin Blueprint'indeki OnInteractionFailed Event'ini tetikler
			IDndInteractableInterface::Execute_OnInteractionFailed(InteractionTarget);
		}
	}
	
	// Yetenek tamamlandi
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	
}
