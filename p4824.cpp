#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;

char s[max_n],t[max_n];
int Next[max_n],record[max_n],St[max_n];
void GetNext(char* str){
	int k=-1,j=0;
	Next[0]=-1;
	int len=strlen(str);
	while(j<len){
		if(k==-1||str[j]==str[k]){
			j++,k++;
			if(str[j]==str[k]) Next[j]=Next[k];
			else Next[j]=k;
		}else{
			k=Next[k];
		}
	}
}
void Print(int* x,int y){
	if(y>0) Print(x,y-1);
	printf("%c",s[x[y]]);
}
int main(){
	scanf("%s %s",s,t);
	GetNext(t);
	int top=-1;
	int j=0;
	int lens=strlen(s),lent=strlen(t);
	for(int i=0;i<lens;i++){
		while(j>=0&&t[j]!=s[i]){
			j=Next[j];
		}
		record[i]=j;
		St[++top]=i;
		j++;
		if(j>=lent){
			for(int m=1;m<=lent;m++) top--;
			if(top>=0) j=record[St[top]]+1;
			else j=0;
		}
	}
	Print(St,top);
	printf("\n");
	return 0;
}
