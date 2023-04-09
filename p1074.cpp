#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int rec[10][10],row[10][10],col[10][10],loc[10][10],s[88][4],score,most,u;
struct Node{
    int cnt,id;
}node[10];
bool cmp(const Node& a,const Node& b){
    return a.cnt<b.cnt;
}
int belong(int i,int j){
    if(i<=3){
        if(j<=3) return 1;
        if(j<=6) return 2;
        return 3;
    }
    if(i<=6){
        if(j<=3) return 4;
        if(j<=6) return 5;
        return 6;
    }
    if(i<=9){
        if(j<=3) return 7;
        if(j<=6) return 8;
        return 9;
    }
}
int point(int i,int j){
    if(i==1||i==9||j==1||j==9) return 6;
    if(i==2||i==8||j==2||j==8) return 7;
    if(i==3||i==7||j==3||j==7) return 8;
    if(i==4||i==6||j==4||j==6) return 9;
    return 10;
}
void init(){
    memset(row,0,sizeof(row));
    memset(col,0,sizeof(col));
    memset(loc,0,sizeof(row));
    score=0;
    most=-1;
    for(int i=1;i<=9;i++) node[i].cnt=0,node[i].id=i;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            scanf("%d",&rec[i][j]);
            if(rec[i][j]>0){
                row[i][rec[i][j]]=col[j][rec[i][j]]=loc[belong(i,j)][rec[i][j]]=1;
                score+=rec[i][j]*point(i,j);
            }else{
                node[i].cnt++;
            }
        }
    }
    sort(node+1,node+10,cmp);
    u=0;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(rec[node[i].id][j]==0){
                s[u][0]=node[i].id;
                s[u][1]=j;
                s[u][2]=belong(node[i].id,j);
                s[u][3]=point(node[i].id,j);
                u++;
            }
        }
    }
    
}
void dfs(int p,int sc){
    if(p==u){
        if(most<sc) most=sc;
        return;
    }
    int x=s[p][0],y=s[p][1],z=s[p][2];
    for(int i=1;i<=9;i++){
        if(!row[x][i]&&!col[y][i]&&!loc[z][i]){
            row[x][i]=col[y][i]=loc[z][i]=1;
            dfs(p+1,sc+s[p][3]*i);
            row[x][i] = col[y][i] = loc[z][i] = 0;
        }
    }
}
int main(){ 
    init();
    dfs(0, score);
    printf("%d\n", most);
    return 0;
}
