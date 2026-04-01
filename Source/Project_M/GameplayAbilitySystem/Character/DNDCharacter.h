// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Project_M/GameplayAbilitySystem/Components/InventoryComponent/DndInventoryComponent.h"
#include "DNDCharacter.generated.h"

USTRUCT(BlueprintType)
struct FDndClassInfo : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	// Sinif Adi (Örn: Fighter, Wizard)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	FText  ClassName;
	
	// Baslangic statlari
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	TMap<FGameplayAttribute, float> BaseAttributes;
	
	// Sinifa ozel yetenekler (Gameplay Ability classlari)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	FGameplayTagContainer StartingProficiencies;
	
	// Karakter yaratma ekraninda oyuncunun secebilecegi "Expertise" sayisi
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	int32 AllowedExpertiseCount;
	
	// Karakterin secebilecegi yetenek havuzu
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Class Info")
	FGameplayTagContainer ChoosableSkillPool;
	
	// Havuzdan kac tane yetenek secme hakki var
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	int32 AllowedProficiencyCount;
	
};

UCLASS()
class PROJECT_M_API ADNDCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADNDCharacter();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Abilities")
	class UDNDAttributeSet* AttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Abilities")
	void GrantAbility(TSubclassOf<class UGameplayAbility> AbilityClass);
	
	// Karakter Class DataTable Rowu
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DND|Character Setup")
	FDataTableRowHandle CharacterClassRow;
	
	// Oyuncunun secebilecegi Expertise sayisi
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DND|Character Setup")
	int32 AvailableExpertisePoints;
	
	// Oyuncunun secebilecegi Proficiency sayisi
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DND|Character Setup")
	int32 AvailableProficiencyPoints;
	
	// UI'in gosterecegi secilebilir yetenek havuzu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DND|Character Setup")
	FGameplayTagContainer AllowedSkillPool;
	
	// Verileri ASC'ye yazacak fonksiyon
	void InitializeCharacterClass();
	
	// UI'dan cagrilacak Expertise secme fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "DND|Class Setup")
	bool AssignExpertise(FGameplayTag TargetSkillTag);
	
	// UI'dan cagrilacak Proficiency secme fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "DND|Class Setup")
	bool AssignProficiency(FGameplayTag TargetSkillTag);
	
	// Envanter Componenti
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category= "DND|Components")
	class UDndInventoryComponent* DndInventoryComponent;

};
