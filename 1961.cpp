#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
char s[max_n];
int Next[max_n];
int N;
void getNext(){
	Next[0]=-1;
	int k=-1,j=0;
	while(j<N){
		if(k==-1||s[j]==s[k]){
			Next[++j]=++k;
		}else{
			k=Next[k];
		}
	}
}
int main(){
	int kase=1;
	while(scanf("%d",&N)&&N){
		scanf("%s",s);
		getNext();
		printf("Test case #%d\n",kase++);
		for(int i=1;i<=N;i++){
			if(i%(i-Next[i])==0&&i/(i-Next[i])>1){
				printf("%d %d\n",i,i/(i-Next[i]));
			}
		}
		printf("\n");
	}
	return 0;
}
