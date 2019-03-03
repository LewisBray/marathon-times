// Simple struct for holding marathon times with a couple of
// functions for use in the project.

#ifndef __MARATHONTIME_H__
#define __MARATHONTIME_H__

#include <ostream>

struct MarathonTime
{
    int mins = 0;
    int secs = 0;
};

bool operator<(const MarathonTime& lhs, const MarathonTime& rhs) noexcept;
std::ostream& operator<<(std::ostream& out, const MarathonTime& time);

#endif
