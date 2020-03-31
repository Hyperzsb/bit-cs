#include<stdio.h>
#include<stack>

using namespace std;

int main() {
    int width = 0;
    while (~scanf("%d", &width)) {
        int tmp = 0, max = 0, flag = 0;
        stack<int> S;
        for (int i = 0; i < width; i++) {
            scanf("%d", &tmp);
            if (max < tmp)
                max = tmp;
            if (S.size() == 0)
                S.push(tmp);
            else {
                if (S.top() == tmp)
                    S.pop();
                else if (S.top() < tmp)
                    flag = 1;
                else
                    S.push(tmp);
            }
        }
        if (flag) {
            printf("NO\n");
            continue;
        }
        if (S.size() == 0)
            printf("YES\n");
        else if (S.size() == 1 && S.top() == max)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}