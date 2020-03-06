/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  
  
void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
             sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    if ( flag == 1 )  
             {    x = sign * sum;  
                  sum = 0;  
                  flag = 2;  
          sign = 1;  
             }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */ 

void multiplication(NODE *polynome_1, NODE *polynome_2, NODE *polynome_ans) {
	NODE *tmp_ans_head = (NODE *)malloc(sizeof(NODE));
	NODE *tmp_ans_current = tmp_ans_head;
	NODE *polynome_1_current = polynome_1, *polynome_2_current = polynome_2,
	      *polynome_ans_current = polynome_ans, *polynome_ans_previous = polynome_ans, *polynome_ans_next = polynome_ans;
	int max_exp[2] = {0};
	NODE *previous_node = polynome_1_current;
	do {
		previous_node = polynome_1_current;
		polynome_1_current = polynome_1_current->next;
		if (polynome_1_current->exp == max_exp[0]) {
			++max_exp[0];
		} else {
			NODE *new_node = (NODE *)malloc(sizeof(NODE));
			new_node->coef = 0, new_node->exp = max_exp[0];
			previous_node->next = new_node, new_node->next = polynome_1_current;
			polynome_1_current = new_node;
			++max_exp[0];
		}
	} while (polynome_1_current->next != NULL);
	previous_node = polynome_2_current;
	do {
		previous_node = polynome_2_current;
		polynome_2_current = polynome_2_current->next;
		if (polynome_2_current->exp == max_exp[1]) {
			++max_exp[1];
		} else {
			NODE *new_node = (NODE *)malloc(sizeof(NODE));
			new_node->coef = 0, new_node->exp = max_exp[1];
			previous_node->next = new_node, new_node->next = polynome_2_current;
			polynome_2_current = new_node;
			++max_exp[1];
		}
	} while (polynome_2_current->next != NULL);
	for (int i = 0; i < max_exp[0] + max_exp[1] - 1; i++) {
		NODE *new_node = (NODE *)malloc(sizeof(NODE));
		new_node->coef = 0, new_node->exp = i, new_node->next = NULL;
		polynome_ans_current->next = new_node, polynome_ans_current = new_node;
	}
	polynome_1_current = polynome_1, polynome_2_current = polynome_2, polynome_ans_current = polynome_ans;
	do {
		polynome_1_current = polynome_1_current->next;
		int coef_1 = polynome_1_current->coef, exp_1 = polynome_1_current->exp;
		polynome_ans_current = polynome_ans_next->next, polynome_ans_next = polynome_ans_next->next;
		polynome_2_current = polynome_2;
		do {
			polynome_2_current = polynome_2_current->next;
			int coef_2 = polynome_2_current->coef, exp_2 = polynome_2_current->exp;
			polynome_ans_current->coef += coef_1 * coef_2;
			polynome_ans_current = polynome_ans_current->next;
		} while (polynome_2_current->next != NULL);
	} while (polynome_1_current->next != NULL);
	polynome_ans_current = polynome_ans;
	do {
		polynome_ans_previous = polynome_ans_current;
		polynome_ans_current = polynome_ans_current->next;
		polynome_ans_next = polynome_ans_current->next;
		if (polynome_ans_current->coef == 0) {
			polynome_ans_previous->next=polynome_ans_next;
			free(polynome_ans_current);
			polynome_ans_current=polynome_ans_previous;
		} 
	} while (polynome_ans_current->next != NULL);
	if(polynome_ans->next==NULL){
		NODE *new_node=(NODE*)malloc(sizeof(NODE));
		new_node->coef=0;
		new_node->exp=0;
		new_node->next=NULL;
		polynome_ans->next=new_node;
	}
}
