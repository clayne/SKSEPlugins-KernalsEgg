#include "Shared/PCH.h"

#include "Shared/Skyrim/T/TESDataHandler.h"

#include "Shared/Skyrim/Addresses.h"
#include "Shared/Skyrim/T/TESFile.h"



namespace Skyrim
{
	TESForm* TESDataHandler::GetForm(FormID formID)
	{
		auto function{ reinterpret_cast<decltype(&TESDataHandler::GetForm)>(Addresses::TESDataHandler::GetForm) };

		return function(formID);
	}

	TESDataHandler* TESDataHandler::GetSingleton()
	{
		auto singleton{ reinterpret_cast<TESDataHandler**>(Addresses::TESDataHandler::Singleton) };

		return *singleton;
	}

	const TESFile* TESDataHandler::GetFile(std::string_view filename) const
	{
		for (auto file : this->files)
		{
			if (_stricmp(file->filename, filename.data()) == 0)
			{
				return file;
			}
		}

		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetFileIndex(std::string_view filename) const
	{
		auto file = this->GetFile(filename);

		return file ? std::make_optional(file->compileIndex) : std::nullopt;
	}

	const TESFile* TESDataHandler::GetLoadedFile(std::string_view filename) const
	{
		for (auto file : this->compiledFileCollection.files)
		{
			if (_stricmp(file->filename, filename.data()) == 0)
			{
				return file;
			}
		}

		return nullptr;
	}

	const TESFile* TESDataHandler::GetLoadedFile(std::uint8_t index) const
	{
		for (auto file : this->compiledFileCollection.files)
		{
			if (file->compileIndex == index)
			{
				return file;
			}
		}

		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetLoadedFileIndex(std::string_view filename) const
	{
		auto file = this->GetLoadedFile(filename);

		return file ? std::make_optional(file->compileIndex) : std::nullopt;
	}

	const TESFile* TESDataHandler::GetLoadedLightFile(std::string_view filename) const
	{
		for (auto smallFile : this->compiledFileCollection.smallFiles)
		{
			if (_stricmp(smallFile->filename, filename.data()) == 0)
			{
				return smallFile;
			}
		}

		return nullptr;
	}

	const TESFile* TESDataHandler::GetLoadedLightFile(std::uint16_t index) const
	{
		for (auto smallFile : this->compiledFileCollection.smallFiles)
		{
			if (smallFile->compileIndex == index)
			{
				return smallFile;
			}
		}

		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetLoadedLightFileIndex(std::string_view filename) const
	{
		auto smallFile = this->GetLoadedLightFile(filename);

		return smallFile ? std::make_optional(smallFile->compileIndex) : std::nullopt;
	}

	TESForm* TESDataHandler::GetFormFromFile(FormID formID, std::string_view filename) const
	{
		auto file = this->GetFile(filename);

		if (!file || file->compileIndex == 0xFF)
		{
			return nullptr;
		}

		if (file->recordFlags.all(TESFile::RecordFlags::kSmallFile))
		{
			formID &= 0xFFF;
			formID |= 0xFE000000;
			formID += file->smallFileCompileIndex << 12;
		}
		else
		{
			formID &= 0xFFFFFF;
			formID += file->compileIndex << 24;
		}

		return TESDataHandler::GetForm(formID);
	}
}