#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=210;

struct Scan{
    double y;
    double lx,rx;
    int mark;
    Scan(){};
    Scan(double _y,double _lx,double _rx,int _mark){
        y=_y;lx=_lx;rx=_rx;mark=_mark;
    }
}scan[max_n];
bool cmp(const Scan& a,const Scan& b){
    return a.y<b.y;
}
int N,cnt,n;
double xx[max_n];
double length[max_n<<2];
int tag[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int p,int pl,int pr){
    if(tag[p]){
        length[p]=xx[pr]-xx[pl];
        return ;
    }
    else if(pl+1==pr) length[p]=0;
    else{
        length[p]=length[ls(p)]+length[rs(p)];
    }
}
void update(int p,int pl,int pr,int L,int R,int val){
    if(L<=pl&&pr<=R){
        tag[p]+=val;
        pushup(p,pl,pr);
        return ;
    }
    if(pl+1==pr) return ;
    int mid=(pl+pr)>>1;
    if(L<=mid) update(ls(p),pl,mid,L,R,val);
    if(R>mid) update(rs(p),mid,pr,L,R,val);
    pushup(p,pl,pr);
}
int main(){
    int caseNo=1;
    double x1,y1,x2,y2;
    while(scanf("%d",&N)&&N){
        cnt=0;
        while(N--){
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            scan[++cnt]=Scan(y1,x1,x2,1);
            xx[cnt]=x1;
            scan[++cnt]=Scan(y2,x1,x2,-1);
            xx[cnt]=x2;
        }
        sort(xx+1,xx+1+cnt);
        sort(scan+1,scan+1+cnt,cmp);
        n=unique(xx+1,xx+1+cnt)-xx-1;
        memset(tag,0,sizeof(tag));
        memset(length,0,sizeof(length));
        double ans=0;
        int L,R;
        for(int i=1;i<=cnt;i++){
            ans+=length[1]*(scan[i].y-scan[i-1].y);
            L=lower_bound(xx+1,xx+1+n,scan[i].lx)-xx;
            R=lower_bound(xx+1,xx+1+n,scan[i].rx)-xx;
            update(1,1,n,L,R,scan[i].mark);
        }
        printf("Test case #%d\n",caseNo++);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}

