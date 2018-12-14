/*
 7_1. MSD для строк.
 Дан массив строк. Количество строк не больше 10^5.
 Отсортировать массив методом поразрядной сортировки MSD по символам.
 Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
*/

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

template <>
class Vector<char *>{
public:
    Vector() {
        data = new char *[capacity];
    }
    ~Vector() {
        for (size_t i = 0; i < size; i++) {
            delete [] data[i];
        }
        delete [] data;
    }

    void push_back(const char * item) {
        if (size == capacity) {
            realloc();
        }

        data[size] = new char[strlen(item) + 1];
        strncpy(data[size], item, strlen(item) + 1);

        size++;
    }

    char **get_data() {
        return data;
    }
    size_t get_size() {
        return size;
    }

private:
    void realloc() {
        capacity *= 2;

        auto *temp_data = new char *[capacity];

        for (size_t i = 0; i < size; i++) {
            temp_data[i] = data[i];
        }

        delete[] data;

        data = temp_data;
    }

    char **data;
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

    count_pos[0] = 0;
    for (size_t i = 1; i < DICT_SIZE; i++) {
        count_pos[i] = count_pos[i - 1] + count[i - 1];
    }
    size_t start = count_pos[1]; // при рекурсивном вызове отбросим \0, если они есть

    auto result = new T[size];
    for (size_t i = 0; i < size; i++) {
        result[count_pos[src[i][digit]]++] = src[i];
    }

    for (size_t i = 0 ; i < size; i++) {
        src[i] = std::move(result[i]);
    }

    delete[] result;

    size_t stop = start;

    while (stop < size - 1) {
        if (src[stop][digit] < src[stop + 1][digit]) {
            if (start != stop) {
                msd_count_sort(src + start, stop - start + 1, digit + 1);
            }
            start = ++stop;
        } else {
            stop++;
        }
    }
    if (start != stop) {
        msd_count_sort(src + start, stop - start + 1, digit + 1);
    }
}

int main() {
    Vector<char *> vec;
    std::string temp;  //ну он только для чтения, удобно же
    while (std::cin >> temp) {
        size_t temp_size = temp.size();
        if(!temp_size) {
            continue;
        }

        vec.push_back(temp.c_str());
    }

    char **str = vec.get_data();
    size_t size = vec.get_size();
    msd_count_sort(str, size, 0);

    for (size_t i = 0; i < size; i++) {
        std::cout << str[i] << std::endl;
    }

    return 0;
}