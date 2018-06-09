#include "database.h"


int MenuChoice();

int main()
{
    database timesDatabase;

    if (!timesDatabase.LoadFromFile()) {
        std::cerr << "Error reading runner data.  Exiting...";
        return -1;
    }

    std::cout << "PB running times program.\n\n";

    bool quit = false;
    while (!quit)
    {
        std::cout << "Menu:\n";
        std::cout << "1) Add new runner.\n";
        std::cout << "2) Remove runner.\n";
        std::cout << "3) Edit runner's personal best.\n";
        std::cout << "4) Show leader-board.\n";
        std::cout << "5) Save changes.\n";
        std::cout << "6) Exit.\n\n";

        int choice = MenuChoice();
        switch (choice)
        {
        case 1: timesDatabase.AddRunners();
                break;
        case 2: timesDatabase.RemoveRunners();
                break;
        case 3: timesDatabase.EditRunnerTimes();
                break;
        case 4: timesDatabase.ShowLeaderboard();
                break;
        case 5: timesDatabase.SaveToFile();
                break;
        case 6: quit = true;
                break;
        }
    }

    return 0;
}


int MenuChoice()
{
    int choice;
    while (true)
    {
        std::string choiceAsString;
        getline(std::cin, choiceAsString);
        choice = stoi(choiceAsString);

        if ((choice < 1) || (choice > 6))
            std::cout << "Not a valid choice.\n";
        else
            break;
    }

    return choice;
}
