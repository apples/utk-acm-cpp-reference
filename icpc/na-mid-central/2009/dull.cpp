#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct DuLL
{
	int users;
	int size;
	
	DuLL() : users(0), size(0) {}
};

struct Program
{
	int size;
	string dulls;
	
	Program() : size(0), dulls() {}
};

int main()
{
	ifstream input ("dull.in");
	
	int N; // Number of DuLLs
	int P; // Number of Programs
	int S; // Number of state changes
		
	vector<DuLL> 	dulls;
	vector<Program> progs;

	int currentMem;
	int maxMem;

	dulls.reserve(20);
	progs.reserve(9);
	
	while (input >>N >>P >>S, N!=0)
	{
		dulls.clear();
		progs.clear();
		
		dulls.resize(N);
		progs.resize(P);
		
		currentMem = 0;
		maxMem = 0;
		
		for (int i=0; i<N; ++i)
		{
			input >>dulls[i].size;
		}
		
		for (int i=0; i<P; ++i)
		{
			input >>progs[i].size >>progs[i].dulls;
		}
		
		for (int i=0; i<S; ++i)
		{
			int progID;
			int dir = 1;
			
			input >>progID;
			
			if (progID < 0)
			{
				progID = -progID;
				dir = -dir;
			}
			
			const Program& prog = progs[progID-1];
			
			currentMem += prog.size * dir;
			
			for (unsigned j=0; j<prog.dulls.size(); ++j)
			{
				DuLL& dull = dulls[prog.dulls[j]-'A'];
				
				if (dull.users==0) currentMem += dull.size;
				dull.users += dir;
				if (dull.users==0) currentMem -= dull.size;
			}
			
			maxMem = max(currentMem, maxMem);
		}
		
		cout << maxMem << endl;
	}
}
