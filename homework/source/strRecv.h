#ifndef __STRRECV_H__
#define __STRRECV_H__

#ifdef __cplusplus
extern "C"
{

#endif __cplusplus

    #define MAX_RCV_STRLEN 100    /* 用户输入字符串的最大长度 */
    #define MAX_PLUS_STRING_OF_INPUT MAX_RCV_STRLEN    /* 加法运算最大字符串长度 */
    
    #define BANNER_STRING "欢迎使用无限混和运算器\n"
    #define HELP_STRING   "help    显示帮助信息\nquit    退出程序\n"
    #define QUIT_STRING   "程序马上退出...\n"
    #define OPERAND_IS_ILLEGAL_STRING "Operand is illegal\n"
    #define LAST_CHAR_MUST_BE_EQUAL_STRING "Last char must be =\n"
    #define OPERAND_LENGTH_EXCEED_STRING "The length of whole string is exceeded!\n"
    #define PLUS_OPERATOR_IS_EXCEEDED "plus operator is exceeded!\n"
    #define OPERAND_MUST_BE_FOLLOW_SPACE "after operand must follow space!\n"
    

    #define APP_IS_IN_INIT_STATUS       0
    #define APP_IS_IN_EXIT_STATUS       APP_IS_IN_INIT_STATUS + 1
    #define APP_IS_IN_WORKING_STATUS    APP_IS_IN_INIT_STATUS + 2

    #define NO_ERROR            0
    #define INPUT_LENGTH_IS_EXCEEDED    (NO_ERROR + 1)

    #define IS_DIGITAL            1
    #define IS_NOT_DIGITAL        2

    #define PREV_OPERAND            1
    #define PREV_OPERATOR           2
    #define PREV_CHAR_DIGITAL       3
    #define PREV_CHAR_SPACE         ' '
    #define PREV_CHAR_PLUS          '+'
    #define PREV_CHAR_MINUS         '-'
    #define PREV_CHAR_MULTI         '*'

    #define NEXT_IS_NOT_EXPECTED    1
    #define NEXT_IS_EXPECTED        2


    void OperatorInit(void);
    void HandleUserInput(void);
    int (*GetFuncgets(void))(void);
    int (*GetFuncPrintf(void))(const char*, ...);
    void SetFuncGets(int (*funcPtr)(void));
    void SetFuncPrintf(int(*funcPtr)(const char*, ...));

    void AllocateMemory(void);
    char *GetReceiveStringAddress(void);
    char *GetOutPutStringAddress(void);
    int RecvStringFromInputDeviceJustOnce(void);
    char *GetUserInputBuffer(void);
    int GetStatusOfApplication(void);
    void SetStatusOfApplication(int);
    int OutPutBuffer(char*);
    char* PlusOperate(char*, char*);
    char* MultiOperate(char*, char*);
    int GetErrorCode(void);
    void SetErrorCode(int errorNumber);
    int CharIsDigital(char);
    int GetOperandDimSize(void);
    int GetOperatorDimSize(void);
    char* GetOperandDimAddr(void);
    char* GetOperatorDimAddr(void);
    void SetOperandFirstDimValue(char ch);
    void SetOperatorFirstDimValue(char ch);
    void CommApiInit(void);
    void SetPreviousOper(int);
    int GetPreviousOper(void);
    void SetPreviousChar(int);
    int GetPreviousChar(void);
    void CommApiInit(void);
    void SetNextExpectDigit(int);
    int  GetNextExpectDigit(void);
    void SetNextExpectSpace(int);
    int  GetNextExpectSpace(void);
    void SetNextExpectPlus(int);
    int  GetNextExpectPlus(void);
    void SetNextExpectMinus(int);
    int  GetNextExpectMinus(void);
    void SetNextExpectMulti(int);
    int  GetNextExpectMulti(void);
    int  AnalysisString(char* );
#ifdef __cplusplus
}
#endif __cplusplus

#endif /* __STRRECV_H__ */
