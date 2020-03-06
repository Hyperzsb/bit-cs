#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
namespace std_namespace {
	using namespace std;
	struct Node {
		int id;
		string *data;
		int in_route_num;
		int *in_routes;
		int out_route_num;
		int *out_routes;
		int flag;
	};
	void TopologicalSort(Node *node_arr, int node_num) {
		int flag = 1;
		while (flag) {
			int flag_tmp = 0;
			for (int i = 0; i < node_num; i++) {
				cout << node_arr[i].data->c_str() << " " << node_arr[i].flag << " " << node_arr[i].in_route_num << endl;
				if (node_arr[i].flag != 1 && node_arr[i].in_route_num == 0) {
					flag_tmp = 1;
					cout << node_arr[i].data->c_str() << "-";
					node_arr[i].flag = 1;
					for (int j = 0; j < node_num; j++) {
						if (node_arr[i].out_routes[j] == 1) {
							node_arr[j].in_route_num--;
							node_arr[j].in_routes[i] = 0;
						}
					}
				}
			}
			flag = flag_tmp;
		}
		return ;
	}
}

int main() {
	using namespace std_namespace;
	int node_num = 0, route_num = 0;
	string data;
	scanf("%d,%d", &node_num, &route_num);
	Node *node_arr = (Node *)malloc(node_num * sizeof(Node));
	Node *node_arr_tmp = (Node *)malloc(node_num * sizeof(Node));
	for (int i = 0; i < node_num; i++) {
		cin >> data;
		node_arr[i].data = new string(data);
		node_arr[i].in_route_num = 0;
		node_arr[i].in_routes = (int *)malloc(node_num * sizeof(int));
		node_arr[i].out_route_num = 0;
		node_arr[i].out_routes = (int *)malloc(node_num * sizeof(int));
		node_arr[i].flag = 0;
		node_arr_tmp[i].data = new string(data);
		node_arr_tmp[i].in_route_num = 0;
		node_arr_tmp[i].in_routes = (int *)malloc(node_num * sizeof(int));
		node_arr_tmp[i].out_route_num = 0;
		node_arr_tmp[i].out_routes = (int *)malloc(node_num * sizeof(int));
		node_arr_tmp[i].flag = 0;
		for (int j = 0; j < node_num; j++) {
			node_arr[i].in_routes[j] = 0;
			node_arr[i].out_routes[j] = 0;
			node_arr_tmp[i].in_routes[j] = 0;
			node_arr_tmp[i].out_routes[j] = 0;
		}
	}
	int start = 0, end = 0, weight = 0;
	printf("???%d\n", route_num);
	for (int i = 0; i < route_num - 1; i++) {
		scanf("<%d,%d,%d>,", &start, &end, &weight);
		node_arr[start].out_route_num++;
		node_arr[start].out_routes[end] = 1;
		node_arr[end].in_route_num++;
		node_arr[end].in_routes[start] = 1;
		node_arr_tmp[start].out_route_num++;
		node_arr_tmp[start].out_routes[end] = 1;
		node_arr_tmp[end].in_route_num++;
		node_arr_tmp[end].in_routes[start] = 1;
	}
	scanf("<%d,%d,%d>", &start, &end, &weight);
	node_arr[start].out_route_num++;
	node_arr[start].out_routes[end] = 1;
	node_arr[end].in_route_num++;
	node_arr[end].in_routes[start] = 1;
	node_arr_tmp[start].out_route_num++;
	node_arr_tmp[start].out_routes[end] = 1;
	node_arr_tmp[end].in_route_num++;
	node_arr_tmp[end].in_routes[start] = 1;
	//TopologicalSort(node_arr_tmp, node_num);

	return 0;
}
