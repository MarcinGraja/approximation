#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
#include <random>
using namespace std;
struct point
{
	double x;
	double y;
};
double legendre(double x, int k)
{
	if (k < 0)
	{
		cout << "fail";
	}
	if (k == 0) return 1;
	if (k == 1) return x;
	else
	{
		double left = x * (2 * k - 1.0) / (k)* legendre(x, k - 1);
		double right = (k - 1.0) / (k)* legendre(x, k - 2);
		return  left - right;
	}
}

vector <point> estimate(vector <point> points)
{
	const int ALPHAS_NEEDED = 4;
	double alphas[ALPHAS_NEEDED];
	
	for (int i = 0; i < ALPHAS_NEEDED; i++)
	{
		double sum = 0;
		double sum2 = 0;
		for (int j = 0; j < points.size(); j++)
		{
			sum += points[j].y * legendre(points[j].x, i);
			sum2 += legendre(points[j].x, i)*legendre(points[j].x, i);
		}
		alphas[i] = sum/sum2;
		cout << "alphas[" << i << "]: " << alphas[i] << endl;
	}
	double h = 0;
	vector <point> returned;
	for (int j = 0; j < points.size(); j++)
	{
		for (int i = 0; i < ALPHAS_NEEDED; i++)
		{
			h += alphas[i] * legendre(points[j].x, i);
			cout<< "j: " << j << " i: " << i << "\t" << legendre(points[j].x, i) << endl;
		}
		point temp;
		temp.x = points[j].x;
		temp.y = h;
		returned.push_back(temp);
	}
	return returned;
}
int main()
{
	srand(time(NULL));
	ofstream ofile;
	ofile.open("input.txt");
	double x = -1;
	for (int i = 0; i < 30; i++)
	{
		double X = x + i * 1.0 / 15;
		double Y = (x + i * 1 / 15.0)*(x + i * 1 / 15.0) + (rand() % 100 - 50) / 10000.0;
		ofile << X << '\t' << Y << endl;
	}
	ofile.close();
	ifstream file;
	file.open("input.txt");
	vector <point> points;
	if (file.good())
	{
		while (!file.eof())
		{
			point temp;
			file >> temp.x >> temp.y;
			points.push_back(temp);
		}
	}

	vector<point> returned = estimate(points);
	for (int i = 0; i < points.size(); i++)
	{
		cout.ios_base::precision(4);
		cout << "points:   \t" << points[i].x << '\t' << points[i].y << endl;
		cout << "returned\t" << returned[i].x << '\t' << returned[i].y << endl;
	}
	cin.ignore();
}