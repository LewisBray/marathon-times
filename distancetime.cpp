#include "distancetime.h"

#include <iomanip>

bool Time::operator<(const Time& other) const
{
    if (mins_ < other.mins_)
        return true;
    else if (mins_ > other.mins_)
        return false;
    else
        return (secs_ < other.secs_);
}

bool Time::operator>(const Time& other) const
{
    if (mins_ > other.mins_)
        return true;
    else if (mins_ < other.mins_)
        return false;
    else
        return (secs_ > other.secs_);
}

std::ostream& operator<<(std::ostream& out, const Time& time)
{
    out << std::setfill('0') << std::setw(2) << time.mins_
        << ':' << std::setw(2) << time.secs_ << std::setfill(' ');
    return out;
}
