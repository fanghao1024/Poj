#include<stdio.h>
#include<string.h>
#include<math.h>
int N,M;
const int max_n=100010;
int num[max_n];
int L[340],R[340];
int belong[max_n];
int rec[340][12][10];
void count_digit(int block,int x){
	for(int i=1;i<=10;i++){
		rec[block][i][x%10]++;
		x/=10;
	}
}
void sub_digit(int block,int x){
	for(int i=1;i<=10;i++){
		rec[block][i][x%10]--;
		x/=10;
	}
}
void build(){
	int len=int(sqrt(N+0.0));
	int blocks=N/len;
	if(N%len) blocks++;
	for(int i=1;i<=N;i++){
		belong[i]=(i-1)/len+1;
	}
	for(int i=1;i<=blocks;i++){
		L[i]=len*(i-1)+1;
		R[i]=len*i;
	}
	R[blocks]=N;
	memset(rec,0,sizeof(rec));
	for(int i=1;i<=N;i++){
		int temp=num[i];
		count_digit(belong[i],temp);
		/*
		if(temp==0){
			rec[belong[i]][1][0]++;
			continue;
		}
		int index=1;
		while(temp>0){
			int m=temp%10;
			rec[belong[i]][index][m]++;
			index++;
			temp/=10;
		  }*/
	}
	
}
void modify(int x,int y){
	int temp=num[x];
	sub_digit(belong[x],temp);
	/*
	if(temp==0){
		rec[belong[x]][1][0]--;
	}else{
		int index=1;
		while(temp>0){
			int m=temp%10;
			rec[belong[x]][index][m]--;
			index++;
			temp/=10;
		}
	  }*/
	num[x]=y;
	count_digit(belong[x],y);
	/*
	temp=num[x];
	if(temp==0){
		rec[belong[x]][1][0]++;
	}else{
		int index=1;
		while(temp>0){
			int m=temp%10;
			rec[belong[x]][index][m]++;
			index++;
			temp/=10;
		}
	  }*/
	
}
int query(int a,int b,int c,int d){
	int l=belong[a];
	int r=belong[b];
	int ans=0;
	if(l==r){
		for(int i=a;i<=b;i++){
			if(int(num[i]/pow(10.0,c-1))%10==d) ans++;
		}
	}else{
		for(int i=a;i<=R[l];i++){
			if(int(num[i]/pow(10.0,c-1))%10==d) ans++;
		}
		for(int i=l+1;i<=r-1;i++){
			ans+=rec[i][c][d];
		}
		for(int i=L[r];i<=b;i++){
			if(int(num[i]/pow(10.0,c-1))%10==d) ans++;
		}
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		for(int i=1;i<=N;i++){
			scanf("%d",&num[i]);
		}
		build();
		char ch;
		int X,Y,LL,RR,DD,PP;
		while(M--){
			scanf(" %c",&ch);
			if(ch=='S'){
				scanf("%d %d",&X,&Y);
				modify(X,Y);
			}else{
				scanf("%d %d %d %d",&LL,&RR,&DD,&PP);
				printf("%d\n",query(LL,RR,DD,PP));
			}
		}
	}
	return 0;
}
