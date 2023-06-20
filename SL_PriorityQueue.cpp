//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
/** ADT priority queue: ADT sorted list implementation.
    @file SL_PriorityQueue.cpp */
 
#include "SL_PriorityQueue.h"  // Header file

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue()
{
  slistPtr = new LinkedSortedList<ItemType>();
}  // end default constructor

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue(const SL_PriorityQueue<ItemType>& pq)
{
  // First, create our own sorted list
  slistPtr = new LinkedSortedList<ItemType>();
  
  // Then add items to it using public methods
  for (int position = 1; position <= pq.slistPtr->getLength(); position++)
    {
      slistPtr->insertSorted(pq.slistPtr->getEntry(position));
    }  // end for
}  // end copy constructor

/*another implementation
  template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue(const SL_PriorityQueue& pq)
{
slistPtr = new LinkedSortedList(*(pq.slistPtr));
  // end for
}  // end copy constructor
*/

template<class ItemType>
SL_PriorityQueue<ItemType>::~SL_PriorityQueue()
{
}  // end destructor

template<class ItemType>
bool SL_PriorityQueue<ItemType>::isEmpty() const
{
  return slistPtr->isEmpty();
}  // end isEmpty

template<class ItemType>
bool SL_PriorityQueue<ItemType>::add(const ItemType& newEntry)
{ 
  slistPtr->insertSorted(newEntry);
  return true;
}  // end add

template<class ItemType>
bool SL_PriorityQueue<ItemType>::remove()
{
  // The highest priority item is at the end of the sorted list
  return slistPtr->remove(slistPtr->getLength());
}  // end remove
   
template<class ItemType>
ItemType SL_PriorityQueue<ItemType>::peek() const throw(PrecondViolatedExcep)
{
  if (isEmpty())
    throw PrecondViolatedExcep("peekFront() called with empty queue.");
   
  // Priority queue is not empty; return highest priority item;
  // it is at the end of the sorted list
  return slistPtr->getEntry(slistPtr->getLength());
}  // end peek


