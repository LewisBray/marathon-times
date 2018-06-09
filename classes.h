
#ifndef __CLASSES_H__
#define __CLASSES_H__

#include <string>


struct time
{
    int mins;
    int secs;
};

class runner
{
    public:
        runner(std::string runnerName, time runner5kTime);

        std::string GetName() const;
        int GetMins() const;
        int GetSecs() const;
        void SetName(const std::string& input);
        void SetTime(const int m, const int s);
        void DisplayRunner() const;

    private:
        std::string name;
        time time5k;
};

#endif
