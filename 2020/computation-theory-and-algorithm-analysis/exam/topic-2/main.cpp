#include <cstdio>
#include <algorithm>
#include <queue>

using std::sort;
using std::priority_queue;

struct work {
    int ddl;
    int fine;
};

bool compare_ddl(work a, work b) {
    return a.ddl > b.ddl;
}

int main() {
    int work_num = 0;
    work work_list[10005] = {0};
    long long fine_sum = 0;
    scanf("%d", &work_num);
    for (int i = 1; i <= work_num; i++)
        scanf("%d", &work_list[i].ddl);
    for (int i = 1; i <= work_num; i++) {
        scanf("%d", &work_list[i].fine);
        fine_sum += work_list[i].fine;
    }

    sort(work_list + 1, work_list + 1 + work_num, compare_ddl);

    priority_queue<int> fine_queue;

    int index = 1;
    while (work_list[index].ddl >= index)
        fine_queue.push(-work_list[index++].fine);

    while (index <= work_num) {
        int tmp = -fine_queue.top();
        if (tmp < work_list[index].fine) {
            fine_queue.pop();
            fine_queue.push(-work_list[index++].fine);
        }
    }

    while (!fine_queue.empty()) {
        fine_sum -= -fine_queue.top();
        fine_queue.pop();
    }

    printf("%lld\n", fine_sum);

    return 0;
}
