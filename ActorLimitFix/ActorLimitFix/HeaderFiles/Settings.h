#pragma once

#include "PCH.h"

#include <nlohmann/json.hpp>



namespace ActorLimitFix
{
	using json = nlohmann::json;

	class Settings
	{
	public:
		class Fixes
		{
		public:
			void Deserialize(const json& fixes);
			json Serialize() const;

			std::uint32_t morphLimit{ 0x80 };
			std::uint32_t moverLimit{ 0x100 };
			bool          replaceStaticArray{ true };
		};

		Settings()                = delete;
		Settings(const Settings&) = delete;
		Settings(Settings&&)      = delete;

		~Settings() = default;

		Settings& operator=(const Settings&) = delete;
		Settings& operator=(Settings&&) = delete;

		explicit Settings(const std::filesystem::path& path);

		static Settings& GetSingleton();

		void Deserialize(const json& settings);
		json Serialize() const;

		Fixes fixes;
	};
}