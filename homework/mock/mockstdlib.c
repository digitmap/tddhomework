#ifdef __TDD_TEST__

#include "mockstdlib.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"

#include "strRecv.h"

/* mock��stdin�豸������󳤶ȴ�һ�������������û������ַ�����ϵͳ��Ƴ��ȵ���� */
#define MAX_STDIN_STRLEN    MAX_RCV_STRLEN*2
static char mock_RecvBuffer[MAX_STDIN_STRLEN];

static int readCount = 0;
int mock_gets(void)
{
/*    memcpy(rcvBuffer, mock_RecvBuffer, strlen(mock_RecvBuffer));*/
    int c = -2;
    c = mock_RecvBuffer[readCount++];
    if(c == '\n')
    {
        readCount = 0;
        memset(mock_RecvBuffer, 0, MAX_STDIN_STRLEN);
    }
    return c;
}

void mock_UserInputString(char *inputString)
{
    int inputStrLen = strlen(inputString);
    memset(mock_RecvBuffer, 0, MAX_STDIN_STRLEN);
    memcpy(mock_RecvBuffer, inputString, inputStrLen);
    *(mock_RecvBuffer + inputStrLen) = '\n';

}

int mock_printf(const char * outstring, ...)
{
    char * tmpOutString = NULL;
    tmpOutString = GetOutPutStringAddress();
    memset(tmpOutString, 0, MAX_RCV_STRLEN);
    memcpy(tmpOutString, outstring, strlen(outstring));
    return 1; /* ��Ϊ�����������澯 */
}

void    mock_CleanReadCount(void)
{
    readCount = 0;
}
#endif /* __TDD_TEST__ */