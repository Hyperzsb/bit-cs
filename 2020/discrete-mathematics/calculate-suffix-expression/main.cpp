#include <cstdio>
#include <cstring>
#include <stack>

int main() {
    char str[1000] = {'\0'};
    gets(str);
    int length = strlen(str);
    std::stack<int> number;
    for (int i = 0; i < length; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            number.push(str[i] - '0');
        } else {
            if (number.size() >= 2) {
                int b = number.top();
                number.pop();
                int a = number.top();
                number.pop();
                switch (str[i]) {
                    case '+': {
                        number.push(a + b);
                        break;
                    }
                    case '-': {
                        number.push(a - b);
                        break;
                    }
                    case '*': {
                        number.push(a * b);
                        break;
                    }
                    case '/': {
                        if (b != 0) {
                            number.push(a / b);
                        } else {
                            printf("DIV0!\n");
                            return 0;
                        }
                    }
                }
            } else {
                printf("ERROR!\n");
                return 0;
            }
        }
    }

    if (number.size() == 1)
        printf("%d\n", number.top());
    else
        printf("ERROR!\n");

    return 0;
}