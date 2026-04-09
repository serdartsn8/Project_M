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
			
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			if (EffectCDO->DurationPolicy == EGameplayEffectDurationType::Instant)
			{
				// Ekrana ve Log'a kırmızı bir hata basıp onu uyaralım!
				UE_LOG(LogTemp, Error, TEXT("DIKKAT: %s esyasina Instant (Kalici) bir efekt baglanmis! Ekipman efektleri her zaman INFINITE olmalidir!"), *ItemToEquip->ItemName.ToString());
			}
			
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddInstigator(GetOwner(), GetOwner());
			
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass,1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				// Effecti uygula ve handle'ini kaydet
				FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				NewEquippedItemData.GrantedEffectHandles.Add(ActiveHandle);
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
	/*
	for (FActiveGameplayEffectHandle EffectHandle : DataToRemove.GrantedEffectHandles)
	{
		if (EffectHandle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(EffectHandle);
		}
	}
	*/
	
	// 2. Efektleri Kaldır (Statları geri al) - DEBUG VERSİYONU
	int32 EfektSayisi = DataToRemove.GrantedEffectHandles.Num();
	UE_LOG(LogTemp, Warning, TEXT("---- UNEQUIP DEBUG BASLIYOR ----"));
	UE_LOG(LogTemp, Warning, TEXT("Bu esyaya ait silinmesi gereken Efekt Makbuzu Sayisi: %d"), EfektSayisi);

	for (FActiveGameplayEffectHandle EffectHandle : DataToRemove.GrantedEffectHandles)
	{
		if (EffectHandle.IsValid())
		{
			// Efekti silmeyi dene ve sonucu bir bool değişkene al
			bool bWasRemoved = ASC->RemoveActiveGameplayEffect(EffectHandle);
            
			if (bWasRemoved)
			{
				UE_LOG(LogTemp, Warning, TEXT("BASARILI: Makbuz GAS sistemine verildi ve efekt silindi!"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("KRITIK HATA: Makbuz gecerli ama GAS bu efekti silmeyi REDDETTI! (Authority veya baska bir sorun olabilir)"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("HATA: Elimizdeki Makbuz (Handle) gecersiz (Invalid) olmus. Efekt zaten ölmüş olabilir."));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("---- UNEQUIP DEBUG BITTI ----"));
	
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
	EquippedItems.Remove(SlotToUnequip);
	UE_LOG(LogTemp,Warning,TEXT("%s %s slotundan kaldirildi!"), *ItemName, *UEnum::GetValueAsString(SlotToUnequip));
	return true;
}
