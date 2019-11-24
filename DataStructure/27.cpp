#include<cstdio>
#include<cstdlib>
#include<algorithm>
struct Node {
	int value;
	int index;
};
bool compare(Node a, Node b) {
	return a.value < b.value;
}
void find(int value, Node *node_list, int start, int end) {
	if (start > end) {
		printf("error\n");
	} else {
		int middle = (start + end) / 2;
		if (node_list[middle].value == value) {
			printf("(%d %d)\n", value, node_list[middle].index);
		} else if (node_list[middle].value < value) {
			find(value, node_list, middle + 1, end);
		} else {
			find(value, node_list, start, middle - 1);
		}
	}
	return ;
}
int main() {
	int zuShu = 0, value = 0, index = 0;
	scanf("%d", &zuShu);
	Node *node_list = (Node *)malloc(zuShu * sizeof(Node));
	for (int i = 0; i < zuShu; i++) {
		scanf("%d%d", &value, &index);
		node_list[i].value = value;
		node_list[i].index = index;
	}
	std::sort(node_list, node_list + zuShu, compare);
	for (int i = 0; i < zuShu; i++) {
		printf("(%d %d)", node_list[i].value, node_list[i].index);
	}
	printf("\n");
	int toFind = 0;
	scanf("%d", &toFind);
	find(toFind, node_list, 0, zuShu - 1);

	return 0;
}

