#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "runner.h"

#include <vector>


// Class for all operations on database of runner times.
class database
{
public:
    bool SaveToFile();
    bool LoadFromFile();
    void AddRunners();
    void RemoveRunners();
    void EditRunnerTimes();
    void ShowLeaderboard();

private:
    static bool DoAgain(const std::string& phrase);
    static time GetTimeFromUser();

    std::vector<runner> runners;
};

#endif
