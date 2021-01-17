#include <iostream> 
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>

using namespace std;
const long INF = numeric_limits<long>::max();

/* Обсудим алгоритм:
С одной стороны нужно добавление и минимум за log n - обычная куча
С другой стороны функция descrease тоже должна работать за log
Эта функция с одной стороны перестраивает кучу за тот же лог
А с другой стороны поиск элемента должен быть за лог
Соответсвенно это бинарный поиск в отсортированном массиве
Отсортированным массивом может быть массив текущих элементов(их порядок)
С другой стороны в этом же самом массиве должна быть и ссылка на ноду дерева
Я думаю не экономить на массивах и реализовать кучу и
Отдельно реализовать отсортированный ассоциативный массив
Или даже множество. Как из массива удалить элемент не за линейное время?
Убирать дырки только при переаллокации памяти.
*/ 
class Heap {
    private:
    vector<long> a;
    vector<long> b;
    long size;
    long counter;

    void swap_els(long i, long j) {
        if (i != j) {
            swap(a[i], a[j]);
            swap(a[i + 1], a[j + 1]);
            swap(b[a[i + 1]], b[a[j + 1]]);
        }
    }

    public:
    Heap() {
        a = vector<long>(0); //val & it
        b = vector<long>(0); //pointers between it -> tree node
        size = 0;
        counter = 0;
    }

    void insert(long val) {
        long i = size;
        long j;
        a.push_back(val);
        a.push_back(counter);
        ++counter;
        b.push_back(i);
        size += 2;
        while (i > 1) {
            j = i / 2 - 1;
            if ((j % 2) == 1) --j;
            if (a[i] < a[j]) {
                swap_els(i, j);
            }
            i = j;
        }
    }

    pair<long, long> extract_min() {
        long cur, left, right, new_i;
        long i = size - 2;
        long res = a[0];
        long res_id = a[1] + 1;
        if (i!= 0) swap_els(i, 0);
        b[a[i + 1]] = -1;
        size -= 2;
        a.pop_back();
        a.pop_back();
        i = 0;
        new_i = i;
        while (2 * i + 2 < size) {
            cur = a[i];
            left = a[2 * i + 2];
            if (2 * i + 4 >= size) {
                right = INF; 
            } else right = a[2 * i + 4];
            if ((left < right) && (left < cur)) {
                swap_els(i, 2 * i + 2);
                new_i = 2 * i + 2;
            } else {
                if (right < cur) {
                    swap_els(i, 2 * i + 4);
                    new_i = 2 * i + 4;
                }
            }
            if (i != new_i) {
                i = new_i;
            } else break;
        }
        return {res, res_id};
    }

    long heap_size() {return size / 2; }

    void decrease_key(long m, long n) {
        long index = -1;
        long i, j;
        for (long i = 0; i < size / 2; ++i) {
            if (n == a[2 * i + 1]) {
                index = i;
                break;
            }
        }
        index *= 2;
        if (index >= 0) {
            a[index] = n;
            i = index;
            while (i > 1) {
                j = i / 2 - 1;
                if ((j % 2) == 1) --j;
                if (a[i] < a[j]) {
                    swap_els(i, j);
                }
                i = j;
            }
        }
    }

    void decrease(long m, long n) {
        --m;
        long j, i;
        if (m < counter) {
            i = b[m];
        } else i = -1;
        if (i >= 0) {
            long old = a[i];
            a[i] = n;
            if (old > a[i]) {
                while (i > 1) {
                    j = i / 2 - 1;
                    if ((j % 2) == 1) --j;
                    if (a[i] < a[j]) {
                        swap_els(i, j);
                    }
                    i = j;
                }
            }
        }
    }

    void print() {
        for (long i = 0; i < size; ++i) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        for (long i = 0; i < counter; ++i) {
            cout << b[i] << ' ';
        }
        cout << '\n';
    }
};


int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    long m, n;
    pair<long, long> res;
    string word;
    Heap heap = Heap();
    while (cin >> word) {
        if (word == "push") {
            cin >> m;
            heap.insert(m);
        } else if (word == "extract-min") {
            if (heap.heap_size() == 0) {
                cout << '*' << '\n';
            } else {
                res = heap.extract_min();
                cout << res.first << ' ' << res.second << '\n';
            }
        } else if (word == "decrease-key") {
            cin >> m >> n;
            heap.decrease(m, n);
        }
        // heap.print();
    }
    return 0;
}
