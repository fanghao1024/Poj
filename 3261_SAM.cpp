#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

const int max_n=40005;
map<int,int> son[max_n];
int lst=1,cnt=1;
int f[max_n],mx[max_n],sz[max_n];
int counts[max_n],r[max_n];
int N,K;
void extend(int x){
	int p=lst;
	int np=lst=++cnt;
	int q,nq;
	mx[np]=mx[p]+1;
	sz[np]=1;
	while(p&&!son[p][x]){
		son[p][x]=np;
		p=f[p];
	}
	if(!p){
		f[np]=1;
		return ;
	}
	q=son[p][x];
	if(mx[q]==mx[p]+1){
		f[np]=q;
	}else{
		nq=++cnt;
		mx[nq]=mx[p]+1;
		son[nq]=son[q];
		f[nq]=f[q];
		f[q]=f[np]=nq;
		while(p&&son[p][x]==q){
			son[p][x]=nq;
			p=f[p];
		}
	}
}
int main(){
	scanf("%d %d",&N,&K);
	int x;
	//memset(f,0,sizeof(f));
	memset(counts,0,sizeof(counts));
	mx[1]=0;
	f[1]=0;
	for(int i=0;i<N;i++){
		scanf("%d",&x);
		extend(x);
	}
	int ans=-1;
	for(int i=1;i<=cnt;i++) counts[mx[i]]++;
	for(int i=1;i<=N;i++) counts[i]+=counts[i-1]; //counts里是等价类的长度的计数，等价类中最长的长度是整个序列的长度，即N
	for(int i=cnt;i;i--) r[counts[mx[i]]--]=i;
	for(int i=cnt;i;i--){
		sz[f[r[i]]]+=sz[r[i]];
		if(sz[r[i]]>=K){
			ans=ans>mx[r[i]]?ans:mx[r[i]];
		}
	}
	for(int i=0;i<=cnt;i++) printf("%d ",mx[i]);
	printf("\n");
	for(int i=0;i<=cnt;i++) printf("%d ",sz[i]);
	printf("\n");
	printf("%d\n",ans);
	return 0;
}
