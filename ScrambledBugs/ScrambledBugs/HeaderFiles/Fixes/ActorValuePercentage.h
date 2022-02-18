#pragma once

#include "PCH.h"

#include "Shared/Skyrim/A/Actor.h"
#include "Shared/Skyrim/A/ActorValue.h"
#include "Shared/Utility/Enumeration.h"



namespace ScrambledBugs::Fixes
{
	class ActorValuePercentage
	{
	public:
		static bool Fix();

	private:
		static float GetActorValuePercentage(Skyrim::Actor* actor, Utility::Enumeration<Skyrim::ActorValue, std::uint32_t> actorValue);
		static float GetHealthPercentage(Skyrim::Actor* actor);
		static float GetStaminaPercentage(Skyrim::Actor* actor);
	};
}
