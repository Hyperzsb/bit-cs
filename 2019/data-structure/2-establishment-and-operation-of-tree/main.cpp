#include<cstdio>
#include<cstdlib>
#include<cstring>

int max_degree = 0;
int degree_num[1000] = {0};

struct TreeNode {
    char data;
    TreeNode *parent;
    TreeNode **child;
    int child_num;
    int win_num;
    int lose_num;

    TreeNode() {

    }

    TreeNode(char data_) {
        data = data_;
    }

    TreeNode(char data_, TreeNode *parent_, TreeNode **child_) {
        data = data_;
        parent = parent_;
        child = child_;
    }
};

TreeNode *CreateTree(char *tree_str) {
    if (strcmp(tree_str, "()") == 0) {
        TreeNode *root = new TreeNode('\0');
        root->child_num = 0;
        root->child = NULL;
        return root;
    }
    int str_len = strlen(tree_str), child_num = 0, child_index = 0, barket[2] = {0}, start = 3, end = 3;
    TreeNode *root = new TreeNode(tree_str[1]);
    for (int i = 3; i < str_len - 1; i++) {
        if (tree_str[i] == '(') {
            barket[0]++;
        } else if (tree_str[i] == ')') {
            barket[1]++;
            if (barket[0] == barket[1]) {
                child_num++;
                barket[0] = barket[1] = 0;
            }
        } else {
            continue;
        }
    }
    barket[0] = barket[1] = 0;
    root->child_num = child_num;
    TreeNode **child_list = (TreeNode **) malloc(child_num * sizeof(TreeNode *));
    for (int i = 3; i < str_len - 1; i++) {
        if (tree_str[i] == '(') {
            end++;
            barket[0]++;
        } else if (tree_str[i] == ')') {
            end++;
            barket[1]++;
            if (barket[0] == barket[1]) {
                char *child_str = (char *) malloc((end - start + 2) * sizeof(char));
                for (int j = 0; j < end - start + 1; j++) {
                    child_str[j] = tree_str[start + j];
                }
                child_str[end - start + 1] = '\0';
                child_list[child_index] = CreateTree(child_str);
                child_index++;
                barket[0] = barket[1] = 0;
                free(child_str);
                i++;
                start = end = i + 1;
            }
        } else {
            end++;
            continue;
        }
    }
    root->child = child_list;
    return root;
}

void TraverseTree(TreeNode *root, int depth) {
    if (root->data == '\0') {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%c\n", root->data);
    for (int i = 0; i < root->child_num; i++) {
        TraverseTree(root->child[i], depth + 1);
    }
    if (max_degree < root->child_num) {
        max_degree = root->child_num;
    }
    degree_num[root->child_num]++;
    return;
}

int main() {
    char tree_str[1000] = {'\0'};
    scanf("%s", tree_str);
    TreeNode *root = CreateTree(tree_str);
    TraverseTree(root, 0);
    printf("Degree of tree: %d\n", max_degree);
    for (int i = 0; i < max_degree + 1; i++) {
        printf("Number of nodes of degree %d: %d\n", i, degree_num[i]);
    }
}