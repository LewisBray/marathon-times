// Contains the function declaration for interfacing with the user.

#ifndef __UI_H__
#define __UI_H__

#include "runners.h"

#include <string>

enum class MenuChoice
{
    AddRunners = 1,
    RemoveRunners = 2,
    EditRunners = 3,
    ShowRunners = 4,
    SaveData = 5,
    Quit = 6
};

void displayMenu();
MenuChoice askUserForMenuChoice();
MarathonTime askUserForMarathonTime();
bool askIfUserWantsTo(const std::string& phrase);

Runner askUserForRunnerToAdd(const Runners& runners);
Runners::iterator askUserForRunnerToEdit(Runners& runners);
Runners::const_iterator askUserForRunnerToRemove(const Runners& runners);

#endif
