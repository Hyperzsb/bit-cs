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
  NODE *polynome_1_current = polynome_1, *polynome_2_current = polynome_2,  
        *polynome_ans_current = polynome_ans, *polynome_ans_previous = polynome_ans;
	while(polynome_1_current->next!=NULL){
		polynome_1_current=polynome_1_current->next;
		polynome_2_current = polynome_2;
		while(polynome_2_current->next!=NULL){
			polynome_2_current=polynome_2_current->next;
			int coef=polynome_1_current->coef*polynome_2_current->coef;
			int exp=polynome_1_current->exp+polynome_2_current->exp;
			if(coef!=0){
				int flag=0;
				polynome_ans_current=polynome_ans,polynome_ans_previous=polynome_ans;
				while(polynome_ans_current->next!=NULL){
					polynome_ans_previous=polynome_ans_current;
					polynome_ans_current=polynome_ans_current->next;
					if(exp==polynome_ans_current->exp){
						polynome_ans_current->coef+=coef;
						if(polynome_ans_current->coef==0){
							polynome_ans_previous->next=polynome_ans_current->next;
							free(polynome_ans_current);
							polynome_ans_current=polynome_ans_previous;
						}
						flag=1;
						break;
					}else if(exp>polynome_ans_previous->exp&&exp<polynome_ans_current->exp){
						NODE *new_node=(NODE*)malloc(sizeof(NODE));
						new_node->coef=coef;
						new_node->exp=exp;
						new_node->next=polynome_ans_current;
						polynome_ans_previous->next=new_node;
						flag=1;
						break;
					}
				}
				if(!flag){
					NODE *new_node=(NODE*)malloc(sizeof(NODE));
						new_node->coef=coef;
						new_node->exp=exp;
						new_node->next=NULL;
						polynome_ans_current->next=new_node;
				}
			}
		}
	}
}  
