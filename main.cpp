// The main entry point of the application, responsible for loading
// the database of runners and handling the UI logic.

#include "runners.h"
#include "ui.h"

#include <algorithm>
#include <iostream>

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

            const MenuChoice userChoice = askUserForMenuChoice();
            switch (userChoice)
            {
            case MenuChoice::AddRunners:
            {
                do
                {
                    const Runner newRunner = askUserForRunnerToAdd(runners);
                    runners.insert(newRunner);
                } while (askIfUserWantsTo("Add another runner"));

                break;
            }

            case MenuChoice::RemoveRunners:
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

            case MenuChoice::EditRunners:
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

                // Have to sort runners here as they are potentially
                // out of order due to editing.  This is a little
                // annoying but it seems consistent with std::map...
                runners.sort();
                break;
            }

            case MenuChoice::ShowRunners:
                std::cout << runners;
                break;

            case MenuChoice::SaveData:
                saveRunnerData(runners, dataFile);
                std::cout << "Changes saved." << std::endl;
                break;

            case MenuChoice::Quit:
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
