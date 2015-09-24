#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <simply/collections/enumerable.h>
#include "stub_enumerator.h"

namespace simply 
{
    template<typename element_t> class stub_enumerable : public enumerable<element_t>
    {
        std::initializer_list<element_t> elements;
    public:
        stub_enumerable()
        {
        }

        stub_enumerable(std::initializer_list<element_t> elements) 
            : elements(elements.begin(), elements.end())
        {
        }

        std::function<std::unique_ptr<enumerator<element_t>>(void)> stub_create_enumerator = [&] 
        { 
            return std::unique_ptr<enumerator<element_t>> { new stub_enumerator<element_t>(elements) }; 
        };

        std::unique_ptr<enumerator<element_t>> create_enumerator() override
        {
            return stub_create_enumerator();
        }
    };
}
