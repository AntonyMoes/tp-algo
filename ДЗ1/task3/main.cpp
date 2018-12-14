/*
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
*/

#include <iostream>
#include <exception>

template <class T>
class Queue {
public:
    Queue() {
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void enqueue(const T &item) {
        if (head == tail && !empty) {
            int *temp_pointer = new T[capacity * 2];

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

int main() {
    size_t n = 0;
    Queue<int> queue;
    bool correct = true;

    std::cin >> n;

    for (size_t i = 0; i < n; i++) {
        size_t choice = 0;
        int item = 0;
        std::cin >> choice >> item;

        if (choice == 3) {
            queue.enqueue(item);
        } else /* if (choice == 2) */ {
            if (queue.is_empty()) {
                if (item != -1) {
                    correct = false;
                }
            } else if (item != queue.dequeue()) {
                correct = false;
            }
        }
    }

    if (correct) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}