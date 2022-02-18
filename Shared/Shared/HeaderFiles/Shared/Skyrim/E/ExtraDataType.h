#pragma once

#include "Shared/PCH.h"



namespace Skyrim
{
	enum class ExtraDataType : std::uint32_t
	{
		kNone        = 0,
		kWorn        = 0x16,
		kWornLeft    = 0x17,
		kCharge      = 0x28,
		kEnchantment = 0x9B,
		kInteraction = 0xA9
	};
	static_assert(sizeof(ExtraDataType) == 0x4);
}
