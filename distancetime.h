#ifndef __DISTANCETIME_H__
#define __DISTANCETIME_H__

#include <ostream>

struct Time
{
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;

    int mins_;
    int secs_;
};

std::ostream& operator<<(std::ostream& out, const Time& time);

#endif
