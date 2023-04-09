#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=140000;
const int max_num=1e6+10;
int N,M,block,L,R,res;
int num[max_n],ans[max_n],cnt[max_num];
char ch[10];
struct Node{
    int l,r,t;
    int id;
}qq[max_n],qr[max_n];
bool cmp(const Node& a,const Node& b){
    if(a.l/block!=b.l/block) return a.l/block<b.l/block;
    if(a.r/block!=b.r/block) return a.r/block<b.r/block;
    return a.t<b.t;
}
void update(int t){
    if(qr[t].l>=L&&qr[t].l<=R){
        if(!--cnt[num[qr[t].l]]) res--;
        if(++cnt[qr[t].r]==1) res++;
    }
    swap(num[qr[t].l],qr[t].r);
}
int main(){
    int noq=0,nor=0,x,y;
    scanf("%d %d",&N,&M);
    block=(int)pow((double)N,2.0/3);
    for(int i=1;i<=N;i++) scanf("%d",&num[i]);
    for(int i=0;i<M;i++){
        scanf("%s %d %d",ch,&x,&y);
        if(ch[0]=='Q'){
            ++noq;
            qq[noq].l=x;qq[noq].r=y;qq[noq].id=noq;qq[noq].t=nor;
        }else{
            ++nor;
            qr[nor].l=x;
            qr[nor].r=y;
        }
    }
    sort(qq+1,qq+1+noq,cmp);
    L=1,R=0,res=0;
    int t=0;
    for(int i=1;i<=noq;i++){
        while(L<qq[i].l) if(!--cnt[num[L++]]) res--;
        while(L>qq[i].l) if(++cnt[num[--L]]==1) res++;
        while(R<qq[i].r) if(++cnt[num[++R]]==1) res++;
        while(R>qq[i].r) if(!--cnt[num[R--]]) res--;
        while(t<qq[i].t) update(++t);
        while(t>qq[i].t) update(t--);
        ans[qq[i].id]=res;
    }
    for(int i=1;i<=noq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}