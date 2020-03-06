/*
 * @descripttion 求命题公式的主范式
 * @author 张少博
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
	 * 引入标准库中的快速排序和栈
	 */
	using std::sort;
	using std::stack;
	/**
	 *@description: 公式类，用于获取公式的主合取范式和主析取范式
	 */
	class Proposition {
	private:
		/**
		 * 用户输入的原始公式字符串 
		 */
		char *original_proposition;
		/**
		 * 公式中包含的变元个数 
		 */
		int variable_num;
		/**
		 * 公式中包含的变元 
		 */
		char variable[60];
		/**
		 * 公式所有赋值的个数 
		 */
		int value_num;
		/**
		 * 公式所有的成真赋值，十进制转化为二进制后二进制各位分别对应各变元的取值 
		 */
		int *true_value;
		/**
		 * @description 获得传入运算符的优先级
		 * @param {char} oper
		 * @return {int} - 运算符的优先级，值越大优先级越低
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
		 * @description 获得指定值在指定运算下的结果
		 * @param {char} oper - 运算符，决定运算类型
		 * @param {a} a - 参与运算的前件
		 * @param {b} [b=0] - 参与运算的后件，默认值为0
		 * @return {int} - 运算结果
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
		 * @description 获取公式的所有成真赋值，并储存到成员变量true_value中
		 * @param {null}
		 * @return {null}
		 */
		void GetTrueValue() {
			/**
			 * 初始化true_value成员变量 
			 */
			this->true_value = (int *)malloc((this->value_num + 10) * sizeof(int));
			for (int i = 0; i < this->value_num; i++)
				this->true_value[i] = 0;
			/**
			 * 其它运行过程中需要的临时变量 
			 */
			int value = 0;
			int variable_value[200] = {0};
			int proposition_length = strlen(original_proposition);
			char *tmp_proposition = (char *)malloc((proposition_length + 10) * sizeof(char));
			/**
			 * 两个栈用于公式值的计算
			 */
			stack<char> oper_stack;
			stack<int> num_stack;
			/**
			 * 对于公式的不同赋值进行循环运算，分别计算不同赋值下公式的真假 
			 */
			for (int i = 0; i < value_num; i++) {
				/**
				 * 给公式的变元赋当前对应的赋值 
				 */
				for (int j = 0; j < variable_num; j++)
					variable_value[(int)variable[j]] = ((1 << (variable_num - j - 1))&value) >> (variable_num - j - 1);
				/**
				 * 将公式中的变元以当前对应的赋值替代 
				 */ 
				for (int j = 0; j < proposition_length; j++)
					if ((original_proposition[j] >= 'a' && original_proposition[j] <= 'z') ||
					    (original_proposition[j] >= 'A' && original_proposition[j] <= 'Z'))
						tmp_proposition[j] = variable_value[(int)original_proposition[j]] + '0';
					else
						tmp_proposition[j] = original_proposition[j];
				/**
				 * 对当前表达式进行运算求解
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
		 * @description 公式类的构造函数
		 * @param {const char *} original_proposition - 原始公式字符串
		 * @return {Proposition}
		 */
		Proposition(const char *original_proposition) {
			int proposition_str_length = strlen(original_proposition);
			this->original_proposition = (char *)malloc((proposition_str_length + 10) * sizeof(char));
			strcpy(this->original_proposition, original_proposition);
			/**
		   * 计算公式中变元个数 
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
			 * 其他成员变量的初始化 
			 */
			true_value = NULL;
			proposition_type = Undefined;
		}
		/**
		 * @description 公式类的析构函数，显式回收空间
		 * @param {null}
		 * @return {null}
		 */
		~Proposition() {
			free(this->original_proposition);
			free(this->true_value);
		}
		/**
		 * @description 输出主合取范式
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
							printf(" ∨ m%d", i);
							order++;
						}
					}
			}
			return ;
		}
		/**
		 * @description 输出主析取范式
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
							printf(" ∧ M%d", i);
							order++;
						}
					}
			}
			return ;
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
	char original_proposition[1000] = {'\0'};
	scanf("%s", original_proposition);
	Proposition *proposition = new Proposition(original_proposition);
	proposition->GetDnf();
	printf(" ; ");
	proposition->GetCnf();
	printf("\n");

	return 0;
}

