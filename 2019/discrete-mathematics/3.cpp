/*
 * @descripttion 求偏序集中的极大元与极小元 
 * @author 张少博
 * @date 2019-12-20 18:01:21
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
namespace std_namespace {
	/**
	 * @description 极值元素类 
	 */
	class ExtremalElement {
	private:
		/**
     * 节点个数
     */
		int node_num;
		/**
		 * 节点列表 
		 */
		char *node;
		/**
		 * 路径列表 
		 */ 
		int **route;
		/**
		 * 极小元个数 
		 */ 
		int minimal_element_num;
		/**
		 * 极大元个数 
		 */ 
		int maximal_element_num;
		/**
		 * 极小元列表 
		 */ 
		char *minimal_element;
		/**
		 * 极大元列表 
		 */ 
		char *maximal_element;
		/**
		 * @description 获取极小元/极大元 
		 * @param {null}
		 * @return {null}
		 */
		void GetExtremalElement() {
			minimal_element = (char *)malloc(node_num * sizeof(char));
			maximal_element = (char *)malloc(node_num * sizeof(char));
			for (int i = 0; i < node_num; i++) {
				int flag = 1;
				for (int j = 0; j < node_num; j++)
					if (route[j][i] == 1) {
						flag = 0;
						break;
					}
				if (flag)
					minimal_element[minimal_element_num++] = node[i];
			}
			minimal_element[minimal_element_num] = '\0';
			for (int i = 0; i < node_num; i++) {
				int flag = 1;
				for (int j = 0; j < node_num; j++)
					if (route[i][j] == 1) {
						flag = 0;
						break;
					}
				if (flag)
					maximal_element[maximal_element_num++] = node[i];
			}
			maximal_element[maximal_element_num] = '\0';
		}

	public:
		/**
		 * @description 极值元素类构造函数 
		 * @param {const char *} node_str - 原始节点列表 
		 * @param {const char *} route_str - 原始路径列表 
		 * @return {ExtremalElement}
		 */ 
		ExtremalElement(const char *node_str, const char *route_str) {
			int num = 0, index = 0, route_str_len = strlen(route_str);
			for (int i = 0; node_str[i] != '\0'; i++)
				if (node_str[i] != ',')
					num++;
			this->node_num = num;
			node = (char *)malloc(node_num * sizeof(char));
			route = (int **)malloc(node_num * sizeof(int *));
			for (int i = 0; i < node_num; i++, index++) {
				node[i] = node_str[index++];
				route[i] = (int *)malloc(node_num * sizeof(int));
				for (int j = 0; j < node_num; j++)
					route[i][j] = 0;
			}
			for (index = 1; index < route_str_len; index++) {
				for (int i = 0; i < node_num; i++)
					if (node[i] == route_str[index]) {
						index += 2;
						for (int j = 0; j < node_num; j++)
							if (node[j] == route_str[index]) {
								route[i][j] = 1;
								index += 3;
								break;
							}
						break;
					}
			}
			minimal_element_num = 0;
			maximal_element_num = 0;
			minimal_element = NULL;
			maximal_element = NULL;
		}
		/**
		 * @description 极值元素类析构函数，显式释放空间 
		 * @param {null}
		 * @return {null}
		 */
		~ExtremalElement() {
			free(node);
			free(route);
		}
		/**
		 * @description 获取极小元列表 
		 * @param {null}
		 * @return {const char *} minimal_element - 极小元列表 
		 */
		const char *get_minimal_element() {
			if (minimal_element == NULL)
				GetExtremalElement();
			return minimal_element;
		}
		/**
		 * @description 获取极大元列表
		 * @param {null}
		 * @return {const char *} maximal_element - 极大元列表 
		 */
		const char *get_maximal_element() {
			if (maximal_element == NULL)
				GetExtremalElement();
			return maximal_element;
		}
	};
}
/**
 * @description 主函数
 * @param {null}
 * @return {int} 
 */
int main() {
	using namespace std_namespace;
	char node_str[50] = {'\0'}, route_str[1000] = {'\0'};
	scanf("%s%s", node_str, route_str);
	ExtremalElement *extremal_element = new ExtremalElement(node_str, route_str);
	const char *minimal_element = extremal_element->get_minimal_element(),
	            *maximal_element = extremal_element->get_maximal_element();
	int minimal_element_num = strlen(minimal_element), maximal_element_num = strlen(maximal_element);
	printf("%c", minimal_element[0]);
	for (int i = 1; i < minimal_element_num; i++)
		printf(",%c", minimal_element[i]);
	printf("\n%c", maximal_element[0]);
	for (int i = 1; i < maximal_element_num; i++)
		printf(",%c", maximal_element[i]);
	printf("\n");
	return 0;
}

