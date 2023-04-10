#pragma once
#include <thread>
#include <future>

#include "quick_sort.hpp"
#include "SchemePolicy.hpp"


template<RandomAccessIterator RandomIt, Comparator<RandomIt> Compare, class SchemePolicy>
void pquicksort(RandomIt first, RandomIt last, Compare comp, SchemePolicy&& partition)
{
    typedef typename std::iterator_traits<RandomIt>::difference_type dif_type;
    dif_type size = std::distance(first, last);

    int threadsCount = partition.CulculateThreadsNumber(size);
    if (threadsCount == 1) {
        quick_sort(first, last, comp);
        return;
    }

    auto slice = size / threadsCount;
    std::vector<RandomIt> ranges;

    for (int i = 0; i < threadsCount; i++)
        ranges.push_back(first + slice * i);
    ranges.push_back(last);

    std::vector<std::thread> threads;
    for (int threadNumber = 0; threadNumber < threadsCount; threadNumber++)
    {
        threads.emplace_back([&](int thrdNum) {
            quick_sort(ranges[thrdNum], ranges[thrdNum + 1], comp);
            }, threadNumber);
    }

    for (auto& thread : threads)
        thread.join();

    for (size_t j = 0; j < ranges.size() - 2; j++)
        std::inplace_merge(ranges[0], ranges[j + 1], ranges[j + 2]);

}

template<RandomAccessIterator RandomIt, class SchemePolicy>
void pquicksort(RandomIt first, RandomIt last, SchemePolicy&& partition)
{
    pquicksort(first, last, std::less< typename std::iterator_traits< RandomIt >::value_type >(), partition);
}