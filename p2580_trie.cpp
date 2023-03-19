#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=8e5;

struct Trie{
	bool repeat;
	int son[26];
	int num;
	bool isEnd;
}tr[max_n];
int cnt=1;
void Insert(char* s){
	int now=0;
	for(int i=0;s[i];i++){
		int pos=s[i]-'a';
		if(tr[now].son[pos]==0){
			tr[now].son[pos]=cnt++;
		}
		now=tr[now].son[pos];
	}
	tr[now].isEnd=true;
	tr[now].repeat=false;
}
int find(char* s){
	int now=0;
	for(int i=0;s[i];i++){
		if(tr[now].son[s[i]-'a']==0) return 3;
		now=tr[now].son[s[i]-'a'];
	}
	if(!tr[now].isEnd) return 3;
	if(!tr[now].repeat){
		tr[now].repeat=true;
		return 1;
	}else{
		return 2;
	}
}
int main(){
	char ch[55];
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",ch);
		Insert(ch);
	}
	int m;
	scanf("%d",&m);
	while(m--){
		scanf("%s",ch);
		int ans=find(ch);
		if(ans==1) printf("OK\n");
		else if(ans==2) printf("REPEAT\n");
		else printf("WRONG\n");
	}
	return 0;
}
