/**                                                                                                                                                             
                                                                                                                                                               
* @Description: This is the implementation file for the event class
																			
* @Name: Rylan Loukusa                                                                                                                                         
    																				* @StadID: sq3572nq                                                                                                                                            
																				* @Due Date: Sunday March 26th                                                                                                                                 
                                                                                                                                                          	* @Instructor: Dr. Jie Hu Meichsner                                                                                                                            
                                                                                              
                                                  		*/
using namespace std;
#include <iostream>
#ifndef EVENT
#define EVENT

class event
{
 private:
  
  char type;
  int time;
  int length;

 public:
  event(char ch, int t, int l)
    {
      type = ch;
      time = t;
      length = l;
    }

  void setTime(int t)
  {
    time = t;
  }

  int setLength(int l)
  {
    length = l;
  }

  int setType(char ch)
  {
    type = ch;
  }
  int getTime()
  {
    return time;
  }

  int getLength()
  {
    return length;
  }
  int getType()
  {
    return type;
  }
  int getDepartureTime()
  {
    return time + length;
  }

  friend istream& operator >>(istream& ins, event& target)
  {
    ins >> target.time
        >> target.length;
    return ins;
  }

  friend ostream& operator <<(ostream& outs, event target)
  {
    outs << "Processing an arrival event at time: "
         << target.time;
    return outs;
  }

}; //end event class                                                           

  //nonmember                                                                                                                                                    
bool operator >(event a1, event a2)
{
  if(a1.getTime() < a2.getTime())
    return true;
  else
    return false;
}

bool operator <(event a1, event a2)
{
  if(a1.getTime() > a2.getTime())
    return true;
  else
    return false;
}

bool operator == (event a1, event a2)
{
  if(a1.getTime() ==  a2.getTime())
    return true;
  else
    return false;
}

bool operator != (event a1, event a2)
{
  if(a1.getTime() !=  a2.getTime())
    return true;
  else
    return false;
}

#endif
