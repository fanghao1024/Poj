#include<cstring>
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;

const int max_n=10;

char mat[max_n][max_n];
char s1[15],s2[15];
int R,C;
int main(){
    while(cin>>s1){
        if (strcmp(s1, "ENDOFINPUT")==0) break;
        cin>>R>>C;
        for(int i=0;i<R;i++) cin>>mat[i];
        for(int i=0;i<R-1;i++){
            for(int j=0;j<C-1;j++){
                cout<<(mat[i][j]+mat[i][j+1]+mat[i+1][j]+mat[i+1][j+1])/4-'0';
            }
            cout<<endl;
        }
        cin>>s2;
    }
    return 0;
}