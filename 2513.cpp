#include<cstdio>
#include<cstring>

const int max_n=600010;
int trie[max_n][30];
bool End[max_n];
int cnt,colorcnt=0;
int degree[max_n],color[max_n];
int par[max_n];

char word1[15];
char word2[15];

void Init(){
	//memset(trie,0,sizeof(trie));
	memset(degree,0,sizeof(degree));
	memset(End,0,sizeof(End));
	memset(color,0,sizeof(color));
	cnt=1;
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		par[a]=b;
	}
}

int insert(char *ch){
	int p=1;
	int i=0;
	
	while(ch[i]!='\0'){
		int c=ch[i++]-'a';
		if(!trie[p][c]){
			trie[p][c]=++cnt;
		}
		p=trie[p][c];
	}
	if(!End[p]){
		color[p]=++colorcnt;
		End[p]=1;
	}
	return color[p];
}

int main(){
	Init();
	for(int i=1;i<max_n;i++) par[i]=i;
	//int kk=0;
	while(~scanf("%s %s",word1,word2)){
		int c1=insert(word1);
		int c2=insert(word2);
		degree[c1]++;
		degree[c2]++;
		unite(c1,c2);
		//if(++kk>=5) break;
	}
	int c=find(1);
	int counts=0;

	for(int i=1;i<=colorcnt;i++){
		if(degree[i]%2==1){
			counts++;
		}
		if(counts>2||find(i)!=c){
			printf("Impossible\n");
			return 0;
		}
	}
	if(counts==0||counts==2) {printf("Possible\n");}
	else {printf("Impossible\n");}
	return 0;
}
