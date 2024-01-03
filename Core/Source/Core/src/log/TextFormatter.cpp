#include "TextFormatter.h"
#include "TextFormatter.h"
#include "Entry.h"
#include <format>
#include <sstream>
#include <Core/src/win/Utilities.h>
namespace machine::log {
	std::wstring TextFormatter::Format(const Entry& e) const
	{
		std::wostringstream oss;
		oss << std::format(L"@{} {{{}}} {}",
			GetLevelName(e.level_),
			std::chrono::zoned_time{ std::chrono::current_zone(), e.timestamp_ },
			e.note_
		);
		if (e.hResult_) {
			oss << std::format(L"\n  !HRESULT [{:#010x}]: {}", *e.hResult_,
				win::GetErrorDescription(*e.hResult_));
		}
		if (e.showSourceLine_.value_or(true)) {
			oss << std::format(L"\n  >> at {}\n     {}({})\n",
				e.sourceFunctionName_,
				e.sourceFile_,
				e.sourceLine_
			);
		}
		else {
			oss << "\n";
		}
		if (e.tracer) {
			oss << e.tracer->Print() << "\n";
		}
		return oss.str();
	}
}
