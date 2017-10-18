#include <iostream>
#include <vector>

#include "classes.h"

using namespace std;

string runner::get_name()
{
    return name;
}

int runner::get_mins()
{
    return time5k.mins;
}

int runner::get_secs()
{
    return time5k.secs;
}

void runner::set_name(const string& input)
{
    name = input;
}

void runner::set_time(const int& m, const int& s)
{
    time5k.mins = m;
    time5k.secs = s;
}

void runner::display_runner()
{
    cout << get_name();
    cout << "\t" << time5k.mins << ":" << time5k.secs;
}
