#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=20005;
const int K=175;
const int nK=87;
int rec[max_n];
int N;

struct SAM{
	int fa[max_n<<1],len[max_n<<1],left[max_n<<1],right[max_n<<1],sz[max_n<<1];
	int nxt[max_n<<1][K];
	int last,cnt;
	int counts[max_n],rk[max_n<<1];
	void init(){
		last=cnt=0;
		fa[0]=-1;
		len[0]=0;
		right[0]=0;
		left[0]=0;
		sz[0]=1;
		memset(nxt,-1,sizeof(nxt));
	}
	void add(int x,int pos){
		int p=last;
		int np=last=++cnt;
		int q,nq;
		len[np]=len[p]+1;
		right[np]=left[np]=pos;
		sz[np]=1;
		while(p!=-1&&nxt[p][x]==-1){
			nxt[p][x]=np;
			p=fa[p];
		}
		if(p==-1){
			fa[np]=0;
		}else{
			q=nxt[p][x];
			if(len[q]==len[p]+1){
				fa[np]=q;
			}else{
				nq=++cnt;
				len[nq]=len[p]+1;
				sz[nq]=0;
				left[nq]=left[q];
				right[nq]=right[q];
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				for(int i=0;i<K;i++) nxt[nq][i]=nxt[q][i];
				while(p!=-1&&nxt[p][x]==q){
					nxt[p][x]=nq;
					p=fa[p];
				}
				
			}
		}
	}
	void work(){
		int ans=-1;
		for(int i=0;i<=N;i++) counts[i]=0;
		for(int i=0;i<=cnt;i++) counts[len[i]]++;
		for(int i=1;i<=N;i++) counts[i]+=counts[i-1];
		for(int i=cnt;i>=0;i--) rk[--counts[len[i]]]=i;
		for(int i=cnt;i>=0;i--){
			int f=fa[rk[i]];
			int s=rk[i];
			sz[f]+=sz[s];
			//left[f]=min(left[f],left[s]);
			right[f]=max(right[f],right[s]);
			//这里必须是>，因为读入的是差分序列，如果等于的话，原序列是有重合的
			if(sz[s]>1&&right[s]-left[s]>len[s]){
				ans=max(ans,len[s]);
			}
		}

		if(ans<4){
			printf("0\n");
		}else{
			printf("%d\n",ans+1);
		}
	}
}sam;

int main(){
	while(scanf("%d",&N)&&N){
		for(int i=0;i<N;i++){
			scanf("%d",&rec[i]);
		}
		if(N<9){
			printf("0\n");
			continue;
		}
		N--;
		sam.init();
		for(int i=0;i<N;i++){
			rec[i]=rec[i+1]-rec[i]+nK;
			sam.add(rec[i],i+1);
		}
		sam.work();
	}	
	return 0;
}
