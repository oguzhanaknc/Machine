#pragma once
#include <string>

namespace machine::utilities
{
	std::wstring ToWide(const std::string& narrow);
	std::string ToNarrow(const std::wstring& wide);
}