#include<stdio.h>
#include<stack>

using namespace std;

int main() {
    int width = 0;
    while (~scanf("%d", &width)) {
        int tmp = 0;
        stack<int> S;
        for (int i = 0; i < width; i++) {
            scanf("%d", &tmp);
            if (S.size() == 0)
                S.push(tmp);
            else {
                if (S.top() % 2 == tmp % 2)
                    S.pop();
                else
                    S.push(tmp);
            }
        }
        if (S.size() < 2)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}