#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define inf 0x3fffffff
struct Info{
	int value;
	int count;
};
bool cmp(const Info &a,const Info &b){
	if(a.value!=b.value){
		return a.value>b.value;
	}else{
		return a.count>b.count;
	}
	
}
int main(){
	int N,C;
	
	Info info[25];
	int used[25];
	scanf("%d %d",&N,&C);
	for(int i=0;i<N;i++){
		scanf("%d %d",&info[i].value,&info[i].count);
	}
	sort(info,info+N,cmp);
	
	int ans=0;
	for(int i=0;i<N;i++){
		if(info[i].value>=C){
			ans+=info[i].count;
			info[i].count=0;
		}
	}
	while(1){
		int cur=C;
		int k;
		bool sign=false;
		memset(used,0,sizeof(used));
		//币值从大到小，能取多少取多少，用数学归纳法证明贪心的有效性
		for(int i=0;i<N;i++){
			if(info[i].count>0){
				k=cur/info[i].value;
				k=min(k,info[i].count);
				used[i]=k;
				cur-=k*info[i].value;
				if(cur==0){
					sign=true;
					break;
				}
			}
		}
		//如果不够，再从小到大来补足差额，尽量等于C
		if(cur>0){
			for(int i=N-1;i>=0;i--){
				while(info[i].count>used[i]){
					used[i]++;
					cur-=info[i].value;
					if(cur<0){
						sign=true;
						break;
					}
				}
				if(sign){
					break;
				}
			}
		}
		//如果此轮无法凑齐C，则退出
		if(!sign){
			break;
		}
		
		int M=inf;
		for(int i=0;i<N;i++){
			if(used[i]>0){
				M=min(M,info[i].count/used[i]);
			}
		}
		ans+=M;
		for(int i=0;i<N;i++){
			if(used[i]>0){
				info[i].count-=M*used[i];
			}
		}
		
	}
	printf("%d\n",ans);
	return 0;
}
