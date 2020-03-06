#include<cstdio>
#include<cstdlib>
#include<memory.h>
namespace std_namespace{
}
int main(){
	using namespace std_namespace;
	int col_num=0,row_num=0,nonzero_element_num=0,sum=1;
	
	scanf("%d%d%d",&col_num,&row_num,&nonzero_element_num);
	int **nonzero_element=(int**)malloc((nonzero_element_num+5)*sizeof(int*));
	int **ans_element=(int**)malloc((nonzero_element_num+5)*sizeof(int*));	
	int *row_element_num=(int*)malloc((row_num+5)*sizeof(int));
	memset(row_element_num,0,(row_num+5)*sizeof(int));
	int *row_element_position=(int*)malloc((row_num+5)*sizeof(int));
	memset(row_element_position,0,(row_num+5)*sizeof(int));
	
	for(int i=1;i<=nonzero_element_num;i++){
		nonzero_element[i]=(int*)malloc(3*sizeof(int));
		ans_element[i]=(int*)malloc(3*sizeof(int));
		scanf("%d%d%d",&nonzero_element[i][0],&nonzero_element[i][1],&nonzero_element[i][2]);
		row_element_num[nonzero_element[i][1]]++;
	}
	for(int i=1;i<=row_num;i++){
		row_element_position[i]+=sum;
		sum+=row_element_num[i];
	}
	printf("num:");
	for(int i=1;i<=row_num;i++){
		printf("%d,",row_element_num[i]);
	}
	printf("\n");
	printf("cpot:");
	for(int i=1;i<=row_num;i++){
		printf("%d,",row_element_position[i]);
	}
	printf("\n");
	for(int i=1;i<=nonzero_element_num;i++){
		
		ans_element[row_element_position[nonzero_element[i][1]]][0]=nonzero_element[i][1];
		ans_element[row_element_position[nonzero_element[i][1]]][1]=nonzero_element[i][0];
		ans_element[row_element_position[nonzero_element[i][1]]][2]=nonzero_element[i][2];
		row_element_position[nonzero_element[i][1]]++;
	}
	for(int i=1;i<=nonzero_element_num;i++){
		printf("%d,%d,%d\n",ans_element[i][0],ans_element[i][1],ans_element[i][2]);
	}
	return 0;
}
