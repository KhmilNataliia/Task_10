#ifndef PARSER
#define PARSER

#include"component.h"
#include<string>

class parser
{
	parser(){};
	~parser(){};
	parser(parser &src){}
	parser& operator=(const parser &src){};

	component *get_operand(string str)
	{
		int len = str.size();
		double res = 0;
		int curnt;
		for (int i(1); i < len; i++) 
		{ 
			curnt = char(str[i]) - '0'; 
			res += curnt*pow(10, static_cast<double>(len - i - 1));
		}
		if (str[0] == '-') res = res*(-1);
		else
		{
			res += (str[0] - '0')*pow(10, static_cast<double>(len - 1));
		}
		return new operand(res);
	}

	component *get_operation(char op)
	{
		switch (op)
		{
		case '+': return new Add();
		case '-': return new Sub();
		case '*': return new Mult();
		case '/': return new Div();
		}
	}

	bool is_operator(char op)
	{
		switch (op)
		{
		case '+': return true;
		case '-': return true;
		case '*': return true;
		case '/': return true;
		default: return false;
		}
	}

	int Prioritet(char x)
	{
		switch (x)
		{
		case '+': return 0;
		case '-': return 0;
		case '*': return 1;
		case '/': return 1;
		}
	}

	bool outer_brackets(string str) 
	{
		int balance = 0;
		int len = str.length();
		for (int i = 0; i < len - 1; i++)
		{
			if (str[i] == '(') ++balance;
			if (str[i] == ')') --balance;
			if (balance == 0) return false;
		}

		if (balance == 1) return true;
		return false;
	}

	int find_operation(string str)
	{
		int len = str.length();
		if (outer_brackets(str)) {
			return 1 + find_operation(str.substr(1, len - 2));
		}
		int min_pos = -1;
		int min_prioritet = 1000;
		int balance = 0;
		for (int i = len - 1; i >= 0; i--) 
		{
			if (str[i]== '(') ++balance;
			if (str[i] == ')') --balance;
			if ((is_operator(str[i])) && (balance == 0)) 
			{
				int prioritet = Prioritet(str[i]);
				if (prioritet < min_prioritet) 
				{
					min_prioritet = prioritet;
					min_pos = i;
					if (min_prioritet == 0) break;
				}
			}
		}
		return min_pos;
	}

public:
	static parser *expression()
	{
		static parser expr;
		return &expr;
	}

	component* parse_str(string str)
	{
		if (str == "") return new operand(0);
		if (outer_brackets(str)) return parse_str(str.substr(1, str.length() - 2));
		int operation_index = find_operation(str);
		if (operation_index == -1) return get_operand(str);
		string left_part = str.substr(0, operation_index);
		string right_part = str.substr(operation_index + 1);
		component *d = get_operation(str[operation_index]);
		d->attach(parse_str(left_part));
		d->attach(parse_str(right_part));
		return d;
	}
};

#endif;