# bankLine
Project7 - CSCI 301

This program uses an ADT Queue to simulate a line at a bank. It first forms the line, as the inputs enter from the back. The inputs exit from the front as they are helped at the bank. As these events happen in order they are added to the priority queue to be executed first.

The programs name is eventQueue.cpp and it is  located at the following directory on CentOS:

/home/STCLOUDSTATE/sq3572nq/Labs/lab9/project7

To compile and link it simply enter:

g++ eventQueue.cpp

To run the program simply enter:

./a.out


The main data structure of this project is the event. The event consists of a char to indicate if it is an arrival event or a departure event. 
The event also contains the time at which this happened and the length the event took. 
These events are inserted into a Linked Queue and then added to and removed from a priority queue as the events happen.

]0;sq3572nq@csci4:~/Labs/lab9/project7[?1034h[sq3572nq@csci4 project7]$ cou[K[K[Kcat testFile.txt
1 5
2 5
4 5
20 5
22 5
24 5
26 5
28 5
30 5
88 3



testScript.txt:

g++ eventQueue.txt
./a.out

Enter input file name: testFile.txt
1
Processing an arrival event at time:  1
Processing an arrival event at time:  2
Processing an arrival event at time:  4
Processing a departure event at time: 6
Processing a departure event at time: 11
Processing a departure event at time: 16
Processing an arrival event at time:  20
Processing an arrival event at time:  22
Processing an arrival event at time:  24
Processing a departure event at time: 25
Processing an arrival event at time:  26
Processing an arrival event at time:  28
Processing an arrival event at time:  30
Processing a departure event at time: 30
Processing a departure event at time: 35
Processing a departure event at time: 40
Processing a departure event at time: 45
Processing a departure event at time: 50
Processing an arrival event at time:  88
Processing a departure event at time: 91
Final Statistics: 
   Total number of custmers processed: 10
   Average amount of time spent waiting: 5.60
exit
