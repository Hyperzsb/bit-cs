#include<stdio.h>
#include<stdlib.h> 
#include<memory.h>
#include<algorithm>
int col=0,row=0;
int map[1000][1000];
int flag[1000][1000]={0};
void dfs(int x,int y,int border,long long int *ansList){
	flag[x][y]=1;
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++)
			printf("%d",flag[i][j]);
		printf("\n");
	}
	printf("\n");
	printf("!!!!%d\n",border);
	int tmpFlag=0,borderMin=-1;
	if(flag[x-1][y]==2){
		printf("#1\n");
		tmpFlag=1;
		if(borderMin==-1)
			borderMin=map[x-1][y];
		else
			borderMin=borderMin<map[x-1][y]?borderMin:map[x-1][y];
		//printf("$%d\n",borderMin);
	}
	if(flag[x+1][y]==2){
		printf("#2\n");
		tmpFlag=1;
		if(borderMin==-1)
			borderMin=map[x+1][y];
		else
			borderMin=borderMin<map[x+1][y]?borderMin:map[x+1][y];
		//printf("$%d\n",borderMin);
	}
	if(flag[x][y-1]==2){
		printf("#3\n");
		tmpFlag=1;
		if(borderMin==-1)
			borderMin=map[x][y-1];
		else
			borderMin=borderMin<map[x][y-1]?borderMin:map[x][y-1];
		//printf("$%d\n",borderMin);
	}
	if(flag[x][y+1]==2){
		printf("#4\n");
		tmpFlag=1;
		if(borderMin==-1)
			borderMin=map[x][y+1];
		else
			borderMin=borderMin<map[x][y+1]?borderMin:map[x][y+1];
		//printf("$%d\n",borderMin);
	}
	printf("!%d\n",border);
	if(border==-1)
		border=borderMin;
		
	printf("!%d\n",border);
	if(tmpFlag){
		if(map[x][y]>=border){
			ansList[0]=map[x][y];
			flag[x][y]=2;
			return ;
		}
		if(border>borderMin)
			border=borderMin;
	}
	printf("!!%d\n",border);
	ansList[1]++;
	ansList[2]+=map[x][y];
	
	if(flag[x-1][y]==0){
		if(map[x-1][y]>=border)
			flag[x-1][y]=2;
		else
			dfs(x-1,y,border,ansList);
	}
	if(flag[x+1][y]==0){
		if(map[x+1][y]>=border)
			flag[x+1][y]=2;
		else
			dfs(x+1,y,border,ansList);
	}
	if(flag[x][y-1]==0){
		if(map[x][y-1]>=border)
			flag[x][y-1]=2;
		else
			dfs(x,y-1,border,ansList);
	}
	if(flag[x][y-1]==0){
		if(map[x][y-1]>=border)
			flag[x][y-1]=2;
		else
			dfs(x,y-1,border,ansList);
	}
	
}
int main(){
	long long int ans=0,ansList[3]={0};
	scanf("%d%d",&col,&row);
	for(int i=0;i<col;i++)
		for(int j=0;j<row;j++){
			scanf("%d",&map[i][j]);
			if(i==0||i==col-1||j==0||j==row-1)
				flag[i][j]=2;
			else
				flag[i][j]=0;
		}
	for(int i=1;i<col-1;i++)
		for(int j=1;j<row-1;j++)
			if(flag[i][j]==0){
				dfs(i,j,-1,ansList);
				printf("ANS:%d %d %d\n",ansList[0],ansList[1],ansList[2]);
				ans+=ansList[0]*ansList[1]-ansList[2];
				memset(ansList,0,sizeof(ansList));
			}
	printf("%lld",ans);		
	return 0;
}
