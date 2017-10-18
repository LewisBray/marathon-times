This program is for keeping track of personal best times for training for a marathon, currently the program only holds the PB for one length of marathon (in this case 5k) but it should be easily upgradeable in the future if necessary.

The program loads information from a binary file "runners.bin" and stores the information in a vector of pointers to a class called 'runner'.  the 'runner' class has two data fields, storing the name and PB of a runner as well as standard 'set' and 'get' functions.

Once loaded the user can perform a few tasks such as adding/removing runners, displaying a leader-board, etc...  The user is also given the option to save any changes, the changes are written to the same binary file "runners.bin".  The format of the file is as follows: the first thing stored is the number of runners in the above-mentioned vector, this is for reading purposes as the program then knows how many times to loop whilst reading.  Then for each runner we store the length of their name, their name and their time (given by two numbers: minutes and seconds), any numbers mentioned are integers.  An example of the file format would be:

27runnerA37437runnerB3518

which would equate to 2 runners with info {runnerA, 37:43} and {runnerB, 35:18}.