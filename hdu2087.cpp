#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;
char s1[max_n],s2[max_n];
int Next[max_n];
void getNext(char* s){
	int k=-1,j=0;
	Next[0]=-1;
	int len=strlen(s);
	while(j<len){
		if(k==-1||s[j]==s[k]){
			j++,k++;
			if(s[j]==s[k]){
				Next[j]=Next[k];
			}else{
				Next[j]=k;
			}
		}else{
			k=Next[k];
		}
	}
}
int main(){
	while(scanf("%s",s1)!=EOF){
		if(s1[0]=='#') break;
		scanf("%s",s2);
		getNext(s2);
		int ans=0;
		int len1=strlen(s1);
		int len2=strlen(s2);
		int j=0;
		int last=-1;
		for(int i=0;i<len1;i++){
			while(j>=0&&s1[i]!=s2[j]){
				j=Next[j];
			}
			j++;
			if(j>=len2){
				if(i-last>=len2){
					ans++;
					last=i;
				}
				
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
