#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=105;
const int K=4;
const int MOD=100000;

int M,N;
int root,L;
char word[20];

struct Mat{
	int a[max_n][max_n];
	Mat(){
		memset(a,0,sizeof(a));
	}
};

Mat mat_mul(Mat A,Mat B){
	Mat f;
	for(int i=0;i<L;i++){
		for(int j=0;j<L;j++){
			for(int k=0;k<L;k++){
				f.a[i][j]=(f.a[i][j]+(long long)A.a[i][k]*B.a[k][j])%MOD;	
			}
		}
	}
	return f;
}

int mat_pow(Mat f,int n){
	Mat ans;
	for(int i=0;i<L;i++){
		ans.a[i][i]=1;
	}
	while(n>0){
		if(n&1){
			ans=mat_mul(ans,f);
		}
		f=mat_mul(f,f);
		n>>=1;
	}
	
	int anss=0;
	for(int i=0;i<L;i++){
		anss=(anss+ans.a[0][i])%MOD;
	}
	return anss;
}
struct AC{
	int nxt[max_n][K],fail[max_n],End[max_n],ids[max_n];
	int idx(char ch){
		int num;
		switch (ch) {
		case 'A':
			num=0;
			break;
		case 'C':
			num=1;
			break;
		case 'T':
			num=2;
			break;
		case 'G':
			num=3;
			break;
		default:
			num=-1;
			break;
		}
		return num;
	}
	int NewNode(){
		for(int i=0;i<K;i++){
			nxt[L][i]=-1;
		}
		//fail[L]=-1;
		End[L]=0;
		return L++;
	}
	void Init(){
		L=0;
		root=NewNode();
	}
	void insert(char s[]){
		int p=root;
		int lens=strlen(s);
		for(int i=0;i<lens;i++){
			int c=idx(s[i]);
			if(nxt[p][c]==-1){
				nxt[p][c]=NewNode();
			}
			p=nxt[p][c];
		}
		End[p]++;
	}
	void build_ac(){
		queue<int> q;
		fail[root]=root;
		for(int i=0;i<K;i++){
			if(nxt[root][i]==-1){
				nxt[root][i]=root;
			}else{
				fail[nxt[root][i]]=root;
				q.push(nxt[root][i]);
				
			}
		}
		while(q.size()){
			int u=q.front();
			q.pop();
			if(End[fail[u]]){
				End[u]++;
			}
			for(int i=0;i<K;i++){
				if(nxt[u][i]!=-1){
					fail[nxt[u][i]]=nxt[fail[u]][i];
					q.push(nxt[u][i]);
				}else{
					nxt[u][i]=nxt[fail[u]][i];
				}
			}
		}
	}
	int query(int n){
		memset(ids,-1,sizeof(ids));
		int mark=0;
		Mat ma;
		for(int i=0;i<L;i++){
			if(!End[i]){
				ids[i]=mark++;
			}
		}
				
		for(int i=0;i<L;i++){
			if(End[i]) continue;
			for(int j=0;j<K;j++){
				int v=nxt[i][j];
				if(!End[v]){
					ma.a[ids[i]][ids[v]]++;
				}
			}
		}
		L=mark;
		return mat_pow(ma,n);
	}
}ac;
int main(){
	while(~scanf("%d %d",&M,&N)){
		ac.Init();
		for(int i=0;i<M;i++){
			scanf("%s",word);
			ac.insert(word);
		}
		ac.build_ac();
		printf("%d\n",ac.query(N));
	}
	return 0;
}

