#include "buffer.h"
#include "bufferlist.h"
#include <iostream>
#include <stdexcept>

bool testRepeatedEnqueueAndDequeue() {
    std::cout << "Testing repeated enqueue and dequeue..." << std::endl;
    BufferList bl(5); // Buffer capacity is 5
    for (int i = 0; i < 10; ++i) {
        bl.enqueue(i);
    }
    for (int i = 0; i < 10; ++i) {
        if (bl.dequeue() != i) {
            std::cerr << "Test failed at iteration " << i << std::endl;
            return false;
        }
    }
    return true;
}

bool testStressTestWithLargeNumberOfElements() {
    std::cout << "Testing stress test with large number of elements..." << std::endl;
    BufferList bl(10); // Buffer capacity is 10
    for (int i = 0; i < 1000; ++i) {
        bl.enqueue(i);
    }
    for (int i = 0; i < 1000; ++i) {
        if (bl.dequeue() != i) {
            std::cerr << "Test failed at iteration " << i << std::endl;
            return false;
        }
    }
    return true;
}

bool testAlternatingEnqueueAndDequeue() {
    std::cout << "Testing alternating enqueue and dequeue..." << std::endl;
    BufferList bl(5); // Buffer capacity is 5
    for (int i = 0; i < 10; ++i) {
        bl.enqueue(i);
        if (bl.dequeue() != i) {
            std::cerr << "Test failed at iteration " << i << std::endl;
            return false;
        }
    }
    return true;
}

bool testEnqueueAndDequeueWithMultipleBuffers() {
    std::cout << "Testing enqueue and dequeue with multiple buffers..." << std::endl;
    BufferList bl(3); // Buffer capacity is 3
    for (int i = 0; i < 9; ++i) {
        bl.enqueue(i);
    }
    for (int i = 0; i < 9; ++i) {
        if (bl.dequeue() != i) {
            std::cerr << "Test failed at iteration " << i << std::endl;
            return false;
        }
    }
    return true;
}

bool testEnqueueBeyondInitialCapacity() {
    std::cout << "Testing enqueue beyond initial capacity..." << std::endl;
    BufferList bl(2); // Buffer capacity is 2
    for (int i = 0; i < 5; ++i) {
        bl.enqueue(i);
    }
    for (int i = 0; i < 5; ++i) {
        if (bl.dequeue() != i) {
            std::cerr << "Test failed at iteration " << i << std::endl;
            return false;
        }
    }
    return true;
}

bool testDequeueFromEmptyBufferList() {
    std::cout << "Testing dequeue from empty BufferList..." << std::endl;
    BufferList bl(3); // Buffer capacity is 3
    try {
        bl.dequeue();
        std::cerr << "Test failed: expected underflow error" << std::endl;
        return false;
    } catch (const std::underflow_error& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
        return true;
    }
}

int main() {
    bool result1 = testRepeatedEnqueueAndDequeue();
    bool result2 = testStressTestWithLargeNumberOfElements();
    bool result3 = testAlternatingEnqueueAndDequeue();
    bool result4 = testEnqueueAndDequeueWithMultipleBuffers();
    bool result5 = testEnqueueBeyondInitialCapacity();
    bool result6 = testDequeueFromEmptyBufferList();

    std::cout << "\nTest Results:\n";
    std::cout << "testRepeatedEnqueueAndDequeue: " << (result1 ? "Passed" : "Failed") << std::endl;
    std::cout << "testStressTestWithLargeNumberOfElements: " << (result2 ? "Passed" : "Failed") << std::endl;
    std::cout << "testAlternatingEnqueueAndDequeue: " << (result3 ? "Passed" : "Failed") << std::endl;
    std::cout << "testEnqueueAndDequeueWithMultipleBuffers: " << (result4 ? "Passed" : "Failed") << std::endl;
    std::cout << "testEnqueueBeyondInitialCapacity: " << (result5 ? "Passed" : "Failed") << std::endl;
    std::cout << "testDequeueFromEmptyBufferList: " << (result6 ? "Passed" : "Failed") << std::endl;

    return (result1 && result2 && result3 && result4 && result5 && result6) ? 0 : 1;
}