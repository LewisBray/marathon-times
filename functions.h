#include "classes.h"

using namespace std;

int find_smallest(const vector<runner*>& runners, const int& index);
int find_runner_index(const vector<runner*>& runners, const string& key);
bool do_again(const string& phrase);
bool load_from_file(vector<runner*>& runners);
void save_to_file(const vector<runner*>& runners);
void sort_ascending(vector<runner*>& runners);
void get_time_from_user(int& mins, int& secs);
void swap_runners(vector<runner*>& runners, const int& index1, const int& index2);
void add_runners(vector<runner*>& runners);
void remove_runners(vector<runner*>& runners);
void edit_time(vector<runner*>& runners);
void display_runners(const vector<runner*>& runners);
