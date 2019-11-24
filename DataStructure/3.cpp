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
    {   printf("%d", head->next->data );  
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

void change(int n, int m, NODE *head) {
	NODE *start = head, *end = head;
	int yu[100] = {0}, flag = 0, shang = 0;
	yu[0] = n;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < i; j++) {
			if (yu[i] == yu[j]) {
				start = start->next;
				head->next = start->next;
				for (int k = 0; k < j; k++) {
					start = start->next;
				}
				end->next = start;
				flag = 1;
				break;
			}
		}
		if (flag)
			break;
		for (shang = 0; yu[i] >= shang * m; shang++)
			;
		yu[i + 1] = (yu[i] - (shang - 1) * m) * 10;
		end->next = (NODE *)malloc(sizeof(NODE));
		end->next->data = shang - 1;
		end = end->next;
		if(yu[i+1]==0){
			start = start->next;
			head->next = start->next;
			end->next=NULL;
			return;
		}
	}
	return;
}
