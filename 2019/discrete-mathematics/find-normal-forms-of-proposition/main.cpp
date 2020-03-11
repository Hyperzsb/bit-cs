#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>

namespace std_namespace {
    using std::sort;
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
            this->true_value = (int *) malloc((this->value_num + 10) * sizeof(int));
            for (int i = 0; i < this->value_num; i++)
                this->true_value[i] = 0;
            int proposition_length = strlen(original_proposition);
            char *tmp_proposition = (char *) malloc((proposition_length + 10) * sizeof(char));
            stack<char> oper_stack;
            stack<int> num_stack;
            for (int i = 0; i < value_num; i++) {
                //Set the varibale' value
                for (int j = 0; j < variable_num; j++)
                    variable_value[(int) variable[j]] =
                            ((1 << (variable_num - j - 1)) & value) >> (variable_num - j - 1);
                for (int j = 0; j < proposition_length; j++)
                    if ((original_proposition[j] >= 'a' && original_proposition[j] <= 'z') ||
                        (original_proposition[j] >= 'A' && original_proposition[j] <= 'Z'))
                        tmp_proposition[j] = variable_value[(int) original_proposition[j]] + '0';
                    else
                        tmp_proposition[j] = original_proposition[j];
//                printf("VALUE: ");
//               for (int j = 0; j < variable_num; j++)
//                    printf("%c-> %d  ", variable[j], variable_value[variable[j]]);
//                printf("\n");
//                printf("PROPOSITION: %s\n", tmp_proposition);
                //Start calculation
                for (int j = 0; j < proposition_length; j++)
                    if (tmp_proposition[j] == '0' || tmp_proposition[j] == '1') {
                        num_stack.push(tmp_proposition[j] - '0');
                        //printf("INPUT NUMBER: %d\n", num_stack.top());
                    } else {
                        if (tmp_proposition[j] == '(') {
                            oper_stack.push(tmp_proposition[j]);
                            //printf("INPUT %c\n", oper_stack.top());
                        } else if (tmp_proposition[j] == ')') {
                            //printf("INPUT )\n");
                            while (oper_stack.top() != '(') {
                                char oper = oper_stack.top();
                                //printf("OPER %c\n", oper);
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
                            //printf("!!!\n");
                            oper_stack.pop();
                            //printf("???\n");
                        } else {
                            if (oper_stack.size() == 0) {
                                oper_stack.push(tmp_proposition[j]);
                            } else {
                                if (OperatorPriority(oper_stack.top()) >= OperatorPriority(tmp_proposition[j])) {
                                    oper_stack.push(tmp_proposition[j]);
                                } else {
                                    while (oper_stack.size() != 0 &&
                                           OperatorPriority(oper_stack.top()) < OperatorPriority(tmp_proposition[j])) {
                                        //printf("%c BIGGER THAN %c\n", oper_stack.top(), tmp_proposition[j]);
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
                //this->true_value[value] = 1;
                while (!oper_stack.empty())
                    oper_stack.pop();
                while (!num_stack.empty())
                    num_stack.pop();
                value++;
            }
            //free(tmp_proposition);
            return;
        }

    public:
        Proposition(const char *original_proposition) {
            int proposition_str_length = strlen(original_proposition);
            this->original_proposition = (char *) malloc((proposition_str_length + 10) * sizeof(char));
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
            value_num = (int) pow(2, variable_num);
            //Initialization of the other properties
            true_value = NULL;
            proposition_type = Undefined;
        }

        ~Proposition() {
            free(this->original_proposition);
            free(this->true_value);
        }

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
            return;
        }

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
            return;
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
    proposition->GetDnf();
    printf(" ; ");
    proposition->GetCnf();
    printf("\n");

    return 0;
}