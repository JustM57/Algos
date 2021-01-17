#!/usr/bin/python3
def merge(a, b, inv):
    n = len(a)
    m = len(b)
    i = 0
    j = 0
    c = []
    while (i + j) < (n + m):
        if ((j == m) or ((i < n) and (a[i] <= b[j]))):
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            inv += n - i
            j += 1
    return c, inv


def merge_sort(a, inv):
    n = len(a)
    if n > 1:
        l = a[:n // 2]
        r = a[n // 2:]
        l, inv = merge_sort(l, inv)
        r, inv = merge_sort(r, inv)
        a, inv = merge(l, r, inv)
    return a, inv


if __name__ == "__main__":
    n = int(input())
    line = input()
    a = list(map(int, line.split()))
    inv = 0
    a, inv = merge_sort(a, inv)
    print(inv)