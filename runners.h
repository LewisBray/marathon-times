// Contains the function declaration for interfacing with the user
// and manipulating the runner database.  The database of runners
// is simply a map between the runners and their times where the
// map is ordered with respect to the values (marathon times) and
// not the keys (runner names).

#ifndef __RUNNERS_H__
#define __RUNNERS_H__

#include "value_ordered_map.hpp"
#include "marathontime.h"

#include <ostream>
#include <string>

std::string getStringFromUser();
MarathonTime askUserForMarathonTime();
bool askIfUserWantsTo(const std::string& phrase);

using Runners = value_ordered_map<std::string, MarathonTime>;
using Runner = Runners::value_type;

Runner askUserForRunnerToAdd(const Runners& runners);
Runners::iterator askUserForRunnerToEdit(Runners& runners);
Runners::const_iterator askUserForRunnerToRemove(const Runners& runners);

std::ostream& operator<<(std::ostream& out, const Runners& runners);

Runners loadRunnerData(const std::string& file);
void saveRunnerData(const Runners& runners, const std::string& file);

#endif
