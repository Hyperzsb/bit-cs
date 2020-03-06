/*
 * @descripttion �����⹫ʽ������ʽ
 * @author ���ٲ�
 * @date 2019-12-20 19:20:33
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
namespace std_namespace {
	/**
	 * @description ���ݱհ��� 
	 */
	class TransitiveClosure {
	private:
		/**
		 * �ڵ���� 
		 */
		int node_num;
		/**
		 * �ڽӾ��� 
		 */
		int **route;
		/**
		 * ���ݱհ����� 
		 */
		int **transitive_closure;
		
	public:
		/**
		 * @description ���ݱհ��๹�캯��
		 * @param {null} 
		 * @return {TransitiveClosure} 
		 */
		TransitiveClosure() {
			char line_str[100] = {'\0'};
			gets(line_str);
			/**
		   * �ж�Ԫ�صĸ��� 
		   */
			node_num = strlen(line_str) / 2 + 1;
			/**
		   * ��ʼ���ڽӾ��� 
		   */
			route = (int **)malloc(node_num * sizeof(int *));
			for (int i = 0; i < node_num; i++)
				route[i] = (int *)malloc(node_num * sizeof(int));
			/**
		   * ѭ�������ڽӾ��� 
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
		   * ��ʼ���հ����� 
		   */
			transitive_closure = NULL;
		}
		/**
		 * @description ��ȡ�հ�����
		 * @param {null}
		 * @return {const int **} transitive_closure - �հ����� 
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
		     * �����ڽӾ���õ��հ����� 
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
		 * @description ��ȡԪ�ظ���
		 * @param {null}
		 * @return {int} node_num - Ԫ�ظ��� 
		 */
		int get_node_num() {
			return node_num;
		}
	};
}
/**
 * @description ������
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

