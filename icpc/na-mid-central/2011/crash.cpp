#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Radio
{
	double x;
	double y;
	double r;
};

class Contact
{
	const Radio& me;
public:
	Contact(const Radio& r)
		: me(r)
	{}

	bool operator()(const Radio& other) const
	{
		double dx = me.x - other.x;
		double dy = me.y - other.y;
		double dist = sqrt(dx*dx + dy*dy);

		return !(dist <= max(me.r, other.r));
	}
};

class Surface
{
	vector<Radio> radios;

public:
	Surface()
	{
		radios.reserve(100);
	}

	void add_radio(Radio lander)
	{
		vector<Radio>::iterator iter;
		vector<Radio>::iterator begin = radios.begin();
		vector<Radio>::iterator end = radios.end();
		
		iter = partition(begin, end, Contact(lander));

		if (iter == end)
		{
			radios.push_back(lander);
			return;
		}

		double count = (radios.end() - iter) + 1.0;
		double area = lander.r*lander.r;

		for (vector<Radio>::iterator i = iter; i != end; ++i)
		{
			const Radio& r = *i;

			lander.x += r.x;
			lander.y += r.y;
			area += r.r*r.r;
		}

		lander.x /= count;
		lander.y /= count;
		lander.r = sqrt(area);

		radios.erase(iter, end);

		return add_radio(lander);
	}

	void reset()
	{
		radios.resize(0);
	}

	int score()
	{
		return radios.size();
	}
};

int main()
{
	ifstream in ("crash.in");

	int N;
	Surface surface;
	Radio lander;

	while (in >>N, N != 0)
	{
		surface.reset();

		for (int i=0; i<N; ++i)
		{
			in >>lander.x >>lander.y >>lander.r;
			surface.add_radio(lander);
		}

		cout <<surface.score() <<endl;
	}
}

