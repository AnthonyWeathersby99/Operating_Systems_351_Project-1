Name and Email:
-Anthony Weathersby
-Antdog_Indahouse@csu.fullerton.edu

Description of Contribution:
-Anthony Weathersby created all the code
Files to look at:
Part 1:
shellskel.cpp
Part 2:
serial.cpp
parallel.cpp

-I am familiar with all the functionality of the assignment

Program Language Used:
-C++

How to Execute Program:
For Part 1:
In terminal, input "./shell"

For Part 2:
In terminal, input  "time "./serial input.txt"     for the serial fetcher,  this will output 5 json files called serialfile#.json
In terminal, input  "time "./parallel input.txt"   for the parallel fetcher this will output 5 json files called parallelfile#.json

Execution Times for Both Fetchers:

Serial Time:
real    0m3.361s
user    0m0.353s
sys     0m0.039s

Parallel Time:
real    0m0.721s
user    0m0.474s
sys     0m0.012s

1. In the output of time, what is the difference between real, user, and sys times?

   Real time is the actual time it took for the program to run. Can be counted by a person.
   User time is the time spent by the CPU outside the kernel, which is the time spent running the code.
   Sys  time is the time spent by the CPU inside the kernel, which it spends executing system calls or operations.

2. Which is longer: user time or sys time? Use your knowledge to explain why.

   User time is longer because

3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you
think that is?



4. Suppose one of the fetcher children crashes. Will this affect other children? Explain.
What is your conclusion regarding the benefits or disadvantages of isolating each fetch
task within a different process?


Did not Implement Extra Credit
