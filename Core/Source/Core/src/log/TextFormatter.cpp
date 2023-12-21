#include "TextFormatter.h"

std::wstring machine::log::TextFormatter::Format(const Entry& e) const
{
	return std::format(L"@{} {{{}}} {}\n  >> at {}\n     {}({})\n",
		GetLevelName(e.level_),
		std::chrono::zoned_time{ std::chrono::current_zone(), e.timeStamp },
		e.note_,
		e.sourceFunctionName_,
		e.sourceFile_,
		e.sourceLine_
	);
}



