#include<stdio.h>
#include<string.h>
int main(){
	int zuShu=0,length=0,tmp[2]={0},flag=1;
	char str[1005]={'\0'},sample[]="fattyhappy";
	scanf("%d",&zuShu);
	int i=0;
	for(;i<zuShu;i++){
		scanf("%s",str);
		length=strlen(str);
		int j=0;
		for(;j<length;j++){
			if(str[j]=='f'){
				//printf("f at:%d\n",j+1);
				int flag1=0,flag2=0;
				int k=0;
				for(;k<10;k++){
					if(flag1>2){
						flag2=1;
						break;
					}
					if(str[k+j]!=sample[k]){
						//printf("error at:%d\n",k+j+1);
						tmp[flag1]=k+j;
						flag1++;
					}
				}
				if(flag2)
					continue;
				else{
					if(flag1==0){
						printf("%d %d\n",j,j+11);
						flag=0;
						break;
					}else if(flag1==1){
						int k=0;
						for(;k<length;k++)
							if((k<j||k>j+9)&&str[k]==sample[tmp[0]-j]){
								if(k+1<tmp[0]+1)
									printf("%d %d\n",k+1,tmp[0]+1);
								else
									printf("%d %d\n",tmp[0]+1,k+1);
								flag=0;
								break;
							}
						continue;
					}
					else
						if(str[tmp[0]]==sample[tmp[1]-j]&&str[tmp[1]]==sample[tmp[0]-j]){
							printf("%d %d\n",tmp[0]+1,tmp[1]+1);
							flag=0;
							break;
						}else
							continue;
				}
			}else
				continue;
		}
		if(flag){
			
		}
		if(flag)
			printf("-1\n");
		else
			flag=1;
	}
	return 0;
}
