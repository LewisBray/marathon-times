#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "distancetime.h"

#include <ostream>
#include <string>

struct Runner
{
    Runner(const std::string& name, const Time& time5k);

    bool operator<(const Runner& other) const;

    std::string name_;
    Time time5k_;
};

std::ostream& operator<<(std::ostream& out, const Runner& runner);

#endif
