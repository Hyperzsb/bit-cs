#include<cstdio>
#include<cstdlib>
#include<cmath>
#define INT_MAX 2100000000
namespace std_namespace {
	int pow_arr[50];
	void InitPowArr() {
		for (int i = 0; i < 50; i++) {
			if (i > 30) {
				pow_arr[i] = INT_MAX;
			} else {
				pow_arr[i] = int(exp2(i));
			}
		}
	}
	int FullTreeNode(int depth) {
		if (depth >= 31) {
			return INT_MAX;
		} else {
			return int(pow_arr[depth + 1] - 1);
		}
	}
	int FullTreeNodeAt(int depth) {
		if (depth >= 32) {
			return INT_MAX;
		} else {
			return int(pow_arr[depth]);
		}
	}
	int MaxTreeNode(int node_sum, int depth) {
		if (node_sum < depth + 1) {
			return 0;
		} else if (node_sum == depth + 1) {
			return 1;
		} else if (node_sum >= FullTreeNode(depth)) {
			return FullTreeNodeAt(depth);
		} else {
			if (node_sum - 1 > FullTreeNode(depth - 1)) {
				return FullTreeNodeAt(depth - 1) + MaxTreeNode(node_sum - FullTreeNode(depth - 1) - 1, depth - 1);
			} else {
				return MaxTreeNode(node_sum - 1, depth - 1);
			}
		}
	}
}

int main() {
	using namespace std_namespace;
	InitPowArr();
	int zuShu = 0;
	scanf("%d", &zuShu);
	while (zuShu--) {
		int node_sum = 0, depth = 0;
		scanf("%d%d", &node_sum, &depth);
		if (node_sum >= FullTreeNode(depth)) {
			printf("%d\n", FullTreeNodeAt(depth));
		} else {
			if (depth > 31) {
				printf("%d\n", MaxTreeNode(node_sum - (depth - 31), 31));
			} else {
				printf("%d\n", MaxTreeNode(node_sum, depth));
			}
		}
	}
	return 0;
}

