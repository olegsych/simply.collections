#pragma once

namespace simply 
{
    template<typename element_t> struct enumerator
    {
        virtual ~enumerator() {};
        virtual bool get_next(element_t* element) = 0;
    };
}
