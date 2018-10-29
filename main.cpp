#include "database.h"

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
        std::string choiceAsString;
        std::getline(std::cin, choiceAsString);
        const int choice = std::stoi(choiceAsString);

        if (choice < 1 || choice > 6)
            std::cout << "Not a valid choice." << std::endl;
        else
            return choice;
    }
}

int main()
{
    Database runnerDatabase;

    if (!runnerDatabase.loadFromFile()) {
        std::cerr << "Error reading runner data.  Exiting...";
        return -1;
    }

    std::cout << "PB running times program.\n" << std::endl;

    bool quit = false;
    while (!quit)
    {
        displayMenu();

        const int userChoice = askUserForMenuChoice();
        switch (userChoice)
        {
        case 1: runnerDatabase.addRunners();
                break;
        case 2: runnerDatabase.removeRunners();
                break;
        case 3: runnerDatabase.editRunnerTimes();
                break;
        case 4: std::cout << runnerDatabase;
                break;
        case 5: runnerDatabase.saveToFile();
                break;
        case 6: quit = true;
                break;
        }
    }

    return 0;
}
