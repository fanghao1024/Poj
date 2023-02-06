#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=40005;
int M,N;
char ch[max_n];
int rec[max_n];
struct SAM{
	int fa[max_n<<1],len[max_n<<1],right[max_n<<1],sz[max_n<<1];
	int son[max_n<<1][26];
	int last,cnt;
	int counts[max_n],rk[max_n<<1];
	void init(){
		last=cnt=0;
		fa[0]=-1;
		len[0]=0;
		right[0]=0;
		sz[0]=1;
		memset(son,-1,sizeof(son));
	}
	void add(int x){
		int p=last;
		int np=last=++cnt;
		int q,nq;
		len[np]=right[np]=len[p]+1;
		sz[np]=1;
		while(p!=-1&&son[p][x]==-1){
			son[p][x]=np;
			p=fa[p];
		}
		if(p==-1){
			fa[np]=0;
		}else{
			q=son[p][x];
			if(len[q]==len[p]+1){
				fa[np]=q;
			}else{
				nq=++cnt;
				fa[nq]=fa[q];
				len[nq]=right[nq]=len[p]+1;
				sz[nq]=0;
				for(int i=0;i<26;i++) son[nq][i]=son[q][i];
				fa[np]=fa[q]=nq;
				while(p!=-1&&son[p][x]==q){
					son[p][x]=nq;
					p=fa[p];
				}
			}
		}
	}
	void work(){
		int ans1=-1,ans2=-1;
		for(int i=0;i<=N;i++) counts[i]=0;
		for(int i=0;i<=cnt;i++) counts[len[i]]++;
		for(int i=1;i<=N;i++) counts[i]+=counts[i-1];
		for(int i=cnt;i>=0;i--) rk[--counts[len[i]]]=i;
		for(int i=cnt;i>0;i--){
			sz[fa[rk[i]]]+=sz[rk[i]];
			right[fa[rk[i]]]=max(right[fa[rk[i]]],right[rk[i]]);
			if(sz[rk[i]]>=M){
				if((ans1<len[rk[i]])||(ans1==len[rk[i]]&&(ans2<right[rk[i]]-len[rk[i]]))){
					ans1=len[rk[i]];
					ans2=right[rk[i]]-len[rk[i]];
				}
			}
		}
		if(ans1==-1){
			printf("none\n");
		}else{
			printf("%d %d\n",ans1,ans2);
		}
	}
}sam;
int main(){
	while(scanf("%d",&M)&&M){
		scanf("%s",ch);
		
		if(M==1){
			printf("%d 0\n",strlen(ch));
			continue;
		}
		sam.init();
		N=strlen(ch);
		for(int i=0;i<N;i++){
			sam.add(ch[i]-'a');
		}
		sam.work();
	}
	return 0;
}
