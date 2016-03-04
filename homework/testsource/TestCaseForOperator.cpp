#ifdef __TDD_TEST__
/*
    c10c 动态申请MAX_RCV_STRLEN个字节的内存（ReceiveStringAddress），用
          来存放用户输入的字符串，并且初始值为0。                               OK      
    c13c 动态申请MAX_RCV_STRLEN个字节的内存（OutPutStringAddress），用
          来存放用户输出的字符串，并且初始值为0。                               OK      
    c15c 初化之后，应用进程为工作状态。                                         OK      
    c20c 打印欢迎LOG“欢迎使用无限混和运算器”。                                	OK  
    c30c 用户输入字符串a，用户输入缓存内容为a。                                 OK      
    c40c 用户输入字符串bbb，再输入字符串aa，用户输入缓存内容为aa，而不是aab。   OK      
    c50c 初始化接收用户输入的函数指针，使其指向gets库函数                       OK      
    c51c 初始化屏蔽输出内容的函数指针，使其指向printf库函数                     OK      
    c53c 用户输入 help， 输出帮助信息                                           OK      
    c54c 用户输入 quit，输出退出的提示                                          OK      
    c55c 用户输入 quit，主程序退出                                              OK      
    c60c 用户输入 1 + 1 = ，输出计算结果 2                                      OK      
    c65c 用户输入 5 * 10 = , 输出计算结果 50                                    OK      
    c68c 用户输入 5 * 10 + 9, 输出计算结果 59                                   OK      
    
    &&&如下为一些输入的异常检测测试用例，还需要完善，先列几条
    c80c 用户输入 a + a =，提示操作数非法                                       OK      
    c81c 用户输入字符串，最后一个字符为#，提示Operand is illegal                OK      
    c82c 用户输入字符串，第一个字符为&，提示Operand is illegal                  OK      
    c83c 用户输入字符串，第一个字符为*，提示Operand is illegal                  NOK
    c84c 用户输入字符串，操作数后面紧跟+，没有空格，提示
         after operand must follow space!                                       NOK
    c100c 用户输入99999999999 + 99，提示最后一个字符必须为=                     OK      
    c120c 用户输入长度为MAX_RCV_STRLEN + 1，提示
           The length of whole string is exceeded!                              OK      
    c130c 用户输入help，再输入help，再输入5 * 10 =，输出计算结果59              NOK
    c132c 用户输入5 * 10 +9 =,再输入5 * 10 =，输出计算结果50                    NOK
    c133c 用户输入5 * 10 =，再输入help,输出帮助信息                             NOK
    c135c 用户输入5 * 10 + 9=，再输入exit，输出退出的提示                       NOK
    c137c 用户输入5 * 10 + 9=，再输入exit，主程序退出                           NOK
    c150c 需要向屏幕输出 welcome，在输出缓存中输出welcome                       OK      
    c155c 向屏幕输出123456，再向屏幕输出789，在输出缓存中输出789                OK      
    c165c 两字符串相加操作。输入字符串分别是"3"和"4",输出字符串内容为"7"        OK      
    c166c 两字符串相加操作。输入字符串分别是"3"和"44",输出字符串内容为"47"      OK      
    c167c 两字符串相加操作。输入字符串分别是"43"和"3",输出字符串内容为"46"      OK      
    c168c 两字符串相乘操作。输入字符串分别是"3"和"4",输出字符串内容为"12"       OK      
    c169c 两字符串相乘操作。输入字符串分别是"5"和"25",输出字符串内容为"125"     OK      
    c170c 两字符串相加操作。输入字符串分别是"33"和"44",输出字符串内容为"77"     OK      
    c171c 两字符串相加操作。输入字符串分别是"1933"和"444",输出字符
          串内容为"2377"                                                        OK      
    c172c 输入字符串分别是"9999"和"99",输出字符
          串内容为"989901"                                                      OK      
    c173c 输入字符串分别是"891"和"100",输出字符
          串内容为"89100"                                                      NOK      
    c175c 两字符串相加操作。输入字符串分别是"89"和"98",输出字符串内容为"187"    OK      
    c180c 两字符串相加操作。第一个加法输入字符串超出最大长度，提示
          plus operator is exceeded                                             OK      
    c181c 两字符串相加操作。第二个加法输入字符串超出最大长度，提示
          plus operator is exceeded                                             OK      
    c190c 两字符串相加操作。输入字符串为全9，并且为最大长度,输
          出字符串内容为"199....8"                                              OK      
    c192c CommApi初始化之后，前一个操作是操作符，不是操作数                     OK      
    c193c CommApi初始化之后，前一个字符是空格                                   OK      
    c200c CommApi初始化之后，操作符字符串第一个数组内容为全0                    OK      
    c201c CommApi初始化之后，操作数字符串第一个数组内容为全0                    OK      
    c202c 操作数字符串数组长度为MAX_RCV_STRLEN/2                                OK      
    c203c 操作符字符串数组长度为MAX_RCV_STRLEN/2                                OK      
    c204c CommApi初始化之后，下一个期望字符可以为数字                           OK      
    c205c CommApi初始化之后，下一个期望字符不可为空格                           OK      
    c206c CommApi初始化之后，下一个期望字符不可为'*'                            OK      
    c207c CommApi初始化之后，下一个期望字符不可为'+'                            OK      
    c208c CommApi初始化之后，下一个期望字符不可为'-'                            OK      
    c209c CommApi初始化之后，操作数的操作符数组下标为0                          NOK
    c213c 字符串解析操作。输入字符串为"10 + 10 =",操作数字符串数组
          内容为10／10                                                          OK      
    c214c 字符串解析操作。输入字符串为"10 + 10 =",操作符字符串数组
          内容为+                                                               OK      
    c215c 字符串解析操作。输入字符串为"10 + 10 - 200=",操作数字符串数组
          内容为10／10/200                                                      OK      
    c216c 字符串解析操作。输入字符串为"10 + 10 - 200=",操作符字符串数组
          内容为+/-                                                             OK      
    c220c 字符串解析操作。输入字符串为"10 + 20 * 30=",操作数字符串数组
          内容为10／20/30                                                       OK      
    c221c 字符串解析操作。输入字符串为"10 + 20 * 30=",操作符字符串数组
          内容为+/*                                                             OK      
    c230c 字符串解析操作。字符为'0'，函数返回值为IS_DIGITAL                     OK      
    c235c 字符串解析操作。字符为'9'，函数返回值为IS_DIGITAL                     OK      
    c240c 字符串解析操作。字符为'0' - 1，函数返回值为IS_NOT_DIGITAL             OK      
    c250c 字符串解析操作。字符为'9' + 1，函数返回值为IS_NOT_DIGITAL             OK      
*/


#include "CppUTest/TestHarness.h"
#include "strRecv.h"
#include "mockstdlib.h"

static void DoUserInputValue(void);

static void DoUserInputValue(void)
{
    if(INPUT_LENGTH_IS_EXCEEDED == RecvStringFromInputDeviceJustOnce())
        return;
    HandleUserInput();
}


/* begin of Init Group */

TEST_GROUP(OperatorInit)
{
    void setup()
    {
        mock_CleanReadCount();
    }
    void teardown()
    {
    }
};

/* c15c */
TEST(OperatorInit, AfterInitalAppIsInWorkingStatus)
{
    int tmpAppStatus = APP_IS_IN_INIT_STATUS; 
    OperatorInit();
    LONGS_EQUAL(APP_IS_IN_WORKING_STATUS, GetStatusOfApplication());
}

/* c10c */
TEST(OperatorInit, AllocateRecvMemoryWhichValueIsZero)
{
    char *ReceiveAddr = NULL;
    void *CompareAddr = malloc(MAX_RCV_STRLEN);
    memset(CompareAddr, 0, MAX_RCV_STRLEN);
    AllocateMemory();
    ReceiveAddr = GetReceiveStringAddress();

    CHECK( 0 == memcmp(ReceiveAddr, CompareAddr, MAX_RCV_STRLEN) );
  
    free(CompareAddr);
}

/* c13c */
TEST(OperatorInit, AllocateOutPutMemoryWhichValueIsZero)
{
    char *OutPutAddr = NULL;
    void *CompareAddr = malloc(MAX_RCV_STRLEN);
    memset(CompareAddr, 0, MAX_RCV_STRLEN);
    AllocateMemory();
    OutPutAddr = GetOutPutStringAddress();

    CHECK( 0 == memcmp(OutPutAddr, CompareAddr, MAX_RCV_STRLEN) );
  
    free(CompareAddr);
}

/* c20c */
TEST(OperatorInit, DisplayWelcomeBanner)
{
    char welcomeBanner[100] = BANNER_STRING;
    OperatorInit();
    SetFuncPrintf(mock_printf);
    OutPutBuffer(BANNER_STRING);
    STRCMP_EQUAL(welcomeBanner, GetOutPutStringAddress());
}

/* c50c */
TEST(OperatorInit, clib_getcharEqualgetcharOfCLib)
{
    int (*Funcgets)(void) = NULL;
    OperatorInit();
    Funcgets = GetFuncgets();
    CHECK_EQUAL( Funcgets ,getchar);
}

/* c51c */
TEST(OperatorInit, clib_printfEqualprintfOfCLib)
{
    int (*FuncPrintf)(const char*, ...) = NULL;
    OperatorInit();
    FuncPrintf = GetFuncPrintf();
    CHECK_EQUAL( FuncPrintf ,printf);
}

/* end of Init Group */

/* begin of Exit Group */

TEST_GROUP(OperatorExit)
{
    void setup()
    {
        OperatorInit();
    }
    void teardown()
    {
    }
};

/* c55c */
TEST(OperatorExit, InputquitThenAppStatusIsExit)
{
    int appStatus = APP_IS_IN_INIT_STATUS;
    SetFuncGets(mock_gets);
    SetFuncPrintf(mock_printf);
    mock_UserInputString("quit");
    DoUserInputValue();
    appStatus = GetStatusOfApplication();
    LONGS_EQUAL(APP_IS_IN_EXIT_STATUS, appStatus);
}

/* end of Exit Group */

/* begin of Recv Group */
TEST_GROUP(OperatorRecv)
{
    void setup()
    {
        mock_CleanReadCount();
        OperatorInit();
        SetFuncGets(mock_gets);
        SetFuncPrintf(mock_printf);
    }
    void teardown()
    {
    }
};

/* c53c */
TEST(OperatorRecv, InputHelpThenOutputHelpInfo)
{
    char * RecvBuffer = NULL;
    char helpInfo[100] = HELP_STRING;
    mock_UserInputString("help");
    DoUserInputValue();
    STRCMP_EQUAL(helpInfo, GetOutPutStringAddress());
}

/* c54c */
TEST(OperatorRecv, InputquitThenOutputHelpInfo)
{
    char * RecvBuffer = NULL;
    char quitInfo[100] = QUIT_STRING;
    mock_UserInputString("quit");
    DoUserInputValue();
    STRCMP_EQUAL(quitInfo, GetOutPutStringAddress());
}

/* c30c */
TEST(OperatorRecv, RecvBufIsa)
{
    char * RecvBuffer = NULL;
    mock_UserInputString("a");
    RecvStringFromInputDeviceJustOnce();
    RecvBuffer = GetUserInputBuffer();
    STRCMP_EQUAL("a", RecvBuffer);
}

/* c40c */
TEST(OperatorRecv, RecvBufIsaaNotaab)
{
    char * RecvBuffer = NULL;
    mock_UserInputString("bbb");
    RecvStringFromInputDeviceJustOnce();
    mock_UserInputString("aa");
    RecvStringFromInputDeviceJustOnce();
    RecvBuffer = GetUserInputBuffer();
    STRCMP_EQUAL("aa", RecvBuffer);
}

/* c60c */
TEST(OperatorRecv, Input1plus1ThenOutput2)
{
    mock_UserInputString("1 + 1 =");
    DoUserInputValue();
    STRCMP_EQUAL("2\n", GetOutPutStringAddress());
}

/* c65c */
TEST(OperatorRecv, Input5multi10ThenOutput50)
{
    mock_UserInputString("5 * 10 =");
    DoUserInputValue();
    STRCMP_EQUAL("50\n", GetOutPutStringAddress());
}

/* c68c */
TEST(OperatorRecv, Input5multi10Plus9ThenOutput59)
{
    mock_UserInputString("5 * 10 + 9 =");
    DoUserInputValue();
    STRCMP_EQUAL("59\n", GetOutPutStringAddress());
}

/* c68c */
TEST(OperatorRecv, Input5mul10mul5Plus9ThenOutput259)
{
    mock_UserInputString("5 * 10 * 5 + 9 =");
    DoUserInputValue();
    STRCMP_EQUAL("259\n", GetOutPutStringAddress());
}


/* end of Recv Group */

/* begin of exception group */

TEST_GROUP(ExceptionGroup)
{
    void setup()
    {
        mock_CleanReadCount();
        OperatorInit();
        SetFuncGets(mock_gets);
        SetFuncPrintf(mock_printf);
    }
    void teardown()
    {
    }
};

/* c80c */
TEST(ExceptionGroup, InputaplusaThenTipOperandIsIllegal)
{
    mock_UserInputString("a + a =");
    DoUserInputValue();
    STRCMP_EQUAL(OPERAND_IS_ILLEGAL_STRING, GetOutPutStringAddress());
}

/* c81c */
TEST(ExceptionGroup, InputLastCharIsIllegalThenTipOperandIsIllegal)
{
    char userIllegalInput[MAX_RCV_STRLEN] = {0};
    memset(userIllegalInput, '1', MAX_RCV_STRLEN);
    userIllegalInput[MAX_RCV_STRLEN - 2] = '#';
    userIllegalInput[MAX_RCV_STRLEN - 1] = 0;
    mock_UserInputString(userIllegalInput);
    DoUserInputValue();
    STRCMP_EQUAL(OPERAND_IS_ILLEGAL_STRING, GetOutPutStringAddress());
}

/* c82c */
TEST(ExceptionGroup, InputFirstCharIsIllegalThenTipOperandIsIllegal)
{
    char userIllegalInput[MAX_RCV_STRLEN] = {0};
    memset(userIllegalInput, '1', MAX_RCV_STRLEN);
    memset(userIllegalInput , '&', 1);
    userIllegalInput[MAX_RCV_STRLEN - 1] = 0;
    mock_UserInputString(userIllegalInput);
    DoUserInputValue(); 
    STRCMP_EQUAL(OPERAND_IS_ILLEGAL_STRING, GetOutPutStringAddress());
}

/* c83c */
IGNORE_TEST(ExceptionGroup, InputFirstCharIsProductThenTipOperandIsIllegal)
{
    char userIllegalInput[MAX_RCV_STRLEN] = {0};
    memset(userIllegalInput, '1', MAX_RCV_STRLEN);
    memset(userIllegalInput , '*', 1);
    userIllegalInput[MAX_RCV_STRLEN - 1] = 0;
    mock_UserInputString(userIllegalInput);
    DoUserInputValue();
    STRCMP_EQUAL(OPERAND_IS_ILLEGAL_STRING, GetOutPutStringAddress());
}
/* c84c */
IGNORE_TEST(ExceptionGroup, AfterOperandMustFollowSpace)
{
    mock_UserInputString("1355+ 456 =");
    DoUserInputValue();
    STRCMP_EQUAL(OPERAND_MUST_BE_FOLLOW_SPACE, GetOutPutStringAddress());
}

/* c100c */
TEST(ExceptionGroup, LastCharMustBeEqualSymbol)
{
    mock_UserInputString("99999999999 + 99");
    DoUserInputValue();
    STRCMP_EQUAL(LAST_CHAR_MUST_BE_EQUAL_STRING, GetOutPutStringAddress());
}

/* c120c */
TEST(ExceptionGroup, InputLenthExceedThenTipExceedInfo)
{
    /* userIllegalInput的最后一个字节必须为0，否则会越界 */
    char userIllegalInput[MAX_RCV_STRLEN + 1] = {0};
    memset(userIllegalInput, '1', MAX_RCV_STRLEN + 1);
    userIllegalInput[MAX_RCV_STRLEN + 1] = 0;
    mock_UserInputString(userIllegalInput);
    DoUserInputValue();
    STRCMP_EQUAL(OPERAND_LENGTH_EXCEED_STRING, GetOutPutStringAddress());
}


/* end of exception group */

/* begin of CommomApi Group */
TEST_GROUP(CommomApi)
{
    void setup()
    {
        mock_CleanReadCount();
        OperatorInit();
        SetFuncGets(mock_gets);
        SetFuncPrintf(mock_printf);
    }
    void teardown()
    {
    }
};

/* c150c */
TEST(CommomApi, OutBufferIsWelcome) 
{
    char welcomestr[] = "welcome!";
    OutPutBuffer(welcomestr);
    STRCMP_EQUAL(welcomestr, GetOutPutStringAddress());
}

/* c155c */
TEST(CommomApi, OutBufferIs789) 
{
    OutPutBuffer("123456");
    OutPutBuffer("789");
    STRCMP_EQUAL("789", GetOutPutStringAddress());
}

/* c165c */
TEST(CommomApi, InputStrAre3And4ThenOutStrIs7)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("3", "4");
    STRCMP_EQUAL("7", outPutAddress);
}

/* c170c */
TEST(CommomApi, InputStrAre33And44ThenOutStrIs77)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("33", "44");
    STRCMP_EQUAL("77", outPutAddress);
}

/* c171c */
TEST(CommomApi, InputStrAre1933And444ThenOutStrIs2377)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("1933", "444");
    STRCMP_EQUAL("2377", outPutAddress);
}

/* c172c */
TEST(CommomApi, InputStrAre9999And99ThenOutStrIs989901)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("9999", "99");
    STRCMP_EQUAL("989901", outPutAddress);
}
/* c173c */
TEST(CommomApi, InputStrAre891And100ThenOutStrIs89100)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("891", "100");
    STRCMP_EQUAL("89100", outPutAddress);
}

TEST(CommomApi, InputStrAre99And100ThenOutStrIs9900)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("99", "100");
    STRCMP_EQUAL("9900", outPutAddress);
}

TEST(CommomApi, InputStrAre9090And100ThenOutStrIs909000)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("9090", "100");
    STRCMP_EQUAL("909000", outPutAddress);
}

/* c166c */
TEST(CommomApi, InputStrAre3And44ThenOutStrIs47)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("3", "44");
    STRCMP_EQUAL("47", outPutAddress);
}

/* c167c */
TEST(CommomApi, InputStrAre43And3ThenOutStrIs46)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("43", "3");
    STRCMP_EQUAL("46", outPutAddress);
}

/* c168c */
TEST(CommomApi, InputStrAre3And4ThenOutStrIs12)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("3", "4");
    STRCMP_EQUAL("12", outPutAddress);
}

/* c169c */
TEST(CommomApi, InputStrAre5And25ThenOutStrIs125)
{
    char * outPutAddress = NULL;
    outPutAddress = MultiOperate("5", "25");
    STRCMP_EQUAL("125", outPutAddress);
}

/* c175c */
TEST(CommomApi, InputStrAre89And98ThenOutStrIs187)
{
    char * outPutAddress = NULL;
    outPutAddress = PlusOperate("89", "98");
    STRCMP_EQUAL("187", outPutAddress);
}

/* c180c */
TEST(CommomApi, InputFirstStringLengthExceedThenTip)
{
    char *operatone = NULL;
    operatone = (char*)(malloc(MAX_PLUS_STRING_OF_INPUT + 2));
    memset(operatone, '1', MAX_PLUS_STRING_OF_INPUT + 1);
    memset(operatone + MAX_PLUS_STRING_OF_INPUT + 1, 0, 1);
    PlusOperate(operatone, "98");
    STRCMP_EQUAL(PLUS_OPERATOR_IS_EXCEEDED, GetOutPutStringAddress());
    free(operatone);
}

/* c181c */
TEST(CommomApi, InputSecondStringLengthExceedThenTip)
{
    char *operatone = NULL;
    operatone = (char*)(malloc(MAX_PLUS_STRING_OF_INPUT + 2));
    memset(operatone, '1', MAX_PLUS_STRING_OF_INPUT + 1);
    memset(operatone + MAX_PLUS_STRING_OF_INPUT + 1, 0,1);
    PlusOperate("198", operatone);
    STRCMP_EQUAL(PLUS_OPERATOR_IS_EXCEEDED, GetOutPutStringAddress());
    free(operatone);
}

/* c190c */
TEST(CommomApi, InputMaxLengthStringThenOutput19998)
{
    char * outPutAddress = NULL;
    char *operatone = NULL;
    char *operattwo = NULL;
    char *outcome   = NULL;
    operatone = (char*)(malloc(MAX_PLUS_STRING_OF_INPUT + 1));
    operattwo = (char*)(malloc(MAX_PLUS_STRING_OF_INPUT + 1));
    outcome = (char*)(malloc(MAX_PLUS_STRING_OF_INPUT + 2));
    memset(operatone, '9', MAX_PLUS_STRING_OF_INPUT);
    memset(operattwo, '9', MAX_PLUS_STRING_OF_INPUT);
    memset(operatone + MAX_PLUS_STRING_OF_INPUT, 0,1);
    memset(operattwo + MAX_PLUS_STRING_OF_INPUT, 0,1);
    memset(outcome, '1', 1);
    memset(outcome + 1, '9',MAX_PLUS_STRING_OF_INPUT - 1);
    memset(outcome + MAX_PLUS_STRING_OF_INPUT, '8', 1);
    memset(outcome + MAX_PLUS_STRING_OF_INPUT + 1, 0, 1);

    outPutAddress = PlusOperate(operatone, operattwo);
    STRCMP_EQUAL(outcome, outPutAddress);
    free(operatone);
    free(operattwo);
    free(outcome);
}

/* c230c */
TEST(CommomApi, 0IsDigital)
{
    LONGS_EQUAL(IS_DIGITAL, CharIsDigital('0'));
}

/* c235c */
TEST(CommomApi, 9IsDigital)
{
    LONGS_EQUAL(IS_DIGITAL, CharIsDigital('9'));
}
/* c240c */
TEST(CommomApi, 0Minus1IsNotDigital)
{
    LONGS_EQUAL(IS_NOT_DIGITAL, CharIsDigital('0' - 1));
}
/* c250c */
TEST(CommomApi, 9Plus1IsNotDigital)
{
    LONGS_EQUAL(IS_NOT_DIGITAL, CharIsDigital('9' + 1));
}
/* c210c */
TEST(CommomApi, 10spluss10OperatorIsPlus)
{
    LONGS_EQUAL(IS_NOT_DIGITAL, CharIsDigital('9' + 1));
}
/* c202c */
TEST(CommomApi, OperandDimSizeIsHalfMaxLen)
{
    LONGS_EQUAL(MAX_RCV_STRLEN/2, GetOperandDimSize());
}
/* c203c */
TEST(CommomApi, OperatorDimSizeIsHalfMaxLen)
{
    LONGS_EQUAL(MAX_RCV_STRLEN/2, GetOperatorDimSize());
}

/* c200c */
TEST(CommomApi, AfterInitOperandIsZero)
{
    char* compareDim = NULL;
    compareDim = (char*) (malloc(MAX_RCV_STRLEN));
    memset(compareDim, 0, sizeof(MAX_RCV_STRLEN));
    SetOperandFirstDimValue(1);
    CommApiInit();
    STRCMP_EQUAL(compareDim, GetOperandDimAddr());
    free(compareDim);
}

/* c201c */
TEST(CommomApi, AfterInitOperatorIsZero)
{
    char* compareDim = NULL;
    compareDim = (char*) (malloc(MAX_RCV_STRLEN));
    memset(compareDim, 0, sizeof(MAX_RCV_STRLEN));
    SetOperatorFirstDimValue(1);
    CommApiInit();
    STRCMP_EQUAL(compareDim, GetOperatorDimAddr());
    free(compareDim);
}

/* c192c */
TEST(CommomApi, AfterInitPreviousOperIsOperator)
{
    SetPreviousOper(PREV_OPERAND);
    CommApiInit();
    LONGS_EQUAL(PREV_OPERATOR, GetPreviousOper());
}

/* c193c */
TEST(CommomApi, AfterInitPreviousCharIsSpace)
{
    SetPreviousChar(PREV_CHAR_DIGITAL);
    CommApiInit();
    LONGS_EQUAL(PREV_CHAR_SPACE, GetPreviousChar());
}

/* c204c */
TEST(CommomApi, AfterInitNextExpectContainDigit)
{
    SetNextExpectDigit(NEXT_IS_NOT_EXPECTED);
    CommApiInit();
    LONGS_EQUAL(NEXT_IS_EXPECTED, GetNextExpectDigit());
}
/* c205c */
TEST(CommomApi, AfterInitNextExpectNoSpace)
{
    SetNextExpectSpace(NEXT_IS_EXPECTED);
    CommApiInit();
    LONGS_EQUAL(NEXT_IS_NOT_EXPECTED, GetNextExpectSpace());
}
/* c206c */
TEST(CommomApi, AfterInitNextExpectNoMulti)
{
    SetNextExpectMulti(NEXT_IS_EXPECTED);
    CommApiInit();
    LONGS_EQUAL(NEXT_IS_NOT_EXPECTED, GetNextExpectMulti());
}
/* c207c */
TEST(CommomApi, AfterInitNextExpectNoPlus)
{
    SetNextExpectPlus(NEXT_IS_EXPECTED);
    CommApiInit();
    LONGS_EQUAL(NEXT_IS_NOT_EXPECTED, GetNextExpectPlus());
}
/* c208c */
TEST(CommomApi, AfterInitNextExpectNoMinus)
{
    SetNextExpectMinus(NEXT_IS_EXPECTED);
    CommApiInit();
    LONGS_EQUAL(NEXT_IS_NOT_EXPECTED, GetNextExpectMinus());
}


/* c213c */
TEST(CommomApi, AfterAnalysisOperandIs10and10)
{
    char* operandDim;
    AnalysisString("10 + 10 =");
    operandDim = GetOperandDimAddr();
    STRCMP_EQUAL("10", operandDim);
    STRCMP_EQUAL("10", operandDim + MAX_RCV_STRLEN);
}

/* c214c */
TEST(CommomApi, AfterAnalysisOperatorIsPlus)
{
    char* operDim;
    AnalysisString("10 + 10 =");
    operDim = GetOperatorDimAddr();
    STRCMP_EQUAL("+", operDim);
}

/* c215c */
TEST(CommomApi, AfterAnalysis1010200OperandIs1010200)
{
    char* operandDim;
    AnalysisString("10 + 10 - 200=");
    operandDim = GetOperandDimAddr();
    STRCMP_EQUAL("10", operandDim);
    STRCMP_EQUAL("10", operandDim + MAX_RCV_STRLEN);
    STRCMP_EQUAL("200", operandDim + 2*MAX_RCV_STRLEN);
}

/* c220c */
TEST(CommomApi, AfterAnalysis102030OperandIs102030)
{
    char* operandDim;
    AnalysisString("10 + 20 * 30=");
    operandDim = GetOperandDimAddr();
    STRCMP_EQUAL("10", operandDim);
    STRCMP_EQUAL("20", operandDim + MAX_RCV_STRLEN);
    STRCMP_EQUAL("30", operandDim + 2*MAX_RCV_STRLEN);
}

/* c216c */
TEST(CommomApi, AfterAnalysisOperatorIsPlusMinus)
{
    char* operDim;
    AnalysisString("10 + 10 - 200=");
    operDim = GetOperatorDimAddr();
    STRCMP_EQUAL("+-", operDim);
}
/* c221c */
TEST(CommomApi, AfterAnalysisOperatorIsPlusMinusMulti)
{
    char* operDim;
    AnalysisString("10 + 20 * 30 =");
    operDim = GetOperatorDimAddr();
    STRCMP_EQUAL("+*", operDim);
}

/* end of CommonApi Group */

#endif /* __TDD_TEST__*/
