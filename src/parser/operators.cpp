// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   operators.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/25 15:35:02 by mc                #+#    #+#             //
//   Updated: 2017/09/20 23:44:17 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"
#include "../error/Error.template.hpp"

extern std::stack<IOperand const *> g_stack;

void do_assert(IOperand const *operand)
{
	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *top = g_stack.top();

	if (top->getType() != operand->getType())
		kthxbye(EXIT_FAILURE); //TODO

	if (top->toString() != operand->toString())
		kthxbye(EXIT_FAILURE); //TODO

	delete operand;
}

void do_push(IOperand const *operand)
{
	g_stack.push(operand);
}

void do_pop(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	delete g_stack.top();
	g_stack.pop();
}

void do_dump(IOperand const *operand)
{
	(void)operand;

    std::stack<IOperand const *> rev_stack = {};

    while (!g_stack.empty()) {
		MSG(g_stack.top()->toString());
        rev_stack.push(g_stack.top());
        g_stack.pop();
    }

    while (!rev_stack.empty()) {
        g_stack.push(rev_stack.top());
        rev_stack.pop();
    }

}

void do_add(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *rhs = g_stack.top();
	g_stack.pop();
	if (g_stack.empty()) {
		delete rhs;
		kthxbye(EXIT_FAILURE); //TODO
	}

	IOperand const *lhs = g_stack.top();
	g_stack.pop();

	g_stack.push(*lhs + *rhs);
	delete lhs;
	delete rhs;
}

void do_sub(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *rhs = g_stack.top();
	g_stack.pop();
	if (g_stack.empty()) {
		delete rhs;
		kthxbye(EXIT_FAILURE); //TODO
	}

	IOperand const *lhs = g_stack.top();
	g_stack.pop();

	g_stack.push(*lhs - *rhs);
	delete lhs;
	delete rhs;
}

void do_mul(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *rhs = g_stack.top();
	g_stack.pop();
	if (g_stack.empty()) {
		delete rhs;
		kthxbye(EXIT_FAILURE); //TODO
	}

	IOperand const *lhs = g_stack.top();
	g_stack.pop();

	g_stack.push(*lhs * *rhs);
	delete lhs;
	delete rhs;
}

void do_div(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *rhs = g_stack.top();
	g_stack.pop();
	if (g_stack.empty()) {
		delete rhs;
		kthxbye(EXIT_FAILURE); //TODO
	}

	IOperand const *lhs = g_stack.top();
	g_stack.pop();

    try {
        g_stack.push(*lhs / *rhs);
    } catch (Error<std::domain_error> const &e) {
        WARNING(e.what());
    }

	delete lhs;
	delete rhs;
}

void do_mod(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *rhs = g_stack.top();
	g_stack.pop();
	if (g_stack.empty()) {
		delete rhs;
		kthxbye(EXIT_FAILURE); //TODO
	}

	IOperand const *lhs = g_stack.top();
	g_stack.pop();

    try {
        g_stack.push(*lhs % *rhs);
    } catch (Error<std::domain_error> const &e) {
        WARNING(e.what());
    }

	delete lhs;
	delete rhs;
}

void do_print(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		kthxbye(EXIT_FAILURE); //TODO

	IOperand const *top = g_stack.top();

	if (top->getType() != Int8)
		kthxbye(EXIT_FAILURE); //TODO

	MSG(static_cast<char>(std::stoi(top->toString())));
}

void do_exit(IOperand const *operand)
{
	(void)operand;

	kthxbye(EXIT_SUCCESS);
}
