#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;

struct Tree{
	int son[26];
	int end;
	int fail;
}tr[max_n];
char s[max_n],t[max_n];
int N,cnt;

void Insert(char* str){
	int now=0,ch;
	int len=strlen(str);
	for(int i=0;i<len;i++){
		ch=str[i]-'a';
		if(tr[now].son[ch]==0){
			tr[now].son[ch]=++cnt;
		}
		now=tr[now].son[ch];
	}
	tr[now].end++;
}
void getFail(){
	queue<int> q;
	int now=0;
	for(int i=0;i<26;i++){
		if(tr[now].son[i]!=0){
			q.push(tr[now].son[i]);
		}
	}
	while(!q.empty()){
		int v=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(tr[v].son[i]){
				tr[tr[v].son[i]].fail=tr[tr[v].fail].son[i];
				q.push(tr[v].son[i]);
			}else{
				tr[v].son[i]=tr[tr[v].fail].son[i];
			}
		}
	}
}
int query(char* str){
	int ans=0;
	int now=0;
	int len=strlen(str);
	for(int i=0;i<len;i++){
		int ch=str[i]-'a';
		now=tr[now].son[ch];
		int temp=now;
		while(temp&&tr[temp].end!=-1){
			ans+=tr[temp].end;
			tr[temp].end=-1;
			temp=tr[temp].fail;
		}
	}
	return ans;
}
int main(){
	scanf("%d",&N);
	cnt=0;
	while(N--){
		scanf("%s",s);
		Insert(s);
	}
	getFail();
	scanf("%s",t);
	printf("%d\n",query(t));
	return 0;
}
