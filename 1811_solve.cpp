#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef long long ll;

ll pri[]= {2,3,5,7,11,13,17,19,23,29,31};//用小素数表做随机种子避免第一类卡米歇尔数的误判
ll multi(ll a,ll b,ll n) //乘法快速幂
{
	ll tmp=0;
	while(b)
	{
		if(b&1)
		{
			tmp+=a;
			if(tmp>=n) tmp-=n;
		}
		a<<=1;
		if(a>=n) a-=n;
		b>>=1;
	}
	return tmp;
}
ll multimod(ll a,ll m,ll n) //乘法快速幂
{
	ll tmp=1;
	a%=n;
	while(m)
	{
		if(m&1) tmp=multi(tmp,a,n);
		a=multi(a,a,n);
		m>>=1;
	}
	return tmp;
}
ll gcd(ll a, ll b)        //迭代算法
{
	while(b)
	{
		ll c=a%b;
		a=b;
		b=c;
	}
	return a;
}
bool Miller_Rabin(ll n) //大素数判断
{
	if(n<2)
		return false;
	if(n==2)
		return true;
	if(!(n&1))
		return false;
	ll k=0,j,m,a;
	m=n-1;
	while(!(m&1))
	{
		m>>=1;
		k++;
	}
	for(int i=0; i<10; i++)
	{
		if(pri[i]>=n)
			return true;
		a=multimod(pri[i],m,n);
		if(a==1)
			continue;
		for(j=0; j<k; j++)
		{
			if(a==n-1)
				break;
			a=multi(a,a,n);
		}
		if(j==k)
			return false;
	}
	return true;
}
ll pollard_rho(ll c,ll n) //查找因数
{
	ll i,x,y,k,d;
	i=1;
	x=y=rand()%n;
	k=2;
	do{
		i++;
		d=gcd(n+y-x,n);
		if(d>1 && d<n)
			return d;
		if(i==k)
		{
			y=x;
			k<<=1;
		}
		x=(multi(x,x,n)+n-c)%n;
	}while(y!=x);
	
	return n;
}
ll rho(ll n)
{
	if(Miller_Rabin(n))
		return n;
	ll t=n;
	while(t>=n)
		t=pollard_rho(rand()%(n-1)+1,n);
	ll a=rho(t);
	ll b=rho(n/t);
	return a<b? a:b;
}

ll ans[10000005],flag;
void rhoAll(ll n) //计算全部质因子
{
	if(Miller_Rabin(n))
	{
		ans[flag++]=n;
		return;
	}
	ll t=n;
	while(t>=n)
		t=pollard_rho(rand()%(n-1)+1,n);
	rhoAll(t);
	rhoAll(n/t);
	return;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int t;
	ll n;
	scanf("%d",&t);
	while(t--)
	{
		flag=0;
		scanf("%lld",&n);
		if(Miller_Rabin(n))
			printf("Prime\n");
		else
		{
			//rhoAll(n);
			printf("%I64d\n",rho(n));
		}
		/*for(int i=0;i<flag;i++) //输出全部质因子
		  if(i!=flag-1)
		  printf("%I64d ",ans[i]);
		  else
		  printf("%I64d\n",ans[i]);*/
	}
	return 0;
}
