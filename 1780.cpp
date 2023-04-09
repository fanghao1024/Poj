#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5;

int st_edge[max_n*10],top_e;
char st_ans[max_n*10];
int top_a;
int num[max_n];
int N,m;
void no_dfs(int v){
    while(num[v]<10){
        int edge=v*10+num[v];
        num[v]++;
        st_edge[top_e++]=edge;
        v=edge%m;
    }
}
int main(){
    while(scanf("%d",&N)&&N){
        top_e=top_a=0;
        m=1;
        for(int i=1;i<N;i++) m*=10;
        for(int i=0;i<m;i++) num[i]=0;
        no_dfs(0);
        while(top_e){
            int edge=st_edge[--top_e];
            st_ans[top_a++]=edge%10+'0';
            no_dfs(edge/10);
        }
        for(int i=1;i<N;i++) printf("0");
        while(top_a){
            printf("%c", st_ans[--top_a]);
        }
        printf("\n");
    }
    return 0;
}