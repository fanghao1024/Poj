#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=1e6;

int a[max_n],b[max_n];
int block,t;
int st[max_n],ed[max_n],belong[max_n],add[max_n];
int N,Q;
char ops[10];
void update(int l,int r,int w){
    int L=belong[l],R=belong[r];
    if(L==R){
        for(int i=l;i<=r;i++) a[i]+=w;
        for(int i=st[L];i<=ed[L];i++) b[i]=a[i];
        sort(b+st[L],b+ed[L]+1);
    }else{
        for(int i=L+1;i<=R-1;i++) add[i]+=w;
        for(int i=l;i<=ed[L];i++){
            a[i]+=w;
        }
        for (int i = st[L]; i <=ed[L]; i++)
        {
            b[i] = a[i];
        }
        sort(b+st[L],b+1+ed[L]);
        for (int i = st[R]; i <= r; i++)
        {
            a[i]+=w;
        }
        for(int i=st[R];i<=ed[R];i++){
            b[i] = a[i];
        }
        
        sort(b+st[R],b+1+ed[R]);
    }
}
int query(int l,int r,int c){
    int L = belong[l], R = belong[r];
    int ans=0;
    if(L==R){
        for(int i=l;i<=r;i++){
            if(a[i]+add[L]>=c) ans++;
        }
    }else{
        for(int i=L+1;i<=R-1;i++){
            int temp = lower_bound(b + st[i], b + ed[i] + 1, c-add[i])-b-st[i];
            ans+=ed[i]-st[i]+1-temp;
            /*
            int ll = st[i], rr = ed[i], result = 0, mid;
            while (ll <= rr)
            {
                mid = (ll + rr) >> 1;
                if (b[mid] + add[i] >= c)
                    rr = mid - 1, result = ed[i] - mid + 1;
                else
                    ll = mid + 1;
            }
            ans += result;
            */
        }
        for(int i=l;i<=ed[L];i++) if(a[i]+add[L]>=c) ans++;
        for(int i=st[R];i<=r;i++) if(a[i]+add[R]>=c) ans++;
    }
    return ans;
}
int main(){
    scanf("%d %d",&N,&Q);
    for(int i=1;i<=N;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    block=sqrt(N);
    t=N/block;
    if(N%block) t++;
    for(int i=1;i<=t;i++){
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    ed[t]=N;
    for(int i=1;i<=t;i++)
        sort(b + st[i], b + ed[i] + 1);
    for(int i=1;i<=N;i++) belong[i]=(i-1)/block+1;
    memset(add,0,sizeof(add));
    int l,r,w,c;
    while(Q--){
        scanf("%s",ops);
        switch (ops[0])
        {
        case 'M':
            scanf("%d %d %d",&l,&r,&w);
            update(l,r,w);
            break;
        
        case 'A':
            scanf("%d %d %d",&l,&r,&c);
            printf("%d\n",query(l,r,c));
            break;
        }
    }
    return 0;
}