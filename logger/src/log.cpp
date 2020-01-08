#include "log.h"

Log &operator<<(std::shared_ptr<Log> logger, std::string str)
{
    std::cout << " string " << std::endl;
    return *logger << str;
}

Log &operator<<(std::shared_ptr<Log> logger, int value)
{
    std::cout << " int " << std::endl;
    return *logger << value;
}

Log &operator<<(std::shared_ptr<Log> logger, typelog /*type*/)
{
    std::cout << " typelog " << std::endl;
    return *logger;
}
