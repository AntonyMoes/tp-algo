/*
 Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 Требуется найти k-ю порядковую статистику. т.е. напечатать число,
 которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 Напишите нерекурсивный алгоритм.

 Требования к дополнительной памяти: O(n).
 Требуемое среднее время работы: O(n).

 Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 Описание для случая прохода от начала массива к концу:
    - Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
    - Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
      Затем располагаются элементы, строго бОльшие опорного.
      В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
    - Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
    - Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
    - Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
    - Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
    - В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

 6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

#include <iostream>
#include <random>

template <class T>
class Comparator {
public:
    virtual bool operator()(const T &arg1, const T &arg2) const = 0;
};

template <class T>
class Less : public Comparator<T> {
public:
    bool operator()(const T &arg1, const T &arg2) const override {
        return arg1 < arg2;
    }
};

template <class T>
class MyIntRandomizer {
public:
    T operator()(T start, T stop) {
        std::mt19937 mt(rd());
        std::uniform_int_distribution<T> dist(start, stop);
        return dist(mt);
    }

private:
    std::random_device rd;
};

template <class T>
size_t partition(T src[], size_t size, const Comparator<T> *comp, MyIntRandomizer<size_t> &randomizer) {
    size_t pivot = randomizer(0, size - 1);
    std::swap(src[0], src[pivot]);

    size_t i = size - 1;
    size_t j = size - 1;

    while (j != 0) {
        if ((*comp)(src[j], src[0])) {
            j--;
        } else {
            std::swap(src[i], src[j]);

            j--;
            i--;
        }
    }

    std::swap(src[0], src[i]);
    pivot = i;

    return pivot;
}

template <class T>
T ord_statistic(const T src[], size_t size, size_t stat, const Comparator<T> *comp) {
    size_t pivot = 0;
    MyIntRandomizer<size_t> randomizer;

    T *temp_arr = new T[size];
    for (size_t i = 0; i < size; i++) {
        temp_arr[i] = src[i];
    }
    auto ptr = temp_arr;

    while (pivot = partition(ptr, size, comp, randomizer), pivot != stat) {
        if (stat < pivot) {
            size = pivot;
        } else {
            ptr += (pivot + 1);
            size -= (pivot + 1);
            stat -= (pivot + 1);
        }
    }
    auto answer = ptr[pivot];

    delete [] temp_arr;

    return answer;
}


int main() {
    size_t size = 0;
    size_t stat = 0;
    std::cin >> size >> stat;

    auto arr = new int[size];
    for (size_t i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    Less<int> comp;
    std::cout << ord_statistic(arr, size, stat, &comp) << std::endl;

    delete[] arr;

    return 0;
}