#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <iomanip>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _exchangeRates;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &copy);
        ~BitcoinExchange();

        bool loadExchangeRates(std::string fileName);
        float getExchangeRate(std::string date) const;
        bool isValidDate(std::string &date) const;
        bool isValidValue(float value) const;
        bool isValidMapSize() const;
};

#endif