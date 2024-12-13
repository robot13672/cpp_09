#include "PmergeMe.hpp"

int main(int argc, char** argv) 
{
    if (argc < 2) 
    {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    try 
    {
        std::vector<int> input;
        for (int i = 1; i < argc; ++i) 
        {
            std::istringstream iss(argv[i]);
            int num;
            if (!(iss >> num) || num < 0) 
            {
                throw std::invalid_argument("Invalid input");
            }
            input.push_back(num);
        }

        PmergeMe sorter;
        sorter.printSequence("Before: ", input);
        sorter.sortWithVector(input);
        sorter.sortWithList(input);
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}