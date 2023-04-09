#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=110;

bool vis[max_n][max_n];
struct Node{
    int a,b;
    int step;
    Node(){};
    Node(int _a,int _b,int _step){
        a=_a;
        b=_b;
        step=_step;
    }
};
struct Rec{
    int a,b;
    int ops;
}rec[max_n][max_n];

int A,B,C;
char ops[6][20] = {"FILL(1)", "FILL(2)", "DROP(1)", "DROP(2)", "POUR(1,2)", "POUR(2,1)"};
queue<Node> q;
void print(int a,int b){
    if(a==0&&b==0) return ;
    print(rec[a][b].a,rec[a][b].b);
    printf("%s\n",ops[rec[a][b].ops]);
}
void bfs(){
    while(!q.empty()) q.pop();
    memset(vis, 0, sizeof(vis));
    vis[0][0] = 1;
    q.push(Node(0,0,0));
    while(!q.empty()){
        Node node=q.front();
        q.pop();
        if(node.a==C||node.b==C){
            printf("%d\n",node.step);
            print(node.a,node.b);
            return ;
        }
        // FILL(1)
        if(!vis[A][node.b]){
            q.push(Node(A,node.b,node.step+1));
            vis[A][node.b]=1;
            rec[A][node.b].a=node.a;
            rec[A][node.b].b=node.b;
            rec[A][node.b].ops=0;
        }
        // FILL(2)
        if (!vis[node.a][B])
        {
            q.push(Node(node.a, B, node.step + 1));
            vis[node.a][B] = 1;
            rec[node.a][B].a = node.a;
            rec[node.a][B].b = node.b;
            rec[node.a][B].ops = 1;
        }
        // DROP(1)
        if(!vis[0][node.b]){
            q.push(Node(0, node.b, node.step + 1));
            vis[0][node.b] = 1;
            rec[0][node.b].a = node.a;
            rec[0][node.b].b = node.b;
            rec[0][node.b].ops = 2;
        }
        // DROP(2)
        if(!vis[node.a][0]){
            q.push(Node(node.a, 0, node.step + 1));
            vis[node.a][0] = 1;
            rec[node.a][0].a = node.a;
            rec[node.a][0].b = node.b;
            rec[node.a][0].ops = 3;
        }
        // POUR(1,2)
        int Min=min(node.a,B-node.b);
        if(!vis[node.a-Min][node.b+Min]){
            q.push(Node(node.a-Min, node.b+Min, node.step + 1));
            vis[node.a-Min][node.b+Min] = 1;
            rec[node.a-Min][node.b+Min].a = node.a;
            rec[node.a - Min][node.b + Min].b = node.b;
            rec[node.a - Min][node.b + Min].ops = 4;
        }
        // POUR(2,1)
        Min = min(node.b, A - node.a);
        if (!vis[node.a + Min][node.b - Min])
        {
            q.push(Node(node.a + Min, node.b - Min, node.step + 1));
            vis[node.a + Min][node.b - Min] = 1;
            rec[node.a + Min][node.b - Min].a = node.a;
            rec[node.a + Min][node.b - Min].b = node.b;
            rec[node.a + Min][node.b - Min].ops = 5;
        }
    }
    printf("impossible\n");
}
int main(){
    scanf("%d %d %d",&A,&B,&C);
    bfs();
    return 0;
}