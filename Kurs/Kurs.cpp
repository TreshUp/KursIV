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
	double f;
	if (r<=2.1*matter.a) f=-2 * matter.D * matter.alpha * exp(matter.alpha * (-r + matter.a))*(exp(matter.alpha * (-r + matter.a)) - 1);
		else f = 0;
	return f;
}
double acceleration(struct material matter, vector <vector<double>> &R, int k,int coord,int N)
{
	double sum = 0,tmp_r=0;
	for (int i = k+1; i < N; i++)
	{
		tmp_r = R[coord][k]- R[coord][i];
		sum+=(-1*derivate(matter, fabs(tmp_r)) * (tmp_r)) / (fabs(tmp_r));
	}
	return sum / matter.mass;
}
void iteration(vector <vector<double>> &R, int i, struct material matter, vector <vector<double>> &speed, vector <vector<double>> &R_old, int N)
{
	double new_x = 0, new_y=0,speed_x=0, speed_y = 0;
	double tau = 1.0 / 20;//0.005;
	//tmp = 2 * R[1][i] - R[0][i] + acceleration(matter,R,i)*tau*tau;
	new_x = R[0][i] + speed[0][i] * tau + 0.5*acceleration(matter, R, i, 0,N)*tau*tau;
	new_y = R[1][i] + speed[1][i] * tau + 0.5*acceleration(matter, R, i, 1,N)*tau*tau;
	speed_x = speed[0][i] + 0.5*acceleration(matter, R, i,0,N)*tau;
	speed_y = speed[1][i] + 0.5*acceleration(matter, R, i, 1,N)*tau;
	//R[0][i] = R[1][i];
	R_old[0][i] = R[0][i];
	R_old[1][i] = R[1][i];
	R[0][i] = new_x;
	R[1][i] = new_y;
	//R[1][i] = R[2][i];
	//R[2][i] = tmp;
	//speed[i] = (0.5 / tau)*(R[2][i] - R[0][i]);
	speed[0][i] = speed_x + 0.5*acceleration(matter, R, i,0,N)*tau;
	speed[1][i] = speed_y + 0.5*acceleration(matter, R, i, 1,N)*tau;
}
bool check(vector <vector<double>> &speed)
{
	int flag = 0;
	for (int i = 0; i < speed.size(); i++)
	{
		if (speed[0][i] != 0 || speed[1][i] != 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1) return false;
	else return true;
}
void Iniz(vector <vector<double>> &speed, vector <vector<double>> &R,int N)
{
	for (int i = 0; i < N; i++)
	{
		speed[1][i] = 2;
		speed[0][i] = 2;
		R[1][i] = i + 1; // *powf(10, -18);
		R[0][i] = 2 * i;// *powf(10, -18);
	}
}
int main()
{
	int N = 2000, count = 0;
	struct material matter;
	matter.D = 0.2703;//*1.6*powf(10, -19);
	matter.a = 3.253;//*powf(10, -10);
	matter.alpha = 1.1646;//*powf(10, 10);
	matter.mass = 26.98; //*powf(10, -26);

	vector<vector<double>> R(2, vector<double>(N));
	vector<vector<double>> R_old(2, vector<double>(N));
	vector<vector<double>> speed(2, vector<double>(N));
	Iniz(speed, R,N);
	do
	{
		count++;
		for (int i = 0; i < N; i++)
		{
			iteration(R, i, matter, speed,R_old,N);
		}
		cout << count << endl;
		cout << speed[0][0] <<" - ";
		cout << speed[1][1] << endl;
		/*cout << "#####" << endl;
		cout << R[1][0] << endl;
		cout << R[1][1] << endl;*/
		system("pause");
	} while (!check(speed));
	return 0;
}

