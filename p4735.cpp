#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=600010;
int N,M;

int trie[max_n*24][2],maxs[max_n*24];
int rt[max_n],s[max_n],cnt;

void insert(int i,int k,int p,int q){
    maxs[p]=i;
    if(k<0) return ;
    int c=s[i]>>k&1;
    if(q) trie[p][c^1]=trie[q][c^1];
    trie[p][c]=++cnt;
    insert(i,k-1,trie[p][c],trie[q][c]);
}
int query(int p,int k,int value,int limit){
    if(k<0) return s[maxs[p]]^value;
    int c=value>>k&1;
    if(maxs[trie[p][c^1]]>=limit) return query(trie[p][c^1],k-1,value,limit);
    else return query(trie[p][c],k-1,value,limit);
}
int main(){
    scanf("%d %d",&N,&M);
    maxs[0]=-1;
    cnt=0;
    s[0]=0;
    rt[0]=++cnt;
    insert(0, 23, rt[0], 0);
    int x;
    for(int i=1;i<=N;i++){
        scanf("%d",&x);
        s[i]=s[i-1]^x;
        rt[i]=++cnt;
        insert(i,23,rt[i],rt[i-1]);
    }
    char ops[3];
    int l,r;
    while(M--){
        scanf("%s",ops);
        switch(ops[0]){
            case 'A':
                scanf("%d",&x);
                rt[++N]=++cnt;
                s[N]=s[N-1]^x;
                insert(N,23,rt[N],rt[N-1]);
                break;
            case 'Q':
                scanf("%d %d %d",&l,&r,&x);
                printf("%d\n",query(rt[r-1],23,s[N]^x,l-1));
                break;
        }
    }
    return 0;
}