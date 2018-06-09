#include "classes.h"

#include <iostream>
#include <vector>


runner::runner(std::string runnerName, time runner5kTime)
    : name{ runnerName }
    , time5k{ runner5kTime }
{}


std::string runner::GetName() const
{
    return name;
}

int runner::GetMins() const
{
    return time5k.mins;
}

int runner::GetSecs() const
{
    return time5k.secs;
}

void runner::SetName(const std::string& input)
{
    name = input;
}

void runner::SetTime(const int m, const int s)
{
    time5k.mins = m;
    time5k.secs = s;
}

void runner::DisplayRunner() const
{
    printf("%s\t%d:%d", name.c_str(), time5k.mins, time5k.secs);
}
