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
void msd_count_sort(T src[], size_t size ,size_t digit) {
    size_t count[DICT_SIZE];
    size_t count_pos[DICT_SIZE];

    std::memset(count, 0, DICT_SIZE * sizeof(size_t));

    for (size_t i = 0; i < size; i++) {
        count[src[i][digit]]++;
    }

    /*count_pos[0] = 0;
    for (size_t i = 1; i < DICT_SIZE; i++) {
        count_pos[i] = count_pos[i - 1] + count[i - 1];
    }*/

    size_t copy_count_pos[DICT_SIZE];
    copy_count_pos[0] = count_pos[0] = 0;
    for (size_t i = 1; i < DICT_SIZE; i++) {
        copy_count_pos[i] = count_pos[i] = count_pos[i - 1] + count[i - 1];
    }

    auto result = new T[size];
    for (size_t i = 0; i < size; i++) {
        result[count_pos[src[i][digit]]++] = src[i];
    }

    for (size_t i = 0 ; i < size; i++) {
        src[i] = std::move(result[i]);
    }

    delete[] result; // TODO()ПЕРВЫЙ ВАРИАНТ: точен copy_count_pos, но не его замена

    /*size_t start = 0;
    size_t stop = 0;
    while (stop < size - 1) {
        if (src[stop][digit] < src[stop + 1][digit]) {
            if (start != stop ) inner_count_sort(src + start, stop - start + 1, digit + 1, count, count_pos);
            start = ++stop;
        } else {
            stop++;
        }
    }
    if (start != stop) {
        inner_count_sort(src + start, stop - start + 1, digit + 1, count, count_pos);
    }*/
    size_t i = 1;
    while (i < DICT_SIZE - 1) {
        if (copy_count_pos[i] != copy_count_pos[i + 1]) {
            msd_count_sort(src + copy_count_pos[i], copy_count_pos[i + 1] - copy_count_pos[i], digit + 1);
        }
        i++;
    }

    if(size - copy_count_pos[DICT_SIZE - 1] != 0) {
        msd_count_sort(src + copy_count_pos[DICT_SIZE - 1], size - copy_count_pos[DICT_SIZE - 1], digit + 1);
    }

    //delete[] copy_count_pos;

}


int main() {
    Vector<char *> vec;

    size_t temp_size = 0;
    char *temp_ptr = nullptr;

    std::string temp;
    while (std::cin >> temp) {
        temp_size = temp.size();
        if(!temp_size) {
            continue;
        }

        temp_ptr = new char[temp_size + 1];
        std::strncpy(temp_ptr, temp.c_str(), temp_size);
        temp_ptr[temp_size] = '\0';

        vec.push_back(temp_ptr);
    }

    char **str = vec.get_data();
    size_t size = vec.get_size();
    msd_count_sort(str, size, 0);

    for (size_t i = 0; i < size; i++) {
        std::cout << str[i] << std::endl;
        delete [] str[i];
    }

    return 0;
}