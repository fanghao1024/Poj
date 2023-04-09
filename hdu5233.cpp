#include<cstdio>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;
map<int,int> mp;
set<int> s[max_n];
int op[max_n];
int N,M;

int main(){
    int x;
    while(scanf("%d %d",&N,&M)!=EOF){
        for(int i=1;i<=N;i++) s[i].clear();
        mp.clear();
        int cnt=0;
        for(int i=1;i<=N;i++){
            scanf("%d",&x);
            if(!mp[x]) mp[x]=++cnt;
            s[mp[x]].insert(i);
        }
        for(int i=1;i<=M;i++){
            scanf("%d",&op[i]);
        }
        for(int i=1;i<=M;i++){
            if(!s[mp[op[i]]].size()) printf("-1\n");
            else{
                printf("%d\n",*s[mp[op[i]]].begin());
                s[mp[op[i]]].erase(s[mp[op[i]]].begin());
            }
        }
    }
    return 0;
}