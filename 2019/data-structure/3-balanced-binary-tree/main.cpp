#include<cstdio>
#include<cstdlib>
#include<cstring>

struct Node {
    char value;
    int child_type;
    int height;
    int left_height;
    int right_height;
    int flag;
    Node *parent;
    Node *left_child;
    Node *right_child;

    Node(char value_) {
        value = value_;
        child_type = 0;
        height = 1;
        left_height = 0;
        right_height = 0;
        flag = 0;
        parent = NULL;
        left_child = NULL;
        right_child = NULL;
    }
};

void RotateRight(Node *root) {
    Node *root_parent = root->parent;
    Node *new_root = root->left_child;
    Node *new_child = new_root->right_child;
    int child_type = root->child_type;
    new_root->right_child = root;
    root->parent = new_root;
    root->child_type = 2;
    root->left_child = new_child;
    if (new_child != NULL) {
        new_child->parent = root;
        new_child->child_type = 1;
    }
    if (root->left_child != NULL) {
        root->left_height = root->left_child->height;
    } else {
        root->left_height = 0;
    }
    if (root->right_child != NULL) {
        root->right_height = root->right_child->height;
    } else {
        root->right_height = 0;
    }
    root->height = (root->left_height > root->right_height ? root->left_height : root->right_height) + 1;
    root->flag = root->left_height - root->right_height;
    if (new_root->left_child != NULL) {
        new_root->left_height = new_root->left_child->height;
    } else {
        new_root->left_height = 0;
    }
    if (new_root->right_child != NULL) {
        new_root->right_height = new_root->right_child->height;
    } else {
        new_root->right_height = 0;
    }
    new_root->height =
            (new_root->left_height > new_root->right_height ? new_root->left_height : new_root->right_height) + 1;
    new_root->flag = new_root->left_height - new_root->right_height;
    if (child_type == 0) {
        new_root->parent = root_parent;
        new_root->child_type = 0;
    } else if (child_type == 1) {
        root_parent->left_child = new_root;
        new_root->parent = root_parent;
        new_root->child_type = 1;
    } else {
        root_parent->right_child = new_root;
        new_root->parent = root_parent;
        new_root->child_type = 2;
    }
    return;
}

void RotateLeft(Node *root) {
    Node *root_parent = root->parent;
    Node *new_root = root->right_child;
    Node *new_child = new_root->left_child;
    int child_type = root->child_type;
    new_root->left_child = root;
    root->parent = new_root;
    root->child_type = 1;
    root->right_child = new_child;
    if (new_child != NULL) {
        new_child->parent = root;
        new_child->child_type = 2;
    }
    if (root->left_child != NULL) {
        root->left_height = root->left_child->height;
    } else {
        root->left_height = 0;
    }
    if (root->right_child != NULL) {
        root->right_height = root->right_child->height;
    } else {
        root->right_height = 0;
    }
    root->height = (root->left_height > root->right_height ? root->left_height : root->right_height) + 1;
    root->flag = root->left_height - root->right_height;
    if (new_root->left_child != NULL) {
        new_root->left_height = new_root->left_child->height;
    } else {
        new_root->left_height = 0;
    }
    if (new_root->right_child != NULL) {
        new_root->right_height = new_root->right_child->height;
    } else {
        new_root->right_height = 0;
    }
    new_root->height =
            (new_root->left_height > new_root->right_height ? new_root->left_height : new_root->right_height) + 1;
    new_root->flag = new_root->left_height - new_root->right_height;
    if (child_type == 0) {
        new_root->parent = root_parent;
        new_root->child_type = 0;
    } else if (child_type == 1) {
        root_parent->left_child = new_root;
        new_root->parent = root_parent;
        new_root->child_type = 1;
    } else {
        root_parent->right_child = new_root;
        new_root->parent = root_parent;
        new_root->child_type = 2;
    }
    return;
}

Node *FindRoot(Node *leaf) {
    if (leaf->parent == NULL) {
        return leaf;
    } else {
        FindRoot(leaf->parent);
    }
}

Node *FindFirstImbalance(Node *leaf) {
    if (leaf->parent == NULL) {
        return NULL;
    } else {
        Node *parent = leaf->parent;
        if (leaf->child_type == 1) {
            parent->left_height = leaf->height;
            parent->height =
                    (parent->left_height > parent->right_height ? parent->left_height : parent->right_height) + 1;
            parent->flag = parent->left_height - parent->right_height;
            if (parent->flag < -1 || parent->flag > 1) {
                return parent;
            } else {
                FindFirstImbalance(parent);
            }
        } else {
            parent->right_height = leaf->height;
            parent->height =
                    (parent->left_height > parent->right_height ? parent->left_height : parent->right_height) + 1;
            parent->flag = parent->left_height - parent->right_height;
            if (parent->flag < -1 || parent->flag > 1) {
                return parent;
            } else {
                FindFirstImbalance(parent);
            }
        }
    }
}

void UpdateTree(Node *leaf) {
    if (leaf->parent == NULL) {
        return;
    } else {
        Node *parent = leaf->parent;
        if (leaf->child_type == 1) {
            parent->left_height = leaf->height;
            parent->height =
                    (parent->left_height > parent->right_height ? parent->left_height : parent->right_height) + 1;
            parent->flag = parent->left_height - parent->right_height;
        } else {
            parent->right_height = leaf->height;
            parent->height =
                    (parent->left_height > parent->right_height ? parent->left_height : parent->right_height) + 1;
            parent->flag = parent->left_height - parent->right_height;
        }
    }
}

void Insert(char value, Node *root) {
    if (value == root->value) {
        //printf("%c EXISTED\n", value);
        return;
    } else if (value < root->value) {
        if (root->left_child != NULL) {
            Insert(value, root->left_child);
        } else {
            //printf("INSERT %c AT LEFT_CHILD\n", value);
            root->left_child = new Node(value);
            root->left_child->parent = root;
            root->left_child->child_type = 1;
            Node *flag_node = FindFirstImbalance(root->left_child);
            //printf("FIND FIRST_IMBALANCE_NODE: ");
            if (flag_node == NULL) {
                //printf("NULL UpdateTree\n");
                UpdateTree(root->left_child);
            } else {
                //printf("%c ", flag_node->value);
                //printf("FLAG %d\n", flag_node->flag);
                if (flag_node->flag > 1) {
                    //printf(">1\n");
                    if (flag_node->left_child->flag < 0) {
                        //printf("PREROTATE\n");
                        RotateLeft(flag_node->left_child);
                        RotateRight(flag_node);
                        //printf("PREROTATE SUCCEED\n");
                    } else {
                        RotateRight(flag_node);
                    }
                } else if (flag_node->flag < -1) {
                    //printf("<-1\n");
                    if (flag_node->right_child->flag > 0) {
                        //printf("PREROTATE\n");
                        RotateRight(flag_node->right_child);
                        RotateLeft(flag_node);
                        //printf("PREROTATE SUCCEED\n");
                    } else {
                        //printf("NO PREROTATE\n");
                        RotateLeft(flag_node);
                        //printf("ROTATE SUCCEED\n");
                    }
                }
            }
        }
    } else {
        if (root->right_child != NULL) {
            Insert(value, root->right_child);
        } else {
            //printf("INSERT %c AT RIGHT_CHILD\n", value);
            root->right_child = new Node(value);
            root->right_child->parent = root;
            root->right_child->child_type = 2;
            Node *flag_node = FindFirstImbalance(root->right_child);
            //printf("FIND FIRST_IMBALANCE_NODE: ");
            if (flag_node == NULL) {
                //printf("NULL UpdateTree\n");
                UpdateTree(root->right_child);
            } else {
                //printf("%c ", flag_node->value);
                //printf("FLAG %d\n", flag_node->flag);
                if (flag_node->flag > 1) {
                    //printf(">1\n");
                    if (flag_node->left_child->flag < 0) {
                        //printf("PREROTATE\n");
                        RotateLeft(flag_node->left_child);
                        RotateRight(flag_node);
                        //printf("PREROTATE SUCCEED\n");
                    } else {
                        //printf("NO PREROTATE\n");
                        RotateRight(flag_node);
                        //printf("ROTATE SUCCEED\n");
                    }
                } else if (flag_node->flag < -1) {
                    //printf("<-1\n");
                    if (flag_node->right_child->flag > 0) {
                        //printf("PREROTATE\n");
                        RotateRight(flag_node->right_child);
                        RotateLeft(flag_node);
                        //printf("PREROTATE SUCCEED\n");
                    } else {
                        //printf("NO PREROTATE\n");
                        RotateLeft(flag_node);
                        //printf("ROTATE SUCCEED\n");
                    }
                }
            }
        }
        return;
    }
}

void PreOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        printf("%c", root->value);
        PreOrderTraverse(root->left_child);
        PreOrderTraverse(root->right_child);
    }
}

void InOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        InOrderTraverse(root->left_child);
        printf("%c", root->value);
        InOrderTraverse(root->right_child);
    }
}

void PostOrderTraverse(Node *root) {
    if (root == NULL) {
        return;
    } else {
        PostOrderTraverse(root->left_child);
        PostOrderTraverse(root->right_child);
        printf("%c", root->value);
    }
}

void Traverse(Node *root, int depth) {
    if (root == NULL) {
        return;
    } else {
        Traverse(root->right_child, depth + 1);
        for (int i = 0; i < depth; i++) {
            printf("    ");
        }
        printf("%c\n", root->value);
        Traverse(root->left_child, depth + 1);
    }
}

int main() {
    char node_str[50] = {'\0'};
    scanf("%s", node_str);
    int str_len = strlen(node_str);
    Node *root = new Node(node_str[0]);
    for (int i = 1; i < str_len; i++) {
        Insert(node_str[i], root);
        root = FindRoot(root);
    }
    printf("Preorder: ");
    PreOrderTraverse(root);
    printf("\nInorder: ");
    InOrderTraverse(root);
    printf("\nPostorder: ");
    PostOrderTraverse(root);
    printf("\nTree:\n");
    Traverse(root, 0);

    return 0;
}