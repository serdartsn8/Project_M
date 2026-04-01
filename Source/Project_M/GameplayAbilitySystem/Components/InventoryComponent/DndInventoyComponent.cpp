#include "DndInventoryComponent.h" 

UDndInventoryComponent::UDndInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDndInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UDndInventoryComponent::AddItem(UDndItemData* ItemToADD)
{
	if (!ItemToADD)
	{
		UE_LOG(LogTemp,Warning, TEXT("Eklenmeye calisilan esya gecersiz!"));
		return false;
	}
	
	if (InventoryItems.Num() >= MaxCapacity)
	{
		UE_LOG(LogTemp,Warning, TEXT("Envanter dolu! %s eklenemedi."), *ItemToADD->ItemName.ToString());
		return false;
	}
	
	InventoryItems.Add(ItemToADD);
	UE_LOG(LogTemp,Warning,TEXT("%s envantere eklendi. Simdiki kapasite: %d/%d"), *ItemToADD->ItemName.ToString(), InventoryItems.Num(), MaxCapacity);
	OnInventoryUpdated.Broadcast();
	return true;
	
}

bool UDndInventoryComponent::RemoveItem(UDndItemData* ItemToRemove)
{
	if (!ItemToRemove)
	{
		return false;
	}
	
	int32 RemovedCount = InventoryItems.RemoveSingle(ItemToRemove);
	
	if (RemovedCount > 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s envanterden kaldirildi. Simdiki kapasite: %d/%d"), *ItemToRemove->ItemName.ToString(), InventoryItems.Num(), MaxCapacity);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	
	return false;
	
}

bool UDndInventoryComponent::HasItem(UDndItemData* ItemToCheck) const
{
	if (!ItemToCheck)
	{
		return false;
	}
	
	return InventoryItems.Contains(ItemToCheck);
	
}