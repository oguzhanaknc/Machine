#include "Core.h"

#include <iostream>

namespace machine::core {
	void Boot() {
		log::Boot();
		win::Boot();
	}
}