#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
int N;
char s[max_n];
int Next[max_n];
void getNext(char* ch){
	int k=-1,j=0;
	Next[0]=-1;
	int len=strlen(ch);
	while(j<len){
		if(k==-1||ch[j]==ch[k]){
			j++,k++;
			if(ch[j]==ch[k]) Next[j]=Next[k];
			else Next[j]=k;
		}else{
			k=Next[k];
		}
	}
}
int main(){
	scanf("%d",&N);
	scanf("%s",s);
	getNext(s);
	printf("%d\n",N-Next[strlen(s)]); 
	return 0;
}
