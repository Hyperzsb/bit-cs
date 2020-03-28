#include<cstdio>
#include<cstdlib>
#include<cstring>

enum Type {
    Atom, List, Head
};

struct Node {
    Type type;
    union {
        char data;
        Node *list_head;
    };
    Node *tail;

    Node(Type type_, char data_, Node *list_head_, Node *tail_) {
        if (type_ == Atom) {
            type = type_;
            data = data_;
            tail = tail_;
        } else if (type_ == List) {
            type = type_;
            list_head = list_head_;
            tail = tail_;
        } else if (type_ == Head) {
            type = type_;
            tail = tail_;
        }
    }
};

Node *CreateList(char *list_str) {
    Node *list = new Node(Head, ' ', NULL, NULL);
    if (strcmp(list_str, "()") == 0) {
        return list;
    } else {
        Node *new_node = new Node(List, ' ', NULL, NULL);
        list->tail = new_node;
        int str_length = strlen(list_str);
        for (int i = 1; i < str_length - 1; i++) {
            if (list_str[i] == ',') {
                continue;
            } else if (list_str[i] == '(') {
                char *new_list_str = (char *) malloc((str_length - 2) * sizeof(char));
                int index = 0, flag = 0;
                new_list_str[index] = '(';
                i++;
                for (; list_str[i] != ')' || flag != 0; i++) {
                    if (list_str[i] == '(') {
                        flag++;
                    }
                    if (list_str[i] == ')') {
                        flag--;
                    }
                    new_list_str[++index] = list_str[i];
                }
                new_list_str[++index] = ')';
                new_list_str[++index] = '\0';
                new_node->type = List;
                new_node->list_head = CreateList(new_list_str);
                new_node->tail = new Node(List, ' ', NULL, NULL);
                new_node = new_node->tail;
            } else {
                new_node->type = Atom;
                new_node->data = list_str[i];
                new_node->tail = new Node(List, ' ', NULL, NULL);
                new_node = new_node->tail;
            }
        }
        return list;
    }
}

//void DestroyList(Node* list){
//
//}
void TraverseList(Node *list) {
    if (list->tail == NULL) {
        printf("()");
        return;
    }
    Node *list_head = list->tail;
    printf("(");
    while (list_head->tail != NULL) {
        if (list_head->type == Head) {
            list_head = list_head->tail;
        } else if (list_head->type == Atom) {
            printf("%c", list_head->data);
            list_head = list_head->tail;
            if (list_head->tail != NULL) {
                printf(",");
            }
        } else if (list_head->type == List) {
            TraverseList(list_head->list_head);
            list_head = list_head->tail;
            if (list_head->tail != NULL) {
                printf(",");
            }
        }
    }
    printf(")");
    return;
}

Node *GetHead(Node *list) {
    Node *head;
    if (list->tail->type == List) {
        head = list->tail->list_head;
        list = list->tail->tail;
        printf("destroy tail\nfree list node\n");
        printf("generic list: ");
        TraverseList(head);
        printf("\n");
    } else if (list->tail->type == Atom) {
        head = list->tail;
        list = list->tail->tail;
        printf("destroy tail\nfree list node\n");
        printf("generic list: ");
        printf("%c", head->data);
        printf("\n");
    }
    //DestroyList(list);
    return head;
}

Node *GetTail(Node *list) {
    Node *tail = new Node(Head, ' ', NULL, NULL);
    tail->tail = list->tail->tail;
    printf("free head node\nfree list node\n");
    printf("generic list: ");
    TraverseList(tail);
    printf("\n");
    list->tail->tail = NULL;
    //DestroyList(list);
    return tail;
}

int main() {
    char list_str[1000] = {'\0'};
    scanf("%s", list_str);
    Node *list = CreateList(list_str);
    printf("generic list: ");
    TraverseList(list);
    printf("\n");
    while (true) {
        if (list->type == Head && list->tail == NULL) {
            break;
        }
        if (list->type == Head && list->tail->list_head == NULL) {
            break;
        }
        if (list->type == Atom) {
            break;
        }
        int order = 0;
        scanf("%d", &order);
        if (order == 1) {
            list = GetHead(list);
        } else if (order == 2) {
            list = GetTail(list);
        }
    }
    return 0;
}