#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=70;

int N,cnt,sum,len,m;
bool flag,used[max_n];
int num[max_n],nxt[max_n];
bool cmp(int a,int b){return a>b;}
void dfs(int k,int stick,int rest){
    int i;
    if(!rest){
        if(k==m){
            flag=true;
            return;
        }
        for(i=1;i<=cnt;i++){
            if(!used[i]) break;
        }
        used[i] = 1;
        dfs(k + 1, i, len - num[i]);
        used[i] = 0;
        if (flag) return;
    }
    int l=stick+1,r=cnt,mid;
    while(l<r){
        mid=(l+r)>>1;
        if(num[mid]<=rest) r=mid;
        else l=mid+1;
    }
    for(i=l;i<=cnt;i++){
        if(used[i]) continue;
        used[i]=1;
        dfs(k,i,rest-num[i]);
        used[i]=0;
        if(flag) return ;

        if(rest==num[i]||rest==len) return ;
        i=nxt[i];
    }
}
int main(){
    scanf("%d",&N);
    cnt=sum=0;
    int x;
    for(int i=1;i<=N;i++){
        scanf("%d",&x);
        if(x<=50){
            num[++cnt]=x;
            sum+=x;
        }
    }
    sort(num+1,num+1+cnt,cmp);
    nxt[cnt]=cnt;
    for(int i=cnt-1;i>0;i--){
        if(num[i]==num[i+1]) nxt[i]=nxt[i+1];
        else nxt[i]=i;
    }
    flag=false;
    memset(used,0,sizeof(used));
    for(len=num[1];len<=sum/2;len++){
        if(sum%len!=0) continue;
        m=sum/len;
        used[1]=1;
        dfs(1,1,len-num[1]);
        used[1]=0;
        if(flag) break;
    }
    if(flag) printf("%d\n",len);
    else printf("%d\n",sum);
    return 0;
}