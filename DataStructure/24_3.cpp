#include<cstdio>
#include<cstdlib>
#include<cstring>
struct Node {
	int id;
	char *data;
	int in_route_num;
	Node **in_routes;
	int *in_routes_weight;
	int out_route_num;
	Node **out_routes;
	int *out_route_weight;
	Node(int id_, char *data_, int node_num) {
		id = id_;
		int data_len = strlen(data_);
		data = (char *)malloc((data_len + 3) * sizeof(char));
		strcpy(data, data_);
		data[data_len] = '\0';
		in_route_num = 0;
		in_routes = (Node **)malloc(node_num * sizeof(Node *));
		out_route_num = 0;
		out_routes = (Node **)malloc(node_num * sizeof(Node *));
	}
};
struct ListNode {
	Node *node;
	ListNode *previous_node;
	ListNode *next_node;
	ListNode(Node *node_) {
		node = node_;
		previous_node = NULL;
		next_node = NULL;
	}
};
void TopolgicalSort(ListNode *head, int node_num) {
	int remained = node_num;
	ListNode *current;
	while (remained > 1) {
		current = head;
		while (current != NULL) {
			if (current->node->in_route_num == 0) {
				printf("%s-", current->node->data);
				for (int i = 0; i < current->node->out_route_num; i++) {
					current->node->out_routes[i]->in_route_num--;
				}
				remained--;
				if (current == head) {
					head = current->next_node;
					if (head != NULL) {
						head->previous_node = NULL;
					}
				} else {
					if (current->next_node == NULL) {
						current->previous_node->next_node = NULL;
					} else {
						current->previous_node->next_node = current->next_node;
						current->next_node->previous_node = current->previous_node;
					}
				}
				delete current;
				break;
			} else {
				current = current->next_node;
			}
		}
	}
	printf("%s\n", head->node->data);
}
int main() {
	int node_num = 0, route_num = 1;
	scanf("%d,%d", &node_num, &route_num);
	ListNode *head, *head_tmp, *current, *current_tmp;
	Node **node_arr = (Node **)malloc(node_num * sizeof(Node *));
	Node **node_arr_tmp = (Node **)malloc(node_num * sizeof(Node *));
	char nodes_c_str[10000] = {'\0'};
	scanf("%s", nodes_c_str);
	int index = 0;
	for (int i = 0; i < node_num; i++) {
		char node_data[100];
		int j = 0;
		for (; ; j++, index++) {
			if ((nodes_c_str[index] == ',') || (nodes_c_str[index] == '\0')) {
				j++;
				index++;
				break;
			}
			node_data[j] = nodes_c_str[index];
		}
		node_data[j] = '\0';
		Node *new_node = new Node(i, node_data, node_num);
		node_arr[i] = new_node;
		Node *new_node_tmp = new Node(i, node_data, node_num);
		node_arr_tmp[i] = new_node_tmp;
		ListNode *new_list_node = new ListNode(new_node);
		ListNode *new_list_node_tmp = new ListNode(new_node_tmp);
		if (i == 0) {
			head = new_list_node;
			current = head;
			head_tmp = new_list_node_tmp;
			current_tmp = head_tmp;
		} else {
			current->next_node = new_list_node;
			new_list_node->previous_node = current;
			current = new_list_node;
			current_tmp->next_node = new_list_node_tmp;
			new_list_node->previous_node = current_tmp;
			current_tmp = new_list_node_tmp;
		}
	}
	getchar();
	int start = 0, end = 0, weight = 0;
	for (int i = 0; i < route_num - 1; i++) {
		scanf("<%d,%d,%d>,", &start, &end, &weight);
		node_arr[start]->out_routes[node_arr[start]->out_route_num] = node_arr[end];
		node_arr[start]->out_route_num++;
		node_arr[end]->in_routes[node_arr[end]->in_route_num] = node_arr[start];
		node_arr[end]->in_route_num++;
		node_arr_tmp[start]->out_routes[node_arr_tmp[start]->out_route_num] = node_arr_tmp[end];
		node_arr_tmp[start]->out_route_num++;
		node_arr_tmp[end]->in_routes[node_arr_tmp[end]->in_route_num] = node_arr_tmp[start];
		node_arr_tmp[end]->in_route_num++;
	}
	scanf("<%d,%d,%d>", &start, &end, &weight);
	node_arr[start]->out_routes[node_arr[start]->out_route_num] = node_arr[end];
	node_arr[start]->out_route_num++;
	node_arr[end]->in_routes[node_arr[end]->in_route_num] = node_arr[start];
	node_arr[end]->in_route_num++;
	node_arr_tmp[start]->out_routes[node_arr_tmp[start]->out_route_num] = node_arr_tmp[end];
	node_arr_tmp[start]->out_route_num++;
	node_arr_tmp[end]->in_routes[node_arr_tmp[end]->in_route_num] = node_arr_tmp[start];
	node_arr_tmp[end]->in_route_num++;

	current = head;
	current_tmp = head_tmp;
	while (current_tmp != NULL) {
		printf("At index: %d data: %s in_route_num: %d out_route_num: %d\n",
		       current_tmp->node->id, current_tmp->node->data, current_tmp->node->in_route_num, current_tmp->node->out_route_num);
		printf("in_routes:\n");
		for (int i = 0; i < current_tmp->node->in_route_num; i++) {
			printf("index: %d data: %s\n", current_tmp->node->in_routes[i]->id, current_tmp->node->in_routes[i]->data);
		}
		printf("out_routes:\n");
		for (int i = 0; i < current_tmp->node->out_route_num; i++) {
			printf("index: %d data: %s\n", current_tmp->node->out_routes[i]->id, current_tmp->node->out_routes[i]->data);
		}
		current_tmp = current_tmp->next_node;
	}
//	TopolgicalSort(head_tmp, node_num);

	return 0;
}

