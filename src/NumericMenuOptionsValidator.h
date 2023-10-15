#ifndef NUMERICMENUOPTIONSVALIDATOR_H
#define NUMERICMENUOPTIONSVALIDATOR_H

#include <iostream>
#include <string>
#include "NumericUtils.h"

using namespace std;

class NumericMenuOptionsValidator
{
    public:
        static bool validate(int numOptions, string option);
        static int getNumericOption(string option);
};

#endif // NUMERICMENUOPTIONSVALIDATOR_H
