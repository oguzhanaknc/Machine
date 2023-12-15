#include "Singletons.h"

namespace machine::ioc
{
    Singletons& Sing()
    {
        static Singletons sing;
        return sing;
    }
}