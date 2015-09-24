#pragma once

#include <memory>
#include <stdexcept>
#include <simply/collections/enumerable.h>
#include <simply/collections/iterator.h>

namespace simply
{
    template<typename element_t> class range
    {
    public:
		range(std::shared_ptr<enumerable<element_t>> enumerable)
			: _enumerable { enumerable }
		{
			if (!enumerable)
			{
				throw std::invalid_argument{ "enumerable must not be nullptr" };
			}
		}

        iterator<element_t> begin() const
        {
			return iterator<element_t> { _enumerable, iterator_position::before_first };
        }

        iterator<element_t> end() const
        {
            return iterator<element_t> { _enumerable, iterator_position::after_last };
        }

	private:
		std::shared_ptr<enumerable<element_t>> _enumerable;
    };
}