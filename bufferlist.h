/******************************************************************************************
** File: bufferlist.h
** Project: CSCE 221 Project 1, Fall 2024
** Author: Daniel Wu
** Date: 9/19/2024
** Section: 597
** E-mail: DanielWu1510@tamu.edu
**
** This file contains the declaration for the BufferList class.
** This class is a circular linked list of Buffer objects.
******************************************************************************************/



#ifndef BUFFERLIST_H
#define BUFFERLIST_H
#include "buffer.h"
class Grader;//this class is for grading purposes, no need to do anything
//the following is your tester class, you add your test functions in this class
//you declare and implement the Tester class in your mytest.cpp file
class Tester;
const int DEFAULT_MIN_CAPACITY = 10;
const int MAX_FACTOR = 16;
const int INCREASE_FACTOR = 2;
class BufferList{
    public:
    friend class Grader;//Grader will have access to private members of BufferList
    friend class Tester;//Tester will have access to private members of BufferList
    BufferList(int minBufCapacity);     //constructor
    ~BufferList();                      //destructor
    BufferList(const BufferList & rhs); //copy constructor
    const BufferList & operator=(const BufferList & rhs);// overloaded assignment operator
    void enqueue(const int & data);	    //add data
    int dequeue();			            //remove data
    void clear();           //clear all data, deallocate all memory
    void dump();            //prints out the contents, for debugging purposes


    private:
    Buffer * m_cursor;      //the cursor is the rear of list and its next points to front of list
    int m_listSize;         //this is the size of linked list, i.e. number of nodes in the list
    int m_minBufCapacity;   //the min size for circular buffers in the list

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
};
#endif