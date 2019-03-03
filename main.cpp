// The main entry point of the application, responsible for loading
// the database of runners and handling the UI logic.

#include "runners.h"

#include <algorithm>
#include <iostream>

static void displayMenu()
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

static int askUserForMenuChoice()
{
    while (true)
    {
        const std::string choiceAsString = getStringFromUser();
        const int choice = std::stoi(choiceAsString);

        if (choice < 1 || choice > 6)
            std::cout << "Not a valid choice." << std::endl;
        else
            return choice;
    }
}

int main()
{
    constexpr char dataFile[] = "runners.bin";
    
    try
    {
        Runners runners = loadRunnerData(dataFile);

        std::cout << "PB running times program.\n" << std::endl;

        bool quit = false;
        while (!quit)
        {
            displayMenu();

            const int userChoice = askUserForMenuChoice();
            switch (userChoice)
            {
            case 1:
            {
                do
                {
                    const Runner newRunner = askUserForRunnerToAdd(runners);
                    runners.insert(newRunner);
                } while (askIfUserWantsTo("Add another runner"));

                break;
            }
            case 2:
            {
                do
                {
                    if (runners.empty()) {
                        std::cout << "There are no runners to remove!!!";
                        break;
                    }

                    const auto runnerToRemove = askUserForRunnerToRemove(runners);
                    runners.erase(runnerToRemove);
                } while (askIfUserWantsTo("Remove another runner"));

                break;
            }
            case 3:
            {
                if (runners.empty()) {
                    std::cout << "There are no runners to edit!!!";
                    break;
                }

                do
                {
                    const auto runnerToEdit = askUserForRunnerToEdit(runners);
                    runnerToEdit->second = askUserForMarathonTime();
                } while (askIfUserWantsTo("Edit another runner's time"));

                // Have to sort runners here as they are potentially out of
                // order due to editing.  This is a little annoying but it
                // seems consistent with std::map...
                std::sort(runners.begin(), runners.end());
                break;
            }
            case 4:
                std::cout << runners;
                break;

            case 5:
                saveRunnerData(runners, dataFile);
                std::cout << "Changes saved." << std::endl;
                break;

            case 6:
                quit = true;
                break;
            }

            std::cout << '\n' << std::endl;
        }

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cout << error.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cout << "Unhandled exception." << std::endl;
        return -1;
    }
}
