#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=10;
int a,b;
int lena,lenb;
int numa[max_n],numb[max_n];
int flag;
int ans;
int nowArr[max_n],nowSeq;
int endArr[max_n],endSeq;
int getNum(int num[],int l,int r){
    int temp=0;
    for(int i=l;i<=r;i++){
        temp=temp*10+num[i];
    }
    return temp;
}
void dfs(int num[],int len,int now,int val,int seq){
    if(val>a) return ;
    if(now==len){
        if(val<=a){
            if(ans==val) flag++;
            else if(ans<val){
                flag=1;
                ans=val;
                endSeq=seq;
                for(int i=0;i<seq;i++){
                    endArr[i]=nowArr[i];
                }
            }
            return ;
        }
    }

    for(int i=1;now+i-1<len;i++){
        nowArr[seq]=i;
        dfs(num,len,now+i,val+getNum(num,now,now+i-1),seq+1);
    }
}
int main(){
    while(scanf("%d %d",&a,&b)!=EOF){
        if(a==0&&b==0) break;
        if(a==b){
            printf("%d %d\n",a,b);
            continue;
        }   

        lenb=0;
        while(b){
            numb[lenb++]=b%10;
            b/=10;
        }
        reverse(numb,numb+lenb);
        flag=0;
        ans=-1;
        dfs(numb,lenb,0,0,0);
        if(flag==1){
            printf("%d",ans);
            int pos=0;
            for(int i=0;i<endSeq;i++){
                printf(" ");
                for(int j=0;j<endArr[i];j++){
                    printf("%d",numb[pos++]);
                }
            }
            printf("\n");
        }
        else if(flag>1)
            printf("rejected\n");
        else printf("error\n");
    }
    return 0;
}