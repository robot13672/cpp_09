#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _exchangeRates(copy._exchangeRates) {};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
    if(this != &copy)
        _exchangeRates = copy._exchangeRates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {};

bool BitcoinExchange::loadExchangeRates(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    std::string line;
    if(!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }

    while(std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        std::string rateStr;
        float rate;
        if (std::getline(ss, date, ',') && std::getline(ss, rateStr))
        {
            char *end;
            rate = std::strtof(rateStr.c_str(), &end);
            if(*end == '\0')
                _exchangeRates[date] = rate; 
        }
    }
    file.close();
    return true;
}

float BitcoinExchange::getExchangeRate(std::string date) const
{
    std::map<std::string, float>::const_iterator it = _exchangeRates.lower_bound(date);
    if(it == _exchangeRates.end() || it->first > date)
        if(it != _exchangeRates.begin())
            it--;
    return it->second;
}

bool BitcoinExchange::isValidDate(std::string &date) const
{
    int year, month, day;

    if (date.length() != 10 || date[4] != '-' || date[7] != '-') 
        return false;

    try 
    {
        year = std::atoi((date.substr(0, 4)).c_str());
        month = std::atoi((date.substr(5, 2)).c_str());
        day = std::atoi((date.substr(8, 2)).c_str()); 
    } 
    catch (...) 
    {
        return false; 
    }


    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) 
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
        return false;
    if (month == 2) 
    {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29 || (day == 29 && !isLeapYear)) 
            return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(float value) const
{
    return value >= 0.0f && value <= 1000.0f;
}

bool BitcoinExchange::isValidMapSize() const
{
    return _exchangeRates.size() > 0;
}