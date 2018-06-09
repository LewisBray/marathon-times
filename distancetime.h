#ifndef __DISTANCETIME_H__
#define __DISTANCETIME_H__

#include <iostream>


// Handles times given in minutes and seconds.
struct time
{
    bool operator<(const time& other) const
    {
        if (mins < other.mins)
            return true;
        else if (mins > other.mins)
            return false;
        else
            return (secs < other.secs);
    }

    bool operator>(const time& other) const
    {
        if (mins > other.mins)
            return true;
        else if (mins < other.mins)
            return false;
        else
            return (secs > other.secs);
    }


    int mins;
    int secs;
};

#endif
