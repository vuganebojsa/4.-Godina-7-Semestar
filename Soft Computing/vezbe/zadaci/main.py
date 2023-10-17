import numpy as np

if __name__ == '__main__':
    a = np.random.randint(1, 10, (4, 4))
    print('a',a)
    row_sum = np.sum(a, axis=1)
    print(row_sum)
    b = np.random.randint(1, 10, (5, 5))
    for i in range(5):
        print(b[i])
    for i in range(b.shape[1]):
        b[:, i].sort()
    print()
    for i in range(5):
        print(b[i])

    min_value = np.min(b)
    