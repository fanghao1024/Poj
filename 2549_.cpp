#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

int num[1010];
const int max_n=5e5+10;
int Hash[max_n];
int Next[max_n];
struct Rec{
	int x;
	int y;
}rec[max_n];
bool solve(int i,int j){
	int key=(i-j+max_n)%max_n;
	int tot=Hash[key];
	while(tot!=-1){
		if(rec[tot].x+rec[tot].y==i-j&&rec[tot].x!=i&&rec[tot].x!=j&&rec[tot].y!=i&&rec[tot].y!=j){
			return true;
		}
		tot=Next[tot];
	}
	return false;
}
int main(){
	int N;
	while(scanf("%d",&N)){
		if(!N) break;
		for(int i=0;i<N;i++) scanf("%d",&num[i]);
		sort(num,num+N);
		memset(Hash,-1,sizeof(Hash));
		int tot=0;
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				rec[tot].x=num[i];
				rec[tot].y=num[j];
				int key=(num[i]+num[j]+max_n)%max_n;
				Next[tot]=Hash[key];
				Hash[key]=tot;
				tot++;
			}
		}
		int res=-1;
		bool flag=false;
		for(int i=N-1;i>=0;i--){
			for(int j=i-1;j>=0;j--){
				flag=solve(num[i],num[j]);
				if(flag){
					res=i;
					break;
				}
			}
			if(flag) break;
		}
		if(res!=-1){
			printf("%d\n",num[res]);
		}else{
			printf("no solution\n");
		}
	}
	return 0;
}
