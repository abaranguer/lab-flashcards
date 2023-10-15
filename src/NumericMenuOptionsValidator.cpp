#include "NumericMenuOptionsValidator.h"

bool NumericMenuOptionsValidator::validate(int numOptions, string option)
{
    /* validate int option between 1 to and numOptions. both included. */
    bool retValue = false;
    if (NumericUtils::isNumeric(option))
    {
        int numericOption = getNumericOption(option);

        if ((numericOption >= 1) && (numericOption <= numOptions))
        {
            retValue = true;
        }
    }

    return retValue;
}

int NumericMenuOptionsValidator::getNumericOption(string option)
{
    int numOption = stoi(option);

    return numOption;
}
