#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;
char s[max_n][20];
char str[20];
int cnt;
bool cmp(char* s1,char* s2){
	int l1=strlen(s1),l2=strlen(s2);
	int i=0;
	if(l1==l2){
		while(i<l1&&s1[i]==s2[i]) i++;
		while(++i<l1){
			if(s1[i]!=s2[i]) return false;
		}
		
	}
	else if(l1==l2+1){
		while(i<l2&&s1[i]==s2[i]) i++;
		while(++i<l1){
			if(s1[i]!=s2[i-1]) return false;
		}
	}
	else if(l1+1==l2){
		while(i<l1&&s1[i]==s2[i]) i++;
		while(++i<l2){
			if(s1[i-1]!=s2[i]) return false;
		}
	}
	else return false;
	return true;
}
int main(){
	cnt=0;
	while(scanf("%s",s[cnt++])!=EOF){
		if(s[cnt-1][0]=='#'){
			cnt--;
			break;
		}
	}
	while(scanf("%s",str)!=EOF){
		if(str[0]=='#') break;
		bool flag=false;
		for(int i=0;i<cnt;i++){
			if(strcmp(s[i],str)==0){
				flag=true;
				printf("%s is correct\n",str);
				break;
			}
		}
		if(!flag){
			printf("%s:",str);
			for(int i=0;i<cnt;i++){
				if(cmp(s[i],str)) printf(" %s",s[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
