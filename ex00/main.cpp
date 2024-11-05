#include "BitcoinExchange.hpp"
 
int main()
{
    BitcoinExchange btc;
    if (!btc.loadExchangeRates("data.csv"))
    {
        std::cerr << "Cannot read database" << std::endl;
        return 1;
    }

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        std::getline(ss, date, '|');
        std::getline(ss, valueStr);
        if (date == "")
        {
            std::cerr << "Error: bad input => no date" << std::endl;
            continue;
        }
        date = date.substr(0, date.find_last_not_of(" ") + 1);
        if (!btc.isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (valueStr == "")
        {
            std::cerr << "Error: bad input => no value" << std::endl;
            continue;
        }

        valueStr = valueStr.substr(valueStr.find_first_not_of(" "));

        float value = atof(valueStr.c_str());
        if (!btc.isValidValue(value))
        {
            if (value < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            if (value > 1000)
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        float rate = btc.getExchangeRate(date);
        std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << value * rate << std::endl;
    }
    inputFile.close();
    return 0;
}