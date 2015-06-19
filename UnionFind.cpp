#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class QuickFindUF {
public:
	QuickFindUF(int N){
		for(int i = 0; i < N; ++i)
			id.push_back(i);
	}
	void Union(int p, int q);
	bool connected(int p, int q);
	//int find(int p);
	//int count();
private:
	vector<int> id;
};

void QuickFindUF::Union(int p, int q) {
	int pid = id[p], qid = id[q];
	for(int i = 0; i < id.size(); ++i) {
		if(id[i] == pid)
			id[i] = qid;
	}
}

bool QuickFindUF::connected(int p, int q) {
	return id[p] == id[q];
}



int main() {
	//test of the program
	ifstream fin("tinyUF.txt");
	int N;
	fin>>N;
	QuickFindUF* uf = new QuickFindUF(N);
	while(!fin.eof()) {
		int p, q;
		fin>>p>>q;
		if(!uf->connected(p, q)) {
			uf->Union(p, q);
			cout<<p<<" "<<q<<endl;
		}
	}
	return 0;
}
