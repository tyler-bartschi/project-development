#pragma once

#include "Tuple.h"

class Heap {
private:
    int _capacity;
    int _size;
    Tuple *_array;

    int _left(const int &index) const {
        return (2 * index) + 1;
    }

    int _right(const int &index) const {
        return (2 * index) + 2;
    }

    int _parent(const int &index) const {
        return (index - 1) / 2;
    }

    void _grow() {
        Tuple *new_array = new Tuple[_capacity * 2];
        for (int i = 0; i < _capacity; i++) {
            new_array[i] = _array[i];
        }
        _capacity = _capacity * 2;
        delete[] _array;
        _array = new_array;
    }

    void _heapify_up() {
        int index = _size - 1;
        while (index > 0 && _array[index].get_freq() > _array[_parent(index)].get_freq()) {
            const int parent = _parent(index);
            swap(parent, index);
            index = parent;
        }
    }

    void swap(int const &index1, int const &index2) {
        Tuple tmp = _array[index1];
        _array[index1] = _array[index2];
        _array[index2] = tmp;
    }

    void _heapify_down() {
        int index = 0;
        bool going = true;
        while (going) {
            int left = _left(index);
            int right = _right(index);
            if (left > _size) {
                // out of bounds
                going = false;
                continue;
            }

            if (right > _size) {
                // only check the left index
                const int left_size = _array[left].get_freq();
                const int current_size = _array[index].get_freq();
                if (current_size < left_size) {
                    swap(index, left);

                }
                going = false;
                continue;
            }

            const int right_size = _array[right].get_freq();
            const int left_size = _array[left].get_freq();
            const int current_size = _array[index].get_freq();
            if (current_size < right_size && current_size < left_size) {
                if (left_size > right_size) {
                    // swap with left
                    swap(index, left);
                    index = left;
                } else {
                    // swap with right
                    swap(index, right);
                    index = right;
                }
            } else if (current_size < right_size) {
                // swap with right
                swap(index, right);
                index = right;
            } else  if (current_size < left_size) {
                // swap with left
                swap(index, left);
                index = left;
            } else {
                going = false;
            }
        }
    }

public:
    Heap() : _capacity(10), _size(0), _array(new Tuple[_capacity]) {
    }

    ~Heap() {
        delete[] _array;
    }

    int size() const {
        return _size;
    }

    void insert(const Tuple &item) {
        if (_size == _capacity) {
            _grow();
        }
        _array[_size] = item;
        _size++;
        _heapify_up();
    }

    Tuple pop() {
        if (_size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        Tuple top = _array[0];
        _size--;
        if (_size > 0) {
            _array[0] = _array[_size];
            _heapify_down();
        }
        return top;
    }

    void clear() {
        _size = 0;
    }
};