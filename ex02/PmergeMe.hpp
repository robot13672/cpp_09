#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>

class PmergeMe 
{
    public:
        PmergeMe();
        ~PmergeMe();

        void sortWithVector(const std::vector<int>& input);
        void sortWithList(const std::vector<int>& input);

        void printSequence(const std::string& message, const std::vector<int>& sequence) const;
        void printSequence(const std::string& message, const std::list<int>& sequence) const;

        void mergeInsertSort(std::vector<int>& sequence);
        void mergeInsertSort(std::list<int>& sequence);
};

#endif