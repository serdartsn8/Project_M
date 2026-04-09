// Fill out your copyright notice in the Description page of Project Settings.


#include "DndLootItem.h"

#include "Project_M/GameplayAbilitySystem/Character/DNDCharacter.h"
#include "Project_M/GameplayAbilitySystem/Components/InventoryComponent/DndInventoryComponent.h"


ADndLootItem::ADndLootItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
	ItemMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
}

void ADndLootItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADndLootItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADndLootItem::Interact_Implementation(class ADNDCharacter* InteractorCharacter)
{
	
	UE_LOG(LogTemp, Warning, TEXT("---- ETKILESHIM TETIKLENDI ----"));
	
	// Karakter ve esya verisi var mi
	if (!ItemData)
	{
		UE_LOG(LogTemp, Error, TEXT("HATA: Bu objenin ItemData'si BOS! Lutfen Blueprint icindeki veya dunyadaki objeye tiklayip bir Data Asset secin."));
		return;
	}	
	
	if (!InteractorCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("HATA: InteractorCharacter gecersiz (NULL)!"));
		return;
	}
	
	// Inventory Componenti bul
	UDndInventoryComponent* Inventory = InteractorCharacter->DndInventoryComponent;
	
	if (!Inventory)
	{
		UE_LOG(LogTemp, Error, TEXT("HATA: Karakterin ustunde InventoryComponent bulunamadi!"));
		return;
	}
	
	bool bAdded = Inventory->AddItem(ItemData);
		
	if (bAdded)
	{
		UE_LOG(LogTemp, Warning, TEXT("BASARILI! %s envantere eklendi ve dunyadan siliniyor."), *ItemData->ItemName.ToString());
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HATA: AddItem fonksiyonu FALSE dondu! Envanter kapasitesi (%d) dolmus olabilir."), Inventory->MaxCapacity);
	}
	
}

FText ADndLootItem::GetInteractText_Implementation()
{
	if (ItemData)
	{
		return FText::Format(NSLOCTEXT("Interaction","TakeItem","Al: {0}"), ItemData->ItemName);
	}
	return FText::FromString(TEXT("Al: Bilinmeyen Esya"));
}
