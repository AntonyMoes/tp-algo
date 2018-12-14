/*
4_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".
Формат выходных данных. Неотрицательное число - количество подходов к корзине.
*/

#include <iostream>
#include <cstring>

template <class T>
class Heap {
public:
    Heap() {
        data = new T[capacity];
    }
    Heap(const T *arr, size_t size) :
        capacity(size), size(size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = arr[i];
        }

        for (long i = size / 2 - 1; i >= 0; --i) {  // size_t i = 0; --i; --> число > 0
            sift_down(i);
        }
    }
    ~Heap() {
        delete[] data;
    }

    void add(const T &item) {
        if (size == capacity) {
            realloc_heap();
        }

        data[size] = item;
        sift_up(size++);

    }
    T extract_max() {
        if (!size) {
            throw std::out_of_range("Heap is empty");;
        }

        T temp = data[0];
        data[0] = data[--size];
        sift_down(0);

        return temp;
    }
    const T &peek_max() {
        return data[0];
    }

    bool is_empty() {
        return size == 0;
    }

private:
    void sift_down(size_t i) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t max = i;

        if (left < size && data[left] > data[i])
            max = left;

        if (right < size && data[right] > data[max])
            max = right;

        if (max != i) {
            std::swap(data[i], data[max]);
            sift_down(max);
        }
    }
    void sift_up(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (data[i] <= data[parent])
                return;
            std::swap(data[i], data[parent]);
            i = parent;
        }

    }

    void realloc_heap() {
        auto *temp_pointer = new T[capacity * 2];
        std::memmove(temp_pointer, data, capacity * sizeof(T)); // и еще один источник

        delete[] data;
        data = temp_pointer;

        capacity *= 2;
    }

    T *data;
    size_t size = 0;
    size_t capacity = 10;
};

template <class T>
class Queue {
public:
    Queue() {
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void enqueue(T item) {
        if (head == tail && !empty) {
            auto *temp_pointer = new T[capacity * 2];

            size_t j = head;
            for (size_t i = 0; i < capacity; i++) {
                temp_pointer[i] = data[j];
                j = ++j % capacity;
            }

            delete[] data;
            data = temp_pointer;

            head = 0;
            tail = capacity;

            capacity *= 2;
        }
        data[tail] = item;

        tail = ++tail % capacity;

        if (empty) {
            empty = false;
        }
    }

    int dequeue() {
        if (empty) {
            throw std::out_of_range("Queue is empty");
        }

        if ((head + 1) % capacity == tail) {
            empty = true;
        }

        T temp = data[head];
        head = ++head % capacity;

        return temp;
    }

    bool is_empty() {
        return empty;
    }

private:
    T *data = nullptr;
    size_t head = 0;
    size_t tail = 0;
    size_t capacity = 10;
    bool empty = true;
};

template <class T>
size_t counter(Heap<T> &heap, size_t hand_capacity) {
    size_t counter = 0;
    Queue<size_t> queue;
    while (!heap.is_empty()) {
        size_t hand_size = 0;
        while(!heap.is_empty() && (hand_capacity - hand_size >= heap.peek_max())) {
            T temp = heap.extract_max();
            hand_size += temp;
            queue.enqueue(temp);
        }

        while (!queue.is_empty()) {
            T temp = queue.dequeue() / 2;
            if (temp) {
                heap.add(temp);
            }
        }

        counter++;
    }

    return counter;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    auto *arr = new size_t[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    Heap<size_t> heap(arr, n);

    size_t hand_capacity = 0;
    std::cin >> hand_capacity;

    std::cout << counter(heap, hand_capacity) << std::endl;

    delete [] arr;

    return 0;
}