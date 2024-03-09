#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int cnt;
struct Trie{
	int son[2];
	bool ed;
}tr[1000];
char s[100];
bool flag;
void Insert(char* str){
	int len=strlen(str);
	int now=0;
	for(int i=0;i<len;i++){
		int ch=str[i]-'0';
		if(tr[tr[now].son[ch]].ed){
			flag=false;
			return ;
		}
		if(tr[now].son[ch]==0){
			tr[now].son[ch]=++cnt;
			tr[cnt].ed=0;
			tr[cnt].son[0]=tr[cnt].son[1]=0;
		}
		now=tr[now].son[ch];
	}
	tr[now].ed=1;
}
int main(){
	int kase=1;
	while(scanf("%s",s)!=EOF){
		memset(tr,0,sizeof(tr));
		cnt=0;
		flag=true;
		while(s[0]!='9'){
			if(flag) Insert(s);
			scanf("%s",s);
		}
		if(flag) printf("Set %d is immediately decodable\n",kase++);
		else printf("Set %d is not immediately decodable\n",kase++);
	}
	return 0;
}
