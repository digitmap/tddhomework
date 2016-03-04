#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "strRecv.h"
#include "assert.h"
#define NOT_ALL_CHARS_ARE_LEGAL 1
#define ALL_CHARS_ARE_LEGAL 2

#define VALIDITY_IS_NOT_OK 1
#define VALIDITY_IS_OK 2

#define LAST_SYMBOL_IS_EQUALSYMBOL 1
#define LAST_SYMBOL_IS_NOT_EQUALSYMBOL 2

#define LENGTH_OF_INPUT_STR_IS_NOT_EXCEEDED 1
#define LENGTH_OF_INPUT_STR_IS_EXCEEDED 2

#define FUN_RUN_SUCCESS 1
#define FUN_RUN_FAIL 2

#define CHAR_CONVERT_INT(ch) (ch - 48)
#define INT_CONVERT_CHAR(ch) (ch + 48)

#define LOWPLUS_STEP_HIGHPLUS  1
#define LOWPLUS_NOSTEP_HIGHPLUS  0

static void * ReceiveStringAddr = NULL;
static void * OutPutStringAddr = NULL;
static int applcationStaus = -1;
static int (*clib_getchar)(void) = NULL;
static int (*clib_printf)(const char*, ...) = NULL;
static char ValidChar[] = {'0','1','2','3','4','5','6','7','8','9',\
                           ' ', '+','-','*','='};
static char operandDim[MAX_RCV_STRLEN/2][MAX_RCV_STRLEN];
static char operatorDim[MAX_RCV_STRLEN/2];
static char plusOutPutBuff[MAX_PLUS_STRING_OF_INPUT + 1] = {0};
static char multiOutPutBuff[MAX_PLUS_STRING_OF_INPUT*2] = {0};
static char tmpMultiStr[MAX_PLUS_STRING_OF_INPUT*2] = {0};
static char tmpLongStr[MAX_PLUS_STRING_OF_INPUT*2] = {0};

static int gloableErrorCode = NO_ERROR;
static int previous_Operator = PREV_OPERATOR;
static int previous_Char = PREV_CHAR_SPACE;
static int next_Expect_Char_Digit = NEXT_IS_EXPECTED;
static int next_Expect_Char_Space = NEXT_IS_EXPECTED;
static int next_Expect_Char_Plus = NEXT_IS_EXPECTED;
static int next_Expect_Char_Minus = NEXT_IS_EXPECTED;
static int next_Expect_Char_Multi = NEXT_IS_EXPECTED;
static int operandOneIndex = 0;
static int operandTwoIndex = 0;
static int operatorOneIndex = 0;

static void CalculateStringFormula(char*);
static void DoInputOfExit(char*);
static int ValidityCheckInputString(char*);
static int RecvCharsAreLegal(char* RecvString);
static int LastCharMustBeEqualSymbol(char* RecvString);
static void FlagInitial(void);
static int HandleDigit(char);
static int HandleSpace(char);
static int HandlePlus(char);
static int HandleMinus(char);
static int HandleMulti(char);
void AllocateMemory(void)
{
    ReceiveStringAddr = malloc(MAX_RCV_STRLEN);
    OutPutStringAddr = malloc(MAX_RCV_STRLEN);
    
    memset(ReceiveStringAddr, 0, MAX_RCV_STRLEN);
    memset(OutPutStringAddr, 0, MAX_RCV_STRLEN);
}

char *GetReceiveStringAddress()
{
    return ReceiveStringAddr;
}

char *GetOutPutStringAddress()
{
    return OutPutStringAddr;
}

void OperatorInit(void)
{
    AllocateMemory();
    CommApiInit();
    SetFuncGets(getchar);
    SetFuncPrintf(printf);
    SetStatusOfApplication(APP_IS_IN_WORKING_STATUS);
}

int (*GetFuncgets(void))(void)
{
    return clib_getchar;
}

void SetFuncGets(int (*FuncGets)(void))
{
    clib_getchar = FuncGets;
}

int (*GetFuncPrintf(void))(const char*, ...)
{
    return clib_printf;
}

void SetFuncPrintf(int(*FuncPrintf)(const char*, ...))
{
    clib_printf = FuncPrintf;
}
int RecvStringFromInputDeviceJustOnce()
{
    int c;
    int looprecvCount = 0;
    memset(ReceiveStringAddr, 0, MAX_RCV_STRLEN);
    while((c = clib_getchar()) != '\n' && c != EOF)
    {
        *((char*)ReceiveStringAddr + looprecvCount) = c;
        looprecvCount ++;
        if(MAX_RCV_STRLEN <= looprecvCount)
        {
            OutPutBuffer(OPERAND_LENGTH_EXCEED_STRING);
            return INPUT_LENGTH_IS_EXCEEDED;
        }
    }
        *((char*)ReceiveStringAddr + looprecvCount) = 0;
        return NO_ERROR;
}


char *GetUserInputBuffer(void)
{
    return ReceiveStringAddr;
}



void HandleUserInput(void)
{
    char * tmpRecvString = NULL;
    tmpRecvString = GetReceiveStringAddress();
    if( 0 == memcmp("help", tmpRecvString,strlen("help")))
    {
        OutPutBuffer(HELP_STRING);
        return;
    }
    if( 0 == memcmp("quit", tmpRecvString,strlen("quit")))
    {
        OutPutBuffer(QUIT_STRING);
        SetStatusOfApplication(APP_IS_IN_EXIT_STATUS);
        return;
    }
    if(NOT_ALL_CHARS_ARE_LEGAL == ValidityCheckInputString(tmpRecvString))
    {
        return;
    }
    CalculateStringFormula(tmpRecvString);
}

int GetStatusOfApplication(void)
{
    return applcationStaus;
}

void SetStatusOfApplication(int appStatus)
{
    applcationStaus = appStatus;
}


static void DoInputOfExit(char* tmpRecvString)
{
    if( 0 == memcmp("quit", tmpRecvString,strlen("quit")))
    {
        OutPutBuffer(QUIT_STRING);
        SetStatusOfApplication(APP_IS_IN_EXIT_STATUS);
    }
}

static void CalculateStringFormula(char* tmpRecvString)
{
    int oLoop;
    int movLoop;
    char* tmpMulti;
    int anayLen;
    anayLen = AnalysisString(tmpRecvString);

    if(0 == anayLen)
        return;
    

    for(oLoop = 0; oLoop < anayLen; oLoop++)
    {
        if(0 == operatorDim[oLoop])
            break;
        if('*' == operatorDim[oLoop])
        {
            tmpMulti = MultiOperate(operandDim[oLoop], operandDim[oLoop+1]);
            memcpy(operandDim[oLoop], tmpMulti, strlen(tmpMulti));
            for(movLoop = 0; movLoop < anayLen - oLoop; movLoop++)
            {
                memset(operandDim[oLoop + 1 + movLoop], 0, strlen(operandDim[oLoop + 1 + movLoop]));
                memcpy(operandDim[oLoop + 1 + movLoop],
                    operandDim[oLoop + 2 + movLoop],
                    strlen(operandDim[oLoop + 2 + movLoop]));
                operatorDim[oLoop + movLoop] = operatorDim[oLoop + 1 +movLoop];
                operatorDim[oLoop + 1 +movLoop] = 0;
            }
            oLoop = oLoop - 1;
        }
    }

    memset(tmpLongStr, 0, MAX_PLUS_STRING_OF_INPUT*2);
    *tmpLongStr = '0';
    
    for(oLoop = 0; oLoop <= strlen(operatorDim); oLoop++)
    {
        tmpMulti = PlusOperate(tmpLongStr, operandDim[oLoop]);
        memcpy(tmpLongStr, tmpMulti, strlen(tmpMulti));
    }
    *(tmpLongStr + strlen(tmpLongStr)) = '\n';
    OutPutBuffer(tmpLongStr);
}

static int ValidityCheckInputString(char* tmpRecvString)
{

    if(NOT_ALL_CHARS_ARE_LEGAL == RecvCharsAreLegal(tmpRecvString))
    {
        OutPutBuffer(OPERAND_IS_ILLEGAL_STRING);
        return VALIDITY_IS_NOT_OK;
    }

    if(LAST_SYMBOL_IS_NOT_EQUALSYMBOL == LastCharMustBeEqualSymbol(tmpRecvString))
    {
        clib_printf(LAST_CHAR_MUST_BE_EQUAL_STRING);
        return VALIDITY_IS_NOT_OK;
    }

    return VALIDITY_IS_OK;
}

static int RecvCharsAreLegal(char* RecvString)
{
    int tmpIllegal = NOT_ALL_CHARS_ARE_LEGAL;
    unsigned int stringloopCount = 0;
    unsigned int validcharloopCount = 0;
    char recvStringValue = 0;
    for (stringloopCount = 0; stringloopCount < strlen(RecvString); stringloopCount++)
    {
        recvStringValue = *(RecvString + stringloopCount);
        for(validcharloopCount = 0; validcharloopCount < strlen(ValidChar); validcharloopCount++)
        {
            tmpIllegal = NOT_ALL_CHARS_ARE_LEGAL;
            if(recvStringValue == *(ValidChar + validcharloopCount))
            {
                tmpIllegal = ALL_CHARS_ARE_LEGAL;
                break;/* 如果相等，跳出小循环 */
            }
        }
        if(NOT_ALL_CHARS_ARE_LEGAL == tmpIllegal)
            break;
    }
    return tmpIllegal;
}

static int LastCharMustBeEqualSymbol(char* RecvString)
{
    int RecvLen = strlen(RecvString);
    if(0 == strcmp("=", RecvString + RecvLen - 1))
    {
        return LAST_SYMBOL_IS_EQUALSYMBOL;
    }
    return LAST_SYMBOL_IS_NOT_EQUALSYMBOL;
}



int OutPutBuffer(char* outBuffer)
{
    clib_printf(outBuffer);
    return FUN_RUN_SUCCESS;
}


char* MultiOperate(char* operator1, char* operator2)
{
    int LengthOfShortOper = 0;
    int LengthOfLongOper = 0;
    int tmpLen = 0;
    char *longOper = NULL;
    char *shortOper = NULL;
    int longLoop = 0;
    int shortLoop = 0;
    char singleMulti = 0;
    int singleMultiLoop = 0;
    char* plusPtr;
    memset(multiOutPutBuff, 0, strlen(multiOutPutBuff));
    memset(tmpMultiStr, 0, strlen(tmpMultiStr));
    memset(tmpLongStr, 0, strlen(tmpLongStr));

    multiOutPutBuff[0] = '0';
    shortOper = operator1;
    longOper = operator2;
    LengthOfShortOper = strlen(operator1);
    LengthOfLongOper = strlen(operator2);

    if(LengthOfShortOper > LengthOfLongOper)
    {
        shortOper = operator2;
        longOper = operator1;
        tmpLen = LengthOfShortOper;
        LengthOfShortOper = LengthOfLongOper;
        LengthOfLongOper = tmpLen;
    }


    memcpy(tmpMultiStr, longOper, LengthOfLongOper);
    for(shortLoop = 0; shortLoop < LengthOfShortOper; shortLoop++)
    {
        memcpy(tmpLongStr,longOper,LengthOfLongOper);
        memset(tmpLongStr + LengthOfLongOper, '0', shortLoop);
        memcpy(tmpMultiStr, tmpLongStr, strlen(tmpLongStr));
        singleMulti = CHAR_CONVERT_INT(*(shortOper + LengthOfShortOper - 1 - shortLoop));
        if(0 == singleMulti)
            continue;
        for(singleMultiLoop = 0; singleMultiLoop < singleMulti - 1; singleMultiLoop++)
        {
            plusPtr = PlusOperate(tmpMultiStr, tmpLongStr);
            memcpy(tmpMultiStr, plusPtr, strlen(plusPtr));
        }
        plusPtr = PlusOperate(multiOutPutBuff, tmpMultiStr);
        memcpy(multiOutPutBuff , plusPtr, strlen(plusPtr));
        memset(tmpMultiStr, 0, strlen(tmpMultiStr));
    }

    return multiOutPutBuff;
}

char* PlusOperate(char* operator1, char* operator2)
{
    int LengthOfShortOper = 0;
    int LengthOfLongOper = 0;
    int tmpLen = 0;
    char *longOper = NULL;
    char *shortOper = NULL;
    int longLoop = 0;
    int shortLoop = 0;
    int stepSymbol = LOWPLUS_NOSTEP_HIGHPLUS;
    int singleOutCome = 0;
    char shortChar = '#';
    char longChar = '#';
    
    shortOper = operator1;
    longOper = operator2;
    LengthOfShortOper = strlen(operator1);
    LengthOfLongOper = strlen(operator2);
    if(MAX_PLUS_STRING_OF_INPUT < LengthOfShortOper || MAX_PLUS_STRING_OF_INPUT < LengthOfLongOper)
    {
        OutPutBuffer(PLUS_OPERATOR_IS_EXCEEDED);
        return NULL;
    }
    plusOutPutBuff[0] = '0';
    memset(plusOutPutBuff + 1, 0, strlen(plusOutPutBuff) - 1);
    if(LengthOfShortOper > LengthOfLongOper)
    {
        shortOper = operator2;
        longOper = operator1;
        tmpLen = LengthOfShortOper;
        LengthOfShortOper = LengthOfLongOper;
        LengthOfLongOper = tmpLen;
    }
    
    for(shortLoop = 0; shortLoop < LengthOfShortOper; shortLoop++)
    {
        shortChar = *(shortOper + LengthOfShortOper - shortLoop - 1 );
        longChar = *(longOper + LengthOfLongOper - shortLoop - 1);
        singleOutCome = CHAR_CONVERT_INT(shortChar) + CHAR_CONVERT_INT(longChar) + stepSymbol;
        if(10 <= singleOutCome)
        {
            singleOutCome = singleOutCome - 10;
            stepSymbol = LOWPLUS_STEP_HIGHPLUS;
        }
        else
        {
            stepSymbol = LOWPLUS_NOSTEP_HIGHPLUS;
        }
        plusOutPutBuff[LengthOfLongOper-shortLoop] = INT_CONVERT_CHAR(singleOutCome);
    }

    for(longLoop = 0; longLoop < (LengthOfLongOper  - LengthOfShortOper); longLoop++)
    {
        shortChar = 0;
        longChar = *(longOper + LengthOfLongOper - longLoop - 1 - shortLoop);
        singleOutCome = CHAR_CONVERT_INT(longChar) + stepSymbol;
        if(10 <= singleOutCome)
        {
            singleOutCome = singleOutCome - 10;
            stepSymbol = LOWPLUS_STEP_HIGHPLUS;
        }
        else
        {
            stepSymbol = LOWPLUS_NOSTEP_HIGHPLUS;
        }
        plusOutPutBuff[LengthOfLongOper -longLoop - shortLoop] = INT_CONVERT_CHAR(singleOutCome);
    }
    if(LOWPLUS_STEP_HIGHPLUS == stepSymbol)
    {
        plusOutPutBuff[0] = '1';
    }
    if('0' == plusOutPutBuff[0])
    {
        memcpy(plusOutPutBuff, plusOutPutBuff + 1, LengthOfLongOper);
        plusOutPutBuff[LengthOfLongOper] = 0;
    }
    return plusOutPutBuff;
}

int GetErrorCode(void)
{
    return gloableErrorCode;
}

void SetErrorCode(int errorNumber)
{
    gloableErrorCode = errorNumber;
}

int CharIsDigital(char ch)
{
    int digitalLoop;
    char digitChar[] = {'0','1','2','3','4','5','6','7','8','9'}; 
    for(digitalLoop = 0; digitalLoop < sizeof(digitChar); digitalLoop++)
    {
        if(ch == digitChar[digitalLoop])
            return IS_DIGITAL;
    }
    return IS_NOT_DIGITAL;
}



int GetOperatorDimSize(void)
{
    int dimSize = 0;
    dimSize = sizeof(operatorDim);
    return dimSize;
}

int GetOperandDimSize(void)
{
    int dimSize = 0;
    dimSize = sizeof(operandDim)/sizeof(operandDim[0]);
    return dimSize;
}

char* GetOperatorDimAddr(void)
{
    return (char*)operatorDim;
}

char* GetOperandDimAddr(void)
{
    return (char*)operandDim;
}


void SetOperatorFirstDimValue(char ch)
{
    memset(operatorDim, ch, MAX_RCV_STRLEN);
}

void SetOperandFirstDimValue(char ch)
{
    memset(operandDim, ch, MAX_RCV_STRLEN);
}

void CommApiInit(void)
{
    memset(operandDim, 0, sizeof(operandDim));
    memset(operatorDim, 0, sizeof(operatorDim));
    FlagInitial();
    operandOneIndex = 0;
    operandTwoIndex = 0;
    operatorOneIndex = 0;
}

void SetPreviousOper(int pre_Oper)
{
    previous_Operator = pre_Oper;
}

int GetPreviousOper(void)
{
    return previous_Operator;
}

void SetPreviousChar(int pre_Char)
{
    previous_Char = pre_Char;
}

int GetPreviousChar(void)
{
    return previous_Char;
}

void SetNextExpectDigit(int next)
{
    next_Expect_Char_Digit = next;
}

int  GetNextExpectDigit(void)
{
    return next_Expect_Char_Digit;
}
void SetNextExpectSpace(int next)
{
    next_Expect_Char_Space = next;
}

int  GetNextExpectSpace(void)
{
    return next_Expect_Char_Space;
}
void SetNextExpectPlus(int next)
{
    next_Expect_Char_Plus = next;
}

int  GetNextExpectPlus(void)
{
    return next_Expect_Char_Plus;
}
void SetNextExpectMinus(int next)
{
    next_Expect_Char_Minus = next;
}

int  GetNextExpectMinus(void)
{
    return next_Expect_Char_Minus;
}
void SetNextExpectMulti(int next)
{
    next_Expect_Char_Multi = next;
}

int  GetNextExpectMulti(void)
{
    return next_Expect_Char_Multi;
}
static void FlagInitial(void)
{
    SetPreviousOper(PREV_OPERATOR);
    SetPreviousChar(PREV_CHAR_SPACE);
    SetNextExpectDigit(NEXT_IS_EXPECTED);
    SetNextExpectSpace(NEXT_IS_NOT_EXPECTED);
    SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
    SetNextExpectMinus(NEXT_IS_NOT_EXPECTED);
    SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
}

int AnalysisString(char* recvStr)
{
    int strLoop = 0;
    int rcvStrLen = strlen(recvStr);
    char currentchar;
    int handleIsOk = FUN_RUN_SUCCESS;
    CommApiInit();
    for(strLoop = 0; strLoop < rcvStrLen; strLoop++)
    {
        currentchar = *(recvStr + strLoop);
        if(IS_DIGITAL == CharIsDigital(currentchar))
        {
            handleIsOk = HandleDigit(currentchar);
        }
        else if(' ' == currentchar)
        {
            handleIsOk = HandleSpace(currentchar);
        }
        else if('+' == currentchar)
        {
            handleIsOk = HandlePlus(currentchar);
        }
        else if('-' == currentchar)
        {
            handleIsOk = HandleMinus(currentchar);
        }
        else if('*' == currentchar)
        {
            handleIsOk = HandleMulti(currentchar);
        }
    }
        if(FUN_RUN_FAIL == handleIsOk)
        {
            OutPutBuffer("Input is illegal!\n");
            CommApiInit();
            return 0;
        }
        else
        {
            return strlen(operatorDim);
        }
}

static int HandleDigit(char ch)
{
    int runflag = FUN_RUN_SUCCESS;
    if(NEXT_IS_EXPECTED == GetNextExpectDigit())
    {
        if(PREV_CHAR_SPACE == GetPreviousChar() ||
            PREV_CHAR_DIGITAL == GetPreviousChar()||
            PREV_CHAR_MINUS == GetPreviousChar())
        {
            operandDim[operandOneIndex][operandTwoIndex] = ch;
            operandTwoIndex++;
            SetNextExpectDigit(NEXT_IS_EXPECTED);
            SetNextExpectSpace(NEXT_IS_EXPECTED);
            SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
            SetNextExpectMinus(NEXT_IS_NOT_EXPECTED);
            SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
            SetPreviousChar(PREV_CHAR_DIGITAL);
        }
        else
        {
            /* 应该是碰到了+或者* */
            runflag = FUN_RUN_FAIL;
        }
    }
    else
    {
        runflag = FUN_RUN_FAIL;
    }
    return runflag;
}

static int HandleSpace(char ch)
{
    int runflag = FUN_RUN_SUCCESS;
    if(NEXT_IS_EXPECTED == GetNextExpectSpace())
    {
        if(PREV_CHAR_DIGITAL == GetPreviousChar())
        {
            operandDim[operandOneIndex][operandTwoIndex] = 0;//不加可能也无碍
            operandOneIndex++;
            operandTwoIndex = 0;
            SetNextExpectMinus(NEXT_IS_EXPECTED);
            SetNextExpectPlus(NEXT_IS_EXPECTED);
            SetNextExpectMulti(NEXT_IS_EXPECTED);
            SetPreviousChar(PREV_CHAR_SPACE);
            SetPreviousOper(PREV_OPERAND);
        }
        else
        {
            if(PREV_CHAR_SPACE == GetPreviousChar())
            {
                runflag = FUN_RUN_FAIL;
            }
            else
            {
                operatorDim[operatorOneIndex] = GetPreviousChar();
                operatorOneIndex++;
                SetNextExpectMinus(NEXT_IS_EXPECTED);
                SetNextExpectDigit(NEXT_IS_EXPECTED);
                SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
                SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
                SetNextExpectSpace(NEXT_IS_NOT_EXPECTED);
                SetPreviousChar(PREV_CHAR_SPACE);
                SetPreviousOper(PREV_OPERATOR);
            }
        }
    }
    else
    {
        runflag = FUN_RUN_FAIL;
    }
    return runflag;
}

static int HandlePlus(char ch)
{
    int runflag = FUN_RUN_SUCCESS;
    if(NEXT_IS_EXPECTED == GetNextExpectPlus())
    {
        SetPreviousChar(PREV_CHAR_PLUS);
        SetNextExpectMinus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectDigit(NEXT_IS_NOT_EXPECTED);
        SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
        SetNextExpectSpace(NEXT_IS_EXPECTED);
    }
    else
    {
        runflag = FUN_RUN_FAIL;
    }
    return runflag;
}

static int HandleMinus(char ch)
{
    int runflag = FUN_RUN_SUCCESS;
    if(NEXT_IS_EXPECTED == GetNextExpectMinus())
    {
        SetPreviousChar(PREV_CHAR_MINUS);
        SetNextExpectMinus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectDigit(NEXT_IS_NOT_EXPECTED);
        SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
        SetNextExpectSpace(NEXT_IS_EXPECTED);
    }
    else
    {
        runflag = FUN_RUN_FAIL;
    }
    return runflag;
}

static int HandleMulti(char ch)
{
    int runflag = FUN_RUN_SUCCESS;
    if(NEXT_IS_EXPECTED == GetNextExpectMulti())
    {
        SetPreviousChar(PREV_CHAR_MULTI);
        SetNextExpectMinus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectDigit(NEXT_IS_NOT_EXPECTED);
        SetNextExpectPlus(NEXT_IS_NOT_EXPECTED);
        SetNextExpectMulti(NEXT_IS_NOT_EXPECTED);
        SetNextExpectSpace(NEXT_IS_EXPECTED);
    }
    else
    {
        runflag = FUN_RUN_FAIL;
    }
    return runflag;
}
