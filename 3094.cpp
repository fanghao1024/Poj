#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

char s[300];

int main(){
    int num;
    while(cin.getline(s,300)){
        if(s[0]=='#') break;
        num=0;
        int x=0;
        while(s[x]==' ') x++;
        int ind=x;
        while(ind<strlen(s)){
            if(s[ind]!=' ')
                num+=(ind-x+1)*(s[ind]-'A'+1);
            ind++;
        }
        printf("%d\n",num);
    }
    return 0;
}