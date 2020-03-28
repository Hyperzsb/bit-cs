#include<cstdio>
#include<cstdlib>
#include<cstring>

struct Node {
    char data;
    Node *left_child;
    Node *right_child;

    Node() {
        data = '\0';
        left_child = NULL;
        right_child = NULL;
    }

    Node(char data_, Node *left_child_, Node *right_child_) {
        data = data_;
        left_child = left_child_;
        right_child = right_child_;
    }
};

void CreateTree(Node *parent, char *tree_str, int index, int &leaf_num) {
    int flag[2] = {0};
    parent->data = tree_str[index];
    if (index * 2 + 1 < strlen(tree_str)) {
        if (tree_str[index * 2 + 1] != '#') {
            Node *left_child = new Node();
            parent->left_child = left_child;
            CreateTree(left_child, tree_str, index * 2 + 1, leaf_num);
        } else {
            flag[0] = 1;
            parent->left_child = NULL;
        }
    } else {
        flag[0] = 1;
        parent->left_child = NULL;
    }
    if (index * 2 + 2 < strlen(tree_str)) {
        if (tree_str[index * 2 + 2] != '#') {
            Node *right_child = new Node();
            parent->right_child = right_child;
            CreateTree(right_child, tree_str, index * 2 + 2, leaf_num);
        } else {
            flag[1] = 1;
            parent->right_child = NULL;
        }
    } else {
        flag[1] = 1;
        parent->right_child = NULL;
    }
    if (flag[0] * flag[1]) {
        leaf_num++;
    }
    return;
}

void SwapTree(Node *root) {
    if (root == NULL) {
        return;
    } else {
        Node *tmp = root->left_child;
        root->left_child = root->right_child;
        root->right_child = tmp;
        SwapTree(root->left_child);
        SwapTree(root->right_child);
    }
}

void PreOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        printf("%c", root->data);
        PreOrderTraverse(root->left_child);
        PreOrderTraverse(root->right_child);
    }
}

void InOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        InOrderTraverse(root->left_child);
        printf("%c", root->data);
        InOrderTraverse(root->right_child);
    }
}

void PostOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        PostOrderTraverse(root->left_child);
        PostOrderTraverse(root->right_child);
        printf("%c", root->data);
    }
}

void TraverseTree(Node *root, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%c\n", root->data);
    if (root->left_child != NULL) {
        TraverseTree(root->left_child, depth + 1);
    }
    if (root->right_child != NULL) {
        TraverseTree(root->right_child, depth + 1);
    }
}

int main() {
    char tree_str[1000] = {'\0'};
    scanf("%s", tree_str);
    int tree_size = strlen(tree_str), leaf_num = 0;
    Node *root = new Node();
    CreateTree(root, tree_str, 0, leaf_num);
    printf("BiTree\n");
    TraverseTree(root, 0);
    printf("pre_sequence  : ");
    PreOrderTraverse(root);
    printf("\n");
    printf("in_sequence   : ");
    InOrderTraverse(root);
    printf("\n");
    printf("post_sequence : ");
    PostOrderTraverse(root);
    printf("\n");
    printf("Number of leaf: %d\n", leaf_num);
    SwapTree(root);
    printf("BiTree swapped\n");
    TraverseTree(root, 0);
    printf("pre_sequence  : ");
    PreOrderTraverse(root);
    printf("\n");
    printf("in_sequence   : ");
    InOrderTraverse(root);
    printf("\n");
    printf("post_sequence : ");
    PostOrderTraverse(root);
    printf("\n");
    return 0;
}