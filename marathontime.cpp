// Implementation of functions that act on MarathonTime structs.

#include "marathontime.h"

#include <iomanip>

bool operator<(const MarathonTime& lhs, const MarathonTime& rhs) noexcept
{
    if (lhs.mins < rhs.mins)
        return true;
    else if (lhs.mins > rhs.mins)
        return false;
    else
        return (lhs.secs < rhs.secs);
}

std::ostream& operator<<(std::ostream& out, const MarathonTime& time)
{
    out << std::setfill('0') << std::setw(2) << time.mins
        << ':' << std::setw(2) << time.secs << std::setfill(' ');
    return out;
}
