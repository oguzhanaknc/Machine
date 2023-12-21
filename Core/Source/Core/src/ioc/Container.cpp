#include "Container.h"

namespace machine::ioc
{
	Container& Get() noexcept
	{
		static Container container;
		return container;
	}
}