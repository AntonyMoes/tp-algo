/*
Даны два массива целых чисел одинаковой длины A[0..n−1] и B[0..n−1].
Необходимо найти первую пару индексов i0 и j0, i0≤j0, такую что A[i0]+B[j0]=max{A[i]+B[j],где0≤i<n,0≤j<n,i≤j}.
Время работы – O(n).
Ограничения: 1≤n≤100000,0≤A[i]≤100000,0≤B[i]≤100000  для любого i.
Sample Input:
4
4 -8 6 0
-10 3 1 1
Sample Output:
0 1
*/

#include <iostream>
#include <tuple>
template <class T>
std::pair<size_t, size_t> get_two_pos(const T *arr1, const T *arr2, size_t  n) {
    size_t max_arr1_pos = 0;
    size_t pos1 = 0;
    size_t pos2 = 0;
    T max = arr2[0] + arr1[0];

    for (size_t i = 1; i < n; ++i) {
        if (arr1[i] > arr1[max_arr1_pos]) {
            max_arr1_pos = i;
        }

        if (arr1[max_arr1_pos] + arr2[i] > max) {
            max = arr1[max_arr1_pos] + arr2[i];
            pos1 = max_arr1_pos;
            pos2 = i;
        }
    }

    return std::make_pair(pos1, pos2);
}

int main()
{
    size_t n = 0;
    std::cin >> n;

    int *arr1 = new int[n];
    int *arr2 = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> arr1[i];
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> arr2[i];
    }

    size_t pos1 = 0;
    size_t pos2 = 0;
    std::tie(pos1, pos2) = get_two_pos(arr1, arr2, n);

    std::cout << pos1 << " " << pos2 << std::endl;

    delete [] arr1;
    delete [] arr2;

    return 0;
}