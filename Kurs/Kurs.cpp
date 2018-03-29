// Kurs.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;
struct material
{
	double D, a, alpha, mass;
};
inline double derivate(struct material matter, double r)
{
	
		double hz=-2 * matter.D * matter.alpha * exp(matter.alpha * (-r + matter.a))*(exp(matter.alpha * (-r + matter.a)) - 1);
		return hz;
}
double acceleration(struct material matter, vector <vector<double>> &R, int k)
{
	double sum = 0,tmp_r=0;
	for (int i = 0; i < R[1].size(); i++)
	{
		if (i != k)
		{
			tmp_r = R[1][k] - R[1][i];
			sum+=(-1*derivate(matter, tmp_r) * (tmp_r)) / (fabs(tmp_r));
		}
	}
	return sum / matter.mass;
}
void iteration(vector <vector<double>> &R, int i, struct material matter, vector<double> &speed)
{
	double tmp = 0;
	double tau = 0.01;
	tmp = 2 * R[1][i] - R[0][i] + acceleration(matter,R,i)*tau*tau;
	R[0][i] = R[1][i];
	R[1][i] = R[2][i];
	R[2][i] = tmp;
	speed[i] = (0.5 / tau)*(R[2][i] - R[0][i]);
}
bool check(vector<double> speed)
{
	int flag = 0;
	for (int i = 0; i < speed.size(); i++)
	{
		if (speed[i] != 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1) return false;
	else return true;
}
void Iniz(vector<double> &speed, vector <vector<double>> &R)
{
	for (int i = 0; i < speed.size(); i++)
	{
		//speed[i]=50;
		R[1][i]=2*i/800000.0;
		R[2][i]=1*i/800000.0;
	}
}
int main()
{
	int N = 2000, count = 0;
	struct material matter;
	matter.D = 0.223;
	matter.a = 2.845*powf(10, -10);
	matter.alpha = matter.a / 6;//2.108963093*powf(10,10);
	matter.mass = 9.2732796 * powf(10,-26);
	/*matter.D = 1;
	matter.a = 1;
	matter.alpha = 1;
	matter.mass = 1;*/
	vector<vector<double>> R(3, vector<double>(N));
	vector<double> speed(N);
	Iniz(speed, R);
	do
	{
		count++;
		for (int i = 0; i < N; i++)
		{
			iteration(R, i, matter, speed);
		}
		cout << count << endl;
		cout << speed[0] << endl;
		cout << speed[1] << endl;
		/*cout << "#####" << endl;
		cout << R[1][0] << endl;
		cout << R[1][1] << endl;*/
		system("pause");
	} while (!check(speed));
	return 0;
}

