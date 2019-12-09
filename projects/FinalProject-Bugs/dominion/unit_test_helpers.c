#include "dominion.h"
#include "unit_test_helpers.h"
#include <stdarg.h>
#include <stdio.h>

void assert(int condition, const char* message, ...)
{
    if(DEBUG || !condition)
    {
        char messageBuf[250];
        va_list args;
        va_start(args, message);
        vsnprintf(messageBuf, sizeof(messageBuf), message, args);
        va_end(args);

        if(!condition)
        {
            printf("FAILED - %s", messageBuf);
        }
        else
        {
            printf("DEBUG - %s", messageBuf);
        }
        
    }
}