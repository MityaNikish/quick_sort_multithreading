#include "pch.h"

#include <chrono>
#include <time.h>

#include "pquicksort.hpp"
#include "generate.hpp"

bool myfunction(int i, int j) { return (i < j); }

struct myclass
{
    bool operator() (int i, int j) { return (i < j); };
};

class Unit
{
public:
    Unit(int arg) : size(arg) {}
    int GetSize(void) { return size; }
    bool operator==(const Unit& that) const { return this->size == that.size; }
private:
    int size;
};


//using Time = std::chrono::steady_clock;
//using ms = std::chrono::milliseconds;
//using float_sec = std::chrono::duration<float>;
//using float_time_point = std::chrono::time_point<Time, float_sec>;
//
//float_time_point
//getCurrentTime() {
//    return Time::now();
//}
//
//int main() {
//    auto startTime = getCurrentTime();
//    std::cout << "Start Time: " << startTime.time_since_epoch().count() << "\n";
//
//    while (true) {
//        std::cout << (getCurrentTime() - startTime).count() << "\n";
//    }
//}


template <typename T>
void write_file(const char* file_name, std::vector<T> v)
{
    std::ofstream fout(file_name, std::ios_base::out);
    if (fout.is_open())
    {
        for (int i = 0; i < v.size(); i++)
            fout << v[i] << "  ";
    }
    else
    {
        throw opening_file_exception();
    }
    fout.close();
}

//int main()
//{
//    auto start = std::chrono::high_resolution_clock::now();
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration<double>(stop - start).count();
//
//    size_t size = 1000000;
//    std::vector<int> vector_date;
//
//    auto times_sum = 0.0;
//
//    //default quick_sort
//    for (int i = 0; i < 5; i++)
//    {
//        vector_date = generate<int>(size);
//
//        start = std::chrono::high_resolution_clock::now();
//
//        quick_sort(vector_date.begin(), vector_date.end());
//
//        stop = std::chrono::high_resolution_clock::now();
//
//        duration = std::chrono::duration<double>(stop - start).count();
//        std::cout << i << " => " << duration << std::endl;
//        times_sum += duration;
//    }
//
//    std::cout << "Average: " << times_sum / 5 << std::endl;
//
//    return 0;
//}



//int main(int argc, char** argv)
//{
//    size_t size = 1000;
//    auto max_threads_number = std::thread::hardware_concurrency();
//    auto times_min = 1000000.0;
//    auto times_max = 0.0;
//    int times_thrd_min = 0;
//    int times_thrd_max = 0;
//
//
//    while (size < 2'000'000)
//    {
//        std::cout << std::endl;
//
//        std::vector<int> vec(size);
//        vec = generate<int>(size);
//
//        times_thrd_min = 0;
//        times_thrd_max = 0;
//        times_min = 1000000.0;
//        times_max = 0.0;
//
//        std::cout << vec.size() << std::endl;
//
//        for (size_t i = 1; i <= max_threads_number; ++i)
//        {
//            SchemePolicy schemePolicy(i);
//
//            auto start = std::chrono::high_resolution_clock::now();
//
//            pquicksort(vec.begin(), vec.end(), schemePolicy);
//
//            auto stop = std::chrono::high_resolution_clock::now();
//            auto duration = std::chrono::duration<double>(stop - start).count();
//
//            std::cout << schemePolicy.CulculateThreadsNumber(vec.size()) << " => " << duration << "\n";
// 
//            //auto start = std::chrono::steady_clock::now();
//            //pquicksort(vec.begin(), vec.end(), schemePolicy);
//            //auto end = std::chrono::steady_clock::now();
//            //auto elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//
//            //std::cout << schemePolicy.CulculateThreadsNumber(vec.size()) << " => " << elapsed_seconds.count() << "\n";
//
//            if (duration < times_min)
//            {
//                times_min = duration;
//                times_thrd_min = i;
//            }
//
//            if (duration > times_max)
//            {
//                times_max = duration;
//                times_thrd_max = i;
//            }
//
//        }
//        std::cout << "Time min: " << times_min << " this " << times_thrd_min << std::endl;
//        std::cout << "Time max: " << times_max << " this " << times_thrd_max << std::endl;
// 
//        size *= 2;
//
//        for (size_t i = 0; i < vec.size() - 1; i++)
//        {
//            if (vec[i] > vec[i + 1])
//                std::cout << "Detected not sorted data: " << vec[i] << ", " << vec[i + 1] << std::endl;
//        }
//    }
//}



TEST(TestCase_NoComp, Test_Performans)
{
    SchemePolicy schemePolicy(2);
    std::vector<int> vector_mysort = generate<int>(64000);
    std::vector<int> vector_stdsort(vector_mysort);

    auto start = std::chrono::high_resolution_clock::now();
    pquicksort(vector_mysort.begin(), vector_mysort.end(), schemePolicy);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_my = std::chrono::duration<double>(stop - start).count();


    start = std::chrono::high_resolution_clock::now();
    std::sort(vector_stdsort.begin(), vector_stdsort.end());
    stop = std::chrono::high_resolution_clock::now();
    auto duration_std = std::chrono::duration<double>(stop - start).count();

    //EXPECT_EQ(vector_mysort, vector_stdsort);
    EXPECT_TRUE(duration_my > duration_std);
}


TEST(TestCase_NoComp, Test_Corect)
{
    SchemePolicy schemePolicy(2);
    std::vector<int> vector_mysort = generate<int>(4000);
    bool expect = true;

    pquicksort(vector_mysort.begin(), vector_mysort.end(), schemePolicy);

    for (size_t i = 0; i < vector_mysort.size() - 1; i++)
    {
        if (vector_mysort[i] > vector_mysort[i + 1])
            expect = false;
    }

    EXPECT_TRUE(expect);
}

TEST(TestCase_CompFunc, Test_Performans)
{
    SchemePolicy schemePolicy(2);
    std::vector<int> vector_mysort = generate<int>(64000);
    std::vector<int> vector_stdsort(vector_mysort);

    auto start = std::chrono::high_resolution_clock::now();
    pquicksort(vector_mysort.begin(), vector_mysort.end(), myfunction, schemePolicy);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_my = std::chrono::duration<double>(stop - start).count();


    start = std::chrono::high_resolution_clock::now();
    std::sort(vector_stdsort.begin(), vector_stdsort.end(), myfunction);
    stop = std::chrono::high_resolution_clock::now();
    auto duration_std = std::chrono::duration<double>(stop - start).count();

    //EXPECT_EQ(vector_mysort, vector_stdsort);
    EXPECT_TRUE(duration_my > duration_std);
}


TEST(TestCase_CompFunc, Test_Corect)
{
    SchemePolicy schemePolicy(2);
    std::vector<int> vector_mysort = generate<int>(4000);
    bool expect = true;

    pquicksort(vector_mysort.begin(), vector_mysort.end(), myfunction, schemePolicy);

    for (size_t i = 0; i < vector_mysort.size() - 1; i++)
    {
        if (vector_mysort[i] > vector_mysort[i + 1])
            expect = false;
    }

    EXPECT_TRUE(expect);
}


//TEST(TestCase_CompLamb, Test_Performans)
//{
//    SchemePolicy schemePolicy(2);
//    std::vector<int> vector_mysort = generate<int>(64000);
//    std::vector<int> vector_stdsort(vector_mysort);
//
//    auto start = std::chrono::high_resolution_clock::now();
//    pquicksort(vector_mysort.begin(), vector_mysort.end(), [](int a, int b) { return a > b; }, schemePolicy);
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration_my = std::chrono::duration<double>(stop - start).count();
//
//
//    start = std::chrono::high_resolution_clock::now();
//    std::sort(vector_stdsort.begin(), vector_stdsort.end(), [](int a, int b) { return a > b; });
//    stop = std::chrono::high_resolution_clock::now();
//    auto duration_std = std::chrono::duration<double>(stop - start).count();
//
//    //EXPECT_EQ(vector_mysort, vector_stdsort);
//    EXPECT_TRUE(duration_my > duration_std);
//}
//
//
//TEST(TestCase_CompLamb, Test_Corect)
//{
//    SchemePolicy schemePolicy(2);
//    std::vector<int> vector_mysort = generate<int>(4000);
//    bool expect = true;
//
//    pquicksort(vector_mysort.begin(), vector_mysort.end(), [](int a, int b) { return a > b; }, schemePolicy);
//
//    for (size_t i = 0; i < vector_mysort.size() - 1; i++)
//    {
//        if (vector_mysort[i] > vector_mysort[i + 1])
//            expect = false;
//    }
//
//    EXPECT_TRUE(expect);
//}