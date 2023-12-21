#include "SeverityLevelPolicy.h"

namespace machine::log {
	SeverityLevelPolicy::SeverityLevelPolicy(Level level) : level_(level)
	{
	}
	bool SeverityLevelPolicy::TransformFilter(Entry& e)
	{
		return e.level_ <= level_;
	}
}

