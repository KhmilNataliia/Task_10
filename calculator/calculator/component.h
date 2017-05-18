#ifndef COMPONENT
#define COMPONENT

#include<iostream>
#include<exception>

using namespace std;

class exception_wrong_compnt :public exception
{
public:
	void error_messege()
	{
		cout << "wrong expression!" << endl;
	}
};

class exception_div_on_zero : public exception
{
public:
	void error_messege()
	{
		cout << "error: dividing by zero! " << endl;
	}
};

class component
{
public:
	virtual double getVal() = 0;
	virtual void attach(component *a_child) = 0;
};

class operand: public component
{
	double val;
public:
	operand(double VAL) :val(VAL){}
	double getVal() { return val; }
	void attach(component *a_child) { throw new exception_wrong_compnt(); }
};

class operation : public component
{
protected:
	component *left_son, *right_son;
public:
	operation()
	{
		left_son = NULL; right_son = NULL;
	}
	virtual double getVal() = 0;
	virtual void attach(component *a_child)
	{
		if (!left_son) left_son = a_child;
		else if (!right_son) right_son = a_child;
		else throw new exception_wrong_compnt();
	}
};

class Add :public operation  // operation "+"
{
public:
	double getVal()
	{
		return left_son->getVal() + right_son->getVal();
	}
};

class Mult : public operation  //operation "*"
{
public:
	double getVal()
	{
		return left_son->getVal() * right_son->getVal();
	}
};

class Sub : public operation //operation "-"
{
public:
	double getVal()
	{
		return left_son->getVal() - right_son->getVal();
	}
};

class Div : public operation //operation "/"
{
public:
	double getVal()
	{
		double divider = right_son->getVal();
		if (divider != 0) { return left_son->getVal() / divider; }
		throw new exception_div_on_zero();
	}
};

#endif;