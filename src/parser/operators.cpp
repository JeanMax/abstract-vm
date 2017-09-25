// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   operators.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/25 15:35:02 by mc                #+#    #+#             //
//   Updated: 2017/09/24 21:35:13 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"
#include "../error/Error.template.hpp"

extern std::stack<IOperand const *> g_stack;

void do_assert(IOperand const *operand)
{
    if (!operand) {
        // WARNING("Assert: no operand");
        return;
    }

    if (g_stack.empty()) {
        delete operand;
        throw Error<std::invalid_argument>("Assert error: empty stack");
    }

    IOperand const *top = g_stack.top();

    if (top->getType() != operand->getType()) {
        delete operand;
        throw Error<std::runtime_error>("Assert error: types differ");
    }

    if (top->toString() != operand->toString()) {
        delete operand;
        throw Error<std::runtime_error>("Assert error: values differ");
    }

    delete operand;
}

void do_push(IOperand const *operand)
{
    if (!operand) {
        // WARNING("Push: no operand");
        return;
    }

    g_stack.push(operand);
}

void do_pop(IOperand const *operand)
{
    (void)operand;

    if (g_stack.empty())
        throw Error<std::invalid_argument>("Pop error: empty stack");

    delete g_stack.top();
    g_stack.pop();
}

void do_dump(IOperand const *operand)
{
    (void)operand;

    std::stack<IOperand const *> rev_stack = {};

    while (!g_stack.empty()) {
        MSG(g_stack.top()->toString() << std::endl);
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
        throw Error<std::invalid_argument>("Add error: empty stack");

    IOperand const *rhs = g_stack.top();
    g_stack.pop();
    if (g_stack.empty()) {
        delete rhs;
        throw Error<std::invalid_argument>("Add error: only one value in stack");
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
        throw Error<std::invalid_argument>("Substract error: empty stack");

    IOperand const *rhs = g_stack.top();
    g_stack.pop();
    if (g_stack.empty()) {
        delete rhs;
        throw Error<std::invalid_argument>("Substract error: only one value in stack");
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
        throw Error<std::invalid_argument>("Multiply error: empty stack");

    IOperand const *rhs = g_stack.top();
    g_stack.pop();
    if (g_stack.empty()) {
        delete rhs;
        throw Error<std::invalid_argument>("Multiply error: only one value in stack");
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
        throw Error<std::invalid_argument>("Divide error: empty stack");

    IOperand const *rhs = g_stack.top();
    g_stack.pop();
    if (g_stack.empty()) {
        delete rhs;
        throw Error<std::invalid_argument>("Divide error: only one value in stack");
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
        throw Error<std::invalid_argument>("Mod error: empty stack");

    IOperand const *rhs = g_stack.top();
    g_stack.pop();
    if (g_stack.empty()) {
        delete rhs;
        throw Error<std::invalid_argument>("Mod error: only one value in stack");
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
        throw Error<std::invalid_argument>("Print error: empty stack");

    IOperand const *top = g_stack.top();

    if (top->getType() != Int8)
        throw Error<std::invalid_argument>("Print error: not an int8");

    MSG(static_cast<char>(std::stoi(top->toString())));
}

void do_exit(IOperand const *operand)
{
    (void)operand;

    kthxbye(EXIT_SUCCESS);
}
