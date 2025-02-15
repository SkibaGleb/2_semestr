#include <iostream>
#include <stack>
using namespace std;

int main()
{
	stack<double> T;
	double N{ -1 };
	do
	{
		cin >> N;
		if (N == 0)
			break;
		T.push(N);
	} while (true);
	do
	{
		double V = T.top();
		if (V > 0)
			cout << V << " ";
		T.pop();
	} while (T.size() != 0);
}