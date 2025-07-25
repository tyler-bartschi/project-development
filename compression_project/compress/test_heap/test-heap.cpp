#include <iostream>
using std::cout, std::endl;
#include <random>
#include "../Heap.h"
#include "../Tuple.h"

int main() {
    Heap my_heap = Heap();
    // auto t1 = Tuple("hello", 74);
    // auto t2 = Tuple("goodbye", 56);
    // auto t3 = Tuple("testing", 112);
    //
    // my_heap.insert(t1);
    // my_heap.insert(t2);
    // my_heap.insert(t3);
    //
    // cout << my_heap.pop().str() << endl;
    // cout << my_heap.pop().str() << endl;
    // cout << my_heap.pop().str() << endl;

    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 1;
    int max = 10000;
    std::uniform_int_distribution<> distrib(min, max);

    for (int i = 100; i > 0; i--) {
        int randomNumber = distrib(gen);
        auto t = Tuple("i", randomNumber);
        my_heap.insert(t);
    }

    int size = my_heap.size();
    for (int i = 0; i < size; i++) {
        cout << my_heap.pop().str() << endl;
    }
}
