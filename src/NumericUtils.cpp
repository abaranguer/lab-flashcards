#include "NumericUtils.h"

bool NumericUtils::isNumeric(string option)
{
    string::const_iterator it = option.begin();

    while (it != option.end() && isdigit(*it)) ++it;

    return !option.empty() && (it == option.end());
}
