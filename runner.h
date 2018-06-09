#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "distancetime.h"

#include <string>


// Handles typical properties of a runner.
struct runner
{
    runner(std::string runnerName, time runner5kTime)
        : name{ runnerName }
        , time5k{ runner5kTime }
    {}

    // Defined so we can call std::sort on vector of runners
    bool operator<(const runner& other) const
    {
        if (time5k < other.time5k)
            return true;
        else if (time5k > other.time5k)
            return false;
        else
            return (name < other.name);
    }

    inline void Display() const
    {
        printf("%s\t%02d:%02d", name.c_str(), time5k.mins, time5k.secs);
    }


    std::string name;
    time time5k;
};

#endif
