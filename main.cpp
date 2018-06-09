#include "functions.h"

#include <iostream>
#include <vector>


int main()
{
    std::vector<runner> runners;
    if (!LoadRunners(runners))
        return -1;

    SortAscending(runners);

    std::cout << "PB running times program.\n\n";

    bool quit = false;
    while (!quit)
    {
        std::cout << "Menu:\n";
        std::cout << "1) Add new runner.\n";
        std::cout << "2) Remove runner.\n";
        std::cout << "3) Update runner's personal best.\n";
        std::cout << "4) Show leader-board.\n";
        std::cout << "5) Save changes.\n";
        std::cout << "6) Exit.\n\n";

        int choice;
        while (true)
        {
            std::cin >> choice;

            if ((choice < 1) || (choice > 6))
                std::cout << "Not a valid choice.\n";
            else
                break;
        }

        switch (choice)
        {
            case 1: AddRunners(runners);
                    break;
            case 2: RemoveRunners(runners);
                    break;
            case 3: EditTime(runners);
                    break;
            case 4: DisplayRunners(runners);
                    break;
            case 5: SaveRunners(runners);
                    break;
            case 6: quit = true;
                    break;
        }
    }

    return 0;
}
