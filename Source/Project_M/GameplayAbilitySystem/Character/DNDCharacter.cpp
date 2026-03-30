// Fill out your copyright notice in the Description page of Project Settings.


#include "DNDCharacter.h"
#include "AbilitySystemComponent.h"
#include "Project_M/GameplayAbilitySystem/AttributeSet/DNDAttributeSet.h"

// Sets default values
ADNDCharacter::ADNDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UDNDAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ADNDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeCharacterClass();
	
}

// Called every frame
void ADNDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADNDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ADNDCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADNDCharacter::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass)
{
	if (AbilitySystemComponent && AbilityClass)
	{
		// Yeteneği karaktere tanımla (Level 1 olarak)
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
	}
}

void ADNDCharacter::InitializeCharacterClass()
{
	// ASC var mi ve DataTable Row'u secilmis mi?
	if (!AbilitySystemComponent || CharacterClassRow.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("ASC yok veya Data Table satiri secilmedi!"));
		return;
	}
	
	// Row'u oku
	FDndClassInfo* ClassInfo = CharacterClassRow.GetRow<FDndClassInfo>(TEXT("Character Initialization"));
	
	if (ClassInfo)
	{
		// Statlari ASC'ye yaz
		for (const TTuple<FGameplayAttribute, float>& Pair : ClassInfo->BaseAttributes)
		{
			AbilitySystemComponent->SetNumericAttributeBase(Pair.Key, Pair.Value);
		}
		
		// Proficiency'leri karaktere kalici olarak ekle
		AbilitySystemComponent->AddLooseGameplayTags(ClassInfo->StartingProficiencies);
		
		// Expertise hakkini kaydet
		AvailableExpertisePoints = ClassInfo->AllowedExpertiseCount;
		
		UE_LOG(LogTemp, Warning,TEXT("Karakter sinifi basariyla yuklendi! Verilen Tag Sayisi: %d"), ClassInfo->StartingProficiencies.Num());
		
	}
	
}

