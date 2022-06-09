#pragma once

#include "Shared/PCH.h"

#include "Shared/Skyrim/T/TESObjectACTI.h"
#include "Shared/Skyrim/T/TESProduceForm.h"



namespace Skyrim
{
	class TESFlora :
		public TESObjectACTI, // 0
		public TESProduceForm // C8
	{
	public:
		// Override
		virtual ~TESFlora() override; // 0

		// Override (TESObjectACTI)
		virtual void Unknown6(TESForm*) override;                                                                                                     // 6
		virtual void Unknown13(TESForm*) override;                                                                                                    // 13
		virtual bool Activate(TESObjectREFR* target, TESObjectREFR* activator, bool deferred, TESBoundObject* item, std::int32_t itemCount) override; // 37
		virtual void Unknown4C(TESBoundObject*) override;                                                                                             // 4C
		virtual void Unknown4D(TESBoundObject*) override;                                                                                             // 4D
	};
	static_assert(sizeof(TESFlora) == 0xE8);
}
