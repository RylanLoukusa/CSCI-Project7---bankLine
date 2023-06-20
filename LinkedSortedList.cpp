//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedSortedList.
    @file LinkedSortedList.cpp */

#include "LinkedSortedList.h"  // Header file
#include <cassert>
#include <string>
  
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : headPtr(NULL), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
  headPtr = copyChain(aList.headPtr);
  itemCount = aList.itemCount;
}  // end copy constructor

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr)
{
  Node<ItemType>* copiedChainPtr = NULL;
  if (origChainPtr != NULL)
    {
      // Build new chain from given one
      copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
      copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
    }  // end if
   
  return copiedChainPtr;
}  // end copyChain

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
  clear();
}  // end destructor

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
  Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
  Node<ItemType>* prevPtr = getNodeBefore(newEntry);
   
  if (isEmpty() || (prevPtr == NULL)) // Add at beginning
    {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
    }
  else // Add after node before
    {
      Node<ItemType>* aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
    } // end if
   
  itemCount++;
} // end insertSorted

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
  bool ableToDelete = false;
  if (!isEmpty())
    {
      Node<ItemType>* nodeToRemovePtr = headPtr;
      Node<ItemType>* prevPtr = getNodeBefore(anEntry);
      if (prevPtr != NULL)
	nodeToRemovePtr = prevPtr->getNext();
       
      ableToDelete = (nodeToRemovePtr != NULL) && 
	(anEntry == nodeToRemovePtr->getItem());
      if (ableToDelete)
	{
	  Node<ItemType>* aftPtr = nodeToRemovePtr->getNext();
	  if (nodeToRemovePtr == headPtr)
	    {
	      // Delete the first node in the chain
	      headPtr = aftPtr;
	    }
	  else
	    {
         
	      // Disconnect indicated node from chain by connecting the
	      // prior node with the one after
	      prevPtr->setNext(aftPtr);
	    }  // end if
         
	  // Return deleted node to system
	  nodeToRemovePtr->setNext(NULL);
	  delete nodeToRemovePtr;
	  nodeToRemovePtr = NULL;
         
	  itemCount--;  // Decrease count of entries
	}  // end if
    }  // end if

  return ableToDelete;
}  // end removeSorted

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
  int position = 1;
  Node<ItemType>* curPtr = headPtr;
   
  while ( (curPtr != NULL) && (anEntry > curPtr->getItem()) )
    {
      curPtr = curPtr->getNext();
      position++;
    } // end while
   
  if ( (curPtr == NULL) || (anEntry != curPtr->getItem()) )
    position = -position;
   
  return position;
}  // end getPosition

//=====================
// List operations:

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
{
  bool ableToDelete = (position >= 1) && (position <= itemCount);
  if (ableToDelete)
    {
      Node<ItemType>* curPtr = NULL;
      if (position == 1)
	{
	  // Delete the first node in the chain
	  curPtr = headPtr; // save pointer to node
	  headPtr = headPtr->getNext();
	}
      else
	{
	  // Find node that is before the one to delete
	  Node<ItemType>* prevPtr = getNodeAt(position - 1);
         
	  // Point to node to delete
	  curPtr = prevPtr->getNext();
         
	  // Disconnect indicated node from chain by connecting the
	  // prior node with the one after
	  prevPtr->setNext(curPtr->getNext());
	}  // end if
      
      // Return deleted node to system
      curPtr->setNext(NULL);
      delete curPtr;
      curPtr = NULL;
      
      itemCount--;  // Decrease count of entries
    }  // end if
   
  return ableToDelete;
}  // end remove

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
{
  while (!isEmpty())
    remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
  // Enforce precondition
  bool ableToGet = (position >= 1) && (position <= itemCount);
  if (ableToGet)
    {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
    }
  else
    {
      std::string message = "getEntry() called with an empty list or "; 
      message = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
    }  // end if
}  // end getEntry

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
  return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
  return itemCount;
}  // end getLength

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
  Node<ItemType>* curPtr = headPtr;
  Node<ItemType>* prevPtr = NULL;
   
  while ( (curPtr != NULL) && (anEntry > curPtr->getItem()) )
    {
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
    } // end while
   
  return prevPtr;
} // end getNodeBefore

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt(int position) const
{
  assert( (position >= 1) && (position <= itemCount) );
   
  // Count from the beginning of the chain
  Node<ItemType>* curPtr = headPtr;
  for (int skip = 1; skip < position; skip++)
    curPtr = curPtr->getNext();
   
  return curPtr;
}  // end getNodeAt
//  End of implementation file.
