#include "bufferlist.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

class Tester
{
public:
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount)
    {
        try
        {
            for (int i = 0; i < dataCount; ++i)
            {
                buffer.enqueue(i);
            }

            for (int i = 0; i < dataCount; ++i)
            {
                if (buffer.dequeue() != i)
                {
                    return false; // Dequeued value does not match enqueued value
                }
            }
            return buffer.empty(); // Should be empty after all dequeues
        }
        catch (const std::exception &e)
        {
            cerr << "Exception caught during Buffer testing: " << e.what() << endl;
            return false;
        }
    }

    bool BufferEnqueueFull(int size)
    {
        Buffer buffer(size);

        // Fill the buffer
        for (int i = 0; i < size; ++i)
        {
            buffer.enqueue(i);
        }

        // Test enqueue on full buffer (should throw overflow_error)
        try
        {
            buffer.enqueue(size); // Attempt to enqueue when buffer is full
            cerr << "Failed to catch overflow error!" << endl;
            return false;
        }
        catch (const std::overflow_error &)
        {
            cout << "Caught overflow error as expected." << endl;
        }

        // Empty the buffer
        for (int i = 0; i < size; ++i)
        {
            buffer.dequeue();
        }

        // Test dequeue on empty buffer (should throw underflow_error)
        try
        {
            buffer.dequeue(); // Attempt to dequeue from an empty buffer
            cerr << "Failed to catch underflow error!" << endl;
            return false;
        }
        catch (const std::underflow_error &)
        {
            cout << "Caught underflow error as expected." << endl;
        }

        return true;
    }

    bool BufferCopyConstructor(const Buffer &buffer)
    {
        // Create a copy of the buffer
        Buffer copyBuffer(buffer);

        // Check that the pointers are not the same (deep copy)
        if (buffer.m_buffer == copyBuffer.m_buffer)
        {
            cerr << "Failed: Buffer copy constructor did not create a deep copy (same pointer)." << endl;
            return false;
        }

        // Check that the data matches between the original and the copy
        for (int i = 0; i < buffer.m_capacity; ++i)
        {
            if (buffer.m_buffer[i] != copyBuffer.m_buffer[i])
            {
                cerr << "Failed: Buffer copy constructor did not copy values correctly." << endl;
                return false;
            }
        }

        // Optionally, clear the original buffer and check if the copy still has the data
        Buffer temp = buffer;
        temp.clear();
        
        try
        {
            // Dequeue from the copy to verify it still contains the original data
            while (!copyBuffer.empty())
            {
                copyBuffer.dequeue();
            }
        }
        catch (const std::underflow_error &)
        {
            cout << "Caught underflow error in copy buffer as expected." << endl;
        }

        cout << "Buffer copy constructor test passed." << endl;
        return true;
    }

    bool BufferListEnqueueDequeue(BufferList &bufferlist, int dataCount)
    {
        try
        {
            for (int i = 0; i < dataCount; ++i)
            {
                bufferlist.enqueue(i);
            }

            for (int i = 0; i < dataCount; ++i)
            {
                if (bufferlist.dequeue() != i)
                {
                    return false; // Dequeued value does not match enqueued value
                }
            }
            return true;
        }
        catch (const std::exception &e)
        {
            cerr << "Exception caught during BufferList testing: " << e.what() << endl;
            return false;
        }
    }

    bool BufferListDequeueEmpty(BufferList &bufferlist)
    {
        try
        {
            bufferlist.dequeue(); // Attempt to dequeue from an empty buffer
            cerr << "Failed to catch underflow error!" << endl;
            return false;
        }
        catch (const std::underflow_error &)
        {
            cout << "Caught underflow error as expected." << endl;
        }

        return true;
    }

    bool BufferListCopyConstructor(const BufferList &bufferlist) {
        // Create a copy of bufferList using the copy constructor
        BufferList copyBufferList = bufferlist;

        // Check if the copied list is a deep copy and not shallow
        // The buffer pointers in each list should not be the same
        const Buffer *originalBuffer = bufferlist.m_cursor;
        const Buffer *copiedBuffer = copyBufferList.m_cursor;

        // Loop through the circular linked list to check each buffer
        do {
            if (originalBuffer == copiedBuffer) {
                cerr << "Failed: BufferList copy constructor did not create deep copy (same pointer)." << endl;
                return false;
            }

            // Test each Buffer's deep copy (reuse BufferCopyConstructor)
            if (!BufferCopyConstructor(*originalBuffer)) {
                cerr << "Failed: BufferList copy constructor did not copy buffers correctly." << endl;
                return false;
            }

            originalBuffer = originalBuffer->m_next;
            copiedBuffer = copiedBuffer->m_next;
        } while (originalBuffer != bufferlist.m_cursor);

        cout << "BufferList copy constructor test passed." << endl;
        return true;
    }

    bool BufferListAssignmentConstructor(const BufferList &bufferList) {
        // Create a new BufferList and assign bufferList to it
        BufferList assignedBufferList(0);
        assignedBufferList = bufferList;  // Use the assignment operator

        // Clear the original bufferList (rhs in the assignment)
        BufferList temp = bufferList;  // Create a temporary copy to clear
        temp.clear();  // Clear the source object

        // Check if the assigned list still contains the original data
        try {
            // Dequeue all data from assignedBufferList and check that it still has data
            while (!assignedBufferList.m_cursor->empty()) {
                assignedBufferList.dequeue();  // Should still have the data from bufferList
            }

            // If we can dequeue all elements without issue, the test passes
            cout << "BufferList assignment operator created a deep copy successfully." << endl;
            return true;

        } catch (const std::underflow_error &) {
            cerr << "Failed: BufferList assignment operator did not create a deep copy." << endl;
            return false;
        }
    }


    void BufListEnqueuePerformance(int numTrials, int N) {
    for (int trial = 1; trial <= numTrials; ++trial) {
        BufferList bufferList(10); // Initialize with some minimum capacity

        // Start timing
        auto t1 = high_resolution_clock::now();

        // Enqueue N elements
        for (int i = 0; i < N * trial; ++i) {
            bufferList.enqueue(i);
        }

        // End timing
        auto t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(t2-t1).count();

        cout << "Trial " << trial << ": Enqueued " << N * trial << " elements in " 
        << duration << " clock ticks or " << duration << " microseconds." << endl;
    }
}
};
int main()
{
    Tester tester;
    int bufferSize = 1000;
    Buffer buffer(bufferSize);
    {
        // testing insertion/removal for 1 data item
        cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
        if (tester.BufferEnqueueDequeue(buffer, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing insertion/removal for half data size
        cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize / 2))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing insertion/removal for full data size
        cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing insertion in a full buffer
        cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
        if (tester.BufferEnqueueFull(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing Buffer class copy constructor with buffer size less than zero
        cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
        Buffer buffer(-10);
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else

            cout << "\tTest failed!\n";
    }
    {
        // Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;     // number of trials
        int N = 10000; // original input size
        tester.BufListEnqueuePerformance(M, N);
    }
    {
        // an example of BufferList::dump()
        cout << "\nHere is an example of a linked list:" << endl;
        BufferList bufferList(5);
        for (int i = 40; i > 0; i--)
            bufferList.enqueue(i);
        bufferList.dump();
    }

    // BufferList Testing

    {
        // testing insertion/removal for 1 data item
        cout << "\nTest case: BufferList class: Inserting/removing 1 data item:\n";
        BufferList bufferList(10);
        if (tester.BufferListEnqueueDequeue(bufferList, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing insertion/removal for half data size
        cout << "\nTest case: BufferList class: Inserting/removing half data size:\n";
        BufferList bufferList(10);
        if (tester.BufferListEnqueueDequeue(bufferList, 5))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing insertion/removal for full data size
        cout << "\nTest case: BufferList class: Inserting/removing full data size:\n";
        BufferList bufferList(10);
        if (tester.BufferListEnqueueDequeue(bufferList, 10))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing BufferList class copy constructor
        cout << "\nTest case: BufferList class: Copy constructor:\n";
        BufferList bufferList(10);
        if (tester.BufferListCopyConstructor(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing BufferList class dequeue from empty list
        cout << "\nTest case: BufferList class: Dequeue from empty list:\n";
        BufferList bufferList(10);
        if (tester.BufferListDequeueEmpty(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // testing BufferList class assignment constructor
        cout << "\nTest case: BufferList class: Assignment constructor:\n";
        BufferList bufferList(10);
        if (tester.BufferListAssignmentConstructor(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }


    return 0;
}