#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=43;
int types,require,end_comb_num,total;
int stamp[max_n];
int now[4],end_comb[4];
bool ties,none;
void compare(){
    
}
void dfs(int k,int val){
    if(val>require) return ;
    if(val==require){
        compare();
    }
    for(int i=k;i<types;i++){
        now[total]=i;
        total++;
        dfs(k,val+stamp[i]);
        total--;
    }
}
int main(){
    int x;
    while(scanf("%d",&x)!=EOF){
        types=0;
        while(x){
            stamp[types++]=x;
        }
        sort(stamp,stamp+types);
        while(scanf("%d",&require)&&require){
            ties=false;
            none=false;
            end_comb_num=0;
            total;
            dfs(0,0);
            
        }
    }
}