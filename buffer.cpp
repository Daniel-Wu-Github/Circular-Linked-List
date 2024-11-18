/******************************************************************************************
** File: buffer.cpp
** Project: CSCE 221 Project 1, Fall 2024
** Author: Daniel Wu
** Date: 9/19/2024
** Section: 597
** E-mail: DanielWu1510@tamu.edu
**
** This file contains the implementation for the Buffer class.
** This class is a circular buffer that stores integer values. The data structure has a FIFO structure.
** The buffer has a fixed capacity and will throw an exception if the buffer is full and enqueue is called.
** The buffer will throw an exception if the buffer is empty and dequeue is called.
******************************************************************************************/

#include "buffer.h"
#include <stdexcept>

/********************************************
** Function: Buffer(int capacity)
** Pre-conditions: capacity is an integer larger than or equal to 0
** Post-conditions: A Buffer object is created with the specified capacity
********************************************/
Buffer::Buffer(int capacity) {
    
    m_count = 0;
    m_start = 0;
    m_end = 0;

    if (capacity < 1) {
        // If capacity is less than 1, set buffer to nullptr
        m_capacity = 0;
        m_buffer = nullptr;
    } 
    else {
        m_capacity = capacity;

        // Allocate memory for the buffer on the heap
        m_buffer = new int[capacity];

        // Initialize buffer to all zeros
        for (int i = 0; i < m_capacity; i++) {
            m_buffer[i] = 0;
        }
    }
}

/********************************************
** Function: clear()
** Pre-conditions: None
** Post-conditions: The buffer is cleared and memory is deallocated
********************************************/
void Buffer::clear() {
    if (m_buffer == nullptr) return; // Added check for nullptr

    delete[] m_buffer;
    m_count = 0;
    m_start = 0;
    m_end = 0;
    m_capacity = 0;
    m_buffer = nullptr;
}

/********************************************
** Function: ~Buffer()
** Pre-conditions: None
** Post-conditions: The buffer is cleared and memory is deallocated
********************************************/
Buffer::~Buffer() {
    clear();
}

/********************************************
** Function: count()
** Pre-conditions: None
** Post-conditions: Returns the number of elements in the buffer
********************************************/
int Buffer::count() {
    return m_count;
}

/********************************************
** Function: capacity()
** Pre-conditions: None
** Post-conditions: Returns the capacity of the buffer
********************************************/
int Buffer::capacity() {
    return m_capacity;
}

/********************************************
** Function: full()
** Pre-conditions: None
** Post-conditions: Returns true if the buffer is full, false otherwise
********************************************/
bool Buffer::full() {
    // If count is greater than or equal to capacity, buffer is full
    return m_count >= m_capacity;
}

/********************************************
** Function: empty()
** Pre-conditions: None
** Post-conditions: Returns true if the buffer is empty, false otherwise
********************************************/
bool Buffer::empty() {
    // If count is 0, buffer is empty
    return m_count == 0;
}

/********************************************
** Function: enqueue(int data)
** Pre-conditions: data is an integer to be added to the buffer
** Post-conditions: data is added to the buffer, throws overflow_error if the buffer is full
********************************************/
void Buffer::enqueue(int data) {
    if (full()) {
        // If buffer is full, throw an exception
        throw std::overflow_error("No space for enqueue! Creating a new buffer..."); // Placeholder until we implement BufferList
    }

    m_buffer[m_end] = data;

    // If end is at the end of the buffer, wrap around to the beginning
    m_end = (m_end + 1) % m_capacity;
    m_count++;
}

/********************************************
** Function: dequeue()
** Pre-conditions: None
** Post-conditions: The oldest data is removed from the buffer and returned, throws underflow_error if the buffer is empty
********************************************/
int Buffer::dequeue() {
    if (empty()) {
        // If buffer is empty, throw an exception
        throw std::underflow_error("Nothing to dequeue!");
    }

    int data = m_buffer[m_start];

    // If start is at the end of the buffer, wrap around to the beginning
    m_start = (m_start + 1) % m_capacity;
    m_count--;
    return data;
}

/********************************************
** Function: Buffer(const Buffer& rhs)
** Pre-conditions: rhs is a Buffer object to be copied
** Post-conditions: A new Buffer object is created as a copy of rhs
********************************************/
Buffer::Buffer(const Buffer& rhs) {
    // Copy the basic attributes
    this->m_start = rhs.m_start;
    this->m_count = rhs.m_count;
    this->m_end = rhs.m_end;

    if (rhs.m_capacity < 1) {
        // create a new empty buffer anyways
        this->m_buffer = new int[0];
        this->m_capacity = 0;
    } 
    else {
        // Allocate memory for the new buffer and copy the contents
        this->m_capacity = rhs.m_capacity;
        this->m_buffer = new int[m_capacity];
        for (int i = 0; i < m_capacity; i++) {
            this->m_buffer[i] = rhs.m_buffer[i];
        }
    }
}

/********************************************
** Function: operator=(const Buffer& rhs)
** Pre-conditions: rhs is a Buffer object to be assigned
** Post-conditions: The current Buffer object is assigned the values of rhs
********************************************/
const Buffer& Buffer::operator=(const Buffer& rhs) {
    if (this == &rhs) return *this; // Self-assignment check

    // Free the existing buffer memory
    delete[] m_buffer;

    this->m_capacity = rhs.m_capacity;
    this->m_start = rhs.m_start;
    this->m_count = rhs.m_count;
    this->m_end = rhs.m_end;

    if (rhs.m_buffer == nullptr) {
        this->m_buffer = nullptr;
    } 
    else {
        // same as copy constructor
        this->m_buffer = new int[m_capacity];
        for (int i = 0; i < m_capacity; i++) {
            this->m_buffer[i] = rhs.m_buffer[i];
        }
    }
    return *this;
}

/********************************************
** Function: dump()
** Pre-conditions: None
** Post-conditions: The contents of the buffer are printed to the console
********************************************/
void Buffer::dump() {
    int start = m_start;
    int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()) {
        while (counter < m_count) {
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else {
        cout << "Buffer is empty!" << endl;
    }
}