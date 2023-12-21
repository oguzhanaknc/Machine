#include "TextFormatter.h"

std::wstring machine::log::TextFormatter::Format(const Entry& e) const
{
	std::wostringstream oss;
	oss << std::format(L"@{} {{{}}} {}\n  >> at {}\n     {}({})\n",
		GetLevelName(e.level_),
		std::chrono::zoned_time{ std::chrono::current_zone(), e.timeStamp },
		e.note_,
		e.sourceFunctionName_,
		e.sourceFile_,
		e.sourceLine_
	);
	if (e.tracer)
	{
		oss << e.tracer->Print() << "\n";
	}
	return oss.str();
}



