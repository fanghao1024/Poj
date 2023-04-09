#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=25;
int g[max_n][max_n],degree[max_n];
char s[100];
int start,N;
int main(){
    while(scanf("%s",s)!=EOF){
        if(strlen(s)>5) break;
        memset(degree,0,sizeof(degree));
        scanf("%d %d",&start,&N);
        getchar();
        int tot = 0;
        for(int i=0;i<N;i++){
            cin.getline(s,100);
            int len=strlen(s);
            int num=0;
            for(int j=0;j<len;j++){
                //printf("%d:%c\n",j,s[j]);
                if(s[j]>='0'&&s[j]<='9'){
                    num=num*10+s[j]-'0';
                    if(j==len-1){
                        degree[i]++;
                        degree[num]++;
                        tot++;
                    }
                }else{
                    degree[i]++;
                    degree[num]++;
                    num=0;
                    tot++;
                }
            }
        }
        bool flag=true;
        int cnt=0;
        int rec[2];
        
        for(int i=0;i<N;i++){
            if(degree[i]%2==1){
                cnt++;
                if(cnt>2){
                    flag=false;
                    break;
                }
                rec[cnt - 1] = i;
            }
        }
        //printf("flag:%d,cnt:%d,rec[0]:%d,rec[1]:%d,start:%d\n",flag,cnt,rec[0],rec[1],start);
        if(!flag) printf("NO\n");
        else{
            if ((cnt == 0 && (start == 0)) || (cnt == 2 && ((rec[0] == 0 && rec[1] == start) || (rec[0] == start && rec[1] == 0))))
            {
                printf("YES %d\n", tot);
            }
            else
            {
                printf("NO\n");
            }
        }
        scanf("%s", s);
    }
    return 0;
}
