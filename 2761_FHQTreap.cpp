#include <cstdio>
#include<cstdlib>
#include<ctime>
#include <algorithm>
using namespace std;

const int max_n = 100100;
const int max_m = 50010;
const int inf = 0x3fffffff;

int N, M, cnt, root;
int num[max_n];
struct Query
{
    int l, r, k, id;
    bool operator<(const Query &a) const
    {
        return l < a.l;
    }
} query[max_m];

struct Tr
{
    int pri;
    int son[2];
    int size, val;
} tr[max_n];
int ans[max_n];
int newNode(int val)
{
    cnt++;
    tr[cnt].son[0] = tr[cnt].son[1] = 0;
    tr[cnt].size = 1;
    tr[cnt].val = val;
    tr[cnt].pri=rand();
    return cnt;
}
void update(int p)
{
    tr[p].size = tr[tr[p].son[0]].size + tr[tr[p].son[1]].size + 1;
}
void Init()
{
    cnt =root= 0;
}

void split(int u,int val,int& L,int &R){
    if(!u){L=R=0;return ;}
    if(tr[u].val<=val){
        L=u;
        split(tr[u].son[1],val,tr[u].son[1],R);
        update(L);
    }else{
        R=u;
        split(tr[u].son[0],val,L,tr[u].son[0]);
        update(R);
    }
}
int merge(int L,int R){
    if(!L||!R) return L+R;
    if(tr[L].pri>tr[R].pri){
        tr[L].son[1]=merge(tr[L].son[1],R);
        update(L);
        return L;
    }else{
        tr[R].son[0]=merge(L,tr[R].son[1]);
        update(R);
        return R;
    }
}
void Insert(int val){
    
    int L=0,R=0;
    split(root,val,L,R);
    root=merge(merge(L,newNode(val)),R);
}
int kth(int u,int k){
    if(tr[tr[u].son[0]].size+1==k) return u;
    if (tr[tr[u].son[0]].size>=k)
        return kth(tr[u].son[0],k);
    return kth(tr[u].son[1], k - tr[tr[u].son[0]].size-1);
}
void Delete(int val){
    int L,R,p;
    split(root,val,L,R);
    split(L,val-1,L,p);
    root=merge(L,R);
    update(root);
}
int main()
{
    srand(time(0));
    while(scanf("%d %d", &N, &M)!=EOF){
    for (int i = 1; i <= N; i++)
        scanf("%d", &num[i]);
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %d", &query[i].l, &query[i].r, &query[i].k);
        query[i].id = i;
    }
    sort(query, query + M);
    Init();
    for (int i = query[0].l; i <= query[0].r; i++)
    {
        Insert(num[i]);
    }
    ans[query[0].id] = tr[kth(root, query[0].k)].val;
    for (int i = 1; i < M; i++)
    {
        for (int j = query[i - 1].l; j < query[i].l && j <= query[i - 1].r; j++)
            Delete(num[j]);
        for (int j = max(query[i - 1].r + 1, query[i].l); j <= query[i].r; j++)
            Insert(num[j]);
        ans[query[i].id] = tr[kth(root, query[i].k)].val;
    }
    for (int i = 0; i < M; i++)
    {
        printf("%d\n", ans[i]);
    }
    }
    return 0;
}