/**                                                                                                                                                             
                                                                                                                                                                 
 * @Description: This is the main file that uese the event class and the priority queue class to form a simulation of a bank line.                                                                                        
                                                                                                                                                                 
 * @Name: Rylan Loukusa                                                                                                                                           
                                                                                                                                                              
 * @StadID: sq3572nq                                                                                                                                              
                                                                                                                                                                
 * @Due Date: Friday April 7th                                                                                                                                   
                                                                                                                                                                
																				
* @Instructor: Dr. Jie Hu Meichsner                                                                                                                              
                                                                                                                                                               
*/
#include "SL_PriorityQueue.h"
#include "LinkedQueue.h"
#include "event.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

bool tellerAvailable = 0;//To determine if departure event can happen
int currentTime = 0, departureTime = 0, customerNumber = 0;
float waitTime = 0; //Int to calculate wait time of arrival events
int processArrival(event &newEvent, SL_PriorityQueue<event>* eventListPtr, QueueInterface<event> *bankListPtr)
{
  //Remove this event from the event queue
  eventListPtr->remove();

  event customer = newEvent; 
  if(bankListPtr->isEmpty() && tellerAvailable) //Add departure event
    {
      departureTime = customer.getTime() + customer.getLength();
      eventListPtr->add(event('D',customer.getDepartureTime(),0));
      tellerAvailable = false;
    }
  else
    bankListPtr->enqueue(customer); //Add event

  cout << "Processing an arrival event at time:  " << currentTime << endl;
}

int processDeparture(event &newEvent, SL_PriorityQueue<event>* eventListPtr, QueueInterface<event> *bankListPtr)
{
  event newDepartureEvent = event('D',departureTime, 0);
  //Remove this event from the event queue
  eventListPtr->remove();

  if(!bankListPtr->isEmpty())
    {
      //Customer at front of line begins transaction
      event customer = bankListPtr->peekFront();
      bankListPtr->dequeue();
      departureTime =  currentTime + customer.getLength();
      newDepartureEvent = event('D', departureTime, 0);
      eventListPtr->add(newDepartureEvent);
      waitTime += currentTime - customer.getTime(); 
    }
  else
    tellerAvailable = true;

  cout << "Processing a departure event at time: " << currentTime << endl;
}

float solve(float number, int place) //Function to round down time variable
{
  cout << fixed;
  cout << setprecision(place);
  return number;
}

int main()
{
  ifstream infile;

  SL_PriorityQueue<event> * eventListPtr = new SL_PriorityQueue<event>(); //Priority Queue
  QueueInterface<event> * bankListPtr = new LinkedQueue<event>(); //Bank Queue

  tellerAvailable = true;

  //open file here
  char inputFile[12];
  cout << "Enter input file name: ";
  cin >> inputFile;
  infile.open(inputFile);
  cout << "1" << endl;
  //Create and add arrival events to event queue
  int t,l;
  while(infile >> t && infile >> l)
    {
      char ch = 'A';
      eventListPtr->add(event(ch,t,l)); //adding all arivial events to priority queue
      customerNumber++;
    }
  infile.close();
  //Event Loop
  while(!eventListPtr->isEmpty())//execturing priority queue
    {
      event newEvent = eventListPtr->peek();//getting next event
      currentTime = newEvent.getTime();//setting time
      if(newEvent.getType() == 'A')
	processArrival(newEvent, eventListPtr, bankListPtr);
      else if(newEvent.getType() == 'D')
	processDeparture(newEvent, eventListPtr, bankListPtr);
    }
  cout << "Final Statistics: " << endl;
  cout <<"   Total number of custmers processed: " << customerNumber << endl;
  float AvgWaitTime = waitTime / customerNumber; 
  cout <<"   Average amount of time spent waiting: " << solve(AvgWaitTime, 2) << endl;
}
