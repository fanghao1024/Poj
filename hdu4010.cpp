#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n = 300010;
const int inf=0x3f3f3f3f;
int N;

struct Linked_Cut_Tree{
    int fa[max_n],son[max_n][2],add[max_n],v[max_n],rec[max_n],st[max_n],top;
    bool rev[max_n];
    void init(){
        for(int i=0;i<=N;i++){
            add[i]=rev[i]=fa[i]=son[i][0]=son[i][1]=0;
        }
        v[0]=-inf;
    }
    void update(int x){
        v[x]=max(max(v[son[x][0]],v[son[x][1]]),rec[x]);
    }
    void pushdown(int x){
        if(rev[x]){
            rev[x]^=1;
            swap(son[x][0],son[x][1]);
            if(son[x][0]) rev[son[x][0]]^=1;
            if(son[x][1]) rev[son[x][1]]^=1;
        }
        if(add[x]){
            if(son[x][0]){add[son[x][0]]+=add[x];rec[son[x][0]]+=add[x];v[son[x][0]]+=add[x];}
            if(son[x][1]){add[son[x][1]]+=add[x];rec[son[x][1]]+=add[x];v[son[x][1]]+=add[x];}
            add[x]=0;
        }
    }
    bool isroot(int x){return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
    void rotate(int x){
        int f=fa[x],g=fa[f];
        int c=son[f][0]==x;
        son[f][!c]=son[x][c];
        fa[son[x][c]]=f;
        fa[x]=g;
        if(!isroot(f)) son[g][son[g][1]==f]=x;
        son[x][c]=f;
        fa[f]=x;
        update(f);
        update(x);
    }
    void splay(int x){
        st[top=1]=x;
        for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
        while(top) pushdown(st[top--]);
        while(!isroot(x)){
            int f=fa[x],g=fa[f];
            if(!isroot(f)) (son[g][0]==f)^(son[f][0]==x)?rotate(x):rotate(f);
            rotate(x);
        }
    }
    void access(int x){
        for(int y=0;x;x=fa[y=x]){
            splay(x);
            son[x][1]=y;
            update(x);
        }
    }
    void makeroot(int x){
        access(x);splay(x);rev[x]^=1;
    }
    void link(int x,int y){
        makeroot(x);
        fa[x]=y;
    }
    int getroot(int x){
        access(x);
        splay(x);
        while(son[x][0]) x=son[x][0];
        return x;
    }
    void cut(int x,int y){
        makeroot(x);
        access(y);
        splay(y);
        son[y][0]=fa[son[y][0]]=0;
        update(y);
    }
    void split(int x,int y){
        makeroot(x);
        access(y);
        splay(y);
    }
    void ADD(int x,int y,int w){
        split(x,y);
        add[y]+=w;v[y]+=w;rec[y]+=w;
    }
}LCT;
int main(){
    while(scanf("%d",&N)!=EOF){
        LCT.init();
        int Q;
        int ops, x, y, w;
        for(int i=1;i<N;i++){
            scanf("%d %d",&x,&y);
            LCT.link(x, y);
        }
        for(int i=1;i<=N;i++){
            scanf("%d",&LCT.rec[i]);
            LCT.v[i]=LCT.rec[i];
        }
        
        scanf("%d",&Q);
        while(Q--){
            scanf("%d",&ops);
            switch(ops){
                case 1:
                    scanf("%d %d",&x,&y);
                    if(LCT.getroot(x)==LCT.getroot(y)){
                        printf("-1\n");
                    }else{
                        LCT.link(x,y);
                    }
                    break;
                case 2:
                    scanf("%d %d",&x,&y);
                    if(x==y||LCT.getroot(x)!=LCT.getroot(y)){
                        printf("-1\n");
                    }else{
                        LCT.cut(x,y);
                    }
                    break;
                case 3:
                    scanf("%d %d %d",&w,&x,&y);
                    if(LCT.getroot(x)!=LCT.getroot(y)){
                        printf("-1\n");
                    }else{
                        LCT.ADD(x,y,w);
                    }
                    break;
                case 4:
                scanf("%d %d",&x,&y);
                if (LCT.getroot(x) != LCT.getroot(y))
                {
                    printf("-1\n");
                }
                else
                {
                    LCT.split(x,y);
                    printf("%d\n",LCT.v[y]);
                }
                break;
            }
        }
        printf("\n");
    }
    return 0;
}