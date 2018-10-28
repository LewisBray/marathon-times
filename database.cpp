#include "database.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

constexpr char const DataFile[] = "runners.bin";

// This should be a const function but it just so happens to sort the order of
// 'runners_'.  You could argue that it's not really changing the class and I
// would agree, it just felt silly to make the only member variable mutable for
// the sake of making this function (and ShowLeaderboard) const as this makes
// const lose all meaning in this class if all member variables can be modified
// by const methods.  N.B.  File format of "runners.bin" described in associated
// readme.txt in repository.
bool Database::saveToFile()
{
    std::sort(runners_.begin(), runners_.end());

    std::ofstream outFile(DataFile, std::ios::trunc | std::ios::binary);
    if (!outFile.is_open())
        return false;

    outFile.seekp(0, std::ios::beg);

    const int numRunners = runners_.size();
    outFile.write(reinterpret_cast<const char*>(&numRunners), sizeof(numRunners));

    for (const Runner& runner : runners_)
    {
        const int nameLength = runner.name_.length();
        const Time time5k = runner.time5k_;

        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(runner.name_.c_str(), nameLength + 1);
        outFile.write(reinterpret_cast<const char*>(&time5k), sizeof(time5k));
    }

    std::cout << std::endl << "Changes saved." << std::endl << std::endl;

    return true;
}

bool Database::loadFromFile()
{
    std::ifstream inFile(DataFile, std::ios::binary);
    if (!inFile.is_open())
        return false;

    inFile.seekg(0, std::ios::beg);

    int numRunners;
    if (!inFile.read(reinterpret_cast<char*>(&numRunners), sizeof(numRunners))
        || (numRunners < 0))
        return false;

    for (int i = 0; i < numRunners; ++i)
    {
        int nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))
            || (nameLength <= 0) || (nameLength > 100))
            return false;

        std::unique_ptr<char[]> nameBuffer = std::make_unique<char[]>(nameLength + 1);
        if (!inFile.read(nameBuffer.get(), nameLength + 1)
            || (nameBuffer[nameLength] != '\0'))
            return false;

        const std::string name{ nameBuffer.get() };

        Time runner5kTime;
        if (!inFile.read(reinterpret_cast<char*>(&runner5kTime), sizeof(runner5kTime)))
            return false;

        runners_.emplace_back(name, runner5kTime);
    }

    return true;
}

void Database::addRunners()
{
    do
    {
        std::cout << "Enter name: ";

        std::string newName;
        getline(std::cin, newName);

        const Time new5kTime = askUserForMarathonTime();

        runners_.emplace_back(newName, new5kTime);
    } while (askUserToDoAgain("Add another runner"));

    std::cout << std::endl << std::endl;
}

void Database::removeRunners()
{
    do
    {
        if (runners_.empty()) {
            std::cout << "There are no runners left to remove!!!";
            return;
        }

        while (true)
        {
            std::cout << "Enter name of runner to remove: ";

            std::string nameToRemove;
            getline(std::cin, nameToRemove);

            const auto runnerToRemove = std::find_if(
                runners_.begin(), runners_.end(),
                [nameToRemove](const Runner& runner) {
                    return (runner.name_ == nameToRemove);
                }
            );

            if (runnerToRemove != runners_.end()) {
                runners_.erase(runnerToRemove);
                break;
            }
            else
                std::cout << "That runner doesn't exist!\n";
        }
    } while (askUserToDoAgain("Remove another runner"));

    std::cout << std::endl << std::endl;
}

void Database::editRunnerTimes()
{
    do
    {
        if (runners_.empty()) {
            std::cout << "There are no runners to edit!!!";
            return;
        }

        while (true)
        {
            std::cout << "Enter name of runner whose time you want to edit: ";

            std::string nameToEdit;
            getline(std::cin, nameToEdit);

            auto runnerToEdit = std::find_if(
                runners_.begin(), runners_.end(),
                [nameToEdit](const Runner& person) {
                    return (person.name_ == nameToEdit);
                }
            );

            if (runnerToEdit != runners_.end()) {
                runnerToEdit->time5k_ = askUserForMarathonTime();
                break;
            }
            else
                std::cout << "That runner doesn't exist!\n";
        }
    } while (askUserToDoAgain("Edit another runner's time"));

    std::cout << std::endl << std::endl;
}

// This function prevents repeated code, 'phrase' specifies what task the user
// is queried about, e.g. "Edit another PB".
bool Database::askUserToDoAgain(const std::string& phrase)
{
    while (true)
    {
        std::cout << phrase << "? -> (Y/N): ";

        std::string choiceAsString;
        getline(std::cin, choiceAsString);
        const char userChoice = choiceAsString[0];

        if (userChoice == 'Y' || userChoice == 'y')
            return true;
        else if (userChoice == 'N' || userChoice == 'n')
            return false;
        else
            std::cout << "Invalid input.  ";
    }
}

Time Database::askUserForMarathonTime()
{
    int mins;
    while (true)
    {
        std::cout << "Enter minutes: ";

        std::string minsAsString;
        getline(std::cin, minsAsString);
        mins = stoi(minsAsString);

        if (mins < 0 || mins >= 60)
            std::cout << "That's not a valid number of minutes.  ";
        else
            break;
    }

    int secs;
    while (true)
    {
        std::cout << "Enter seconds: ";

        std::string secsAsString;
        getline(std::cin, secsAsString);
        secs = stoi(secsAsString);

        if (secs < 0 || secs >= 60)
            std::cout << "That's not a valid number of seconds.  ";
        else
            break;
    }

    return Time{ mins, secs };
}

std::ostream& operator<<(std::ostream& out, Database& database)
{
    std::sort(database.runners_.begin(), database.runners_.end());

    out << std::endl << "5k times:" << std::endl << std::endl;

    int position = 1;
    for (const Runner& runner : database.runners_)
        out << "  " << position++ << ") " << runner << std::endl;

    out << std::endl << std::endl;

    return out;
}
