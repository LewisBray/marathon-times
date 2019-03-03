// Implementation of functions used for interfacing with the user
// and manipulating the runner database.

#include "runners.h"

#include <algorithm>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string getStringFromUser()
{
    std::string userInput;
    std::getline(std::cin, userInput);

    return userInput;
}

MarathonTime askUserForMarathonTime()
{
    MarathonTime time;
    while (true)
    {
        std::cout << "Enter minutes: ";

        const std::string minsAsString = getStringFromUser();
        time.mins = stoi(minsAsString);

        if (time.mins < 0 || time.mins >= 60)
            std::cout << "That's not a valid number of minutes.  ";
        else
            break;
    }

    while (true)
    {
        std::cout << "Enter seconds: ";

        const std::string secsAsString = getStringFromUser();
        time.secs = stoi(secsAsString);

        if (time.secs < 0 || time.secs >= 60)
            std::cout << "That's not a valid number of seconds.  ";
        else
            break;
    }

    return time;
}

bool askIfUserWantsTo(const std::string& phrase)
{
    while (true)
    {
        std::cout << phrase << "? -> (Y/N): ";

        const std::string choiceAsString = getStringFromUser();
        const char userChoice = choiceAsString[0];

        if (userChoice == 'Y' || userChoice == 'y')
            return true;
        else if (userChoice == 'N' || userChoice == 'n')
            return false;
        else
            std::cout << "Invalid input.  ";
    }
}

Runner askUserForRunnerToAdd(const Runners& runners)
{
    while (true)
    {
        std::cout << "Enter name: ";
        const std::string newName = getStringFromUser();

        if (runners.find(newName) != runners.end()) {
            std::cout << "That runner already exists!\n";
            continue;
        }

        const MarathonTime new5kTime = askUserForMarathonTime();

        return std::make_pair(newName, new5kTime);
    }
}

// This is a bit strange in that we cannot return an iterator from a
// function that takes its parameters by const& so we have to take the
// runners in by non-const reference but they are practically const.
Runners::iterator askUserForRunnerToEdit(Runners& runners)
{
    while (true)
    {
        std::cout << "Enter name of runner whose time you want to edit: ";

        const std::string nameToEdit = getStringFromUser();

        const auto runnerToEdit = runners.find(nameToEdit);

        if (runnerToEdit != runners.end())
            return runnerToEdit;
        else
            std::cout << "That runner doesn't exist!\n";
    }
}

Runners::const_iterator askUserForRunnerToRemove(const Runners& runners)
{
    while (true)
    {
        std::cout << "Enter name of runner to remove: ";

        const std::string nameToRemove = getStringFromUser();

        const auto runnerToRemove = runners.find(nameToRemove);

        if (runnerToRemove != runners.end())
            return runnerToRemove;
        else
            std::cout << "That runner doesn't exist!\n";
    }
}

static std::ostream& operator<<(std::ostream& out, const Runner& runner)
{
    out << std::left << std::setw(16) << runner.first
        << std::right << runner.second;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Runners& runners)
{
    out << "\n5k times:\n\n";

    int position = 1;
    for (const auto runner : runners)
        out << "  " << position++ << ") " << runner << '\n';

    out << std::flush;

    return out;
}

// Couldn't make lambda template inside loadRunnerData so had to put here.
template <typename T>
static T readFromFile(std::ifstream& file)
{
    T t;
    file.read(reinterpret_cast<char*>(&t), sizeof(t));

    return t;
}

Runners loadRunnerData(const std::string& file)
{
    std::ifstream inputFile(file, std::ios::binary);
    if (!inputFile.is_open())
    {
        const std::string error = "Failed to open " + file + " for writing data";
        throw std::exception(error.c_str());
    }

    inputFile.seekg(0, std::ios::beg);

    const int numRunners = readFromFile<int>(inputFile);

    const auto readNameFromFile = [&inputFile](const int length)
    {
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(length + 1);
        if (!inputFile.read(buffer.get(), length + 1) || buffer[length] != '\0')
            throw std::exception{ "Failed to read runner name" };

        const std::string name{ buffer.get() };
        return name;
    };

    Runners runners;
    for (int i = 0; i < numRunners; ++i)
    {
        const int nameLength = readFromFile<int>(inputFile);
        if (nameLength <= 0 || nameLength > 100)
        {
            std::stringstream error;
            error << "Invalid name length for runner " << i;
            throw std::exception{ error.str().c_str() };
        }

        const std::string name = readNameFromFile(nameLength);

        const MarathonTime time5k = readFromFile<MarathonTime>(inputFile);
        if (time5k.mins < 0 || time5k.mins >= 60
            || time5k.secs < 0 || time5k.secs >= 60)
        {
            std::stringstream error;
            error << "Invalid time read for runner " << i;
            throw std::exception{ error.str().c_str() };
        }

        runners.insert(Runner{ name, time5k });
    }

    return runners;
}

void saveRunnerData(const Runners& runners, const std::string& file)
{
    std::ofstream outputFile(file, std::ios::trunc | std::ios::binary);
    if (!outputFile.is_open())
    {
        const std::string error = "Failed to open " + file + " for saving data";
        throw std::exception{ error.c_str() };
    }

    outputFile.seekp(0, std::ios::beg);

    const int numRunners = runners.size();
    outputFile.write(reinterpret_cast<const char*>(&numRunners), sizeof(numRunners));

    for (const Runner& runner : runners)
    {
        const std::string& name = runner.first;
        const int nameLength = name.length();
        const MarathonTime time5k = runner.second;

        outputFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outputFile.write(name.c_str(), nameLength + 1);
        outputFile.write(reinterpret_cast<const char*>(&time5k), sizeof(time5k));
    }
}
