#include<stdio.h>
char ch[5010];
int record[5010];
int N;
bool f[5010];
int fs[5010];

int ope(int k){
	int ops=0;
	if(record[0]==0){
		f[0]=0;
	}else{
		f[0]=1;
		ops++;
	}
	fs[0]=f[0];

	for(int i=1;i<=N-k;i++){
		if(i<k){
			f[i]=(fs[i-1]+record[i])%2;
			fs[i]=fs[i-1]+f[i];
		}else{
			f[i]=(fs[i-1]-fs[i-k]+record[i])%2;
			fs[i]=fs[i-1]+f[i];
		}
		if(f[i]==1){
			ops++;
		}
	}
	for(int i=N-k+1;i<N;i++){
		if((fs[N-k]-fs[i-k]+record[i])%2==1) return -1;
	}
	return ops;
}
int main(){
	
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf(" %c",&ch[i]);
	}
	for(int i=0;i<N;i++){
		switch (ch[i]) {
		case 'F':
			record[i]=0;
			break;
		case 'B':
			record[i]=1;
			break;
		}
	}
	int ans=N;
	int K=1;
	for(int k=1;k<=N;k++){
		int res=ope(k);
		if(res==-1) continue;
		if(res<ans){
			ans=res;
			K=k;
		}
	}
	printf("%d %d\n",K,ans);
	return 0;
}
