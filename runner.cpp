#include "runner.h"

#include <iomanip>

Runner::Runner(const std::string& name, const Time& time5k)
    : name_{ name }
    , time5k_{ time5k }
{}

bool Runner::operator<(const Runner& other) const
{
    if (time5k_ < other.time5k_)
        return true;
    else if (time5k_ > other.time5k_)
        return false;
    else
        return (name_ < other.name_);
}

std::ostream& operator<<(std::ostream& out, const Runner& runner)
{
    out << std::left << std::setw(16) << runner.name_
        << std::right << runner.time5k_;
    return out;
}
