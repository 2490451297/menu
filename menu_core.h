#ifndef __MENU_CORE_H
#define __MENU_CORE_H

#include "headfile.h"

#define COUNT_OF(A) (sizeof(A) / sizeof(*(A)))
#define MAX_MENU_LEVELS 4

typedef void (*tMenuFunc)(void);
typedef struct sMenuItem *tMenuItem;
typedef struct sMenu *tMenu;

/*�˵���*/
struct sMenuItem
{
    const char *pszTitle;            //�˵�ҳ����
    tMenuFunc pfMenuFunc;       //���ܺ���
    tMenuFunc pfUpDownMenuFunc; //���¶���ִ�еĹ���
    tMenu psSubMenu;            //�Ӳ˵�
};

/*�˵�ҳ*/
struct sMenu
{
    const char *pszTitle;   //�˵�ҳ����
    tMenuItem psItems; //�˵�ҳ�а����Ĳ˵���
    uint8 nItems;      //�˵�����
};

extern void Menu_Init(void);
extern void DisplayMenu(void);
extern void SelFunc(void);
extern void ReturnFunc(void);
extern void UpFunc(void);
extern void DownFunc(void);
extern void MainMenuInit(void);
extern void MenuTask(void);
#endif
