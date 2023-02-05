
#include "allFunctions.h"

int main()
{
    loadBusBookingDataIntoGlobalVariables();
    int whileIsTrue = 1;
    char userId[80];
    while(whileIsTrue)
    {
        if(whileIsTrue == 1)
        {
            whileIsTrue = showWelcomePage(userId);
        }
        else if(whileIsTrue == 2)
        {
            whileIsTrue = showRegistrationPage(userId);
        }
    }
    return 0;
}
