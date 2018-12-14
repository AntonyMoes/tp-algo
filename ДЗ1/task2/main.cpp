/*
    Дан массив целых чисел А[0..n-1].
    Известно, что на интервале [0, m] значения массива строго возрастают,
    а на интервале [m, n-1] строго убывают. Найти m за O(log m).
    2 ≤ n ≤ 10000.
*/

#include <iostream>
template <class T>
size_t bin_index_search(const T *arr, size_t left_border, size_t right_border) {
    while (left_border + 1 < right_border) {
        size_t middle = (left_border + right_border) / 2;

        if (arr[middle] > arr[middle - 1]) {
            if (arr[middle] > arr[middle + 1]) {
                return middle;
            } else {
                left_border = middle;
            }
        } else {
            right_border = middle;
        }
    }

    return arr[left_border] > arr[right_border] ? left_border : right_border;

}

template <class T>
size_t bin_start(const T *arr, size_t n) {
    size_t j = 1;
    size_t prev_j = 0;
    while (arr[j] > arr[j - 1] && j <= n - 1) {
        prev_j = j;
        j *= 2;
    }

    if (j > n - 1) {
        j = n - 1;
    }

    return bin_index_search(arr, prev_j, j);
}

int main() {
    size_t n = 0;
    std::cin >> n;

    auto arr = new int[n];

    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    size_t result = bin_start(arr, n);
    std::cout << result << std::endl;

    delete [] arr;

    return 0;
}



