#include "functions.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>


int FindSmallest(const std::vector<runner>& runners, const int index)
{
    int smallest = index;

    int numRunners = (int)runners.size();
    for (int i = index + 1; i < numRunners; i++)
    {
        if(runners[i].GetMins() < runners[smallest].GetMins()){smallest = i;}
        else if(runners[i].GetMins() == runners[smallest].GetMins())//If runners have same minutes then check seconds
        {
            if(runners[i].GetSecs() < runners[smallest].GetSecs()){smallest = i;}
            else if(runners[i].GetSecs() == runners[smallest].GetSecs())//If runners have same minutes and seconds
            {                                                               //then arrange alphabetically
                if(runners[i].GetName() < runners[smallest].GetName()){smallest = i;}
            }
        }
    }

    return smallest;
}

int FindRunnerIndex(const std::vector<runner>& runners, const std::string& key)
{
    int last = runners.size();

    for(int i = 0; i < last; i++)
    {
        if(runners[i].GetName() == key){return i;}
    }

    return -1;
}

bool DoAgain(const std::string& phrase)
{
    while (true)
    {
        printf("%s? -> (Y/N): ", phrase.c_str());
        char choice;
        std::cin >> choice;

        if ((choice == 'Y') || (choice == 'y'))
            return true;
        else if ((choice == 'N') || (choice == 'n'))
            return false;
        else
            std::cout << "Invalid input.  ";
    }
}

bool LoadRunners(std::vector<runner>& runners)
{
    std::ifstream ifile("runners.bin", std::ios::binary);

    if (!ifile.is_open()) {
        std::cout << "Error opening file.  Exiting...";
        return false;
    }

    ifile.seekg(0, std::ios::beg);

    int numRunners;
    if (!ifile.read(reinterpret_cast<char*>(&numRunners), sizeof(numRunners))) {
        std::cout << "Error reading number of entries from file.  Exiting...";
        return false;
    }

    for (int i = 0; i < numRunners; ++i)
    {
        int nameLength;
        if (!ifile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) {
            printf("Error reading entry %d's name length from file.  Exiting...", i);
            return false;
        }

        if ((nameLength <= 0) || (nameLength > 100)) {
            printf("Entry %d 's name length is outside of the range [0, 100].  Exiting...", i);
            return false;
        }

        std::unique_ptr<char[]> stringBuffer = std::make_unique<char[]>(nameLength + 1);

        if (!ifile.read(stringBuffer.get(), nameLength + 1)) {
            printf("Error reading entry %d's string from file.  Exiting...", i);
            return false;
        }

        if (stringBuffer[nameLength] != '\0')
            stringBuffer[nameLength] = '\0';

        std::string name{stringBuffer.get()};
        
        int mins;
        if (!ifile.read(reinterpret_cast<char*>(&mins), sizeof(mins))) {
            printf("Error reading entry %d's minutes from file.  Exiting...", i);
            return false;
        }

        int secs;
        if (!ifile.read(reinterpret_cast<char*>(&secs), sizeof(secs))) {
            printf("Error reading entry %d's seconds from file.  Exiting...", i);
            return false;
        }

        runners.emplace_back(name, time{ mins, secs });
    }

    return true;
}

void SaveRunners(const std::vector<runner>& runners)
{
    std::ofstream ofile("runners.bin", std::ios::trunc | std::ios::binary);

    if (!ofile.is_open()) {
        std::cout << "Error opening file.";
        return;
    }

    ofile.seekp(0, std::ios::beg);

    int numRunners = runners.size();
    ofile.write(reinterpret_cast<char*>(&numRunners), sizeof(numRunners));

    for (int i = 0; i < numRunners; ++i)
    {
        int nameLength = runners[i].GetName().length();
        int mins = runners[i].GetMins();
        int secs = runners[i].GetSecs();

        ofile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        ofile.write(runners[i].GetName().c_str(), nameLength + 1);
        ofile.write(reinterpret_cast<char*>(&mins), sizeof(mins));
        ofile.write(reinterpret_cast<char*>(&secs), sizeof(secs));
    }

    std::cout << "\nChanges saved.\n\n";
}

void SortAscending(std::vector<runner>& runners)
{
    const int numRunners = runners.size();
    for (int i = 0; i < numRunners - 1; ++i)
        SwapRunners(runners, i, FindSmallest(runners, i));
}

void GetTimeFromUser(int& mins, int& secs)
{
    while (true)
    {
        std::cout << "Enter minutes: ";
        std::cin >> mins;

        if ((mins < 0) || (mins >= 60))
            std::cout << "That's not a valid number of minutes.  ";
        else
            break;
    }

    while (true)
    {
        std::cout << "Enter seconds: ";
        std::cin >> secs;

        if ((secs < 0) || (secs >= 60))
            std::cout << "That's not a valid number of seconds.  ";
        else
            break;
    }
}

void SwapRunners(std::vector<runner>& runners, const int index1, const int index2)
{
    runner* temp = &runners[index1];
    runners[index1] = runners[index2];
    runners[index2] = *temp;
}

void AddRunners(std::vector<runner>& runners)
{
    while (true)
    {
        std::string newName;
        std::cout << "Enter name: ";
        getline(std::cin, newName);

        int mins, secs;
        GetTimeFromUser(mins, secs);

        runners.emplace_back(newName, time{ mins, secs });

        if (!DoAgain("Add another runner"))
            break;
    }

    if (runners.size() > 1)
        SortAscending(runners);

    std::cout << "\n\n";
}

void RemoveRunners(std::vector<runner>& runners)
{
    if (runners.empty()) {
        std::cout << "There are no runners left to remove!!!";
        return;
    }

    while (true)
    {
        int index;
        while (true)
        {
            std::string nameToRemove;
            std::cout << "Enter name of runner to remove: ";
            getline(std::cin, nameToRemove);

            index = FindRunnerIndex(runners, nameToRemove);

            if (index == -1)
                std::wcout << "That runner doesn't exist!\n";
            else
                break;
        }

        runners.erase(runners.begin() + index);

        if (runners.empty()) {
            std::cout << "There are no runners left to remove.";
            break;
        }

        if (!DoAgain("Remove another runner"))
            break;
    }

    std::cout << "\n\n";
}

void EditTime(std::vector<runner>& runners)
{
    if (runners.empty()) {
        std::cout << "There are no runners to edit!!!";
        return;
    }

    while (true)
    {
        std::string nameToEdit;
        int index;

        while (true)
        {
            std::cout << "Enter name of runner whose time you want to edit: ";
            getline(std::cin, nameToEdit);

            index = FindRunnerIndex(runners, nameToEdit);

            if (index == -1)
                std::cout << "That runner doesn't exist!\n";
            else
                break;
        }

        int mins, secs;
        GetTimeFromUser(mins, secs);

        runners[index].SetTime(mins, secs);

        if (!DoAgain("Edit another runner's time"))
            break;
    }

    if (runners.size() > 1)
        SortAscending(runners);

    std::cout << "\n\n";
}

void DisplayRunners(const std::vector<runner>& runners)
//Prints out the list of runners and their times in a pre-defined format
{
    std::cout << "\n5k times:\n\n";

    for (int i = 0, numRunners = runners.size(); i < numRunners; i++)
    {
        printf("  %d) ", i + 1);
        runners[i].DisplayRunner();
        std::cout << "\n";
    }

    std::cout << "\n\n";
}
