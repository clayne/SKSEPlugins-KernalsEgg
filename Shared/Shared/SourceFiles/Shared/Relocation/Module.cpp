#include "Shared/PCH.h"

#include "Shared/Relocation/Module.h"

#include "Shared/Utility/MessageBox.h"



extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace Relocation
{
	Plugin::Plugin(std::uintptr_t address) :
		address_(address)
	{
		this->SetPath(this->address_);
		this->SetSize(this->address_);
	}

	const Plugin& Plugin::GetSingleton()
	{
		static Plugin singleton(reinterpret_cast<std::uintptr_t>(std::addressof(__ImageBase)));

		return singleton;
	}

	void Plugin::SetPath(std::uintptr_t address)
	{
		char path[MAX_PATH];

		if (!::GetModuleFileNameA(reinterpret_cast<::HMODULE>(address), path, MAX_PATH))
		{
			Utility::MessageBox::Error("Path not found, last-error code {}.", ::GetLastError());
		}

		this->path_ = std::filesystem::path(path);
	}

	void Plugin::SetSize(std::uintptr_t address)
	{
		::MODULEINFO moduleInfo;

		if (!::GetModuleInformation(::GetCurrentProcess(), reinterpret_cast<::HMODULE>(address), std::addressof(moduleInfo), sizeof(::MODULEINFO)))
		{
			Utility::MessageBox::Error("Module information not found, last-error code {}.", ::GetLastError());
		}

		this->size_ = moduleInfo.SizeOfImage;
	}

	Executable::Executable(std::uintptr_t address) :
		Plugin(address)
	{
		this->SetProductVersion(this->path_);
	}

	const Executable& Executable::GetSingleton()
	{
		static Executable singleton(reinterpret_cast<std::uintptr_t>(::GetModuleHandleA(NULL)));

		return singleton;
	}

	void Executable::SetProductVersion(const std::filesystem::path& path)
	{
		std::uint32_t     dummy;
		std::vector<char> fileVersionInfo(::GetFileVersionInfoSizeA(path.string().c_str(), reinterpret_cast<::LPDWORD>(std::addressof(dummy))));

		if (fileVersionInfo.empty())
		{
			Utility::MessageBox::Error("{} file version info size not found, last-error code {}.", path.filename().string(), ::GetLastError());
		}

		if (!::GetFileVersionInfoA(path.string().c_str(), 0, static_cast<::DWORD>(fileVersionInfo.size()), fileVersionInfo.data()))
		{
			Utility::MessageBox::Error("{} file version info not found, last-error code {}.", path.filename().string(), ::GetLastError());
		}

		void*         productVersionPointer{ nullptr };
		std::uint32_t productVersionSize{ 0 };

		if (!::VerQueryValueW(fileVersionInfo.data(), L"\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(productVersionPointer), std::addressof(productVersionSize))) // 0x0409 = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 0x04B0 = UTF-16
		{
			Utility::MessageBox::Error("{} product version not found.", path.filename().string());
		}

		std::wistringstream productVersionStringStream(std::wstring(static_cast<const wchar_t*>(productVersionPointer), productVersionSize));
		std::wstring        productVersionString;

		if (!std::getline(productVersionStringStream, productVersionString, L'.'))
		{
			Utility::MessageBox::Error("{} major product version not found.", path.filename().string());
		}

		this->productVersion_.major = std::stoi(productVersionString);

		if (!std::getline(productVersionStringStream, productVersionString, L'.'))
		{
			Utility::MessageBox::Error("{} minor product version not found.", path.filename().string());
		}

		this->productVersion_.minor = std::stoi(productVersionString);

		if (!std::getline(productVersionStringStream, productVersionString, L'.'))
		{
			Utility::MessageBox::Error("{} revision product version not found.", path.filename().string());
		}

		this->productVersion_.revision = std::stoi(productVersionString);

		if (!std::getline(productVersionStringStream, productVersionString, L'.'))
		{
			Utility::MessageBox::Error("{} build product version not found.", path.filename().string());
		}

		this->productVersion_.build = std::stoi(productVersionString);
	}
}
