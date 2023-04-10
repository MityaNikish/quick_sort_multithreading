#pragma once
#include <vector>
#include <algorithm>
#include <random>

template <typename T>
std::vector<T> generate(size_t size)
{
	std::vector<T> v;
	v.resize(size);

	std::for_each(v.begin(), v.end(), [](T& i) {
		i = std::mt19937(std::random_device{}())() % 1000000;
	});

	return v;
}