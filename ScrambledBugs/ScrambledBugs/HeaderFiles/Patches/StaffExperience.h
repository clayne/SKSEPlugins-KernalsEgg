#pragma once

#include "PCH.h"

#include "Shared/Skyrim/E/EnchantmentItem.h"
#include "Shared/Skyrim/M/MagicItem.h"



namespace ScrambledBugs::Patches
{
	class StaffExperience
	{
	public:
		static bool Patch();

	private:
		static bool GetSkillUsageData(Skyrim::EnchantmentItem* enchantment, Skyrim::MagicItem::SkillUsageData& skillUsageData);

		static decltype(&StaffExperience::GetSkillUsageData) getSkillUsageDataEnchantmentItem_;
		static decltype(&StaffExperience::GetSkillUsageData) getSkillUsageDataSpellItem_;
	};
}
