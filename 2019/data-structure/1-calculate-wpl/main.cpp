#include<cstdio>
#include<cstdlib>
#include<string>
#include<queue>

namespace std_namespace {
    using std::string;
    using std::priority_queue;
}

int main() {
    using namespace std_namespace;
    priority_queue<int> p_queue;
    int node_num = 0, node_weight = 0, ans = 0;
    scanf("%d", &node_num);
    for (int i = 0; i < node_num; i++) {
        scanf("%d", &node_weight);
        p_queue.push(-node_weight);
    }
    while (p_queue.size() != 1) {
        int a = 0, b = 0;
        a = -p_queue.top();
        p_queue.pop();
        b = -p_queue.top();
        p_queue.pop();
        ans += a + b;
        p_queue.push(-(a + b));
    }
    printf("WPL=%d\n", ans);

    return 0;
}