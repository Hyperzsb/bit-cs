#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<algorithm>
int main(){
	int zuShu=0;
	scanf("%d",&zuShu);
	for(int i=0;i<zuShu;i++){
		long long int length=0,depth1[3]={0},depth2[3]={0},v1=0,v2=0;
		long long int ans=0;
		scanf("%d",&length);
		int *depthList=(int*)malloc(length*sizeof(int));
		for(int j=0;j<length;j++){
			scanf("%d",&depthList[j]);
		}
		
		depth1[0]=depthList[0];
		depth1[1]=0;
		depth1[2]=0;
		depth2[0]=depthList[length-1];
		depth2[1]=length-1;
		depth2[2]=length-1;
		
		for(int j=1;j<length;j++){
			//printf("!%d\n",j);
			if(depth1[2]==depth2[2]){
				if(depth1[1]==depth2[1])
					break;
				int height=depth1[0]<depth2[0]?depth1[0]:depth2[0];
				long long int tmp=(depth2[1]-depth1[1]-1)*height;
				//printf("!!!:%d\n",tmp);
				ans+=tmp-v1-v2;
				if(depthList[j-1]<height||(depth1[1]==j-1)||(depth2[1]==j-1))
					ans+=depthList[j-1];
				break;
			}
			if(depth1[2]==depth2[2]-1){
				int height=depth1[0]<depth2[0]?depth1[0]:depth2[0];
				long long int tmp=(depth2[1]-depth1[1]-1)*height;
				//printf("!!!:%d\n",tmp);
				tmp-=v1+v2;
				ans+=tmp;
				break;
			}
			if(depth1[0]>depthList[j]){
				v1+=depthList[j];
				depth1[2]=j;
			}
			else{
				long long int tmp=(depth1[2]-depth1[1])*depth1[0]-v1;
				ans+=tmp;
				//printf("a%d\n",tmp);
				depth1[0]=depthList[j];
				depth1[1]=j;
				depth1[2]=j;
				v1=0;
			}
			if(depth2[0]>depthList[length-1-j]){
				v2+=depthList[length-1-j];
				depth2[2]=length-1-j;
			}
			else{
				long long int tmp=(depth2[1]-depth2[2])*depth2[0]-v2;
				ans+=tmp;
				//printf("b%d\n",tmp);
				depth2[0]=depthList[length-1-j];
				depth2[1]=length-1-j;
				depth2[2]=length-1-j;
				v2=0;
			}
			//printf("%d %d %d %d\n",depth1[0],depth1[1],depth1[2],v1);
			//printf("%d %d %d %d\n",depth2[0],depth2[1],depth2[2],v2);
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
