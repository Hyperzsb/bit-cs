/*
 * @descripttion 求命题公式的主范式
 * @author 张少博
 * @date 2019-12-20 19:20:33
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
namespace std_namespace {
	/**
	 * @description 传递闭包类 
	 */
	class TransitiveClosure {
	private:
		/**
		 * 节点个数 
		 */
		int node_num;
		/**
		 * 邻接矩阵 
		 */
		int **route;
		/**
		 * 传递闭包矩阵 
		 */
		int **transitive_closure;
		
	public:
		/**
		 * @description 传递闭包类构造函数
		 * @param {null} 
		 * @return {TransitiveClosure} 
		 */
		TransitiveClosure() {
			char line_str[100] = {'\0'};
			gets(line_str);
			/**
		   * 判断元素的个数 
		   */
			node_num = strlen(line_str) / 2 + 1;
			/**
		   * 初始化邻接矩阵 
		   */
			route = (int **)malloc(node_num * sizeof(int *));
			for (int i = 0; i < node_num; i++)
				route[i] = (int *)malloc(node_num * sizeof(int));
			/**
		   * 循环输入邻接矩阵 
		   */
			int index = 0;
			for (int i = 0; i < node_num; i++, index++)
				route[0][i] = line_str[index++] - '0';
			for (int i = 1; i < node_num; i++) {
				gets(line_str);
				int index = 0;
				for (int j = 0; j < node_num; j++, index++)
					route[i][j] = line_str[index++] - '0';
			}
			/**
		   * 初始化闭包矩阵 
		   */
			transitive_closure = NULL;
		}
		/**
		 * @description 获取闭包矩阵
		 * @param {null}
		 * @return {const int **} transitive_closure - 闭包矩阵 
		 */ 
		const int **get_transitive_closure() {
			if (transitive_closure == NULL) {
				transitive_closure = (int **)malloc(node_num * sizeof(int **));
				for (int i = 0; i < node_num; i++) {
					transitive_closure[i] = (int *)malloc(node_num * sizeof(int));
					for (int j = 0; j < node_num; j++)
						transitive_closure[i][j] = route[i][j];
				}
				/**
		     * 根据邻接矩阵得到闭包矩阵 
		     */
				for (int i = 0; i < node_num; i++)
					for (int j = 0; j < node_num; j++)
						if (transitive_closure[j][i] == 1)
							for (int k = 0; k < node_num; k++)
								transitive_closure[j][k] |= transitive_closure[i][k];
			}
			return (const int **)transitive_closure;
		}
		/**
		 * @description 获取元素个数
		 * @param {null}
		 * @return {int} node_num - 元素个数 
		 */
		int get_node_num() {
			return node_num;
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
	TransitiveClosure *transitive_closure = new TransitiveClosure();
	const int node_num = transitive_closure->get_node_num(),
	          **transitive_closure_ans = transitive_closure->get_transitive_closure();
	for (int i = 0; i < node_num; i++) {
		printf("%d", transitive_closure_ans[i][0]);
		for (int j = 1; j < node_num; j++)
			printf(" %d", transitive_closure_ans[i][j]);
		printf("\n");
	}
	return 0;
}

