/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct sdata {
    char data;
    struct sdata *next;
} SNODE;

void setlink(SNODE *, char *), outlink(SNODE *);

int listlen(SNODE *);

SNODE *ziplist(SNODE *, SNODE *);

SNODE *findlist(SNODE *, SNODE *);

int main() {
    SNODE *head1, *head2, *head;
    char str1[100], str2[100];

    gets(str1);
    gets(str2);

    head1 = (SNODE *) malloc(sizeof(SNODE));
    head2 = (SNODE *) malloc(sizeof(SNODE));
    head = (SNODE *) malloc(sizeof(SNODE));
    head->next = head1->next = head2->next = NULL;

    setlink(head1, str1);
    setlink(head2, str2);

    head->next = ziplist(head1, head2);

    head->next = findlist(head1, head2);
    outlink(head);
    return 0;
}

void setlink(SNODE *head, char *str) {
    SNODE *p;

    while (*str != '\0') {
        p = (SNODE *) malloc(sizeof(SNODE));
        p->data = *str;
        p->next = NULL;
        str++;
        head->next = p;
        head = p;
    }
    return;
}

void outlink(SNODE *head) {
    while (head->next != NULL) {
        printf("%c", head->next->data);
        head = head->next;
    }
    printf("\n");
    return;
}

int listlen(SNODE *head) {
    int len = 0;
    while (head->next != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

SNODE *findlist(SNODE *head1, SNODE *head2) {
    int m, n;
    SNODE *p1 = head1, *p2 = head2;

    m = listlen(head1);
    n = listlen(head2);
    while (m > n) {
        p1 = p1->next;
        m--;
    }
    while (m < n) {
        p2 = p2->next;
        n--;
    }

    while (p1->next != NULL && p1->next != p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1->next;
}

/* Here is waiting for you!     */
/*  
  SNODE * ziplist( SNODE * head1, SNODE * head2 )  
  {  
  }  
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

SNODE *ziplist(SNODE *head1, SNODE *head2) {
    int m, n;
    SNODE *p1 = head1, *p2 = head2, *ans = NULL, *previous = NULL;

    m = listlen(head1);
    n = listlen(head2);
    while (m > n) {
        p1 = p1->next;
        m--;
    }
    while (m < n) {
        p2 = p2->next;
        n--;
    }

    int flag = 0;
    while (p1->next != NULL) {
        if (p1->next->data == p2->next->data) {
            if (flag) {
                p1 = p1->next;
                p2 = p2->next;
                continue;
            } else {
                previous = p2;
                ans = p1->next;
                flag = 1;
                p1 = p1->next;
                p2 = p2->next;
                continue;
            }
        } else {
            if (flag) {
                flag = 0;
                ans = NULL;
                p1 = p1->next;
                p2 = p2->next;
            } else {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    if (ans != NULL) {
        previous->next = ans;
    }
    return ans;
}  