#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
    std::cout << "Copy constructor called" << std::endl;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other) 
    {
        std::cout << "Copy assignment operator called" << std::endl;
    }
    return *this;
}

void PmergeMe::printSequence(const std::string& message, const std::vector<int>& sequence) const 
{
    std::cout << message;
    for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printSequence(const std::string& message, const std::list<int>& sequence) const 
{
    std::cout << message;
    for (std::list<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sortWithVector(const std::vector<int>& input) 
{
    std::vector<int> sequence = input;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    mergeInsertSort(sequence);
    clock_gettime(CLOCK_MONOTONIC, &end);

    long long duration = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    printSequence("After (vector): ", sequence);
    std::cout << "Time to process with std::vector: " << duration << " ns" << std::endl;
}

void PmergeMe::sortWithList(const std::vector<int>& input) 
{
    std::list<int> sequence(input.begin(), input.end());
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    mergeInsertSort(sequence);
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long duration = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    printSequence("After (list): ", sequence);
    std::cout << "Time to process with std::list: " << duration << " ns" << std::endl;
}


void PmergeMe::mergeInsertSort(std::vector<int>& sequence) 
{
    if (sequence.size() <= 1) return;

    std::vector<int> left(sequence.begin(), sequence.begin() + sequence.size() / 2);
    std::vector<int> right(sequence.begin() + sequence.size() / 2, sequence.end());

    mergeInsertSort(left);
    mergeInsertSort(right);

    sequence.clear();
    std::vector<int>::iterator itL = left.begin();
    std::vector<int>::iterator itR = right.begin();
    while (itL != left.end() || itR != right.end()) 
    {
        if (itR == right.end() || (itL != left.end() && *itL < *itR)) 
        {
            sequence.push_back(*itL);
            ++itL;
        } 
        else 
        {
            sequence.push_back(*itR);
            ++itR;
        }
    }
}

void PmergeMe::mergeInsertSort(std::list<int>& sequence) 
{
    if (sequence.size() <= 1) return;

    std::list<int> left, right;
    std::list<int>::iterator it = sequence.begin();
    for (size_t i = 0; i < sequence.size() / 2; ++i, ++it) 
    {
        left.push_back(*it);
    }
    for (; it != sequence.end(); ++it) 
    {
        right.push_back(*it);
    }

    mergeInsertSort(left);
    mergeInsertSort(right);

    sequence.clear();
    std::list<int>::iterator itL = left.begin();
    std::list<int>::iterator itR = right.begin();
    while (itL != left.end() || itR != right.end()) 
    {
        if (itR == right.end() || (itL != left.end() && *itL < *itR)) 
        {
            sequence.push_back(*itL);
            ++itL;
        } 
        else 
        {
            sequence.push_back(*itR);
            ++itR;
        }
    }
}