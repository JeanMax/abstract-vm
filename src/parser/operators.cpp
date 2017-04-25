// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   operators.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/25 15:35:02 by mc                #+#    #+#             //
//   Updated: 2017/04/25 16:17:09 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"

// extern OperandFactory const *g_factory;
std::forward_list<IOperand const *> g_stack = {};

void do_assert(IOperand const *operand)
{
	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *front = g_stack.front();

	if (front->getType() != operand->getType())
		exit(43); //TODO

	if (front->toString() != operand->toString())
		exit(44); //TODO

	delete operand;
}

void do_push(IOperand const *operand)
{
	g_stack.push_front(operand);
}

void do_pop(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	delete g_stack.front();
	g_stack.pop_front();
}

void do_dump(IOperand const *operand)
{
	(void)operand;

	for (IOperand const *op : g_stack) {
		std::cout << op->toString() << std::endl;
	}
}

void do_add(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *lhs = g_stack.front();
	g_stack.pop_front();
	if (g_stack.empty())
		exit(43); //TODO

	IOperand const *rhs = g_stack.front();
	g_stack.pop_front();

	g_stack.push_front(*lhs + *rhs);
	delete lhs;
	delete rhs;
}

void do_sub(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *lhs = g_stack.front();
	g_stack.pop_front();
	if (g_stack.empty())
		exit(43); //TODO

	IOperand const *rhs = g_stack.front();
	g_stack.pop_front();

	g_stack.push_front(*lhs - *rhs);
	delete lhs;
	delete rhs;
}

void do_mul(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *lhs = g_stack.front();
	g_stack.pop_front();
	if (g_stack.empty())
		exit(43); //TODO

	IOperand const *rhs = g_stack.front();
	g_stack.pop_front();

	g_stack.push_front(*lhs * *rhs);
	delete lhs;
	delete rhs;
}

void do_div(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *lhs = g_stack.front();
	g_stack.pop_front();
	if (g_stack.empty())
		exit(43); //TODO

	IOperand const *rhs = g_stack.front();
	g_stack.pop_front();

	g_stack.push_front(*lhs / *rhs);
	delete lhs;
	delete rhs;
}

void do_mod(IOperand const *operand)
{
	(void)operand;

	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *lhs = g_stack.front();
	g_stack.pop_front();
	if (g_stack.empty())
		exit(43); //TODO

	IOperand const *rhs = g_stack.front();
	g_stack.pop_front();

	g_stack.push_front(*lhs % *rhs);
	delete lhs;
	delete rhs;
}

void do_print(IOperand const *operand)
{
	if (g_stack.empty())
		exit(42); //TODO

	IOperand const *front = g_stack.front();

	if (front->getType() != Int8)
		exit(43); //TODO

	std::cout << static_cast<char>(std::stoi(front->toString())) << std::endl;

	(void)operand;
}

void do_exit(IOperand const *operand)
{
	(void)operand;

	exit(0); //TODO
}
