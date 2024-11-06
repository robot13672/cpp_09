#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <string>

class RPN
{
    public:
        static int evaluate(const std::string exp);
    private:
        static bool isOperator(const char token);
        static int makeOperation(int val1, int val2, const char op);
};

#endif