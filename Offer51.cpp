#include<bits/stdc++.h>
using namespace std;

struct Info{
	int val;
	int id;
	Info(int v,int x){
		this->val=v;
		this->id=x;
	}
	Info(){};
};
vector<Info> vi;
int tree[50010];
int rec[50010];
int N;
int lowbit(int x){
	return x&(-x);
}
void update(int x,int d){
	while(x<=N){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int get_sum(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
bool cmp(const Info& a,const Info& b){
	if(a.val!=b.val){
		return a.id<b.id;
	}else{
		return a.val<b.val;
	}
}
class Solution {
public:
	int reversePairs(vector<int>& nums) {
		N=nums.size();
		for(int i=0;i<N;i++){
			vi.push_back(Info(nums[i],i+1));
		}
		sort(vi.begin(),vi.end(),cmp);
		for(int i=0;i<N;i++){
			rec[vi[i].id]=i+1;
		}
		int ans=0;
		memset(tree,0,sizeof(tree));
		for(int i=N;i>0;i--){
			ans+=get_sum(rec[i]);
			update(rec[i],1);
		}
		return ans;
	}
};
Solution s;
