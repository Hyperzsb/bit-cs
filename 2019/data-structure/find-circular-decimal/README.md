# Find circular decimal (求循环小数)

**Description:**

对于任意的真分数 N/M （ 0 < N < M ），均可以求出对应的小数。如果采用链表表示各个小数，对于循环节采用循环链表表示，则所有分数均可以表示为如下链表形式。

![链表示意图](http://lexue.bit.edu.cn/pluginfile.php/212360/mod_programming/intro/%E5%BE%AA%E7%8E%AF%E8%8A%82.JPG)

**Input:**

N M

**Output:**

转换后的小数（不超过 50 ）

**Prefix Code:**

```C
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
```

**Example:**

- Input:

```
1 8
```

- Output:

```
0.125
```

