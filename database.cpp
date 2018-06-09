#include "database.h"

#include <algorithm>
#include <iostream>
#include <fstream>


// Saves runner data from 'runners' to "runners.bin".
/*
This should be a const function but it just so happens to sort the order of
'runners'.  You could argue that it's not really changing the class and I would
agree, it just felt silly to make the only member variable mutable for the sake
of making this function (and ShowLeaderboard) const as this makes const lose all
meaning in this class if all member variables can be modified by const methods.

File format of "runners.bin" described in associated readme.txt in repository.
*/
bool database::SaveToFile()
{
    std::sort(runners.begin(), runners.end());

    std::ofstream outFile("runners.bin", std::ios::trunc | std::ios::binary);
    if (!outFile.is_open())
        return false;

    outFile.seekp(0, std::ios::beg);

    const int numRunners = runners.size();
    outFile.write(reinterpret_cast<const char*>(&numRunners), sizeof(numRunners));

    for (const runner& person : runners)
    {
        const int nameLength = person.name.length();
        const time time5k = person.time5k;

        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(person.name.c_str(), nameLength + 1);
        outFile.write(reinterpret_cast<const char*>(&time5k), sizeof(time5k));
    }

    std::cout << "\nChanges saved.\n\n";

    return true;
}


// Loads all runner data from "runners.bin" and puts into member variable.
/*
File format of "runners.bin" described in associated readme.txt in repository.
*/
bool database::LoadFromFile()
{
    std::ifstream inFile("runners.bin", std::ios::binary);
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

        std::unique_ptr<char[]> stringBuffer = std::make_unique<char[]>(nameLength + 1);
        if (!inFile.read(stringBuffer.get(), nameLength + 1)
            || (stringBuffer[nameLength] != '\0'))
            return false;

        std::string name{ stringBuffer.get() };

        time runner5kTime;
        if (!inFile.read(reinterpret_cast<char*>(&runner5kTime), sizeof(runner5kTime)))
            return false;

        runners.emplace_back(name, runner5kTime);
    }

    return true;
}


// Gets new runner details from user and adds to the member vector of runners.
void database::AddRunners()
{
    while (true)
    {
        std::cout << "Enter name: ";

        std::string newName;
        getline(std::cin, newName);

        const time new5kTime = GetTimeFromUser();

        runners.emplace_back(newName, new5kTime);

        if (!DoAgain("Add another runner"))
            break;
    }

    std::cout << "\n\n";
}


// Asks user for a name and if this is a runner it removes that entry from 'runners'.
void database::RemoveRunners()
{
    while (true)
    {
        if (runners.empty()) {
            std::cout << "There are no runners left to remove!!!";
            return;
        }

        while (true)
        {
            std::cout << "Enter name of runner to remove: ";

            std::string nameToRemove;
            getline(std::cin, nameToRemove);

            const auto runnerToRemove = std::find_if(
                runners.begin(), runners.end(),
                [nameToRemove](const runner& person) {
                    return (person.name == nameToRemove);
                }
            );

            if (runnerToRemove != runners.end()) {
                runners.erase(runnerToRemove);
                break;
            }
            else
                std::cout << "That runner doesn't exist!\n";
        }

        if (!DoAgain("Remove another runner"))
            break;
    }

    std::cout << "\n\n";
}


// Asks the user for a name and allows them to edit that person's 5k time.
void database::EditRunnerTimes()
{
    while (true)
    {
        if (runners.empty()) {
            std::cout << "There are no runners to edit!!!";
            return;
        }

        while (true)
        {
            std::cout << "Enter name of runner whose time you want to edit: ";

            std::string nameToEdit;
            getline(std::cin, nameToEdit);

            auto runnerToEdit = std::find_if(
                runners.begin(), runners.end(),
                [nameToEdit](const runner& person) {
                return (person.name == nameToEdit);
            }
            );

            if (runnerToEdit != runners.end()) {
                runnerToEdit->time5k = GetTimeFromUser();
                break;
            }
            else
                std::cout << "That runner doesn't exist!\n";
        }

        if (!DoAgain("Edit another runner's time"))
            break;
    }

    std::cout << "\n\n";
}


// Prints the leader-board for 5k times.
/*
See the comments for SaveToFile to see why this function isn't const.
*/
void database::ShowLeaderboard()
{
    std::sort(runners.begin(), runners.end());

    std::cout << "\n5k times:\n\n";

    int position = 1;
    for (const runner& person : runners)
    {
        printf("  %d) ", position++);
        person.Display();
        std::cout << "\n";
    }

    std::cout << "\n\n";
}


// Asks the user if they would like to do the specified task again.
/*
This function prevents repeated code, 'phrase' specifies what task the user is
queried about (e.g. "Edit another PB").
*/
bool database::DoAgain(const std::string& phrase)
{
    while (true)
    {
        printf("%s? -> (Y/N): ", phrase.c_str());

        std::string choiceAsString;
        getline(std::cin, choiceAsString);
        char choice = choiceAsString[0];

        if ((choice == 'Y') || (choice == 'y'))
            return true;
        else if ((choice == 'N') || (choice == 'n'))
            return false;
        else
            std::cout << "Invalid input.  ";
    }
}


// Gets a valid distance time from the user.
time database::GetTimeFromUser()
{
    int mins, secs;
    while (true)
    {
        std::cout << "Enter minutes: ";

        std::string minsAsString;
        getline(std::cin, minsAsString);
        mins = stoi(minsAsString);

        if ((mins < 0) || (mins >= 60))
            std::cout << "That's not a valid number of minutes.  ";
        else
            break;
    }

    while (true)
    {
        std::cout << "Enter seconds: ";

        std::string secsAsString;
        getline(std::cin, secsAsString);
        secs = stoi(secsAsString);

        if ((secs < 0) || (secs >= 60))
            std::cout << "That's not a valid number of seconds.  ";
        else
            break;
    }

    return time{ mins, secs };
}

