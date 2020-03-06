#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<stack>
namespace std_namespace {
	using std::sort;
	using std::string;
	using std::stack;
	enum PropositionType {
	  Contradiction = 0,
	  Tautology = 1,
	  Contingency = 2,
	  Undefined = -1
	};
	//Because of the OJ, the Proposition class is written in a signle file not in .h or .cpp files
	class Proposition {
	private:
		//The string of user's original input proposition
		char *original_proposition;
		//The number of propositional varibale in the original proposition
		int variable_num;
		//The array of propositional varibale
		char variable[60];
		//The number of values for variables
		int value_num;
		//The values make the proposition true
		int *true_value;
		//The string of original proposition's disjunctive normal form
		char *disjunctive_normal_form;
		//The string of original proposition's conjunctive normal form
		char *conjunctive_normal_form;
		//The proposition type of the original proposition
		PropositionType proposition_type;
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
		void GetTrueValue() {
			int value = 0;
			int variable_value[200] = {0};
			this->true_value = (int *)malloc((this->value_num + 10) * sizeof(int));
			for (int i = 0; i < this->value_num; i++)
				this->true_value[i] = 0;
			int proposition_length = strlen(original_proposition);
			char *tmp_proposition = (char *)malloc((proposition_length + 10) * sizeof(char));
			stack<char> oper_stack;
			stack<int> num_stack;
			for (int i = 0; i < value_num; i++) {
				//Set the varibale' value
				for (int j = 0; j < variable_num; j++)
					variable_value[(int)variable[j]] = ((1 << (variable_num - j - 1))&value) >> (variable_num - j - 1);
				for (int j = 0; j < proposition_length; j++)
					if ((original_proposition[j] >= 'a' && original_proposition[j] <= 'z') ||
					    (original_proposition[j] >= 'A' && original_proposition[j] <= 'Z'))
						tmp_proposition[j] = variable_value[(int)original_proposition[j]] + '0';
					else
						tmp_proposition[j] = original_proposition[j];
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
		Proposition(const char *original_proposition) {
			int proposition_str_length = strlen(original_proposition);
			this->original_proposition = (char *)malloc((proposition_str_length + 10) * sizeof(char));
			strcpy(this->original_proposition, original_proposition);
			//Count and select the varibale
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
			//Initialization of the other properties
			true_value = NULL;
			disjunctive_normal_form = NULL;
			conjunctive_normal_form = NULL;
			proposition_type = Undefined;
		}
		~Proposition() {
			free(this->original_proposition);
			free(this->true_value);
			free(this->disjunctive_normal_form);
			free(this->conjunctive_normal_form);
		}
		const char *GetDnf() {
			if (disjunctive_normal_form == NULL) {
				if (this->true_value == NULL)
					this->GetTrueValue();
				int true_value_num = 0;
				for (int i = 0; i < this->value_num; i++)
					if (this->true_value[i] == 1)
						true_value_num++;
				if (true_value_num == 0) {
//					disjunctive_normal_form = (char *)malloc(5 * sizeof(char));
//					disjunctive_normal_form[0] = '0';
//					disjunctive_normal_form[1] = '\0';
				} else {
					disjunctive_normal_form = (char *)malloc((5 * (true_value_num - 1) + 10) * sizeof(char));
					for (int i = 0; i < 5 * (true_value_num - 1) + 10; i++)
						disjunctive_normal_form[i] = '\0';
					int order = 0;
//					char tmp_str[20] = {'\0'};
					for (int i = 0; i < this->value_num; i++)
						if (this->true_value[i] == 1) {
							if (order == 0) {
								printf("m%d", i);
//								sprintf(tmp_str, "m%d", i);
//								strcat(disjunctive_normal_form, tmp_str);
								order++;
							} else {
								printf(" ¡Å m%d", i);
//								sprintf(tmp_str, " | m%d", i);
//								strcat(disjunctive_normal_form, tmp_str);
								order++;
							}
						}
				}
			}
			return this->disjunctive_normal_form;
		}
		const char *GetCnf() {
			if (conjunctive_normal_form == NULL) {
				if (this->true_value == NULL)
					this->GetTrueValue();
				int false_value_num = 0;
				for (int i = 0; i < this->value_num; i++)
					if (this->true_value[i] == 0)
						false_value_num++;
				if (false_value_num == 0) {
//					conjunctive_normal_form = (char *)malloc(5 * sizeof(char));
//					conjunctive_normal_form[0] = '0';
//					conjunctive_normal_form[1] = '\0';
				} else {
					conjunctive_normal_form = (char *)malloc((5 * (false_value_num - 1) + 10) * sizeof(char));
					for (int i = 0; i < 5 * (false_value_num - 1) + 10; i++)
						conjunctive_normal_form[i] = '\0';
					int order = 0;
//					char tmp_str[20] = {'\0'};
					for (int i = 0; i < this->value_num; i++)
						if (this->true_value[i] == 0) {
							if (order == 0) {
								printf("M%d", i);
//								sprintf(tmp_str, "M%d", i);
//								strcat(conjunctive_normal_form, tmp_str);
								order++;
							} else {
								printf(" ¡Ä M%d", i);
//								sprintf(tmp_str, " & M%d", i);
//								strcat(conjunctive_normal_form, tmp_str);
								order++;
							}
						}
				}
			}
			return this->conjunctive_normal_form;
		}
		const PropositionType GetPropositionType() {
			if (proposition_type == Undefined)
				this->GetDnf();
			return this->proposition_type;
		}
	};
}

int main() {
	using namespace std_namespace;
	char original_proposition[1000] = {'\0'};
	scanf("%s", original_proposition);
	Proposition *proposition = new Proposition(original_proposition);
//	const char *dnf = proposition->GetDnf(), *cnf = proposition->GetCnf();
//	int dnf_length = strlen(dnf), cnf_length = strlen(cnf);
//	for (int i = 0; i < dnf_length; i++)
//		if (dnf[i] == '|') {
//			printf("¡Å");
//		} else {
//			printf("%c", dnf[i]);
//		}
//	printf(" ; ");
//	for (int i = 0; i < cnf_length; i++)
//		if (cnf[i] == '&') {
//			printf("¡Ä");
//		} else {
//			printf("%c", cnf[i]);
//		}
	proposition->GetDnf();
	printf(" ; ");
	proposition->GetCnf();
	printf("\n");

	return 0;
}

