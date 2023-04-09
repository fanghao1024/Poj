#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;

int P;

struct Node{
    int a,b;
    int g,h;
    Node(){}
    Node(int _a,int _b,int _g){
        a=_a;
        b=_b;
        g=_g;
        h=0;
        int temp=a>b?a:b;
        while(temp<P){
            h++;
            temp<<=1;
        }
    }
    bool operator<(const Node& m) const{
        return g+h==m.g+m.h?h>m.h:g+h>m.g+m.h;
    }
};
int astar(){
    priority_queue<Node> q;
    q.push(Node(1,0,0));
    while(!q.empty()){
        Node node=q.top();
        q.pop();
        if(node.a==P||node.b==P){
            return node.g;
        }
        q.push(Node(node.a*2,node.b,node.g+1));
        q.push(Node(node.a, node.b*2, node.g + 1));
        q.push(Node(node.a, node.a*2, node.g + 1));
        q.push(Node(node.b * 2, node.b, node.g + 1));
        q.push(Node(node.a+node.b, node.b, node.g + 1));
        q.push(Node(node.a, node.b+node.a, node.g + 1));
        q.push(Node(abs(node.a-node.b), node.b, node.g + 1));
        q.push(Node(node.a , abs(node.b-node.a), node.g + 1));
    }
}
int main(){
    scanf("%d",&P);
    printf("%d\n",astar());
    return 0;

}