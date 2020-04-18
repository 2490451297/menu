#include "menu_core.h"
#include "headfile.h"
#include "menu_display.h"
#include "shell.h"
#include "menu_button.h"

uint8 g_MenuItemIndex = 0;     //�˵���
uint8 g_nMenuLevel = 0;        //�˵�ҳ
uint8 g_lastMenuItemIndex = 0; //�ϴβ˵���
uint8 ItemNumb[MAX_MENU_LEVELS];
tMenuItem psMenuItem, psCurrentMenuItem; //�˵�ҳ��Ĳ˵����ǰ�˵�ҳ��Ĳ˵���
tMenu psPrevMenu[MAX_MENU_LEVELS];       //
tMenu psCurrentMenu;                     //��ǰ�˵�ҳ

/*private functions*/
void IdleFunc(void);
void Menu_test(void);
/*------------------------------ Menu level 3 -------------------------------*/
struct sMenuItem SubMenuItems_1_1[] = {
    /*�˵�������, Ҫִ�еĺ�����Ҫִ�еĺ�������һ��*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1_1 = {"     Level 3", SubMenuItems_1_1, COUNT_OF(SubMenuItems_1_1)};

struct sMenuItem SubMenuItems_1_2[] = {
    /*�˵�������, Ҫִ�еĺ�����Ҫִ�еĺ�������һ��*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1_2 = {"     Level 3", SubMenuItems_1_2, COUNT_OF(SubMenuItems_1_2)};

/*------------------------------ Menu level 2 -------------------------------*/
struct sMenuItem SubMenuItems_1[] = {
    /*�˵�������, Ҫִ�еĺ�����Ҫִ�еĺ�������һ��*/
    {"Item 1", IdleFunc, IdleFunc, &SubMenu_1_1},
    {"Item 2", IdleFunc, IdleFunc, &SubMenu_1_2},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1 = {"     Level 2", SubMenuItems_1, COUNT_OF(SubMenuItems_1)};

struct sMenuItem SubMenuItems_2[] = {
    /*�˵�������, Ҫִ�еĺ�������Ӧ�Ĺ��ܺ����������¶���ʱ�Ĺ��ܣ���һ���˵�*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_2 = {"     Level 2", SubMenuItems_2, COUNT_OF(SubMenuItems_2)};

struct sMenuItem SubMenuItems_3[] = {
    /*�˵�������, Ҫִ�еĺ�������Ӧ�Ĺ��ܺ����������¶���ʱ�Ĺ��ܣ���һ���˵�*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_3 = {"     Level 2", SubMenuItems_3, COUNT_OF(SubMenuItems_3)};
/*------------------------------ Menu level 1 -------------------------------*/
struct sMenuItem MainMenuItems[] = {
    /*�˵�������, Ҫִ�еĺ�������Ӧ�Ĺ��ܺ����������¶���ʱ�Ĺ��ܣ���һ���˵�*/
    {"Item One", IdleFunc, IdleFunc, &SubMenu_1},
    {"Item Two", IdleFunc, IdleFunc, &SubMenu_2},
    {"Item Three", IdleFunc, IdleFunc, &SubMenu_3},
    {"Item Four", IdleFunc, IdleFunc, NULL},
    {"Item Five", IdleFunc, IdleFunc, NULL}};
struct sMenu MainMenu = {"     Main menu", MainMenuItems, COUNT_OF(MainMenuItems)};

/**
 * @brief ��ʼ���˵�
*/
void Menu_Init(void)
{
    //��ǰ�˵�ҳ
    psCurrentMenu = &MainMenu;
    //��һ���˵�
    psPrevMenu[g_nMenuLevel] = psCurrentMenu;
    //��ǰ�˵�ҳ��Ĳ˵���
    psMenuItem = MainMenuItems;
}

/**
 * @brief ��ʾ�˵�
*/
void DisplayMenu(void)
{
    uint32 line = 0, index = 0;
    tMenuItem psMenuItem2;

    /*��ɫ�����Ļ*/
    MENU_setScreenColor(BACK_COLOR);
    /*��ʾ�˵�����*/
    MENU_DisplayStringLine(line, psCurrentMenu->pszTitle);
    line++;
    /*��ʾ����ǰ�˵�ҳ���в˵���*/
    while (!(index >= (psCurrentMenu->nItems)))
    {
        psMenuItem2 = &(psCurrentMenu->psItems[index]);
        MENU_DisplayStringLine(line, psMenuItem2->pszTitle);
        line++;
        index++;
    }

    /*��ʾѡ�еĲ˵���*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, SELECT_COLOR);
    psMenuItem = &(psCurrentMenu->psItems[g_MenuItemIndex]);
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
}

/**
 * @brief ��ʼ���˵������ʩ
*/
void MainMenuInit(void)
{
    /*ips200��Ļ��ʼ��,ע��������Ĳ˵�ʹ�õ���Ļ��Ҫ����display.h�еĺ궨��*/
    ips200_init();
    /*LCD��Ļ��ʼ��*/
    //lcd_init();
    /*�˵���ť��ʼ��*/
    menuButtonInit();
    /*��ʼ���˵��������*/
    Menu_Init();
    /*��ʾ�˵�*/
    DisplayMenu();
}

/**
 * @brief �˵�����
*/
void MenuTask(void)
{
    uint8 key_event;
    /*��ð�������*/
    key_event = menuPressEvent();

    switch (key_event)
    {
    case BUTTON_UP_EVENT:
        UpFunc();
        break;
    case BUTTON_DOWN_EVENT:
        DownFunc();
        break;
    case BUTTON_SURE_EVENT:
        SelFunc();
        break;
    case BUTTON_CANCEL_EVENT:
        ReturnFunc();
        break;
    }
}

/**
 * @brief None
*/
void IdleFunc(void)
{
    /*Nothing to execute:return*/
    return;
}

/**
 * @brief ѡ�ж���
*/
void SelFunc(void)
{
    /*�õ���ǰ�˵�ҳ�еĲ˵���*/
    psCurrentMenuItem = psMenuItem;

    /*�����Ӳ˵���ת*/
    if (psMenuItem->psSubMenu != NULL)
    {
        g_nMenuLevel++;
        g_MenuItemIndex = ItemNumb[g_nMenuLevel];
        /*�õ���ǰ�˵�����Ӳ˵�*/
        psCurrentMenu = psCurrentMenuItem->psSubMenu;
        psMenuItem = &(psCurrentMenu->psItems)[g_MenuItemIndex];
        DisplayMenu();
        psPrevMenu[g_nMenuLevel] = psCurrentMenu;
    }
    /*ִ�в˵����*/
    psCurrentMenuItem->pfMenuFunc();
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), SelFunc, SelFunc, SelFunc);

/**
 * @brief ���ض���
*/
void ReturnFunc(void)
{
    psMenuItem->pfUpDownMenuFunc();

    if (g_nMenuLevel == 0)
        g_nMenuLevel++;

    /*�õ���һ���˵�*/
    psCurrentMenu = psPrevMenu[g_nMenuLevel - 1];
    psMenuItem = &psCurrentMenu->psItems[0];
    ItemNumb[g_nMenuLevel] = 0;
    g_nMenuLevel--;
    g_MenuItemIndex = ItemNumb[g_nMenuLevel];

    DisplayMenu();
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), ReturnFunc, ReturnFunc, ReturnFunc);

/**
 * @brief ����
*/
void UpFunc(void)
{
    /*ȡ��ѡ��״̬*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, BACK_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*�ж��±�״̬*/
    if (g_MenuItemIndex > 0)
        g_MenuItemIndex--;
    else
        g_MenuItemIndex = psCurrentMenu->nItems - 1;
    /*����ѡ��״̬*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, SELECT_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*��ѡ�еĲ˵�*/
    ItemNumb[g_nMenuLevel] = g_MenuItemIndex;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), UpFunc, UpFunc, UpFunc);

/**
 * @brief ����
*/
void DownFunc(void)
{
    /*ȡ��ѡ��״̬*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, BACK_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*�ж��±�״̬*/
    if (g_MenuItemIndex >= ((psCurrentMenu->nItems) - 1))
        g_MenuItemIndex = 0;
    else
        g_MenuItemIndex++;
    /*����ѡ��״̬*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, SELECT_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /**/
    ItemNumb[g_nMenuLevel] = g_MenuItemIndex;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), DownFunc, DownFunc, DownFunc);

void Menu_test(void)
{
    MENU_setScreenColor(GREEN);
}