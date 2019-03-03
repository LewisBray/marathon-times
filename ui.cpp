// Contains the function definitions for interfacing with the user.

#include "ui.h"

#include <iostream>

void displayMenu()
{
    std::cout << "Menu:\n"
        << "1) Add new runner.\n"
        << "2) Remove runner.\n"
        << "3) Edit runner's personal best.\n"
        << "4) Show leader-board.\n"
        << "5) Save changes.\n"
        << "6) Exit.\n"
        << std::endl;
}

static std::string getStringFromUser()
{
    std::string userInput;
    std::getline(std::cin, userInput);

    return userInput;
}

MenuChoice askUserForMenuChoice()
{
    while (true)
    {
        const std::string choiceAsString = getStringFromUser();
        const int choice = std::stoi(choiceAsString);

        if (choice < 1 || choice > 6)
            std::cout << "Not a valid choice." << std::endl;
        else
            return static_cast<MenuChoice>(choice);
    }
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
