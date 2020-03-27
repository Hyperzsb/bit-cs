# 1. Word Compression Storage (单词压缩存储)

**Description:**

如果采用单链表保存单词，可采用如下办法压缩存储空间。如果两个单词的后缀相同，则可以用同一个存储空间保存相同的后缀。例如，原来分别采用单链表保存的单词Str1“loading”和单词Str2“being”，经过压缩后的存储形式如下。

![单词压缩](http://lexue.bit.edu.cn/pluginfile.php/212371/mod_programming/intro/%E5%8D%95%E8%AF%8D%E5%8E%8B%E7%BC%A9.jpg)

请设计一个高效的算法完成两个单链表的压缩存储。

要求：阅读预设代码，编写函数SNODE * ziplist( SNODE * head1, SNODE * head2 )
ziplist的功能是：在两个串链表中，查找公共后缀，若有公共后缀，则压缩 并返回指向公共后缀的指针；否则返回NULL。

**Prefix Code:**

```C
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct sdata  
{  char  data;  
   struct sdata *next;  
} SNODE;  
  
void setlink( SNODE *, char * ), outlink( SNODE * );  
int listlen( SNODE * );  
SNODE * ziplist( SNODE *, SNODE * );  
SNODE * findlist( SNODE *, SNODE * );  
  
int main( )  
{  
    SNODE * head1, * head2, *head;  
    char str1[100], str2[100];  
  
    gets( str1 );  
    gets( str2 );  
  
    head1 = (SNODE *) malloc( sizeof(SNODE) );  
    head2 = (SNODE *) malloc( sizeof(SNODE) );  
    head = (SNODE *) malloc( sizeof(SNODE) );  
    head->next = head1->next = head2->next = NULL;  
  
    setlink( head1, str1 );  
    setlink( head2, str2);  
  
    head->next = ziplist( head1, head2 );  
  
    head->next = findlist( head1, head2 );  
    outlink( head );  
    return 0;  
}  
  
void setlink( SNODE *head, char *str )  
{  
    SNODE *p ;  
  
    while ( *str != '\0' )  
    {   p  = ( SNODE * ) malloc( sizeof( SNODE ) );  
        p->data = *str;  
        p->next = NULL;  
        str++;  
        head->next = p;  
        head = p;  
    }  
    return;  
}  
  
void outlink( SNODE * head )  
{  
    while ( head->next != NULL )  
    {  
        printf( "%c", head -> next -> data );  
        head = head -> next;  
    }  
    printf("\n");  
    return;  
}  
  
int listlen( SNODE * head )  
{  
    int len=0;  
    while ( head->next != NULL )  
    {  
        len ++;  
        head = head->next;  
    }  
    return len;  
}  
  
SNODE * findlist( SNODE * head1, SNODE * head2 )  
{  
    int m, n;  
    SNODE *p1=head1, *p2=head2;  
  
    m = listlen( head1 );  
    n = listlen( head2 );  
    while  ( m > n )  
    {   p1 = p1->next;  
        m--;  
    }  
    while  ( m < n )  
    {   p2 = p2->next;  
        n--;  
    }  
  
    while( p1->next != NULL && p1->next != p2->next )  
    {  
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
```

**Example:**

- Input:

```
abcdef
dbdef
```

- Output:

```
def
```

