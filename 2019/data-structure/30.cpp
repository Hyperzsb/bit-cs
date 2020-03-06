#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using std::sort;
int median_num = 0, median[100] = {0};
int GetNum(char *str) {
	int str_len = strlen(str);
	int ans = 0;
	if (str[0] == '-') {
		for (int i = 1; i < str_len; i++)
			ans = ans * 10 + (str[i] - '0');
		ans = -ans;
	} else {
		for (int i = 0; i < str_len; i++)
			ans = ans * 10 + (str[i] - '0');
	}
	return ans;
}
void Swap(int *node, int index_a, int index_b) {
	node[index_a] ^= node[index_b];
	node[index_b] ^= node[index_a];
	node[index_a] ^= node[index_b];
}
void QuickSort(int *node, int start, int end) {
	if (end - start < 4) {
		sort(node + start, node + end + 1);
	} else {
		int center = (start + end) / 2;
		if ((node[start] < node[center] && node[center] < node[end]) || (node[start] > node[center] && node[center] > node[end]))
			Swap(node, center, start);
		if ((node[start] < node[end] && node[end] < node[center]) || (node[start] > node[end] && node[end] > node[center]))
			Swap(node, end, start);
		median[median_num++] = node[start];
		int i = start + 1, j = end, flag = node[start];
		while (true) {
			while (node[i] <= flag)
				i++;
			while (node[j] >= flag)
				j--;
			if (i < j) {
				Swap(node, i, j);
			} else
				break;
		}
		Swap(node, j, start);
		QuickSort(node, start, j - 1);
		QuickSort(node, j + 1, end);
	}
}
int main() {
	char tmp_str[20] = {'\0'};
	int node_num = 0, node[1000] = {0};
	scanf("%s", tmp_str);
	while (strcmp(tmp_str, "#") != 0) {
		node[node_num++] = GetNum(tmp_str);
		scanf("%s", tmp_str);
	}
	if (node_num <= 5)
		sort(node, node + node_num);
	else
		QuickSort(node, 0, node_num - 1);
	printf("After Sorting:\n");
	for (int i = 0; i < node_num; i++)
		printf("%d ", node[i]);
	printf("\nMedian3 Value:\n");
	if (median_num != 0) {
		for (int i = 0; i < median_num; i++)
			printf("%d ", median[i]);
		printf("\n");
	} else
		printf("none\n");

	return 0;
}
