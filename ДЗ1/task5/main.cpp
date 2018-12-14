/*
5_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
*/

#include <iostream>
#include <cstring>

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

struct time_point {
    time_point() = default;

    size_t year = 0;
    size_t month = 0;
    size_t day = 0;
    int value = 0;

    bool operator > (const time_point &t) const {
        if (year != t.year) {
            return year > t.year;
        } else if (month != t.month) {
            return month > t.month;
        } else if (day != t.day){
            return day > t.day;
        } else {
            return value > t.value;
        }
    }
    bool operator < (const time_point &t) const {
        if (year != t.year) {
            return year < t.year;
        } else if (month != t.month) {
            return month < t.month;
        } else if (day != t.day) {
            return day < t.day;
        } else {
            return value < t.value;
        }
    }
    bool operator == (const time_point &t) const {
        return year == t.year && month == t.month && day == t.day;
    }
    bool operator != (const time_point &t) const {
        return !(*this == t);
    }
};
std::istream &operator >> (std::istream &is, time_point &t) {
    is >> t.day;
    is >> t.month;
    is >> t.year;

    return is;
}

template <class T>
inline void merge(T *dest, size_t size1, size_t size2, const Comparator<T> *comp) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    auto *src1 = new T[size1 + size2];
    auto *src2 = src1 + size1;

    for (size_t l = 0; l < size1 + size2; ++l) {
        src1[l] = dest[l];
    }

    while (i != size1 && j!= size2) {
        if ((*comp)(src1[i], src2[j])) {
            dest[k++] = src1[i++];
        } else {
            dest[k++] = src2[j++];
        }
    }

    while(i != size1) {
        dest[k++] = src1[i++];
    }

    while(j != size2) {
        dest[k++] = src2[j++];
    }

    delete [] src1;
}

template <class T>
void merge_sort(T *src, size_t size, const Comparator<T> *comp) {
    if (size == 1) {
        return;
    }

    size_t middle = size / 2;  // 2->1 (2 el)  3->1 (2el)  4->2(3 el)

    size_t size1 = middle;
    size_t size2 = size - middle;

    merge_sort(src, size1, comp);
    merge_sort(src + middle, size2, comp);

    merge(src, size1, size2, comp);
}

void get_dates(time_point *arr, size_t n, size_t &size) {
    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        time_point temp_birth;
        time_point temp_death;

        std::cin >> temp_birth >> temp_death;

        temp_birth.value = 1;
        temp_death.value = -1;

        time_point temp_18 = temp_birth;
        temp_18.year += 18;
        if (!(temp_18 < temp_death)) {
            size -= 2;
            continue;
        }

        time_point temp_80 = temp_18;
        temp_80.year += 62;
        temp_80.value = -1;

        time_point temp_disabled = temp_80 < temp_death ? temp_80 : temp_death;

        arr[j++] = temp_18;
        arr[j++] = temp_disabled;
    }
}

int main() {
    size_t n = 0;
    std::cin >> n;
    size_t size = n * 2;
    auto arr = new time_point[size];

    get_dates(arr, n, size);

    Less<time_point> comp;
    merge_sort(arr, size, &comp);

    size_t max = 0;
    size_t curr = 0;
    for (size_t i = 0; i < size; i++) {
        curr += arr[i].value;

        if(curr > max) {
            max = curr;
        }
    }

    std::cout << max << std::endl;

    delete[] arr;

    return 0;
}