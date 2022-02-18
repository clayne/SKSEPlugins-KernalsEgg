#include "PCH.h"

#include "Patches/PowerAttackStamina.h"

#include "Addresses.h"
#include "Patterns.h"
#include "Shared/Utility/Assembly.h"
#include "Shared/Utility/Memory.h"
#include "Shared/Utility/Trampoline.h"



namespace ScrambledBugs::Patches
{
	bool PowerAttackStamina::Patch()
	{
		if (!Patterns::Patches::PowerAttackStamina::GetAttackStaminaActor() ||
			!Patterns::Patches::PowerAttackStamina::GetAttackStaminaPlayerCharacter() ||
			!Patterns::Patches::PowerAttackStamina::HasStaminaActor() ||
			!Patterns::Patches::PowerAttackStamina::HasStaminaPlayerCharacter())
		{
			return false;
		}

		Utility::Memory::SafeWrite(Addresses::Patches::PowerAttackStamina::HasStaminaActor, Utility::Assembly::NoOperation2);
		Utility::Memory::SafeWrite(Addresses::Patches::PowerAttackStamina::HasStaminaPlayerCharacter, Utility::Assembly::NoOperation2);

		PowerAttackStamina::getAttackStaminaActor_ = reinterpret_cast<decltype(PowerAttackStamina::getAttackStaminaActor_)>(Utility::Memory::ReadRelativeCall(Addresses::Patches::PowerAttackStamina::GetAttackStaminaActor));
		Utility::Trampoline::GetSingleton().RelativeCall(Addresses::Patches::PowerAttackStamina::GetAttackStaminaActor, reinterpret_cast<std::uintptr_t>(std::addressof(PowerAttackStamina::HasAttackStaminaActor)));

		PowerAttackStamina::getAttackStaminaPlayerCharacter_ = reinterpret_cast<decltype(PowerAttackStamina::getAttackStaminaPlayerCharacter_)>(Utility::Memory::ReadRelativeCall(Addresses::Patches::PowerAttackStamina::GetAttackStaminaPlayerCharacter));
		Utility::Trampoline::GetSingleton().RelativeCall(Addresses::Patches::PowerAttackStamina::GetAttackStaminaPlayerCharacter, reinterpret_cast<std::uintptr_t>(std::addressof(PowerAttackStamina::HasAttackStaminaPlayerCharacter)));

		return true;
	}

	float PowerAttackStamina::HasAttackStaminaActor(Skyrim::ActorValueOwner* actorValueOwner, Skyrim::BGSAttackData* attackData)
	{
		auto attackStamina = PowerAttackStamina::getAttackStaminaActor_(actorValueOwner, attackData);

		if (attackStamina <= 0.0F)
		{
			return attackStamina; // true
		}

		auto stamina = actorValueOwner->GetActorValue(Skyrim::ActorValue::kStamina);

		return stamina >= attackStamina ? 0.0F : attackStamina; // true/false
	}

	float PowerAttackStamina::HasAttackStaminaPlayerCharacter(Skyrim::ActorValueOwner* actorValueOwner, Skyrim::BGSAttackData* attackData)
	{
		auto attackStamina = PowerAttackStamina::getAttackStaminaPlayerCharacter_(actorValueOwner, attackData);

		if (attackStamina <= 0.0F)
		{
			return attackStamina; // true
		}

		auto stamina = actorValueOwner->GetActorValue(Skyrim::ActorValue::kStamina);

		return stamina >= attackStamina ? 0.0F : attackStamina; // true/false
	}

	decltype(&PowerAttackStamina::HasAttackStaminaActor)           PowerAttackStamina::getAttackStaminaActor_;
	decltype(&PowerAttackStamina::HasAttackStaminaPlayerCharacter) PowerAttackStamina::getAttackStaminaPlayerCharacter_;
}
