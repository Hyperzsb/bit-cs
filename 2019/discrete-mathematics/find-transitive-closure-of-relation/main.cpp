#include<cstdio>
#include<cstdlib>
#include<cstring>

namespace std_namespace {
    class TransitiveClosure {
    private:
        int node_num;
        int **route;
        int **transitive_closure;
    public:
        TransitiveClosure() {
            char line_str[100] = {'\0'};
            gets(line_str);
            node_num = strlen(line_str) / 2 + 1;
            route = (int **) malloc(node_num * sizeof(int *));
            for (int i = 0; i < node_num; i++)
                route[i] = (int *) malloc(node_num * sizeof(int));
            int index = 0;
            for (int i = 0; i < node_num; i++, index++)
                route[0][i] = line_str[index++] - '0';
            for (int i = 1; i < node_num; i++) {
                gets(line_str);
                int index = 0;
                for (int j = 0; j < node_num; j++, index++)
                    route[i][j] = line_str[index++] - '0';
            }
            transitive_closure = NULL;
        }

        const int **get_transitive_closure() {
            if (transitive_closure == NULL) {
                transitive_closure = (int **) malloc(node_num * sizeof(int **));
                for (int i = 0; i < node_num; i++) {
                    transitive_closure[i] = (int *) malloc(node_num * sizeof(int));
                    for (int j = 0; j < node_num; j++)
                        transitive_closure[i][j] = route[i][j];
                }
                for (int i = 0; i < node_num; i++)
                    for (int j = 0; j < node_num; j++)
                        if (transitive_closure[j][i] == 1)
                            for (int k = 0; k < node_num; k++)
                                transitive_closure[j][k] |= transitive_closure[i][k];
            }
            return (const int **) transitive_closure;
        }

        int get_node_num() {
            return node_num;
        }
    };
}

int main() {
    using namespace std_namespace;
    TransitiveClosure *transitive_closure = new TransitiveClosure();
    const int node_num = transitive_closure->get_node_num(),
            **transitive_closure_ans = transitive_closure->get_transitive_closure();
    for (int i = 0; i < node_num; i++) {
        printf("%d", transitive_closure_ans[i][0]);
        for (int j = 1; j < node_num; j++)
            printf(" %d", transitive_closure_ans[i][j]);
        printf("\n");
    }
    return 0;
}  