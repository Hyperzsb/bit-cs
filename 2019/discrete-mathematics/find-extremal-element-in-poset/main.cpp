#include<cstdio>
#include<cstdlib>
#include<cstring>

namespace std_namespace {
    class ExtremalElement {
    private:
        int node_num;
        char *node;
        int **route;
        int minimal_element_num;
        int maximal_element_num;
        char *minimal_element;
        char *maximal_element;

        void GetExtremalElement() {
            minimal_element = (char *) malloc(node_num * sizeof(char));
            maximal_element = (char *) malloc(node_num * sizeof(char));
            for (int i = 0; i < node_num; i++) {
                int flag = 1;
                for (int j = 0; j < node_num; j++)
                    if (route[j][i] == 1) {
                        flag = 0;
                        break;
                    }
                if (flag)
                    minimal_element[minimal_element_num++] = node[i];
            }
            minimal_element[minimal_element_num] = '\0';
            for (int i = 0; i < node_num; i++) {
                int flag = 1;
                for (int j = 0; j < node_num; j++)
                    if (route[i][j] == 1) {
                        flag = 0;
                        break;
                    }
                if (flag)
                    maximal_element[maximal_element_num++] = node[i];
            }
            maximal_element[maximal_element_num] = '\0';
        }

    public:
        ExtremalElement(const char *node_str, const char *route_str) {
            int num = 0, index = 0, route_str_len = strlen(route_str);
            for (int i = 0; node_str[i] != '\0'; i++)
                if (node_str[i] != ',')
                    num++;
            this->node_num = num;
            node = (char *) malloc(node_num * sizeof(char));
            route = (int **) malloc(node_num * sizeof(int *));
            for (int i = 0; i < node_num; i++, index++) {
                node[i] = node_str[index++];
                route[i] = (int *) malloc(node_num * sizeof(int));
                for (int j = 0; j < node_num; j++)
                    route[i][j] = 0;
            }
            for (index = 1; index < route_str_len; index++) {
                for (int i = 0; i < node_num; i++)
                    if (node[i] == route_str[index]) {
                        index += 2;
                        for (int j = 0; j < node_num; j++)
                            if (node[j] == route_str[index]) {
                                route[i][j] = 1;
                                index += 3;
                                break;
                            }
                        break;
                    }
            }
            minimal_element_num = 0;
            maximal_element_num = 0;
            minimal_element = NULL;
            maximal_element = NULL;
        }

        ~ExtremalElement() {
            free(node);
            free(route);
        }

        const char *get_minimal_element() {
            if (minimal_element == NULL)
                GetExtremalElement();
            return minimal_element;
        }

        const char *get_maximal_element() {
            if (maximal_element == NULL)
                GetExtremalElement();
            return maximal_element;
        }
    };

}

int main() {
    using namespace std_namespace;
    char node_str[50] = {'\0'}, route_str[1000] = {'\0'};
    scanf("%s%s", node_str, route_str);
    ExtremalElement *extremal_element = new ExtremalElement(node_str, route_str);
    const char *minimal_element = extremal_element->get_minimal_element(),
            *maximal_element = extremal_element->get_maximal_element();
    int minimal_element_num = strlen(minimal_element), maximal_element_num = strlen(maximal_element);
    printf("%c", minimal_element[0]);
    for (int i = 1; i < minimal_element_num; i++)
        printf(",%c", minimal_element[i]);
    printf("\n%c", maximal_element[0]);
    for (int i = 1; i < maximal_element_num; i++)
        printf(",%c", maximal_element[i]);
    printf("\n");
    return 0;
}