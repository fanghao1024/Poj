#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=70;

int N,cnt,num[max_n],len,sum,m;
int nxt[max_n];
bool ok,used[max_n];
bool cmp(int a,int b){return a>b;}
void dfs(int k,int last,int rest){
	if(!rest){
		if(k==m){
			ok=true;
			return ;
		}
		int i;
		for(i=1;i<=cnt;i++){
			if(!used[i]) break;
		}
		used[i]=1;
		dfs(k+1,i,len-num[i]);
		used[i]=0;
		if(ok) return ;
	}
	int l=last+1,r=cnt;
	int mid;
	while(l<r){
		mid=(l+r)>>1;
		if(num[mid]<=rest) r=mid;
		else l=mid+1;
	}
	for(int i=r;i<=cnt;i++){
		if(!used[i]){
			used[i]=1;
			dfs(k,i,rest-num[i]);
			used[i]=0;
			if(ok) return ;
			
			if(rest==num[i] || rest==len) return; //优化7 
			i=nxt[i]; //优化3 
			//if(i==cnt) return;
		}
	}
}
int main(){
	scanf("%d",&N);
	cnt=sum=0;
	int x;
	for(int i=1;i<=N;i++){
		scanf("%d",&x);
		if(x<=50){
			num[++cnt]=x;
			sum+=x;
		}
	}
	sort(num+1,num+1+cnt,cmp);
	nxt[cnt]=cnt;
	for(int i=cnt-1;i>0;i--){
		if(num[i]==num[i+1]) nxt[i]=nxt[i+1];
		else nxt[i]=i;
	}
	memset(used,0,sizeof(used));
	for(len=num[1];len<=sum/2;len++){
		if(sum%len!=0) continue;
		m=sum/len;
		ok=false;
		used[1]=1;
		dfs(1,1,len-num[1]);
		used[1]=0;
		if(ok) break;
	}
	if(ok) printf("%d\n",len);
	else printf("%d\n",sum);
	return 0;
}
