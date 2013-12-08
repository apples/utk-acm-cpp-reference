#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Represents a DuLL.
struct DuLL
{
	int users; // Number of programs using this DuLL.
	int size;  // Memory needed to load this DuLL.
	
	DuLL() : users(0), size(0) {} // Mainly needed to ensure that users == 0.
};

// Represents a loaded program.
struct Program
{
	int size;     // Memory needed.
	string dulls; // Required DuLLs.
};

int main()
{
	ifstream input ("dull.in");
	
	int N; // Number of DuLLs
	int P; // Number of Programs
	int S; // Number of state changes

	vector<DuLL>    dulls; // All DuLLs.
	vector<Program> progs; // All programs.

	int currentMem; // Current memory usage.
	int maxMem;     // Maximum memory usage.

	dulls.reserve(20); // Guaranteed at most 20 DuLLs.
	progs.reserve(9);  // Guaranteed at most 9 programs.
	
	// The `dulls` and `progs` vectors are scoped outside of the loop
	// to minimize dynamic memory allocation.
	
	while (input >>N >>P >>S, N!=0)
	{
		dulls.clear();
		progs.clear();
		
		dulls.resize(N);
		progs.resize(P);
		
		currentMem = 0;
		maxMem = 0;
		
		// Read in data for the DuLLs.
		for (int i=0; i<N; ++i)
		{
			input >>dulls[i].size;
		}
		
		// Read in data for the programs.
		for (int i=0; i<P; ++i)
		{
			input >>progs[i].size >>progs[i].dulls;
		}
		
		// Run the simulation.
		for (int i=0; i<S; ++i)
		{
			int progID; // Current program id.
			int direction = 1; // == 1 if starting program, == -1 if ending.
			
			input >>progID;
			
			if (progID < 0)
			{
				progID = -progID;
				direction = -1;
			}
			
			const Program& prog = progs[progID-1];
			
			currentMem += prog.size * direction;
			
			// Process required DuLLs.
			for (unsigned j=0; j<prog.dulls.size(); ++j)
			{
				DuLL& dull = dulls[prog.dulls[j]-'A'];
				
				// dull.users == 0 if the DuLL needs to be loaded.
				if (dull.users==0) currentMem += dull.size;
				
				dull.users += direction;
				
				// dull.users == 0 if the DuLL should be unloaded.
				if (dull.users==0) currentMem -= dull.size;
			}
			
			maxMem = max(currentMem, maxMem);
		}
		
		cout << maxMem << endl;
	}
}
