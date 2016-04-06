# QuashProject No. 1: Quite a Shell (quash)
Submission due: Feb. 29, 2016

GRADING POLICY
Partial credits will be given for incomplete efforts. However, a program that cannot compile will
get 0 points. Point breakdown for features is below:
1. Run executables without arguments (5)
2. Run executables with arguments (5)
3. set for HOME and PATH work properly (5)
4. exit and quit work properly (5)
5. cd (with and without arguments) and pwd works properly (5)
6. PATH works properly. Give error messages when the executable is not found (10)
7. Child process inheritance (inherit environment variable) (10)
8. Allow background/foreground execution (&) (5)
9. Printing/reporting of background processes, (including the jobs command) (10)
10. Allow file redirection (> and <) (10)
11. Allow (1) pipe (|) (10)
12. Report (10)
13. Bonus points
a. Support multiple pipes in one command. (10)
$ ls | wc | more
b. kill command delivers signals to background processes. The kill command has
the format: killSIGNUMJOBID, where SIGNUM is an integer specifying the
signal number, and JOBID is an integer that specifies the job that should receive
the signal. (5)

