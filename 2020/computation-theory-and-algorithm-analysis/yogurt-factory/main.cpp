#include <cstdio>

int main() {
    int week_num = 0, store_cost = 0, week_demand = 0, min_cost = 0, current_cost = 0;
    long long sum = 0;
    scanf("%d%d", &week_num, &store_cost);
    scanf("%d%d", &current_cost, &week_demand);
    min_cost = current_cost;
    sum += min_cost * week_demand;
    week_num--;
    min_cost += store_cost;
    while (week_num--) {
        scanf("%d%d", &current_cost, &week_demand);
        if (current_cost < min_cost)
            min_cost = current_cost;
        sum += min_cost * week_demand;
        min_cost += store_cost;
    }
    printf("%lld\n", sum);
    return 0;
}