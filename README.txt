This program is for keeping track of personal best times for training for a
marathon, currently the program only holds the PB for one length of marathon (in
this case 5k) but it should be easily upgradeable in the future if necessary.

The program loads information from a binary file "runners.bin" and stores the
information in a vector of the runner class.  This vector is a member of a class
that looks after the runner database which allows the user to perform tasks
like: adding/removing runners; displaying a leader-board, etc...  The user is
also given the option to save any changes, the changes are written to the same
binary file "runners.bin".

The format of the file is as follows: the first 4 bytes stored is an int holding
the number of runners in the above-mentioned vector, this is for reading
purposes as the program then knows how many times to loop whilst reading.  Then
for each runner we store the length of their name, their name and their time
(given by two ints: minutes and seconds), any numbers mentioned are integers.
An example of the file format would be:

27runnerA37437runnerB3518

which would equate to 2 runners with info {runnerA, 37:43} and {runnerB, 35:18}.

Some things to add in the future are: give user ability to save to/load from
different files; keep track of any changes and ask if user wants to save if they
try to quit before saving; add 10k times, etc...  Also this should really be a
GUI application, could be good practice using the Win32 API/MFC.
