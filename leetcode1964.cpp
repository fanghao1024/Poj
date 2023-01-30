#include<iostream>
#include<algorithm>
using namespace std;

vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
	vector<int> rec,ans;
	for(int i=0;i<obstacles.size();i++){
		if(rec.size()==0||obstacles[i]>=rec.back()){
			rec.push_back(obstacles[i]);
			ans.push_back(rec.size());
		}else{
			int loc=upper_bound(rec.begin(),rec.end(),obstacles[i])-rec.begin();
			cout<<obstacles[i]<<"===="<<loc<<endl;
			ans.push_back(loc+1);
			rec[loc]=obstacles[i];
		}
	}
	return ans;
}
int main(){
	int a[6]={2,2,1,2,4,3};
	vector<int> obstacles;
	for(int i=0;i<6;i++) obstacles.push_back(a[i]);
	vector<int> ans=longestObstacleCourseAtEachPosition(obstacles);
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}



