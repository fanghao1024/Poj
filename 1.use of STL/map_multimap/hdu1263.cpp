#include<iostream>
#include<map>
#include<string>
using namespace std;


int main(){
	int N,M;
	string a,b;
	int v;
	cin>>N;
	for(int case_num=0;case_num<N;case_num++){
		if(case_num) cout<<endl;
		cin>>M;
		map<string,map<string,int> > mpi;
		for(int i=0;i<M;i++){
			cin>>a>>b>>v;
			mpi[b][a]+=v;
		}
		map<string,map<string,int> >::iterator it1;
		map<string,int>::iterator it2;
		for(it1=mpi.begin();it1!=mpi.end();it1++){
			cout<<it1->first<<endl;
			for(it2=it1->second.begin();it2!=it1->second.end();it2++){
				cout<<"   |----"<<it2->first<<"("<<it2->second<<")"<<endl;
			}
		}
		
	}
	return 0;
}
