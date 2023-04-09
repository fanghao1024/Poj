#include<cstdio>
#include<queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > q;
int main(){
    int n,x;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&x);
        q.push(x);
    }
    int ans=0;
    while(q.size()>1){
        int a=q.top();
        q.pop();
        int b=q.top();
        q.pop();
        ans+=(a+b);
        q.push(a+b);
    }
    printf("%d\n",ans);
    return 0;
}