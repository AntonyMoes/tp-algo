#include <iostream>
#include <vector>
#include <cmath>


template <class T>
class Hash {
  public:
    size_t operator()(const T& data, size_t size) const {
        size_t hash = 0;
        modf(size * modf(data * (sqrt(5) - 1) / 2), hash);

        return hash;
    }

};

template<>
size_t Hash<std::string>::operator()(const std::string& data, size_t size) const {
    size_t hash = 0;
    for (const auto &datum : data) {
        hash = (hash * 127 + datum) % size;
    }
    return hash;
}

template <class T, class Hasher = Hash<T>>
class Set {
  public:
    Set() = default;
    Set(const Set<T> &table) = delete;
    Set(Set<T> &&table) = delete;

    Set<T> &operator =(const Set<T> &table) = delete;
    Set<T> &operator =(Set<T> &&table) = delete;

    bool has(const T &data) const {
        auto index = hasher(data, table.size());
        for(size_t i = 0; i < table.size(); i++) {
            index = (index + i + 1) % table.size();

            if (table[index] == "EMPTY" || table[index] == "DELETED") {
                if (table[index] == "DELETED") {
                    continue;
                } else {
                    break;
                }
            } else {
                if (table[index] == data) {
                    return true;
                }
            }
        }

        return false;
    }

    bool add(const T &data) {
        if (static_cast<float>(size) / table.size() >= max_alpha) {
            grow_table();
        }

        auto index = hasher(data, table.size());
        ssize_t first_del = -1;
        for (size_t i = 0; i < table.size(); i++) {
            index = (index + i + 1) % table.size();

            if (!(table[index] == "EMPTY" || table[index] == "DELETED")) {
                if (table[index] == data) {
                    return false;
                }
            } else if (table[index] == "DELETED" && first_del == -1) {
                first_del = index;
            } else {
                table[index] = data;
                size++;
                return true;
            }
        }

        if (first_del != -1) {
            table[first_del] = data;
            size++;
            return true;
        } else {
            return false;
        }
    }

    bool remove(const T &data) {
        auto index = hasher(data, table.size());
        for(size_t i = 0; i < table.size(); i++) {
            index = (index + i + 1) % table.size();

            if (table[index] == "EMPTY" || table[index] == "DELETED") {
                if (table[index] == "DELETED") {
                    continue;
                } else {
                    break;
                }
            } else if (table[index] == data){
                table[index] = "DELETED";
                size--;
                return true;
            }
        }

        return false;
    }

  private:
    void grow_table()  {
        auto temp_table = table;
        auto size = static_cast<size_t>(temp_table.size() * grow_factor);
        table = std::vector<T>(size, (T)"EMPTY");

        for (const auto &item : temp_table) {
            if (!(item == "EMPTY" || item == "DELETED")) {
                this->add(item);
            }
        }
    }

    Hasher hasher;
    const size_t default_table_size = 4;
    const float grow_factor = 2;
    const float max_alpha = 0.75;
    size_t size = 0;

    std::vector<T> table = std::vector<T>(4, (T)"EMPTY");
    /*
     * В этой таблице не храним цепочки, па при вставке пробируем
     * Нужны два значения: DEL и EMP:
     * EMP - ключа нет
     * DEL - идем дальше
     * вставка: запомнили первую позицию DEL, дальше идем до EMP/конца(table.size() шагов)
     *      вставляем в первый DEL, если был, или в EMP
     */
};

int main() {
    Set<std::string> set;
    char operation = 0;
    std::string data;
    while (std::cin >> operation >> data) {
        switch (operation) {
            case '+':
                std::cout << (set.add(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (set.remove(data) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (set.has(data) ? "OK" : "FAIL") << std::endl;
                break;
            default:;
        }
    }

    return 0;
}