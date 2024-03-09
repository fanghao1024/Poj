#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_len=1024;
char s[max_len];
int indeg[26],outdeg[26],N;
int fa[26];
void init(){
	memset(indeg,0,sizeof(indeg));
	memset(outdeg,0,sizeof(outdeg));
	for(int i=0;i<26;i++) fa[i]=i;
}
int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		//memset(g,0,sizeof(g));
		scanf("%d",&N);
		init();
		while(N--){
			scanf("%s",s);
			int u=s[0]-'a';
			int v=s[strlen(s)-1]-'a';
			if(find(u)!=find(v)){
				fa[find(u)]=find(v);
			}
			outdeg[u]++;
			indeg[v]++;
		}
		bool flag=true;
		int ru=0,chu=0,cnt=0;
		for(int i=0;i<26;i++){
			if(find(i)==i&&indeg[i]+outdeg[i]>0) cnt++;
			if(indeg[i]!=outdeg[i]){
				if(indeg[i]==outdeg[i]+1) ru++;
				else if(indeg[i]==outdeg[i]-1) chu++;
				else flag=false;
			}
		}
		if(flag&&cnt==1&&((ru==1&&chu==1)||(ru==0&&chu==0))) printf("Ordering is possible.\n");
		else printf("The door cannot be opened.\n");
	}
	return 0;
}
