/*
 * @descripttion �����⹫ʽ������ʽ
 * @author ���ٲ�
 * @date 2019-12-01 10:37:03
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
namespace std_namespace {
	/**
	 * �����׼���еĿ��������ջ
	 */
	using std::sort;
	using std::stack;
	/**
	 *@description: ��ʽ�࣬���ڻ�ȡ��ʽ������ȡ��ʽ������ȡ��ʽ
	 */
	class Proposition {
	private:
		/**
		 * �û������ԭʼ��ʽ�ַ��� 
		 */
		char *original_proposition;
		/**
		 * ��ʽ�а����ı�Ԫ���� 
		 */
		int variable_num;
		/**
		 * ��ʽ�а����ı�Ԫ 
		 */
		char variable[60];
		/**
		 * ��ʽ���и�ֵ�ĸ��� 
		 */
		int value_num;
		/**
		 * ��ʽ���еĳ��渳ֵ��ʮ����ת��Ϊ�����ƺ�����Ƹ�λ�ֱ��Ӧ����Ԫ��ȡֵ 
		 */
		int *true_value;
		/**
		 * @description ��ô�������������ȼ�
		 * @param {char} oper
		 * @return {int} - ����������ȼ���ֵԽ�����ȼ�Խ��
		 */
		int OperatorPriority(char oper) {
			switch (oper) {
				case '!':
					return 0;
					break;
				case '&':
					return 1;
					break;
				case '|':
					return 1;
					break;
				case '-':
					return 2;
					break;
				case '+':
					return 2;
					break;
				case '(':
					return 3;
					break;
			}
		}
		/**
		 * @description ���ָ��ֵ��ָ�������µĽ��
		 * @param {char} oper - �������������������
		 * @param {a} a - ���������ǰ��
		 * @param {b} [b=0] - ��������ĺ����Ĭ��ֵΪ0
		 * @return {int} - ������
		 */
		int Operation(char oper, int a, int b = 0) {
			switch (oper) {
				case '&':
					return a && b;
					break;
				case '|':
					return a || b;
					break;
				case '!':
					return !a;
					break;
				case '-':
					return (!a) || b;
					break;
				case '+':
					return (a && b) || (!a && !b);
					break;
			}
		}
		/**
		 * @description ��ȡ��ʽ�����г��渳ֵ�������浽��Ա����true_value��
		 * @param {null}
		 * @return {null}
		 */
		void GetTrueValue() {
			/**
			 * ��ʼ��true_value��Ա���� 
			 */
			this->true_value = (int *)malloc((this->value_num + 10) * sizeof(int));
			for (int i = 0; i < this->value_num; i++)
				this->true_value[i] = 0;
			/**
			 * �������й�������Ҫ����ʱ���� 
			 */
			int value = 0;
			int variable_value[200] = {0};
			int proposition_length = strlen(original_proposition);
			char *tmp_proposition = (char *)malloc((proposition_length + 10) * sizeof(char));
			/**
			 * ����ջ���ڹ�ʽֵ�ļ���
			 */
			stack<char> oper_stack;
			stack<int> num_stack;
			/**
			 * ���ڹ�ʽ�Ĳ�ͬ��ֵ����ѭ�����㣬�ֱ���㲻ͬ��ֵ�¹�ʽ����� 
			 */
			for (int i = 0; i < value_num; i++) {
				/**
				 * ����ʽ�ı�Ԫ����ǰ��Ӧ�ĸ�ֵ 
				 */
				for (int j = 0; j < variable_num; j++)
					variable_value[(int)variable[j]] = ((1 << (variable_num - j - 1))&value) >> (variable_num - j - 1);
				/**
				 * ����ʽ�еı�Ԫ�Ե�ǰ��Ӧ�ĸ�ֵ��� 
				 */ 
				for (int j = 0; j < proposition_length; j++)
					if ((original_proposition[j] >= 'a' && original_proposition[j] <= 'z') ||
					    (original_proposition[j] >= 'A' && original_proposition[j] <= 'Z'))
						tmp_proposition[j] = variable_value[(int)original_proposition[j]] + '0';
					else
						tmp_proposition[j] = original_proposition[j];
				/**
				 * �Ե�ǰ���ʽ�����������
				 */
				for (int j = 0; j < proposition_length; j++)
					if (tmp_proposition[j] == '0' || tmp_proposition[j] == '1') {
						num_stack.push(tmp_proposition[j] - '0');
					} else {
						if (tmp_proposition[j] == '(') {
							oper_stack.push(tmp_proposition[j]);
						} else if (tmp_proposition[j] == ')') {
							while (oper_stack.top() != '(') {
								char oper = oper_stack.top();
								oper_stack.pop();
								if (oper == '!') {
									int a = num_stack.top();
									num_stack.pop();
									num_stack.push(Operation(oper, a));
								} else {
									int b = num_stack.top();
									num_stack.pop();
									int a = num_stack.top();
									num_stack.pop();
									num_stack.push(Operation(oper, a, b));
								}
							}
							oper_stack.pop();
						} else {
							if (oper_stack.size() == 0) {
								oper_stack.push(tmp_proposition[j]);
							} else {
								if (OperatorPriority(oper_stack.top()) >= OperatorPriority(tmp_proposition[j])) {
									oper_stack.push(tmp_proposition[j]);
								} else {
									while (oper_stack.size() != 0 && OperatorPriority(oper_stack.top()) < OperatorPriority(tmp_proposition[j])) {
										char oper = oper_stack.top();
										oper_stack.pop();
										if (oper == '!') {
											int a = num_stack.top();
											num_stack.pop();
											num_stack.push(Operation(oper, a));
										} else {
											int b = num_stack.top();
											num_stack.pop();
											int a = num_stack.top();
											num_stack.pop();
											num_stack.push(Operation(oper, a, b));
										}
									}
									oper_stack.push(tmp_proposition[j]);
								}
							}
						}
					}
				while (num_stack.size() != 1) {
					char oper = oper_stack.top();
					oper_stack.pop();
					if (oper == '!') {
						int a = num_stack.top();
						num_stack.pop();
						num_stack.push(Operation(oper, a));
					} else {
						int b = num_stack.top();
						num_stack.pop();
						int a = num_stack.top();
						num_stack.pop();
						num_stack.push(Operation(oper, a, b));
					}
				}
				this->true_value[value] = num_stack.top();
				while (!oper_stack.empty())
					oper_stack.pop();
				while (!num_stack.empty())
					num_stack.pop();
				value++;
			}
			return ;
		}

	public:
		/**
		 * @description ��ʽ��Ĺ��캯��
		 * @param {const char *} original_proposition - ԭʼ��ʽ�ַ���
		 * @return {Proposition}
		 */
		Proposition(const char *original_proposition) {
			int proposition_str_length = strlen(original_proposition);
			this->original_proposition = (char *)malloc((proposition_str_length + 10) * sizeof(char));
			strcpy(this->original_proposition, original_proposition);
			/**
		   * ���㹫ʽ�б�Ԫ���� 
		   */
			variable_num = 0;
			for (int i = 0; i < proposition_str_length; i++)
				if ((original_proposition[i] >= 'a' && original_proposition[i] <= 'z') ||
				    (original_proposition[i] >= 'A' && original_proposition[i] <= 'Z')) {
					int flag = 1;
					for (int j = 0; j < variable_num; j++)
						if (variable[j] == original_proposition[i]) {
							flag = 0;
							break;
						}
					if (flag) {
						variable[variable_num] = original_proposition[i];
						variable_num++;
					}
				}
			sort(variable, variable + variable_num);
			value_num = (int)pow(2, variable_num);
			/**
			 * ������Ա�����ĳ�ʼ�� 
			 */
			true_value = NULL;
			proposition_type = Undefined;
		}
		/**
		 * @description ��ʽ���������������ʽ���տռ�
		 * @param {null}
		 * @return {null}
		 */
		~Proposition() {
			free(this->original_proposition);
			free(this->true_value);
		}
		/**
		 * @description �������ȡ��ʽ
		 * @param {null}
		 * @return {null}
		 */
		void GetDnf() {
			if (this->true_value == NULL)
				this->GetTrueValue();
			int true_value_num = 0;
			for (int i = 0; i < this->value_num; i++)
				if (this->true_value[i] == 1)
					true_value_num++;
			if (true_value_num == 0) {
				printf("0");
			} else {
				int order = 0;
				for (int i = 0; i < this->value_num; i++)
					if (this->true_value[i] == 1) {
						if (order == 0) {
							printf("m%d", i);
							order++;
						} else {
							printf(" �� m%d", i);
							order++;
						}
					}
			}
			return ;
		}
		/**
		 * @description �������ȡ��ʽ
		 * @param {null}
		 * @return {null}
		 */
		void GetCnf() {
			if (this->true_value == NULL)
				this->GetTrueValue();
			int false_value_num = 0;
			for (int i = 0; i < this->value_num; i++)
				if (this->true_value[i] == 0)
					false_value_num++;
			if (false_value_num == 0) {
				printf("1");
			} else {
				int order = 0;
				for (int i = 0; i < this->value_num; i++)
					if (this->true_value[i] == 0) {
						if (order == 0) {
							printf("M%d", i);
							order++;
						} else {
							printf(" �� M%d", i);
							order++;
						}
					}
			}
			return ;
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
	char original_proposition[1000] = {'\0'};
	scanf("%s", original_proposition);
	Proposition *proposition = new Proposition(original_proposition);
	proposition->GetDnf();
	printf(" ; ");
	proposition->GetCnf();
	printf("\n");

	return 0;
}

