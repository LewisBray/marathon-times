#include <iostream>
#include <vector>

#include "functions.h"

using namespace std;

int main()
{
    vector<runner*> runners;

    if(!load_from_file(runners)){return 1;}

    sort_ascending(runners);


    cout << "PB running times program." << endl << endl;

    bool quit = false;

    while(!quit)
    {
        int choice;

        cout << "Menu:" << endl;
        cout << "1) Add new runner." << endl;
        cout << "2) Remove runner." << endl;
        cout << "3) Update runner's personal best." << endl;
        cout << "4) Show leader-board." << endl;
        cout << "5) Save changes." << endl;
        cout << "6) Exit." << endl << endl;

        while(1)
        {
            cin >> choice;

            if(choice < 1 || choice > 6)
            {
                cout << "Not a valid choice." << endl;
            }
            else{break;}
        }

        switch(choice)
        {
            case 1: add_runners(runners);
                    break;
            case 2: remove_runners(runners);
                    break;
            case 3: edit_time(runners);
                    break;
            case 4: display_runners(runners);
                    break;
            case 5: save_to_file(runners);
                    break;
            case 6: quit = true;
                    break;
        }
    }

    for(int i = 0; i < runners.size(); i++){delete runners[i];}

    return 0;
}
