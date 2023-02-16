#include<cstdio>

const int max_n=600010;
int N,M,cnt;
int rt[max_n],trie[max_n*24][2],mark[max_n*24],s[max_n];
void insert(int i,int k,int p,int q){
    mark[p] = i;
    if(k<0) return ;
    int c=s[i]>>k&1;
    if(q) trie[p][c^1]=trie[q][c^1];
    trie[p][c]=++cnt;
    insert(i,k-1,trie[p][c],trie[q][c]);
}
int query(int p,int k,int val,int limit){
    if(k<0) return s[mark[p]]^val;
    int c=val>>k&1;
    if(mark[trie[p][c^1]]>=limit) return query(trie[p][c^1],k-1,val,limit);
    else return query(trie[p][c],k-1,val,limit);
}
int main(){
    scanf("%d %d",&N,&M);
    cnt=0;
    mark[0]=-1;
    rt[0]=++cnt;
    s[0]=0;
    insert(0,23,rt[0],0);
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