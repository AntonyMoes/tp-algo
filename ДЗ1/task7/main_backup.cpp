//
// Created by antonymo on 14.10.18.
//

#include <iostream>
#include <cstring>

const size_t DICT_SIZE = 256;

template <class T>
class Vector{
public:
    Vector() {
        data = new T[capacity];
    }
    ~Vector() {
        delete[] data;
    }

    void push_back(const T &item) {
        if (size == capacity) {
            realloc();
        }

        data[size++] = item;
    }

    T *get_data() {
        return data;
    }
    size_t get_size() {
        return size;
    }

private:
    void realloc() {
        capacity *= 2;

        auto *temp_data = new T[capacity];

        for (size_t i = 0; i < size; i++) {
            temp_data[i] = std::move(data[i]);
        }

        delete[] data;

        data = temp_data;
    }

    T *data;
    size_t size = 0;
    size_t capacity = 1000;
};

template <class T>
inline void msd_count_sort(T src[], size_t size ,size_t digit) {
    auto count = new size_t[DICT_SIZE];

    std::memset(count, 0, DICT_SIZE * sizeof(size_t));

    for (size_t i = 0; i < size; i++) {
        count[src[i][digit]]++;
    }

    auto count_pos = new size_t[DICT_SIZE];
    auto copy_count_pos = new size_t[DICT_SIZE];
    copy_count_pos[0] = count_pos[0] = 0;
    for (size_t i = 1; i < DICT_SIZE; i++) {
        copy_count_pos[i] = count_pos[i] = count_pos[i - 1] + count[i - 1];
    }

    auto result = new T[size];
    for (size_t i = 0; i < size; i++) {
        result[count_pos[src[i][digit]]++] = src[i];
    }

    for (size_t i = 0 ; i < size; i++) {
        src[i] = result[i];
    }

    delete[] count;
    delete[] count_pos;
    delete[] result;

    digit++;

    size_t i = 1;
    while (i < DICT_SIZE - 1) {
        if (copy_count_pos[i] != copy_count_pos[i + 1]) {
            msd_count_sort(src + copy_count_pos[i], copy_count_pos[i + 1] - copy_count_pos[i], digit);
        }
        i++;
    }

    if(size - copy_count_pos[DICT_SIZE - 1] != 0) {
        msd_count_sort(src + copy_count_pos[DICT_SIZE - 1], size - copy_count_pos[DICT_SIZE - 1], digit);
    }

    delete[] copy_count_pos;

}

int main() {
    Vector<std::string> vec;

    std::string temp;
    while (std::cin >> temp) {
        vec.push_back(temp);
    }

    std::string *str = vec.get_data();
    size_t size = vec.get_size();
    msd_count_sort(str, size, 0);

    for (size_t i = 0; i < size; i++) {
        std::cout << str[i] << std::endl;
    }
    return 0;
}