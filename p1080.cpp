#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e4+10;
const int up=1e4;

struct VAL{
    int num[1000];
    int top;
    VAL(){memset(num,0,sizeof(num));top=0;}
};
struct Node{
    int l,r;
}node[max_n];
void setVAL(VAL& a,int val){
    if(val==0){
        memset(a.num,0,sizeof(a.num));
        a.top=0;
    }else{
        int top=0;
        while(val){
            a.num[top++]=val%up;
            val/=up;
        }
        a.top=top-1;
    }
}
bool Less(const VAL& m,const VAL& n){
    if(m.top<n.top) return true;
    else if(m.top>n.top) return false;
    else{
        for(int i=m.top;i>=0;i--){
            if(m.num[i]<n.num[i]) return true;
            else if(m.num[i]>n.num[i]) return false;
        }
        return false;
    }
}
void mul(VAL m,int n,VAL& k){
    int jinwei=0;
    for(int i=0;i<=m.top;i++){
        int temp=m.num[i]*n+jinwei;
        k.num[i]=temp%up;
        jinwei=temp/up;
    }
    int top=m.top;
    while(jinwei>0){
        top++;
        k.num[top]=jinwei%up;
        jinwei/=up;
    }
    k.top=top;
}
void div(VAL m,int n,VAL& k){
    int jinwei=0;
    k.top=0;
    for(int i=m.top;i>=0;i--){
        int temp=jinwei*up+m.num[i];
        int shang=temp/n;
        jinwei=temp%n;
        k.num[i]=shang;
        if(shang>0&&i>k.top) k.top=i;
    }
}
void copy(VAL m,VAL &n){
    n.top=m.top;
    for(int i=0;i<=m.top;i++) n.num[i]=m.num[i]; 
}
void Print(VAL m){
    printf("%d",m.num[m.top]);
    for(int i=m.top-1;i>=0;i--){
        printf("%04d",m.num[i]);
    }
    printf("\n");
}
bool cmp(const Node& m,const Node& n){
    return m.l*m.r<n.l*n.r;
}
int n;
int main(){
    scanf("%d",&n);
    for(int i=0;i<=n;i++){
        scanf("%d %d",&node[i].l,&node[i].r);
    }
    sort(node+1,node+1+n,cmp);
    VAL res,ans,temp;
    setVAL(res,1);
    setVAL(ans,0);
    for(int i=1;i<=n;i++){
        mul(res,node[i-1].l,res);
        div(res,node[i].r,temp);
        if(Less(ans,temp)) copy(temp,ans);
    }
    Print(ans);
    return 0;
}