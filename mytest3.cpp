#include "bufferlist.h"
class Tester{
    public:
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
    bool BufferEnqueueFull(int size);
    bool BufferCopyConstructor(const Buffer &buffer);

    bool BufferListEnqueueDequeue(BufferList &bufferlist, int dataCount);
    bool BufferListDequeueEmpty(BufferList &bufferlist);
    bool BufferListCopyConstructor(BufferList &bufferlist);
    bool BufferListAssignmentConstructor(BufferList &bufferlist);

    void BufListEnqueuePerformance(int numTrials, int N);

    
};
int main(){
    Tester tester;
    int bufferSize = 1000;
    Buffer buffer(bufferSize);
    {
        //testing insertion/removal for 1 data item
        cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
        if (tester.BufferEnqueueDequeue(buffer, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for half data size
        cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize/2))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for full data size
        cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion in a full buffer
        cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
        if (tester.BufferEnqueueFull(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing Buffer class copy constructor with buffer size less than zero
        cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
        Buffer buffer(-10);
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;//number of trials
        int N = 10000;//original input size
        tester.BufListEnqueuePerformance(M, N);
    }
    {
        //an example of BufferList::dump()
        cout << "\nHere is an example of a linked list:" << endl;
        BufferList bufferList(5);
        for (int i=40;i>0;i--)
            bufferList.enqueue(i);
        bufferList.dump();
    }
    {
        //testing insertion in a full buffer
        cout << "\nTest case: BufferList class: Throwing exception while dequeueing empty buffer:\n";
        BufferList buf(100);
        if (tester.BufferListDequeueEmpty(buf)) 
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing BufferList class copy constructor with buffer size less than zero
        cout << "\nTest case: BufferList class: Copy constructor, negative buffer size:\n";
        BufferList buffer(-10);
        buffer.enqueue(1345);
        if (tester.BufferListCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    {
        //testing Buffer class copy constructor with buffer size less than zero
        cout << "\nTest case: BufferList class: Copy constructor, multiple buffers in linked list:\n";
        BufferList buffer(10);
        for(int i = 0; i < 50; i++) {
            buffer.enqueue(i);
        }
        if (tester.BufferListCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    {
        //testing BufferList class Assignment constructor with buffer size less than zero
        cout << "\nTest case: BufferList class: Assignment constructor, negative buffer size:\n";
        BufferList buffer(-10);
        buffer.enqueue(1345);
        if (tester.BufferListAssignmentConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    {
        //testing Buffer class Assignment constructor with buffer size less than zero
        cout << "\nTest case: BufferList class: Assignment constructor, multiple buffers in linked list:\n";
        BufferList buffer(10);
        for(int i = 0; i < 50; i++) {
            buffer.enqueue(i);
        }
        if (tester.BufferListAssignmentConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    return 0;
}

bool Tester::BufferEnqueueDequeue(Buffer &buffer, int dataCount) { 
    for(int i=0; i<dataCount;i++) {
        buffer.enqueue(i);
    }
    for(int i = 0; i < dataCount; i++) {
        if(buffer.dequeue() != i) {
            return false;
        }
    }
    try {
        //trying to dequeue in empty buffer
        buffer.dequeue();
    } catch(underflow_error &e) {
        return true;
    } catch(...) {
        return false;
    }
    return false; // no error means something is wrong
 }

bool Tester::BufferEnqueueFull(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++)
        aBuffer.enqueue(i);
    try{
        //trying to insert in a full buffer
        aBuffer.enqueue(size+1);
    }
    catch(overflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}
bool Tester::BufferCopyConstructor(const Buffer &buffer){ 
    Buffer other(buffer);
    if(other.m_buffer == buffer.m_buffer) {
        return false;
    }
    for(int i = 0; i < other.capacity(); i++) {
        if(other.m_buffer[i] != buffer.m_buffer[i]) {
            return false;
        }
    }
    return true;
}

bool Tester::BufferListEnqueueDequeue(BufferList &bufferlist, int dataCount) { 
    for(int i=0; i<dataCount;i++) {
        bufferlist.enqueue(i);
    }
    for(int i = 0; i < dataCount; i++) {
        if(bufferlist.dequeue() != i) {
            return false;
        }
    }
    try {
        //trying to dequeue in empty buffer
        bufferlist.dequeue();
    } catch(underflow_error &e) {
        return true;
    } catch(...) {
        return false;
    }
    return false;
}

bool Tester::BufferListDequeueEmpty(BufferList &bufferlist) { 
    int last = 0;
    try {
        bufferlist.enqueue(1);
        while(true) {
            last = bufferlist.dequeue();
        }
    } catch(underflow_error &e) {
        return last == 1;
    } catch(...) {
        return false;
    }
    return false; 
}

bool TestDeepCopy(BufferList &a, BufferList &b) {
    a.clear();
    try {
        b.dequeue();
        return true;
    } catch(underflow_error &e) {
        return false;
    }
    return false;
}
bool Tester::BufferListCopyConstructor(BufferList &bufferlist) { 
    BufferList buf(bufferlist);
    return TestDeepCopy(buf,bufferlist);
}
bool Tester::BufferListAssignmentConstructor(BufferList &bufferlist) { 
    BufferList buf(10);
    // fill to be assigned buffer
    for(int i = 0; i < 20; i++) {
        buf.enqueue(i);
    }
    buf = bufferlist;
    return TestDeepCopy(buf,bufferlist);
}

void Tester::BufListEnqueuePerformance(int numTrials, int N) {
    for(int trial = 1; trial <= numTrials; trial++) {
        clock_t t = clock();
        BufferList buf(N);
        for(int i = 0; i < N; i++) {
            buf.enqueue(i);
        }
        t = clock()-t;
        cout << "Inserting " << N*trial << " members took " << t << " clock ticks (" << ((float) t)/CLOCKS_PER_SEC << " seconds)" << endl;
    }
}