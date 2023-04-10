#pragma once

class SchemePolicy
{
public:
    SchemePolicy(const int fixThreadsCount = 0) : fixedThreadsCount(fixThreadsCount) {}
    size_t CulculateThreadsNumber(size_t elementsCount) const
    {
        if (fixedThreadsCount != 0)
            return fixedThreadsCount;

        int threadsCount;

        if (elementsCount > 64000)
        {
            threadsCount = 2;
        }
        else
        {
            threadsCount = 1;
        }
            
        return threadsCount;
    }
private:
    int fixedThreadsCount;
};