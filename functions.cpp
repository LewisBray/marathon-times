#include <iostream>
#include <fstream>
#include <vector>

#include "functions.h"

using namespace std;

int find_smallest(const vector<runner*>& runners, const int& index)
//Finds the index of the smallest entry in the vector, sorts by minutes then seconds then by name
{
    int smallest = index;

    for(int i = index + 1; i < runners.size(); i++)
    {
        if(runners[i]->get_mins() < runners[smallest]->get_mins()){smallest = i;}
        else if(runners[i]->get_mins() == runners[smallest]->get_mins())//If runners have same minutes then check seconds
        {
            if(runners[i]->get_secs() < runners[smallest]->get_secs()){smallest = i;}
            else if(runners[i]->get_secs() == runners[smallest]->get_secs())//If runners have same minutes and seconds
            {                                                               //then arrange alphabetically
                if(runners[i]->get_name() < runners[smallest]->get_name()){smallest = i;}
            }
        }
    }

    return smallest;
}

int find_runner_index(const vector<runner*>& runners, const string& key)
//Returns the integer index for the runner with name = key, returns -1 if the runner is not an element of the list
{
    int last = runners.size();

    for(int i = 0; i < last; i++)
    {
        if(runners[i]->get_name() == key){return i;}
    }

    return -1;
}

bool do_again(const string& phrase)
//Prompts the user if they would like to repeat the action chosen in the menu, returns true if they do
{
    char choice;

    while(1)
    {
        cout << phrase;//Phrase goes here to customise the interaction with the user and makes the code reusable
        cout << "? -> (Y/N): ";
        cin >> choice;

        if(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        {
            cout << "Invalid input.  ";
        }
        else if(choice == 'N' || choice == 'n'){return false;}
        else{return true;}
    }
}

bool load_from_file(vector<runner*>& runners)
//Opens up runners.bin and extracts runner names and times, returns true unless any errors are encountered
{
    ifstream ifile("runners.bin", ios::binary);

    if(!ifile.is_open())
    {
        cout << "Error opening file.  Exiting...";
        return false;
    }

    ifile.seekg(0, ios::beg);//Start reading from beginning of file

    int no_of_runners;//Finds the number of entries first to see how many times it needs to loop and read entries

    if(!ifile.read(reinterpret_cast<char*>(&no_of_runners), sizeof(no_of_runners)))
    {
        cout << "Error reading number of entries from file.  Exiting...";
        return false;
    }

    if(no_of_runners > 0)//If no_of_runners = 0 then no need to extract any info
    {
        for(int i = 0; i < no_of_runners; i++)
        {
            int name_length, mins, secs;
            string key;

            if(!ifile.read(reinterpret_cast<char*>(&name_length), sizeof(name_length)))
            {
                cout << "Error reading entry " << i << "'s name length from file.  Exiting...";
                return false;
            }

            if(name_length > 0 && name_length < 100)//Makes sure we aren't allocating too much memory, no name should be
            {                                       //over 100 characters
                char* p_str_buf = new char[name_length + 1];//+ 1 for null character which terminates string

                if(!ifile.read(p_str_buf, name_length + 1))
                {
                    delete[] p_str_buf;
                    cout << "Error reading entry " << i << "'s string from file.  Exiting...";
                    return false;
                }

                if(p_str_buf[name_length] == 0)//Makes sure string is null-terminated
                {
                    key = string(p_str_buf);
                }
                else
                {
                    delete[] p_str_buf;
                    cout << "Entry " << i << "'s name string is not null-terminated.  Exiting...";
                    return false;
                }

                delete[] p_str_buf;
            }
            else
            {
                cout << "Entry " << i << "'s name length is outside of the range [0, 100].  Exiting...";
                return false;
            }

            if(!ifile.read(reinterpret_cast<char*>(&mins), sizeof(mins)))
            {
                cout << "Error reading entry " << i << "'s minutes from file.  Exiting...";
                return false;
            }

            if(!ifile.read(reinterpret_cast<char*>(&secs), sizeof(secs)))
            {
                cout << "Error reading entry " << i << "'s seconds from file.  Exiting...";
                return false;
            }

            runners.push_back(new runner);//Allocate memory for runner data and set data fields in runner class
            runners[i]->set_name(key);
            runners[i]->set_time(mins, secs);
        }
    }

    return true;
}

void save_to_file(const vector<runner*>& runners)
//Opens runners.bin, deletes the data then writes the data stored in our vector to the file
{
    ofstream ofile("runners.bin", ios::trunc | ios::binary);

    if(!ofile.is_open())
    {
        cout << "Error opening file.";
        return;
    }

    ofile.seekp(0, ios::beg);//Seek to beginning of file to write

    int no_of_runners = runners.size();//First datum saved is number of runners for reading purposes

    ofile.write(reinterpret_cast<char*>(&no_of_runners), sizeof(no_of_runners));

    for(int i = 0; i < no_of_runners; i++)
    {
        int name_length = runners[i]->get_name().length(), mins = runners[i]->get_mins(), secs = runners[i]->get_secs();

        ofile.write(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        ofile.write(runners[i]->get_name().c_str(), name_length + 1);
        ofile.write(reinterpret_cast<char*>(&mins), sizeof(mins));
        ofile.write(reinterpret_cast<char*>(&secs), sizeof(secs));
    }

    cout << endl << "Changes saved." << endl << endl;
}

void sort_ascending(vector<runner*>& runners)
//Goes through the vector from the start and swaps the current element with the smallest in the remainder of the vector
{
    for(int i = 0; i < runners.size() - 1; i++)
    {
        swap_runners(runners, i, find_smallest(runners, i));
    }
}

void get_time_from_user(int& mins, int& secs)
//Makes sure the time input by the user is in the range [0, 59] since we are dealing with times
{
    while(1)
    {
        cout << "Enter minutes: ";
        cin >> mins;

        if(mins < 0 || mins >= 60){cout << "That's not a valid number of minutes.  ";}
        else{break;}
    }

    while(1)
    {
        cout << "Enter seconds: ";
        cin >> secs;

        if(secs < 0 || secs >= 60){cout << "That's not a valid number of seconds.  ";}
        else{break;}
    }
}

void swap_runners(vector<runner*>& runners, const int& index1, const int& index2)
{
    runner* p_temp = runners[index1];
    runners[index1] = runners[index2];
    runners[index2] = p_temp;
}

void add_runners(vector<runner*>& runners)
//Takes in information for a new runner and allocates new memory for it, loops until user does not want to add more
{
    bool add_more = true;

    while(add_more)
    {
        string new_name;
        int m, s;

        cin.get();//Having error whilst running, where after selecting an option at the main menu the following getline function
                  //is being called prematurely, so added this in as a buffer, similar in other functions
        cout << "Enter name: ";
        getline(cin, new_name);

        get_time_from_user(m, s);

        runners.push_back(new runner);
        runners[runners.size() - 1]->set_name(new_name);
        runners[runners.size() - 1]->set_time(m, s);

        if(!do_again("Add another runner")){add_more = false;}
    }

    if(runners.size() > 1){sort_ascending(runners);}//After being added the list is sorted to make sure it's in the correct place

    cout << endl << endl;
}

void remove_runners(vector<runner*>& runners)
//Takes in a runner's name and removes them from the list, loops until the user no longer wants to remove any or list size is 0
{
    bool remove_more = true;

    if(runners.size() == 0)//Insures function doesn't run if there are no entries to remove
    {
        cout << "There are no runners left to remove!!!";
        remove_more = false;
    }

    while(remove_more)
    {
        string name_to_remove;
        int index;

        cin.get();

        while(1)
        {
            cout << "Enter name of runner to remove: ";
            getline(cin, name_to_remove);

            index = find_runner_index(runners, name_to_remove);

            if(index == -1){cout << "That runner doesn't exist!" << endl;}
            else{break;}
        }

        delete runners[index];//Frees up memory pointed to by the entry about to be removed

        runners[index] = NULL;//Sets the pointer to NULL to avoid any errors in rest of run-time

        runners.erase(runners.begin() + index);

        if(runners.size() == 0)//Doesn't give option to remove more if there aren't any to remove
        {
            cout << "There are no runners left to remove.";
            break;
        }

        if(!do_again("Remove another runner")){remove_more = false;}
    }

    cout << endl << endl;
}

void edit_time(vector<runner*>& runners)
//Takes in a runner's name and allows the user to update the runner's time
{
    bool edit_more = true;

    if(runners.size() == 0)//Makes sure there are entries to edit
    {
        cout << "There are no runners to edit!!!";
        edit_more = false;
    }

    while(edit_more)
    {
        string name_to_edit;
        int index, m, s;

        cin.get();

        while(1)
        {
            cout << "Enter name of runner whose time you want to edit: ";
            getline(cin, name_to_edit);

            index = find_runner_index(runners, name_to_edit);

            if(index == -1){cout << "That runner doesn't exist!" << endl;}
            else{break;}
        }

        get_time_from_user(m, s);

        runners[index]->set_time(m, s);

        if(!do_again("Edit another runner's time")){edit_more = false;}
    }

    if(runners.size() > 1){sort_ascending(runners);}//Times have been updated so this can change the rankings

    cout << endl << endl;
}

void display_runners(const vector<runner*>& runners)
//Prints out the list of runners and their times in a pre-defined format
{
    cout << endl << "5k times:" << endl << endl;

    for(int i = 0; i < runners.size(); i++)
    {
        cout << "  " << i + 1 << ") ";
        runners[i]->display_runner();
        cout << endl;
    }

    cout << endl << endl;
}
