#include"calc.h"

int main()
{
	cout << "input your expression:" << endl;
	string our_expr;
	cin >> our_expr;
	double res = calc::expression().do_calc(our_expr);
	cout << "the result = " << res << endl;
	system("pause");
}