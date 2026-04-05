#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
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

bool UDndInventoryComponent::EquipItem(UDndItemData* ItemToEquip)
{
	if (!ItemToEquip || ItemToEquip->EquipmentSlot == EEquipmentSlot::None)
	{
		return false;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (!ASC)
	{
		return  false;
	}
	
	if (EquippedItems.Contains(ItemToEquip->EquipmentSlot))
	{
		UnequipItem(ItemToEquip->EquipmentSlot);
	}
	
	FEquippedItemData NewEquippedItemData;
	NewEquippedItemData.Item = ItemToEquip;
	
	for (TSubclassOf<UGameplayEffect> EffectClass : ItemToEquip->GrantedEffect)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddInstigator(GetOwner(), GetOwner());
			
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass,1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				// Effecti uygula ve handle'ini kaydet
				FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
	
	for (TSubclassOf<UGameplayAbility> AbilityClass : ItemToEquip->GrantedAbility)
	{
		if (AbilityClass)
		{
			// Yeteneği karaktere tanımla ve handle'ini kaydet
			FGameplayAbilitySpecHandle AbilityHandle = ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
			NewEquippedItemData.GrantedAbilityHandles.Add(AbilityHandle);
		}
	}
	
	// Esyayi MAP'e kaydet
	EquippedItems.Add(ItemToEquip->EquipmentSlot, NewEquippedItemData);
	UE_LOG(LogTemp,Warning,TEXT("%s %s slotuna kusanildi!"),*ItemToEquip->ItemName.ToString(), *UEnum::GetValueAsString(ItemToEquip->EquipmentSlot));
	return true;
	
}

bool UDndInventoryComponent::UnequipItem(EEquipmentSlot SlotToUnequip)
{
	if (!EquippedItems.Contains(SlotToUnequip))
	{
		return false;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (!ASC)
	{
		return false;
	}
	
	// Kusanilmis esyanin verisini cek
	FEquippedItemData& DataToRemove = EquippedItems[SlotToUnequip];
	
	// Verilen effectleri kaldir
	for (FActiveGameplayEffectHandle EffectHandle : DataToRemove.GrantedEffectHandles)
	{
		if (EffectHandle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(EffectHandle);
		}
	}
	
	// Verilen yetenekleri kaldir
	for (FGameplayAbilitySpecHandle AbilityHandle : DataToRemove.GrantedAbilityHandles)
	{
		if (AbilityHandle.IsValid())
		{
			ASC->ClearAbility(AbilityHandle);
		}
	}
	
	// Esyayi MAP'ten kaldir
	FString ItemName = DataToRemove.Item ? DataToRemove.Item->ItemName.ToString() : TEXT("Esya");
	UE_LOG(LogTemp,Warning,TEXT("%s %s slotundan kaldirildi!"), *ItemName, *UEnum::GetValueAsString(SlotToUnequip));
	return true;
}
