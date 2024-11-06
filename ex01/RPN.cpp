#include "RPN.hpp"

bool RPN::isOperator(const char token)
{
    return token == '-' || token == '+' || token == '/' || token == '*'; 
}

int RPN::makeOperation(int val1, int val2, const char op)
{
    if(op == '+') return val1 + val2;
    if(op == '-') return val1 - val2;
    if(op == '*') return val1 * val2;
    if(op == '/')
    {
        if(val2 == 0)
            throw std::runtime_error("Error: Division by zero");
        return val1 / val2;
    }
    throw std::runtime_error("Error: Unknown operator");
}

int RPN::evaluate(std::string exp)
{
    std::deque<int> stack;
    std::istringstream ss(exp);
    char token;

    while(ss >> token)
    {
        if(std::isdigit(token))
            stack.push_back(token - '0');
        else if(isOperator(token))
        {
            if(stack.size() < 2)
                throw std::runtime_error("Error: Invalid expression");
            int val2 = stack.back();
            stack.pop_back();
            int val1 = stack.back();
            stack.pop_back();
            int result = makeOperation(val1, val2, token);
            stack.push_back(result);
        }
        else
            throw std::runtime_error("Error: Invalid token");
    }
    if(stack.size() != 1)
        throw std::runtime_error("Error: Invalid expression");
    return stack.back();
}

