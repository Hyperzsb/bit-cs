#include<stdio.h>
#include<stack>
#include<queue>

using namespace std;

int main() {
    int caoZuo = 0, opClass = 0, num = 0, flagList[4] = {1};
    while (~scanf("%d", &caoZuo)) {
        int flag = 0, flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1;
        stack<int> S;
        queue<int> Q;
        priority_queue<int> smallPQ;
        priority_queue<int> bigPQ;
        for (int i = 0; i < caoZuo; i++) {
            scanf("%d%d", &opClass, &num);
            if (opClass == 1) {
                S.push(num);
                Q.push(num);
                smallPQ.push(-num);
                bigPQ.push(num);
            } else {
                if (flag1 && S.top() != num) {
                    flagList[0] = 0;
                    flag1 = 0;
                    flag++;
                } else
                    S.pop();
                if (flag2 && Q.front() != num) {
                    flag2 = 0;
                    flag++;
                } else
                    Q.pop();
                if (flag3 && -smallPQ.top() != num) {
                    flag3 = 0;
                    flag++;
                } else
                    smallPQ.pop();
                if (flag4 && bigPQ.top() != num) {
                    flag4 = 0;
                    flag++;
                } else
                    bigPQ.pop();
            }
        }
        if (flag == 3)
            if (flag1 == 1)
                printf("stack\n");
            else if (flag2 == 1)
                printf("queue\n");
            else if (flag3 == 1)
                printf("small priority queue\n");
            else
                printf("big priority queue\n");
        else if (flag == 4)
            printf("pool zls\n");
        else
            printf("not sure\n");
    }

    return 0;
}