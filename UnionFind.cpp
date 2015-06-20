#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class UF{
public:
	UF(int N){
		for(int i = 0; i < N; ++i)
			id.push_back(i);
	}
	virtual void Union(int p, int q) = 0;
	virtual bool connected(int p, int q) = 0;
	//int find(int p);
	//int count();
	vector<int> id;
};

class QuickFindUF : public UF {
public:
	QuickFindUF(int N) : UF(N){}
	void Union(int p, int q);
	bool connected(int p, int q);
	//int find(int p);
	//int count();
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


class QuickUnionUF : public UF {
public:
	QuickUnionUF(int N) : UF(N) {}
	void Union(int p, int q);
	bool connected(int p, int q);
private:
	int root(int i){
		while(i != id[i]) {
			i = id[i];
		}
		return i;
	}
};

void QuickUnionUF::Union(int p, int q) {
	int i = root(p);
	int j = root(q);
	id[i] = j;
}

bool QuickUnionUF::connected(int p, int q) {
	return root(p) == root(q);
}


//weighted quick union with path compression
class WQUPC : public UF{
public:
	WQUPC(int N) : UF(N) {
		for(int i = 0; i < N; ++i)
			sz.push_back(1);
	}
	void Union(int p, int q);
	bool connected(int p, int q);
private:
	vector<int> sz;
	int root(int i) {
		while(i != id[i]) {
			id[i] = id[id[i]];
			i = id[i];
		}
		return i;
	}
};

void WQUPC::Union(int p, int q) {
	int pid = root(p), qid = root(q);
	if(pid == qid) return;
	if(sz[pid] < sz[qid]) {
		id[pid] = qid; 
		sz[qid] += sz[pid];
	}
	else{
		id[qid] = id[pid];
		sz[pid] += sz[qid];
	}
}

bool WQUPC::connected(int p, int q) {
	return root(p) == root(q);
}


int main() {
	//test of the program
	ifstream fin("tinyUF.txt");
	int N;
	fin>>N;
	UF* uf = new WQUPC(N);
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
