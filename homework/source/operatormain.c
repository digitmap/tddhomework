#ifndef __TDD_TEST__

#include "strRecv.h"

int main(int argc, char* argv[])
{
    OperatorInit();
    OutPutBuffer(BANNER_STRING);
    while(1)
    {
        RecvStringFromInputDeviceJustOnce();
        HandleUserInput();
        if(APP_IS_IN_EXIT_STATUS == GetStatusOfApplication())
        {
            break;
        }
    }
	return 0;
}

#endif /* end of __TDD_TEST__ */