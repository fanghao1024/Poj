#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int max_n=20;
bool rows[max_n][max_n];
bool cols[max_n][max_n];
bool grid[max_n][max_n];
int matrix[max_n][max_n];
char ch[max_n];
int get_grid(int x,int y){
	return ((x-1)/3)*3+(y-1)/3+1;
}
bool dfs(int x,int y){
	if(y>9){
		y=1;
		x+=1;
	}
	if(x>9){
		for(int i=1;i<=9;i++){
			for(int j=1;j<=9;j++){
				printf("%d",matrix[i][j]);
			}
			printf("\n");
		}
		return true;
	}
	if(matrix[x][y]!=0){
		if(dfs(x,y+1)) return true;
	}else{
		for(int i=1;i<=9;i++){
			if(!rows[x][i]&&!cols[y][i]&&!grid[get_grid(x,y)][i]){
				rows[x][i]=1;
				cols[y][i]=1;
				grid[get_grid(x,y)][i]=1;
				matrix[x][y]=i;
				if(dfs(x,y+1)) return true;
				matrix[x][y]=0;
				rows[x][i]=0;
				cols[y][i]=0;
				grid[get_grid(x,y)][i]=0;
			}
		}
	}
	return false;
}
int main(){
	int case_num;
	scanf("%d",&case_num);
	while(case_num--){
		memset(rows,0,sizeof(rows));
		memset(cols,0,sizeof(cols));
		memset(grid,0,sizeof(grid));
		/*
		for(int i=0;i<9;i++){
			scanf("%s",ch);
			for(int j=0;j<9;j++){
				if(ch[j]!='0'){
					int v=ch[j]-'0';
					matrix[i+1][j+1]=v;
					rows[i+1][v]=1;
					cols[j+1][v]=1;
					grid[get_grid(i+1,j+1)][v]=1;
				}
			}
		}
		  */
		char chs;
		for(int i=0;i<9;i++){
			//scanf("%s",ch);
			for(int j=0;j<9;j++){
				cin>>chs;
				if(chs!='0'){
					int v=chs-'0';
					matrix[i+1][j+1]=v;
					rows[i+1][v]=1;
					cols[j+1][v]=1;
					grid[get_grid(i+1,j+1)][v]=1;
				}
			}
		}
		dfs(1,1);
		
	}
	return 0;
}
