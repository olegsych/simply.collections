#include "stdafx.h"
#include <memory>
#include <vector>
#include <simply/collections/range.h>
#include "stub_enumerable.h"
#include "stub_enumerator.h"

using namespace std;

namespace simply
{
    TEST_CLASS(range_test)
    {
		template<typename element_t> shared_ptr<enumerable<element_t>> create_enumerable(initializer_list<element_t> elements)
		{
			auto enumerable_stub = new stub_enumerable<element_t>(elements);
			return shared_ptr<enumerable<element_t>> { enumerable_stub };
		}

    public:
		TEST_METHOD(constructor_throws_invalid_argument_when_enumerable_is_null)
		{
			shared_ptr<enumerable<int>> enumerable{ nullptr };
			auto e = assert::throws<invalid_argument>([&] { range<int> { enumerable }; });
			assert::find("enumerable must not be nullptr", e->what());
		}

        TEST_METHOD(begin_returns_iterator_pointing_before_first_element_of_enumerable)
        {
            const int expected { random<int>() };
			range<int> sut { create_enumerable({ expected }) };
			iterator<int> result { sut.begin() };
			assert::is_equal(expected, *result);
        }

        TEST_METHOD(end_returns_iterator_pointing_after_last_element_of_enumerable)
        {
			shared_ptr<enumerable<int>> enumerable { create_enumerable({ random<int>() }) };
			range<int> sut { enumerable };
			iterator<int> result { sut.end() };
			iterator<int> expected { enumerable, iterator_position::after_last };
			assert::is_true(expected == result);
		}

        TEST_METHOD(range_can_be_used_in_for_loop)
        {
			initializer_list<int> expected { random<int>(), random<int>(), random<int>() };
			vector<int> actual;
			range<int> sut { create_enumerable(expected) };
			for (int value : sut)
			{
				actual.push_back(value);
			}
			assert::is_true(vector<int> { expected } == actual); // no << for vector<int>
        }

		TEST_METHOD(range_can_be_used_in_for_loop_over_empty_enumerable)
		{
			range<int> sut { create_enumerable<int>({}) };
			for (int value : sut) {}
		}
    };
}