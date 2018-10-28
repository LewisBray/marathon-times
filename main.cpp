#include "database.h"

#include <iostream>

static void displayMenu()
{
    std::cout << "Menu:" << std::endl
        << "1) Add new runner." << std::endl
        << "2) Remove runner." << std::endl
        << "3) Edit runner's personal best." << std::endl
        << "4) Show leader-board." << std::endl
        << "5) Save changes." << std::endl
        << "6) Exit." << std::endl << std::endl;
}

static int askUserForMenuChoice()
{
    while (true)
    {
        std::string choiceAsString;
        std::getline(std::cin, choiceAsString);
        const int choice = stoi(choiceAsString);

        if (choice < 1 || choice > 6)
            std::cout << "Not a valid choice.\n";
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

    std::cout << "PB running times program." << std::endl << std::endl;

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
