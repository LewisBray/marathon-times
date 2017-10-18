using namespace std;

struct time//It isn't necessary to define this structure, I just thought it made the code more readable and allows the possibility
{          //to add in extra categories in the future, e.g. 10k times
    int mins;
    int secs;
};

class runner//Class containing the name and time(s) for each runner as well as standard functions
{
    public:
        string get_name();
        int get_mins();
        int get_secs();
        void set_name(const string& input);
        void set_time(const int& m, const int& s);
        void display_runner();

    private:
        string name;
        time time5k;
};
