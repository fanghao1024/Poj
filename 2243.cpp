#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
using namespace std;

typedef unsigned long long ll;
int N,L;
int root,cnt;
const int max_n=40;
const int K=26;
struct Mat{
	ll a[max_n][max_n];
	int _n;
	Mat(int n_){
		_n=n_;
		memset(a,0,sizeof(a));
	}
};
Mat mat_mul(Mat A,Mat B){
	Mat C(A._n);
	for(int i=0;i<A._n;i++){
		for(int j=0;j<B._n;j++){
			for(int k=0;k<C._n;k++){
				C.a[i][j]+=A.a[i][k]*B.a[k][j];
			}
		}
	}
	return C;
}
Mat mat_pow(Mat m,int n){
	Mat f(m._n);
	for(int i=0;i<cnt;i++)
		f.a[i][i]=1;
	while(n>0){
		if(n&1){
			f=mat_mul(f,m);
		}
		m=mat_mul(m,m);
		n>>=1;
	}
	return f;
}
struct AC{
	int nxt[max_n][K],fail[max_n],End[max_n],ids[max_n];
	int NewNode(){
		for(int i=0;i<K;i++){
			nxt[cnt][i]=-1;
		}
		End[cnt]=0;
		return cnt++;
	}
	void Init(){
		cnt=0;
		root=NewNode();
	}
	void insert(char s[]){
		int lens=strlen(s);
		int p=root;
		for(int i=0;i<lens;i++){
			int c=s[i]-'a';
			if(nxt[p][c]==-1){
				nxt[p][c]=NewNode();
			}
			p=nxt[p][c];
		}
		End[p]++;
	}
	void build(){
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
		while(!q.empty()){
			int now=q.front();
			q.pop();
			if(End[fail[now]]){
				End[now]++;
			}
			for(int i=0;i<K;i++){
				if(nxt[now][i]==-1){
					nxt[now][i]=nxt[fail[now]][i];
				}else{
					fail[nxt[now][i]]=nxt[fail[now]][i];
					q.push(nxt[now][i]);
				}
			}
		}
	}
	ll query(int n){
		memset(ids,-1,sizeof(ids));
		int mark=0;
		
		for(int i=0;i<cnt;i++){
			if(!End[i]){
				ids[i]=mark++;
			}
		}
		Mat m(mark+1);
		for(int i=0;i<cnt;i++){
			if(End[i]) continue;
			for(int j=0;j<K;j++){
				int v=nxt[i][j];
				if(!End[v]){
					m.a[ids[i]][ids[v]]++;
				}
			}
		}
		for(int i=0;i<mark+1;i++){
			m.a[i][mark]=1;
		}
		Mat f=mat_pow(m,n);
		ll ans=0;
		for(int i=0;i<=f._n;i++){
			ans+=f.a[0][i];
		}
		return --ans;
	}
}ac;
ll pow_2(int n){
	Mat m(2);
	m.a[0][0]=26;
	m.a[0][1]=m.a[1][1]=1;
	Mat f=mat_pow(m,n);
	return f.a[0][0]+f.a[0][1]-1;
}
int main(){
	char ch[10];
	while(scanf("%d %d",&N,&L)!=EOF){
		ac.Init();		
		for(int i=0;i<N;i++){
			scanf("%s",ch);
			ac.insert(ch);
		}
		ac.build();
		cout<<pow_2(L)-ac.query(L)<<endl;
		//printf("%lld\n",pow_2(L)-ac.query(L));
	}
	return 0;
}
