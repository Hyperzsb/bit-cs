#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<algorithm>
int main(){
	int zuShu=0;
	scanf("%d",&zuShu);
	for(int i=0;i<zuShu;i++){
		int length=0;
		long long int depth1[3]={0},depth2[3]={0},v1=0,v2=0,maxHeight[2]={0},ans=0;
		scanf("%d",&length);
		int *depthList=(int*)malloc(length*sizeof(int));
		for(int j=0;j<length;j++){
			scanf("%d",&depthList[j]);
			if(depthList[j]>maxHeight[1]){
				maxHeight[0]=j;
				maxHeight[1]=depthList[j];
			}
		}
		
		depth1[0]=depthList[0];
		depth1[1]=0;
		depth1[2]=0;
		depth2[0]=depthList[length-1];
		depth2[1]=length-1;
		depth2[2]=length-1;
		
		for(int j=1;j<=maxHeight[0];j++){
			if(depth1[0]>depthList[j]){
				v1+=depthList[j];
				depth1[2]=j;
			}
			else{
				long long int tmp=(depth1[2]-depth1[1])*depth1[0]-v1;
				ans+=tmp;
				depth1[0]=depthList[j];
				depth1[1]=j;
				depth1[2]=j;
				v1=0;
			}
		}
		for(int j=length-1;j>=maxHeight[0];j--){
			if(depth2[0]>depthList[j]){
				v2+=depthList[j];
				depth2[2]=j;
			}
			else{
				long long int tmp=(depth2[1]-depth2[2])*depth2[0]-v2;
				ans+=tmp;
				depth2[0]=depthList[j];
				depth2[1]=j;
				depth2[2]=j;
				v2=0;
			}
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
