#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
set<int> si;
int num[max_n];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        si.clear();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&num[i]);
        }
        int ans=1;
        int l=1,r=1;
        while(r<=n){
            while(r<=n&&!si.count(num[r])) si.insert(num[r++]);
            ans=max(ans,r-l);
            si.erase(num[l++]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
