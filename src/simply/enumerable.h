#pragma once

#include <memory>
#include <simply/enumerator.h>

namespace simply
{
    template<typename element_t> struct enumerable
    {
        virtual ~enumerable() {};
        virtual std::unique_ptr<enumerator<element_t>> create_enumerator() = 0;
    };
}
