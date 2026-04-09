// Fill out your copyright notice in the Description page of Project Settings.


#include "DNDCharacter.h"
#include "AbilitySystemComponent.h"
#include "Project_M/GameplayAbilitySystem/AttributeSet/DNDAttributeSet.h"

// Sets default values
ADNDCharacter::ADNDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Ability System Component'i olustur ve replikasyonu aktif et
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UDNDAttributeSet>(TEXT("AttributeSet"));
	
	// Envanter Component'i olustur
	DndInventoryComponent = CreateDefaultSubobject<UDndInventoryComponent>(TEXT("InventoryComponent"));

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
		
		AvailableProficiencyPoints = ClassInfo->AllowedProficiencyCount;
		AllowedSkillPool = ClassInfo->ChoosableSkillPool;
		
		UE_LOG(LogTemp, Warning,TEXT("Karakter sinifi basariyla yuklendi! Verilen Tag Sayisi: %d"), ClassInfo->StartingProficiencies.Num());
		
	}
	
}

bool ADNDCharacter::AssignExpertise(FGameplayTag TargetSkillTag)
{
	// Karakterin Expertise hakkı var mi?
	if (AvailableExpertisePoints <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Harcayacak Expertise puaniniz kalmadi!"));
		return false;
	}
	
	FString SkillName = TargetSkillTag.ToString();
	FGameplayTag ProficiencyTag = FGameplayTag::RequestGameplayTag(FName(*(SkillName + TEXT(".Proficiency"))), false);
	FGameplayTag ExpertiseTag = FGameplayTag::RequestGameplayTag((FName(*(SkillName + TEXT(".Expertise")))), false);
	
	// ASC var mi ve Tag'ler gecerli mi?
	if (!AbilitySystemComponent || !ProficiencyTag.IsValid() || !ExpertiseTag.IsValid())
	{
		return false;
	}
	
	// Karakterin zaten Expertise'i var mi?
	if (AbilitySystemComponent->HasMatchingGameplayTag(ExpertiseTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Bu yetenekte zaten Expertise'niz var!"));
		return false;
	}
	
	// Karakterin Proficiency'si var mi? Expertise eklemek icin proficiency on sart
	if (!AbilitySystemComponent->HasMatchingGameplayTag(ProficiencyTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Kural geregi, Expertise eklemek icin once Proficiency'niz olmalidir! %s yeteneginde Proficiency'niz yok."), *SkillName);
		return false;
	}
	
	// Expertise'i ekle ve hakkı azalt
	AbilitySystemComponent->AddLooseGameplayTag(ExpertiseTag);
	AvailableExpertisePoints--;
	
	UE_LOG(LogTemp, Warning, TEXT("BASARILI! %s yetenegi icin uzmanlik eklendi. Kalan puan %d"), *SkillName, AvailableExpertisePoints);
	return true;
	
}

bool ADNDCharacter::AssignProficiency(FGameplayTag TargetSkillTag)
{
	if (AvailableProficiencyPoints <= 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Harcayacak Proficiency bonusu kalmadi!"))
		return false;
	}
	
	// Secilmek istenen skill bu classin havuzunda var mi?
	if (!AllowedSkillPool.HasTagExact(TargetSkillTag))
	{
		UE_LOG(LogTemp,Warning,TEXT("Kural Ihlali: %s yetenegi bu karakter sinifinin secilebilir havuzunda yok!"), *TargetSkillTag.ToString());
		return false;
	}
	
	// Tag'i olustur
	FString SkillName = TargetSkillTag.ToString();
	FGameplayTag ProficiencyTag = FGameplayTag::RequestGameplayTag(FName(*(SkillName + TEXT(".Proficiency"))), false);
	
	if (!AbilitySystemComponent || !ProficiencyTag.IsValid())
	{
		return false;
	}
	
	// Zaten proficiency var mi?
	if (AbilitySystemComponent->HasMatchingGameplayTag(ProficiencyTag))
	{
		UE_LOG(LogTemp,Warning,TEXT("Bub yetenekte zaten Proficiency'niz var!"));
		return false;
	}
	
	// Proficiency'i ekle ve hakkı azalt
	AbilitySystemComponent->AddLooseGameplayTag(ProficiencyTag);
	AvailableProficiencyPoints--;
	
	UE_LOG(LogTemp,Warning,TEXT("BASARILI! %s yetenegi icin proficiency eklendi. Kalan puan %d"), *SkillName, AvailableProficiencyPoints);
	return true;
	
}

void ADNDCharacter::TraceForInteractables()
{
	FVector StartLocation = GetPawnViewLocation();
	FVector EndLocation = StartLocation + (GetViewRotation().Vector() * InteractionRange);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation, ECC_Visibility, QueryParams);
	
	if (bHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor->Implements<UDndInteractableInterface>())
		{
			if (FocusedInteractableActor != HitActor)
			{
				FocusedInteractableActor = HitActor;
				
				// UI icin delegate yapilacak
				UE_LOG(LogTemp, Warning, TEXT("Etkilesimli bir objeye bakiyorsun: %s"), *HitActor->GetName());
			}
			return;
		}
	}
	
	if (FocusedInteractableActor)
	{
		FocusedInteractableActor = nullptr;
		// UI icin delegate yapilacak
		UE_LOG(LogTemp,Warning,TEXT("Objeden gozunu cektin!"));
	}
	
	
}

void ADNDCharacter::InteractKeyPressed()
{
	if (FocusedInteractableActor)
	{
		IDndInteractableInterface::Execute_Interact(FocusedInteractableActor,this);
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Etkilesime girilecek bir sey yok."));
	}
}
