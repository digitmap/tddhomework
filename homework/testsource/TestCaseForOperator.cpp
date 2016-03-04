#ifdef __TDD_TEST__
/*
    c10c ��̬����MAX_RCV_STRLEN���ֽڵ��ڴ棨ReceiveStringAddress������
          ������û�������ַ��������ҳ�ʼֵΪ0��                               OK      
    c13c ��̬����MAX_RCV_STRLEN���ֽڵ��ڴ棨OutPutStringAddress������
          ������û�������ַ��������ҳ�ʼֵΪ0��                               OK      
    c15c ����֮��Ӧ�ý���Ϊ����״̬��                                         OK      
    c20c ��ӡ��ӭLOG����ӭʹ�����޻������������                                	OK  
    c30c �û������ַ���a���û����뻺������Ϊa��                                 OK      
    c40c �û������ַ���bbb���������ַ���aa���û����뻺������Ϊaa��������aab��   OK      
    c50c ��ʼ�������û�����ĺ���ָ�룬ʹ��ָ��gets�⺯��                       OK      
    c51c ��ʼ������������ݵĺ���ָ�룬ʹ��ָ��printf�⺯��                     OK      
    c53c �û����� help�� ���������Ϣ                                           OK      
    c54c �û����� quit������˳�����ʾ                                          OK      
    c55c �û����� quit���������˳�                                              OK      
    c60c �û����� 1 + 1 = ����������� 2                                      OK      
    c65c �û����� 5 * 10 = , ��������� 50                                    OK      
    c68c �û����� 5 * 10 + 9, ��������� 59                                   OK      
    
    &&&����ΪһЩ������쳣����������������Ҫ���ƣ����м���
    c80c �û����� a + a =����ʾ�������Ƿ�                                       OK      
    c81c �û������ַ��������һ���ַ�Ϊ#����ʾOperand is illegal                OK      
    c82c �û������ַ�������һ���ַ�Ϊ&����ʾOperand is illegal                  OK      
    c83c �û������ַ�������һ���ַ�Ϊ*����ʾOperand is illegal                  NOK
    c84c �û������ַ������������������+��û�пո���ʾ
         after operand must follow space!                                       NOK
    c100c �û�����99999999999 + 99����ʾ���һ���ַ�����Ϊ=                     OK      
    c120c �û����볤��ΪMAX_RCV_STRLEN + 1����ʾ
           The length of whole string is exceeded!                              OK      
    c130c �û�����help��������help��������5 * 10 =�����������59              NOK
    c132c �û�����5 * 10 +9 =,������5 * 10 =�����������50                    NOK
    c133c �û�����5 * 10 =��������help,���������Ϣ                             NOK
    c135c �û�����5 * 10 + 9=��������exit������˳�����ʾ                       NOK
    c137c �û�����5 * 10 + 9=��������exit���������˳�                           NOK
    c150c ��Ҫ����Ļ��� welcome����������������welcome                       OK      
    c155c ����Ļ���123456��������Ļ���789����������������789                OK      
    c165c ���ַ�����Ӳ����������ַ����ֱ���"3"��"4",����ַ�������Ϊ"7"        OK      
    c166c ���ַ�����Ӳ����������ַ����ֱ���"3"��"44",����ַ�������Ϊ"47"      OK      
    c167c ���ַ�����Ӳ����������ַ����ֱ���"43"��"3",����ַ�������Ϊ"46"      OK      
    c168c ���ַ�����˲����������ַ����ֱ���"3"��"4",����ַ�������Ϊ"12"       OK      
    c169c ���ַ�����˲����������ַ����ֱ���"5"��"25",����ַ�������Ϊ"125"     OK      
    c170c ���ַ�����Ӳ����������ַ����ֱ���"33"��"44",����ַ�������Ϊ"77"     OK      
    c171c ���ַ�����Ӳ����������ַ����ֱ���"1933"��"444",����ַ�
          ������Ϊ"2377"                                                        OK      
    c172c �����ַ����ֱ���"9999"��"99",����ַ�
          ������Ϊ"989901"                                                      OK      
    c173c �����ַ����ֱ���"891"��"100",����ַ�
          ������Ϊ"89100"                                                      NOK      
    c175c ���ַ�����Ӳ����������ַ����ֱ���"89"��"98",����ַ�������Ϊ"187"    OK      
    c180c ���ַ�����Ӳ�������һ���ӷ������ַ���������󳤶ȣ���ʾ
          plus operator is exceeded                                             OK      
    c181c ���ַ�����Ӳ������ڶ����ӷ������ַ���������󳤶ȣ���ʾ
          plus operator is exceeded                                             OK      
    c190c ���ַ�����Ӳ����������ַ���Ϊȫ9������Ϊ��󳤶�,��
          ���ַ�������Ϊ"199....8"                                              OK      
    c192c CommApi��ʼ��֮��ǰһ�������ǲ����������ǲ�����                     OK      
    c193c CommApi��ʼ��֮��ǰһ���ַ��ǿո�                                   OK      
    c200c CommApi��ʼ��֮�󣬲������ַ�����һ����������Ϊȫ0                    OK      
    c201c CommApi��ʼ��֮�󣬲������ַ�����һ����������Ϊȫ0                    OK      
    c202c �������ַ������鳤��ΪMAX_RCV_STRLEN/2                                OK      
    c203c �������ַ������鳤��ΪMAX_RCV_STRLEN/2                                OK      
    c204c CommApi��ʼ��֮����һ�������ַ�����Ϊ����                           OK      
    c205c CommApi��ʼ��֮����һ�������ַ�����Ϊ�ո�                           OK      
    c206c CommApi��ʼ��֮����һ�������ַ�����Ϊ'*'                            OK      
    c207c CommApi��ʼ��֮����һ�������ַ�����Ϊ'+'                            OK      
    c208c CommApi��ʼ��֮����һ�������ַ�����Ϊ'-'                            OK      
    c209c CommApi��ʼ��֮�󣬲������Ĳ����������±�Ϊ0                          NOK
    c213c �ַ������������������ַ���Ϊ"10 + 10 =",�������ַ�������
          ����Ϊ10��10                                                          OK      
    c214c �ַ������������������ַ���Ϊ"10 + 10 =",�������ַ�������
          ����Ϊ+                                                               OK      
    c215c �ַ������������������ַ���Ϊ"10 + 10 - 200=",�������ַ�������
          ����Ϊ10��10/200                                                      OK      
    c216c �ַ������������������ַ���Ϊ"10 + 10 - 200=",�������ַ�������
          ����Ϊ+/-                                                             OK      
    c220c �ַ������������������ַ���Ϊ"10 + 20 * 30=",�������ַ�������
          ����Ϊ10��20/30                                                       OK      
    c221c �ַ������������������ַ���Ϊ"10 + 20 * 30=",�������ַ�������
          ����Ϊ+/*                                                             OK      
    c230c �ַ��������������ַ�Ϊ'0'����������ֵΪIS_DIGITAL                     OK      
    c235c �ַ��������������ַ�Ϊ'9'����������ֵΪIS_DIGITAL                     OK      
    c240c �ַ��������������ַ�Ϊ'0' - 1����������ֵΪIS_NOT_DIGITAL             OK      
    c250c �ַ��������������ַ�Ϊ'9' + 1����������ֵΪIS_NOT_DIGITAL             OK      
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
    /* userIllegalInput�����һ���ֽڱ���Ϊ0�������Խ�� */
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
