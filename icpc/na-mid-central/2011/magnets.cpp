#include <fstream>
#include <iostream>
#include <set>

using namespace std;

// Determines if a string contains no duplicate letters.
bool is_valid(const string& str)
{
    bool seen['Z'-'A'+1] = {};

    for (char c : str)
    {
        if (c != ' ')
        {
            int index = c - 'A';

            if (seen[index])
            {
                return false;
            }
            else
            {
                seen[index] = true;
            }
        }
    }

    return true;
}

int main()
{
    ifstream in ("magnets.in");

    string line;

    while (getline(in, line) && line != "END")
    {
        if (is_valid(line))
        {
            cout << line << endl;
        }
    }
}
