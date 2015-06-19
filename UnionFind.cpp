#include <iostream>
#include <fstream>
using namespace std;

class UF {
	UF(int N);
	void Union(int p, int q);
	bool connected(int p, int q);
	int find(int p);
	int count;
};

int main() {
	//test of the program
	ifstream fin("tinyUF.txt");
	fin>>N;
	UF uf = new UF(N);
	while(!fin.eof()) {
		int p, q;
		fin>>p>>q;
		if(!uf.connected(p, q)) {
			uf.union(p, q);
			cout<<p<<" "<<q<<endl;
		}
	}
	return 0;
}
