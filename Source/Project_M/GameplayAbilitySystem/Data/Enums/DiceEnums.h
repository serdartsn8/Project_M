#include "CoreMinimal.h"
#include "DiceEnums.generated.h"

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	Strength UMETA(DisplayName = "Strength"),
	Dexterity UMETA(DisplayName = "Dexterity"),
	Constitution UMETA(DisplayName = "Constitution"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Wisdom UMETA(DisplayName = "Wisdom"),
	Charisma UMETA(DisplayName = "Charisma")
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Acrobatics UMETA(DisplayName = "Acrobatics"),  // Dexterity
	AnimalHandling UMETA(DisplayName = "Animal Handling"),  // Wisdom
	Arcana UMETA(DisplayName = "Arcana"),  // Intelligence
	Athletics UMETA(DisplayName = "Athletics"),  // Strength
	Deception UMETA(DisplayName = "Deception"),  // Charisma
	History UMETA(DisplayName = "History"),  // Intelligence
	Insight UMETA(DisplayName = "Insight"),  // Wisdom
	Intimidation UMETA(DisplayName = "Intimidation"),  // Charisma
	Investigation UMETA(DisplayName = "Investigation"),  // Intelligence
	Medicine UMETA(DisplayName = "Medicine"),  // Wisdom
	Nature UMETA(DisplayName = "Nature"),  // Intelligence
	Perception UMETA(DisplayName = "Perception"),  // Wisdom
	Performance UMETA(DisplayName = "Performance"),  // Charisma
	Persuasion UMETA(DisplayName = "Persuasion"),  // Charisma
	Religion UMETA(DisplayName = "Religion"),  // Intelligence
	SleightOfHand UMETA(DisplayName = "Sleight of Hand"),  // Dexterity
	Stealth UMETA(DisplayName = "Stealth"),  // Dexterity
	Survival UMETA(DisplayName = "Survival")  // Wisdom
};