
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "classes.h"

#include <vector>


int FindSmallest(const std::vector<runner>& runners, const int index);
int FindRunnerIndex(const std::vector<runner>& runners, const std::string& key);
bool DoAgain(const std::string& phrase);
bool LoadRunners(std::vector<runner>& runners);
void SaveRunners(const std::vector<runner>& runners);
void SortAscending(std::vector<runner>& runners);
void GetTimeFromUser(int& mins, int& secs);
void SwapRunners(std::vector<runner>& runners, const int index1, const int index2);
void AddRunners(std::vector<runner>& runners);
void RemoveRunners(std::vector<runner>& runners);
void EditTime(std::vector<runner>& runners);
void DisplayRunners(const std::vector<runner>& runners);

#endif
