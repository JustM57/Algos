from collections import defaultdict


#обратное преобразование будем делать исходя из свойств биекции - составим словарь
def int_to_roman(num):
    res = ''
    d = num // 10
    ds = {
        5: 'L',
        4: 'XL',
        3: 'XXX',
        2: 'XX',
        1: 'X',
        0: ''
    }
    res += ds[d]
    c = num % 10
    cs = {
        9: 'IX',
        8: 'VIII',
        7: 'VII',
        6: 'VI',
        5: 'V',
        4: 'IV',
        3: 'III',
        2: 'II',
        1: 'I',
        0: ''
    }
    res += cs[c]
    return res


def roman_to_dict():
    convertor = {}
    for i in range (1, 51):
        convertor[int_to_roman(i)] = i
    return convertor


def sorted_roman(li):
    tr_dict = roman_to_dict()
    li = sorted(list(map(lambda x: tr_dict[x], li)))
    li = list(map(int_to_roman, li))
    return li


if __name__ == "__main__":
    n = int(input())
    kings = defaultdict(list)
    for i in range(n):
        line = input()
        king = line.split()
        kings[king[0]].append(king[1])
    for key in sorted(kings.keys()):
        for king in sorted_roman(kings[key]):
            print(' '.join([key, king]))
