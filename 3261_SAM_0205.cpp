#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

int N,K;
const int max_n=40005;
struct SAM{
	int fa[max_n],len[max_n],sz[max_n];
	map<int,int> son[max_n];
	int last,cnt;
	int counts[max_n],rk[max_n];
	void init(){
		last=cnt=0;
		len[0]=0;
		fa[0]=-1;
		sz[0]=1;
	}
	void add(int x){
		int p=last;
		int np=last=++cnt;
		int q,nq;
		sz[np]=1;
		len[np]=len[p]+1;
		while(p!=-1&&!son[p][x]){
			son[p][x]=np;
			p=fa[p];
		}
		if(p==-1){
			fa[np]=0;
		}else{
			q=son[p][x];
			if(len[q]==len[p]+1){
				fa[np]=q;
			}
			else{
				nq=++cnt;
				len[nq]=len[p]+1;
				fa[nq]=fa[q];
				sz[nq]=0;
				son[nq]=son[q];
				fa[np]=fa[q]=nq;
				while(p!=-1&&son[p][x]==q){
					son[p][x]=nq;
					p=fa[p];
				}
			}
		}
	}
	void work(){
		memset(counts,0,sizeof(counts));
		int ans=-1;
		for(int i=0;i<=cnt;i++) counts[len[i]]++;
		for(int i=1;i<=N;i++) counts[i]+=counts[i-1];
		for(int i=cnt;i>=0;i--) rk[--counts[len[i]]]=i;
		for(int i=cnt;i>=0;i--){
			sz[fa[rk[i]]]+=sz[rk[i]];
			if(sz[rk[i]]>=K){
				ans=ans>len[rk[i]]?ans:len[rk[i]];
			}
		}
		printf("%d\n",ans);
	}
}sam;
int main(){
	scanf("%d %d",&N,&K);
	int x;
	sam.init();
	for(int i=0;i<N;i++){
		scanf("%d",&x);
		sam.add(x);
	}
	sam.work();
	return 0;
}
