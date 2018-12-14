#include <iostream>
#include <cstring>

const size_t DICT_SIZE = 256;
size_t count[DICT_SIZE];
size_t count_pos[DICT_SIZE];

template <class T>
class My_vector{
public:
    My_vector() {
        data = new T[capacity];
    }
    ~My_vector() {
        for (size_t i = 0; i < size; i++) {
            delete[] data[i];
        }
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
void msd_count_sort(T *src, size_t size ,size_t digit) {
    std::memset(count, 0, DICT_SIZE * sizeof(size_t));

    for (size_t i = 0; i < size; i++) {
        count[src[i][digit]]++;
    }

    count_pos[0] = 0;

    for (size_t i = 1; i < DICT_SIZE; i++) {
        count_pos[i] = count_pos[i - 1] + count[i - 1];
    }

    auto result = new T[size];
    for (size_t i = 0; i < size; i++) {
        result[count_pos[src[i][digit]]++] = src[i];
    }

    std::memcpy(src, result, size * sizeof(T));

    delete[] result;

    size_t start = 0;
    size_t stop = 0;
    while (stop < size - 1) {
        if (src[stop][digit] < src[stop + 1][digit]) {
            if (start != stop ) msd_count_sort(src + start, stop - start + 1, digit + 1);
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
    My_vector<char *> vec;

    //char buff[BUFF_SIZE];
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
    }

    return 0;
}
