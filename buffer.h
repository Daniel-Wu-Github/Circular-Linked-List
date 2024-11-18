/******************************************************************************************
** File: buffer.h
** Project: CSCE 221 Project 1, Fall 2024
** Author: Daniel Wu
** Date: 9/19/2024
** Section: 597
** E-mail: DanielWu1510@tamu.edu
**
** This file contains the declaration for the Buffer class.
** This class is a circular buffer that stores integer values. The data structure has a FIFO structure.
******************************************************************************************/



#ifndef BUFFER_H
#define BUFFER_H
#include <stdexcept>
#include <iostream>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
//the following is your tester class, you add your test functions in this class
//you declare and implement the Tester class in your mytest.cpp file
class Tester;
//forward declaration, BufferList will be a friend of Buffer class
class BufferList;
class Buffer{
    public:
    friend class Grader;//Grader will have access to private members of Buffer
    friend class Tester;//Tester will have access to private members of Buffer
    friend class BufferList;//BufferList will have access to private members of Buffer
    Buffer(int capacity);       //constructor
    ~Buffer();                  //destructor
    Buffer(const Buffer & rhs); //copy constructor
    const Buffer & operator=(const Buffer & rhs);// overloaded assignment operator
    void enqueue(int data); // inserts at the end
    int dequeue();          // removes from start
    void clear();           // deallocate memory
    bool empty();           // returns true if buffer holds no items
    bool full();            // returns true if no space left in buffer
    int count();            // returns number of items currently held in the buffer
    int capacity();         // returns maximum number of items this buffer can hold
    void dump();            // prints out the contents, for debugging purposes


    private:
    int *m_buffer ;         // pointer to dynamically allocated array for buffer 
    int m_capacity ;        // length of the allocated space pointed by m_buffer
    int m_count ;           // current number of items in the buffer
    int m_start ;           // index of the first (oldest) item in the buffer
    int m_end ;             // index of the last (newest) item in the buffer
    Buffer* m_next;         // pointer to the next buffer in a linked list

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
};
#endif