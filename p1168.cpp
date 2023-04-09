#include<cstdio>
#include<queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > q1;
priority_queue<int, vector<int>, less<int> > q2;
int N,x;
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%d",&x);
        if(q1.empty()||x>q1.top())
            q1.push(x);
        else q2.push(x);

        if(i%2==1){
            while(q1.size()>(i/2+1)) q2.push(q1.top()),q1.pop();
            while(q1.size()<(i/2)+1) q1.push(q2.top()),q2.pop();
            printf("%d\n",q1.top());
        }
    }
    return 0;
}