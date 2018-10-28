#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "distancetime.h"
#include "runner.h"

#include <ostream>
#include <vector>

class Database
{
public:
    bool saveToFile();
    bool loadFromFile();
    void addRunners();
    void removeRunners();
    void editRunnerTimes();

    friend std::ostream& operator<<(std::ostream& out, Database& database);

private:
    static bool askUserToDoAgain(const std::string& phrase);
    static Time askUserForMarathonTime();

    std::vector<Runner> runners_;
};

#endif
