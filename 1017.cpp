#include<stdio.h>

int main(){
	int num[10];
	while(scanf("%d %d %d %d %d %d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])){
		if(num[1]==0&&num[2]==0&&num[3]==0&&num[4]==0&&num[5]==0&&num[6]==0){
			break;
		}
		int ans=0;
		int index;
		ans+=num[6];
		
		ans+=num[5];
		if(num[5]*11<num[1]){
			num[1]-=num[5]*11;
		}else{
			num[1]=0;
		}

		ans+=num[4];
		if(num[4]*5<num[2]){
			num[2]-=num[4]*5;
		}else{
			int store=(num[4]*5-num[2])*4;
			num[2]=0;
			if(num[1]>store){
				num[1]-=store;
			}else{
				num[1]=0;
			}
		}
		
		ans+=num[3]/4;
		num[3]=num[3]%4;
		
		if(num[3]>0){
			ans+=1;
			index=4-num[3];
			int mark=index*2-1;
			if(num[2]>mark){
				num[2]-=mark;
				index=index*9-mark*4;
			}else{
				index=index*9-num[2]*4;
				num[2]=0;
			}
			if(num[1]>index){
				num[1]-=index;
			}
			else{
				num[1]=0;
			}
		}

		ans+=num[2]/9;
		num[2]=num[2]%9;
		if(num[2]>0){
			ans+=1;
			index=36-4*num[2];
			if(index<num[1]){
				num[1]-=index;
			}else{
				num[1]=0;
			}
		}

		ans+=(num[1]+35)/36;
		printf("%d\n",ans);
	}
	return 0;
}
