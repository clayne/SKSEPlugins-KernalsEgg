#pragma once

#include "PrecompiledHeader.h"



namespace ScrambledBugs::Fixes
{
	class PowerCooldowns
	{
	public:
		static void Fix(bool& powerCooldowns);

	private:
		static void SaveCastPowerItems(Skyrim::Actor* actor, Skyrim::BGSSaveFormBuffer* saveFormBuffer);
	};
}
