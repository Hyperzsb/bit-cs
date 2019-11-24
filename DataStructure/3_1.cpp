/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */    
  
#include <stdio.h>    
#include <stdlib.h>    
    
typedef struct node    
{   int         data;    
    struct node * next;    
} NODE;    
    
void output( NODE * );    
void change( int, int, NODE * );    
    
void output( NODE * head )    
{   int k=0;    
    
    printf("0.");    
    while ( head->next != NULL && k<50 )    
    {   printf("%d ", head->next->data );    
        head = head->next;    
        k ++;    
    }    
    printf("\n");    
}    
    
int main()    
{   int n, m;    
    NODE * head;    
    
    scanf("%d%d", &n, &m);    
    head = (NODE *)malloc( sizeof(NODE) );    
    head->next = NULL;    
    head->data = -1;    
    change( n, m, head );    
    output( head );    
    return 0;    
}    
    
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */   
void change( int n, int m, NODE * head){
	NODE *p,*r;
	int i;
	for(i=0;i<=50&&n!=0;i++){
		p=(NODE*)malloc(sizeof(NODE));
		n=n*10;
		p->data=n/m;
		n=n%m;
		if(head->next==NULL) head->next=p;
		else r->next=p;
		p->next=NULL;
		r=p;
	}
}  
