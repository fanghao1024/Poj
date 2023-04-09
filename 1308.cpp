#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

map<int,int> par,degree;
set<int> si;
int main(){
    int x,y;
    int caseNo=1;
    while(scanf("%d %d",&x,&y)!=EOF){
        if(x==-1&&y==-1) break;
        par.clear();
        degree.clear();
        si.clear();
        bool flag=true;
        if(x==0&&y==0){
            printf("Case %d is a tree.\n", caseNo++);
            continue;
        }
        do{
            if(x==0&&y==0) break;
            if(!flag) continue;
            si.insert(x);
            si.insert(y);
            if(par[y]!=0){
                flag=false;
            }else{
                par[y]=x;
                degree[y]++;
                if(degree[y]>1) flag=false;
            }
        }while(scanf("%d %d",&x,&y));
        if(!flag)
            printf("Case %d is not a tree.\n",caseNo++);
        else{
            int cnt=0;
            flag=true;
            for(set<int>::iterator it=si.begin();it!=si.end();it++){
                if(degree[*it]==0) cnt++;
                if(degree[*it]>1){
                    flag=false;
                    break;
                }
            }
            if(!flag||cnt!=1)
                printf("Case %d is not a tree.\n", caseNo++);
            else
                printf("Case %d is a tree.\n",caseNo++);
        }
    }
}