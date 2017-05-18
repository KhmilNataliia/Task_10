#include"parser.h"
#include"component.h"

class calc
{
	static calc *expr;
	parser *Parser;
	calc()
	{
		Parser = parser::expression();
	}
public:
	static calc expression()
	{
		if (!expr) expr = new calc();
		return *expr;
	}
	double do_calc(string str)
	{
		component *source = Parser->parse_str(str);
		return source->getVal();
	}
};

calc *calc::expr = NULL;