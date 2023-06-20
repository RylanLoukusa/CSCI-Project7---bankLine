//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file LinkedQueue.cpp */

#include "LinkedQueue.h"  
#include <cassert>
#define nullptr NULL

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue()
{
  backPtr = nullptr;
  frontPtr = nullptr;
}  // end default constructor

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& aQueue)
{  
  Node<ItemType>* origChainPtr = aQueue.frontPtr;  // Points to nodes in original chain
   
  if (origChainPtr == nullptr)
    {
      frontPtr = nullptr;  // Original queue is empty
      backPtr = nullptr;
    }   
  else
    {
      // Copy first node
      frontPtr = new Node<ItemType>();
      frontPtr->setItem(origChainPtr->getItem());
      
      // Advance original-chain pointer
      origChainPtr = origChainPtr->getNext(); 

      // Copy remaining nodes
      Node<ItemType>* newChainPtr = frontPtr;        // Points to last node in new chain
      while (origChainPtr != nullptr)
	{
	  // Get next item from original chain
	  ItemType nextItem = origChainPtr->getItem();
         
	  // Create a new node containing the next item 
	  Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);  
         
	  // Link new node to end of new chain
	  newChainPtr->setNext(newNodePtr); 
         
	  // Advance pointers       
	  newChainPtr = newChainPtr->getNext();
	  origChainPtr = origChainPtr->getNext();
	}  // end while
      
      newChainPtr->setNext(nullptr);               // Flag end of chain
      backPtr = newChainPtr;
    }  // end if
}  // end copy constructor

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
  while (!isEmpty())
    dequeue();
  assert ( (backPtr == nullptr) && (frontPtr == nullptr) );
}  // end destructor

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const
{
  return backPtr == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
  Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

  // Insert the new node
  if (isEmpty())
    frontPtr = newNodePtr;        // Insertion into empty queue
  else
    backPtr->setNext(newNodePtr); // Insertion into nonempty queue
   
  backPtr = newNodePtr;            // New node is at back
   
  return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
  bool result = false;
  if (!isEmpty())
    {
      // Queue is not empty; delete front
      Node<ItemType>* nodeToDeletePtr = frontPtr;
      if (frontPtr == backPtr)
	{  // Special case: one node in queue
	  frontPtr = nullptr;
	  backPtr = nullptr;
	}
      else
	frontPtr = frontPtr->getNext();
      
      // Return deleted node to system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      
      result = true;
    }  // end if
   
  return result;
}  // end dequeue

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const throw(PrecondViolatedExcep)
{
  if (isEmpty())
    throw PrecondViolatedExcep("getFront() called with empty queue.");

  // Queue is not empty; return front
  return frontPtr->getItem();
}  // end peekFront
// End of implementation file.
