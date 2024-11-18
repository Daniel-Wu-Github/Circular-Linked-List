#include "buffer.h"
#include <stdexcept>
#include <iostream>

using namespace std;

void testBufferConstructor(){
    Buffer test(10);
    test.dump();
}

//No memory leaks detected, destructor is working properly

void testBufferDestructor(){
    Buffer test(10);
    test.dump();
    test.~Buffer();
    test.dump();
}

void testEnqueue(){//not full
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.dump();
}

void testDequeue(){
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.dump();
    cout << "now dequeuing" << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "remaining count: " << test.count() << endl;
    test.dump();
}

void testBoth(){
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.dump();
    cout << "now dequeuing" << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "remaining count: " << test.count() << endl;
    test.dump();
    cout << "now enqueuing" << endl;
    test.enqueue(6);
    test.enqueue(7);
    test.enqueue(8);
    //test.enqueue(9);
    test.dump();
}

void testCopyConstructor(){
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.dump();
    Buffer test2(test);
    test2.dump();
}

void testAssignmentOperator(){
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.dump();
    Buffer test2 = test;
    test2.dump();
}

void testCopyAfterChange(){
    Buffer test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.dump();
    cout << "now dequeuing" << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "remaining count: " << test.count() << endl;
    test.dump();
    cout << "now enqueuing" << endl;
    test.enqueue(6);
    test.enqueue(7);
    test.enqueue(8);
    //test.enqueue(9);
    test.dump();
    Buffer test2(test);
    test2.dump();
    Buffer test3 = test2;
    test3.dump();
}

//now testing bufferlist.cpp

#include "bufferlist.h"

void testBufferListConstructor(){
    BufferList test(10);
    test.dump();
}


void testBufferListQueueing(){
    BufferList test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.enqueue(6);
    test.dump();
    test.enqueue(7);
    test.enqueue(8);
    test.enqueue(9);
    test.enqueue(10);
    test.enqueue(11);
    test.enqueue(12);
    test.enqueue(13);
    test.enqueue(14);
    test.enqueue(15);
    test.dump();
    //cout << "HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
    //test.enqueue(16);
    //cout << "BYEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
    //test.dump();
    cout << "now dequeuing" << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    test.dump();
    cout << "this item was just dequeued: " << test.dequeue() << endl; //NOTE TO SELF: the message nothing to dequeue is being displayed, remember to delete
    test.dump();
    test.enqueue(17);
    test.dump();
    test.enqueue(18);
    test.enqueue(19);
    test.dump();
    cout << "now dequeuing, please work" << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    test.enqueue(20);
    test.enqueue(21);
    test.dump();
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    cout << "this item was just dequeued: " << test.dequeue() << endl;
    test.dump();
}

void testBufferListCopyConstructor(){
    BufferList test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.enqueue(6);
    test.dump();
    BufferList test2(test);
    test2.dump();
}

void testBufferListAssignmentOperator(){
    BufferList test(5);
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    test.enqueue(4);
    test.enqueue(5);
    test.enqueue(6);
    test.dump();
    BufferList test2 = test;
    test2.dump();
}






int main(){
    cout << "Testing Buffer constructor" << endl;
    testBufferConstructor();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Buffer destructor" << endl;
    testBufferDestructor();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Enqueue" << endl;
    testEnqueue();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Dequeue" << endl;
    testDequeue();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Both" << endl;
    testBoth();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Copy Constructor" << endl;
    testCopyConstructor();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Assignment Operator" << endl;
    testAssignmentOperator();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing Copy After Change" << endl;
    testCopyAfterChange();
    cout << "---------------------------------------------------" << endl;

    cout << "***************************************************" << endl;
    cout << "Now tesing bufferlist.cpp" << endl;
    cout << "***************************************************" << endl;

    cout << "Testing BufferList Constructor" << endl;
    testBufferListConstructor();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing BufferList Enqueue/Dequeue" << endl;
    testBufferListQueueing();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing BufferList Copy Constructor" << endl;
    testBufferListCopyConstructor();
    cout << "---------------------------------------------------" << endl;

    cout << "Testing BufferList Assignment Operator" << endl;
    testBufferListAssignmentOperator();
    cout << "---------------------------------------------------" << endl;

    return 0;
}