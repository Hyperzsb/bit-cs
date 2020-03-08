#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<algorithm>
#define inf 0x3f3f3f
bool cmp(int a,int b){
	return a>b;
}
int main(){
	int area[2]={0},suSheShu=0,diDianShu=0,tmpX=0,tmpY=0,min1=0,min2=0,min3=0,min4=0,ans=LONG_MAX,lengthList[4]={0};
	scanf("%d%d%d",&area[0],&area[1],&suSheShu);
	for(int i=0;i<suSheShu;i++){
		scanf("%d%d",&tmpX,&tmpY);
		if(min1>tmpX+tmpY)
			min1=tmpX+tmpY;
		if(min2>tmpX-tmpY)
			min2=tmpX-tmpY;
		if(min3>-tmpX+tmpY)
			min3=-tmpX+tmpY;
		if(min4>-tmpX-tmpY)
			min4=-tmpX-tmpY;
	}
	scanf("%d",&diDianShu);
	for(int i=0;i<diDianShu;i++){
		scanf("%d%d",&tmpX,&tmpY);
		lengthList[0]=tmpX+tmpY-min1;
		lengthList[1]=tmpX-tmpY-min2;
		lengthList[2]=-tmpX+tmpY-min3;
		lengthList[3]=-tmpX-tmpY-min4;
		std::sort(lengthList,lengthList+4,cmp);
		if(lengthList[0]<ans)
			ans=lengthList[0];
	}
	printf("%d\n",ans);
	
	return 0;
}
