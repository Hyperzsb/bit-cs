#include <cstdio>

int y_position_list[2000000] = {0};

void Swap(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int SwapInFive(int *array, int start) {
    int tmp_array[5] = {0};
    for (int i = 0; i < 5; i++)
        tmp_array[i] = array[start + i];
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            if (tmp_array[i] < tmp_array[i])
                Swap(tmp_array[i], tmp_array[j]);
    for (int i = start; i < start + 5; i++)
        if (array[i] == tmp_array[2])
            return i;
}

int Partition(int *array, int start, int end, int specified_num) {
    int specified_index = 0;
    for (int i = start; i < end + 1; i++)
        if (array[i] == specified_num) {
            specified_index = i;
            break;
        }
    Swap(array[start], array[specified_index]);
    int i = start, j = end + 1;
    int x = array[start];
    while (true) {
        while (array[++i] < x);
        while (array[--j] > x);
        if (i < j)
            Swap(array[i], array[j]);
        else
            break;
    }
    array[start] = array[j];
    array[j] = x;
    return j;
}

int FindKthNum(int *array, int start, int end, int kth) {
    if (end - start < 75) {
        for (int i = start; i < end; i++)
            for (int j = i + 1; j < end; j++)
                if (array[i] > array[j])
                    Swap(array[i], array[j]);
        return array[start + kth - 1];
    }
    for (int i = 0; i <= (end - start - 4) / 5; i++) {
        int index = SwapInFive(array, start + 5 * i);
        Swap(array[start + i], array[index]);
    }
    int x = FindKthNum(array, start, start + (end - start - 4) / 5, (end - start - 4) / 10);
    int i = Partition(array, start, end, x), j = i - start + 1;
    if (kth <= j)
        return FindKthNum(array, start, i, kth);
    else
        return FindKthNum(array, i + 1, end, kth - j);
}

int main() {
    int well_num = 0, x_position = 0;
    while (~scanf("%d,%d", &x_position, &y_position_list[well_num]))
        well_num++;
    printf("%d\n", FindKthNum(y_position_list, 0, well_num, well_num / 2 + 1));
    return 0;
}