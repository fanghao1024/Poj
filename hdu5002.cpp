#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100010;
const int inf=0x3f3f3f3f;
int T,N,M;

struct Linked_Cut_Tree{
    int fa[max_n],son[max_n][2],ta[max_n],tc[max_n],st[max_n],num[max_n],size[max_n],top;
    int mx1[max_n],mx2[max_n],c1[max_n],c2[max_n];
    bool rev[max_n]; 
    void init()
    {
        for(int i=0;i<=N;i++){
            fa[i]=son[i][0]=son[i][1]=ta[i]=rev[i]=0;
            tc[i]=-inf;
            size[i]=1;
        }
        size[0]=0;
    }
    void initial(int x){
        mx1[x]=num[x];c1[x]=1;
        mx2[x]=-inf;c2[x]=0;
    }
    void cnt(int x,int val,int c){
        if(val>mx1[x]) mx2[x]=mx1[x],c2[x]=c1[x],mx1[x]=val,c1[x]=c;
        else if(val==mx1[x]) c1[x]+=c;
        else if(val>mx2[x]) mx2[x]=val,c2[x]=c;
        else if(val==mx2[x]) c2[x]+=c;
    }
    void change(int x, int val)
    {
        mx1[x] = val;
        num[x] = val;
        c1[x] = size[x];
        mx2[x] = -inf;
        c2[x] = 0;
        tc[x] = val;
        if (ta[x])
            ta[x] = 0;
    }
    void addval(int x, int val)
    {
        mx1[x] += val;
        num[x] += val;
        ta[x] += val;
        if (mx2[x] != -inf)
            mx2[x] += val;
    }
    void update(int x){
        int l=son[x][0],r=son[x][1];
        mx1[x]=mx2[x]=-inf;
        c1[x]=c2[x]=0;
        cnt(x,num[x],1);
        if(l) cnt(x,mx1[l],c1[l]),cnt(x,mx2[l],c2[l]);
        if(r) cnt(x,mx1[r],c1[r]),cnt(x,mx2[r],c2[r]);
        size[x]=size[l]+size[r]+1;
    }
    
    
    void pushdown(int x){
        int l = son[x][0], r = son[x][1];
        if(rev[x]){
            rev[x]^=1;
            swap(son[x][0],son[x][1]);
            if(l) rev[l]^=1;
            if(r) rev[r]^=1;
        }
        if(tc[x]!=-inf){
            if(l) change(l,tc[x]);
            if(r) change(r,tc[x]);
            tc[x]=-inf;
        }
        if(ta[x]){
            if(l) addval(l,ta[x]);
            if(r) addval(r,ta[x]);
            ta[x]=0;
        }
    }
    bool isroot(int x){return son[fa[x]][1]!=x&&son[fa[x]][0]!=x;}
    void rotate(int x){
        int f=fa[x],g=fa[f];
        int c=son[f][0]==x;
        son[f][!c]=son[x][c];
        fa[son[x][c]]=f;
        fa[x]=g;
        if(!isroot(f)) son[g][son[g][1]==f]=x;
        son[x][c]=f;
        fa[f]=x;
        update(f);update(x);
    }
    void splay(int x){
        st[top=1]=x;
        for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
        while(top) pushdown(st[top--]);
        while(!isroot(x)){
            int f=fa[x],g=fa[f];
            if(!isroot(f)) (son[f][0]==x)^(son[g][0]==f)?rotate(x):rotate(f);
            rotate(x);
        }
    }
    void access(int x){
        for(int y=0;x;x=fa[y=x]){
            splay(x);son[x][1]=y;update(x);
        }
    }
    void makeroot(int x){
        access(x);splay(x);rev[x]^=1;
    }
    void link(int x,int y){
        makeroot(x);
        fa[x]=y;
    }
    void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }
    void cut(int x, int y)
    {
        // if(findroot(x)==findroot(y)){
        split(x, y);
        // if(son[y][0]==x&&!son[x][1]){
        son[y][0] = fa[son[y][0]] = 0;
        update(y);
        //}
        // }
    }
    int findroot(int x){
        int l = son[x][0], r = son[x][1];
        access(x);splay(x);
        while(l) x=l;
        return x;
    }
    
    
}LCT;
int main(){
    int x,y;
    scanf("%d",&T);
    for(int case_no=1;case_no<=T;case_no++){
        printf("Case #%d:\n",case_no);
        scanf("%d %d", &N, &M);
        LCT.init();
        for(int i=1;i<=N;i++) scanf("%d",&LCT.num[i]),LCT.initial(i);
        /*
        for(int i=1;i<=N;i++){
            LCT.mx1[i] = LCT.num[i], LCT.c1[i] = 1;
            LCT.mx2[i] = -inf, LCT.c2[i] = 0;
            LCT.size[i] = 1;
        }
        for(int i=1;i<=N;i++){
            LCT.fa[i] = LCT.son[i][0] = LCT.son[i][1] = 0;
            LCT.ta[i] = LCT.rev[i] = 0;
            LCT.tc[i] = -inf;
        }
        */
        for(int i=1;i<N;i++){
            scanf("%d %d",&x,&y);
            LCT.link(x,y);
        }
        int c,a,b;
        while(M--){
            scanf("%d",&c);
            switch(c){
                case 1:
                    scanf("%d %d %d %d",&x,&y,&a,&b);
                    LCT.cut(x,y);
                    LCT.link(a,b);
                    break;
                case 2:
                    scanf("%d %d %d",&a,&b,&x);
                    LCT.split(a,b);
                    LCT.change(b,x);
                    break;
                case 3:
                    scanf("%d %d %d", &a, &b, &x);
                    LCT.split(a,b);
                    LCT.addval(b,x);
                    break;
                case 4:
                    scanf("%d %d", &a, &b);  
                    LCT.split(a,b);
                    //printf("~~~%d %d\n",LCT.c1[b],LCT.size[b]);
                    if(LCT.c1[b]==LCT.size[b]) printf("ALL SAME\n"); 
                    else printf("%d %d\n",LCT.mx2[b],LCT.c2[b]);
                    break;
            }
        }
    }
    return 0;
}