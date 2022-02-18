#pragma once

#include "Shared/PCH.h"



namespace Skyrim
{
	enum class FormType
	{
		kNone        = 0,
		kEnchantment = 0x15,
		kScroll      = 0x17,
		kArmor       = 0x1A,
		kContainer   = 0x1C,
		kStatic      = 0x22,
		kTree        = 0x26,
		kFlora       = 0x27,
		kFurniture   = 0x28,
		kWeapon      = 0x29,
		kNPC         = 0x2B,
		kCell        = 0x3C,
		kActor       = 0x3E,
		kTotal       = 0x8A
	};
}
