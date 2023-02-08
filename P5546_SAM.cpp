#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

const int max_n=200005;
string s[10];
int anslen[max_n<<1],cnt[max_n<<1];
struct SAM{
	int fa[max_n<<1],len[max_n<<1],nxt[max_n<<1][26];
	int v[max_n<<1],tlen[max_n<<1];
	int sz,last,ans;
	SAM(){
		sz=0;
		fa[0]=-1;
		len[0]=0;
		last=0;
		memset(nxt,0,sizeof(nxt));
		memset(tlen,0,sizeof(tlen));
		memset(cnt,0,sizeof(cnt));
	}
	void insert(int c){
		int p=last;
		int cur=last=++sz;
		anslen[cur]=len[cur]=len[p]+1;
		int np,q,nq;
		while(p!=-1&&nxt[p][c]==0){
			nxt[p][c]=cur;
			p=fa[p];
		}
		if(p==-1){
			fa[cur]=0;
			return ;
		}
		q=nxt[p][c];
		if(len[q]==len[p]+1){
			fa[cur]=q;
		}else{
			nq=++sz;
			fa[nq]=fa[q];
			len[nq]=anslen[nq]=len[p]+1;
			fa[cur]=fa[q]=nq;
			//memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
			for(int i=0;i<26;i++) nxt[nq][i]=nxt[q][i];
			while(p!=-1&&nxt[p][c]==q){
				nxt[p][c]=nq;
				p=fa[p];
			}
		}
	}
	void work(int ids){
		int p=0,sum=0;
		int top=0;
		for(int i=0;i<s[ids].length();i++){
			//printf("%c\n",s[ids][i]);
			while(p!=-1&&nxt[p][s[ids][i]-'a']==0){
				//printf("$$$%d\n",p);
				p=fa[p];
				if(p==-1) break;
				sum=len[p];
			}
			if(p==-1){
				p=0;
				sum=0;
			}else{
				sum++;
				p=nxt[p][s[ids][i]-'a'];
			}
			//printf("===%d\n",p);
			int k=p;
			tlen[k]=max(tlen[k],sum);
			do{
				v[++top]=k;
				
				if(cnt[k]==ids-1) cnt[k]=ids;
				//printf("~~~%d %d %d %d %d\n",k,top,cnt[k],ids,sum);
				k=fa[k];
				
			}while(k!=-1);
		}
		for(int i=top;i>0;i--){
			int item=v[i];
			anslen[item]=min(anslen[item],tlen[item]);
		}
		for(int i=top;i>0;i--) tlen[v[i]]=0;
	}
	
	int get_ans(int n){
		ans=0;
		for(int i=1;i<=sz;i++){
			if(cnt[i]==n)
				ans=max(ans,anslen[i]);
		}
		return ans;
	}
}sam;
int solve(int n){
	int minL=max_n,minid;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		if(s[i].length()<minL){
			minL=s[i].length();
			minid=i;
		}
	}
	for(int i=0;i<s[minid].length();i++){
		sam.insert(s[minid][i]-'a');
	}
	//for(int i=1;i<=sam.sz;i++) printf("%d %d\n",sam.fa[i],sam.len[i]);
	for(int i=1;i<=n;i++){
		sam.work(i);
	}
	return sam.get_ans(n);
}
int main(){
	int N;
	cin>>N;
	memset(cnt,0,sizeof(cnt));
	printf("%d\n",solve(N));
	return 0;
}
