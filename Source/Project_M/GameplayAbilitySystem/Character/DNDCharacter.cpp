// Fill out your copyright notice in the Description page of Project Settings.


#include "DNDCharacter.h"
#include "AbilitySystemComponent.h"
#include "Project_M/GameplayAbilitySystem/Attribute/DNDAttributeSet.h"

// Sets default values
ADNDCharacter::ADNDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	AttributeSet = CreateDefaultSubobject<UDNDAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ADNDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

