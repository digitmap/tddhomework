
#ifndef __MOCKSTDLIB_H__
#define __MOCKSTDLIB_H__

#ifdef __TDD_TEST__

#ifdef __cplusplus
extern "C"
{

#endif __cplusplus

int     mock_gets(void);
void    mock_UserInputString(char*);
int     mock_printf(const char *, ...);
void    mock_CleanReadCount(void);

#ifdef __cplusplus
}
#endif __cplusplus

#endif /* __MOCKSTDLIB_H__ */

#endif /* __TDD_TEST__ */
