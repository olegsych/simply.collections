#include <CppUnitTest.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include <simply/assert.h>
#include <simply/collections.h>
#include <vector>

using namespace simply;

class answer_enumerator : public enumerator<int>
{
    const std::vector<int> answers;
    size_t index = 0;
public:
    answer_enumerator(const std::vector<int> answers) : answers(answers)
    {
    }

    bool get_next(int* element) override
    {
        if (index < answers.size())
        {
            *element = answers[index++];
            return true;
        }

        return false;
    }
};

class answer_enumerable : public enumerable<int>
{
    std::vector<int> answers { 40, 41, 42 };
public:
    std::unique_ptr<enumerator<int>> create_enumerator() override
    {
        return std::make_unique<answer_enumerator>(answers);
    }
};

class question
{
public:
    range<int> answers()
    {
        return range<int> { std::make_shared<answer_enumerable>() };
    }
};

TEST_CLASS(scenario_test)
{
public:
    TEST_METHOD(range_in_foreach_loop)
    {
        question q;
        range<int> answers { q.answers() };
        for (int answer : answers)
        {
            std::cout << answer;
        }
    }

    TEST_METHOD(range_in_algorithms)
    {
        question q;
        range<int> answers { q.answers() };
        std::for_each(std::begin(answers), std::end(answers), [](int answer) {
            std::cout << answer;
        });
    }
};