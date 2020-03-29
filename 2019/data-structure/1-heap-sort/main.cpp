#include<cstdio>
#include<cstdlib>

bool IsHeap(int *node, int index, int node_num) {
    if (index * 2 + 1 > node_num - 1) {
        return true;
    } else if (index * 2 + 2 > node_num - 1) {
        if (node[index] >= node[index * 2 + 1])
            return true;
        else
            return false;
    } else {
        int maxNum = node[index * 2 + 1] >= node[index * 2 + 2] ? 1 : 2;
        if (node[index] >= node[index * 2 + maxNum])
            return true;
        else
            return false;
    }
}

void Reform(int *node, int index, int node_num) {
    if (index * 2 + 1 > node_num - 1) {
        return;
    } else if (index * 2 + 2 > node_num - 1) {
        if (node[index] < node[index * 2 + 1]) {
            node[index] ^= node[index * 2 + 1];
            node[index * 2 + 1] ^= node[index];
            node[index] ^= node[index * 2 + 1];
            Reform(node, index * 2 + 1, node_num);
        }
    } else {
        int maxNum = node[index * 2 + 1] >= node[index * 2 + 2] ? 1 : 2;
        if (node[index] < node[index * 2 + maxNum]) {
            node[index] ^= node[index * 2 + maxNum];
            node[index * 2 + maxNum] ^= node[index];
            node[index] ^= node[index * 2 + maxNum];
            Reform(node, index * 2 + maxNum, node_num);
        }
    }
}

void CreateHeap(int *node, int node_num) {
    for (int i = node_num - 1; i >= 0; i--) {
        if (IsHeap(node, i, node_num))
            continue;
        else {
            if (i * 2 + 2 > node_num - 1) {
                if (node[i] < node[i * 2 + 1]) {
                    node[i] ^= node[i * 2 + 1];
                    node[i * 2 + 1] ^= node[i];
                    node[i] ^= node[i * 2 + 1];
                }
            } else {
                int maxNum = node[i * 2 + 1] >= node[i * 2 + 2] ? 1 : 2;
                if (node[i] < node[i * 2 + maxNum]) {
                    node[i] ^= node[i * 2 + maxNum];
                    node[i * 2 + maxNum] ^= node[i];
                    node[i] ^= node[i * 2 + maxNum];
                    Reform(node, i * 2 + maxNum, node_num);
                }
            }
        }
    }
}

void PopHeap(int *node, int node_num) {
    node[0] = node[node_num - 1];
    Reform(node, 0, node_num - 1);
}

int main() {
    int node_num = 0, node[1000] = {0};
    scanf("%d", &node_num);
    for (int i = 0; i < node_num; i++)
        scanf("%d", &node[i]);
    CreateHeap(node, node_num);
    for (int i = 0; i < node_num; i++)
        printf("%d ", node[i]);
    printf("\n");
    PopHeap(node, node_num--);
    for (int i = 0; i < node_num; i++)
        printf("%d ", node[i]);
    printf("\n");
    PopHeap(node, node_num--);
    for (int i = 0; i < node_num; i++)
        printf("%d ", node[i]);
    printf("\n");

    return 0;
}