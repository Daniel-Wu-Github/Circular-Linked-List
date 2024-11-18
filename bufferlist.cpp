/******************************************************************************************
** File: bufferlist.cpp
** Project: CSCE 221 Project 1, Fall 2024
** Author: Daniel Wu
** Date: 9/19/2024
** Section: 597
** E-mail: DanielWu1510@tamu.edu
**
** This file contains the implementation for the BufferList class.
** This class is a circular linked list of Buffer objects.
** Every object is a circular buffer that stores integer values. The data structure has a FIFO structure.
** Everytime the buffer is full, a new buffer is created with twice the capacity of the previous buffer.
** Everytime the buffer is empty, the buffer is deleted.
******************************************************************************************/


#include "bufferlist.h"
#include <stdexcept>

/********************************************
** Function: BufferList(int minBufCapacity)
** Pre-conditions: minBufCapacity is an integer larger than 0
** Post-conditions: A BufferList object is created on the heap with a Buffer object
********************************************/
BufferList::BufferList(int minBufCapacity) {
    
    m_listSize = 0;

    if (minBufCapacity < 1) {
        // set to default value of 10
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
    } 
    else {
        m_minBufCapacity = minBufCapacity;
    }

    // create a new buffer with the min capacity
    m_cursor = new Buffer(m_minBufCapacity);
    m_cursor->m_next = m_cursor;
    m_listSize += 1;
}

/********************************************
** Function: ~BufferList()
** Pre-conditions: None
** Post-conditions: the clear function is called to deallocate all memory
********************************************/
BufferList::~BufferList() {
    clear();
}

/********************************************
** Function: clear()
** Pre-conditions: None
** Post-conditions: All buffers in the list are deallocated and memory is freed
********************************************/
void BufferList::clear() {
    if (m_cursor == nullptr) return; // Added check for nullptr

    // set both pointers to the beginning of the linked list
    Buffer* bufferDelete = m_cursor->m_next;
    Buffer* nodeDelete = m_cursor->m_next;

    // iterate through the linked list and delete each node
    while (bufferDelete != m_cursor) {
        bufferDelete->clear();
        bufferDelete = bufferDelete->m_next;
        delete nodeDelete;
        nodeDelete = bufferDelete;
    }

    // clear the cursor
    m_cursor->clear();
    delete m_cursor;
    m_cursor = nullptr;
    m_listSize = 0;
}

/********************************************
** Function: enqueue(const int& data)
** Pre-conditions: data is an integer to be added to the buffer
** Post-conditions: data is added to the buffer, a new buffer is created if the current buffer is full
********************************************/
void BufferList::enqueue(const int& data) {
    try {
        // try to enqueue the data with the current cursor
        this->m_cursor->enqueue(data);
    } 
    catch (const std::overflow_error& e) {
        int newSize = (this->m_cursor->capacity()) * INCREASE_FACTOR;
        if (newSize > MAX_FACTOR * m_minBufCapacity) {
            newSize = m_minBufCapacity;
        }

        // create a new buffer with the calculated capacity
        Buffer* newBuffer = new Buffer(newSize);
        newBuffer->m_next = this->m_cursor->m_next;
        this->m_cursor->m_next = newBuffer;
        this->m_cursor = newBuffer;

        // enqueue the data with the new cursor
        this->m_cursor->enqueue(data);
        this->m_listSize += 1;
    }
}

/********************************************
** Function: dequeue()
** Pre-conditions: None
** Post-conditions: The oldest data is removed from the buffer and returned, a buffer is deleted if it becomes empty
********************************************/
int BufferList::dequeue() {
    if (m_listSize == 0) {
        throw std::underflow_error("Nothing to dequeue!");
    }
    try {
        int data = this->m_cursor->m_next->dequeue();

        // Check if the buffer is empty after dequeue
        if (this->m_cursor->m_next->empty() && m_listSize > 1) {
            // create a temporary pointer to the second buffer
            Buffer* temp = m_cursor->m_next->m_next;

            // delete the first buffer
            delete m_cursor->m_next;
            m_cursor->m_next = temp;
            m_listSize -= 1;
        }

        return data;
    } 
    catch (const std::underflow_error& e) {
        if (m_listSize == 1) { // if there is only one buffer in the list
            throw std::underflow_error("Nothing to dequeue! Only one buffer in the list.");
        }

        // create a temporary pointer to the second buffer
        Buffer* temp = m_cursor->m_next->m_next;

        // delete the first buffer
        delete m_cursor->m_next;
        m_cursor->m_next = temp;
        m_listSize -= 1;
        int data = this->m_cursor->m_next->dequeue();
        return data;
    }
}

/********************************************
** Function: BufferList(const BufferList& rhs)
** Pre-conditions: rhs is a BufferList object to be copied
** Post-conditions: A new BufferList object is created as a copy of rhs
********************************************/
BufferList::BufferList(const BufferList& rhs) {
    if (rhs.m_cursor == nullptr) {
        this->m_cursor = nullptr;
        return;
    }

    // copy the list size and min buffer capacity
    this->m_listSize = rhs.m_listSize;
    this->m_minBufCapacity = rhs.m_minBufCapacity;

    // create a pointer to the first buffer in the list
    Buffer* RHScurrent = rhs.m_cursor->m_next;
    m_cursor = new Buffer(*RHScurrent);

    // create a pointer to the first buffer in the new list, saves it for circular structure
    Buffer* LHSstart = m_cursor;

    // create a pointer to the previous buffer in the new list, used for traversal and linking
    Buffer* LHSprev = m_cursor;

    while (RHScurrent != rhs.m_cursor) {
        RHScurrent = RHScurrent->m_next;
        m_cursor->m_next = new Buffer(*RHScurrent);
        m_cursor = m_cursor->m_next;
        LHSprev->m_next = m_cursor;
        LHSprev = LHSprev->m_next;
    }

    // Maintain circular structure
    m_cursor->m_next = LHSstart;
}

/********************************************
** Function: operator=(const BufferList& rhs)
** Pre-conditions: rhs is a BufferList object to be assigned
** Post-conditions: The current BufferList object is assigned the values of rhs
********************************************/
const BufferList& BufferList::operator=(const BufferList& rhs) {
    if (this == &rhs) return *this; // Self-assignment check

    this->clear();

    if (rhs.m_cursor == nullptr) {
        this->m_cursor = nullptr;
        return *this;
    }

    // same as copy constructor
    this->m_listSize = rhs.m_listSize;
    this->m_minBufCapacity = rhs.m_minBufCapacity;

    Buffer* RHScurrent = rhs.m_cursor->m_next;
    m_cursor = new Buffer(*RHScurrent);
    Buffer* LHSstart = m_cursor;
    Buffer* LHSprev = m_cursor;

    while (RHScurrent != rhs.m_cursor) {
        RHScurrent = RHScurrent->m_next;
        m_cursor->m_next = new Buffer(*RHScurrent);
        m_cursor = m_cursor->m_next;
        LHSprev->m_next = m_cursor;
        LHSprev = LHSprev->m_next;
    }

    m_cursor->m_next = LHSstart;

    return *this;
}

/********************************************
** Function: dump()
** Pre-conditions: None
** Post-conditions: The contents of the buffer list are printed to the console
********************************************/
void BufferList::dump() {
    Buffer* temp = m_cursor->m_next;
    for (int i = 0; i < m_listSize; i++) {
        temp->dump();
        temp = temp->m_next;
    }
}