# 1. Multiplication of Univariate Polynomials (多项式相乘) <font color=Red>(Buggy)</font>

**Description:**

要求采用链表形式，求两个一元多项式的乘积：h<sub>3</sub> = h<sub>1</sub>*h<sub>2</sub>。函数原型为：void multiplication( NODE * h1, NODE * h2, NODE * h3 )。

**Input:**

输入数据为两行，分别表示两个一元多项式。每个一元多项式以指数递增的顺序输入多项式各项的系数（整数）、指数（整数）。

例如：1+2x+x<sup>2</sup>表示为：<1,0>,<2,1>,<1,2>,

**Output:**

以指数递增的顺序输出乘积： <系数,指数>,<系数,指数>,<系数,指数>,

零多项式的输出格式为：<0,0>,

**Prefix Code:**

```C
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
```

**Example:**

- Input:

```
<1,0>,<2,1>,<1,2>,
<1,0>,<1,1>,
```

- Output:

```
<1,0>,<3,1>,<3,2>,<1,3>,
```
