#include "menu_core.h"
#include "headfile.h"
#include "menu_display.h"
#include "shell.h"
#include "menu_button.h"

uint8 g_MenuItemIndex = 0;     //菜单项
uint8 g_nMenuLevel = 0;        //菜单页
uint8 g_lastMenuItemIndex = 0; //上次菜单项
uint8 ItemNumb[MAX_MENU_LEVELS];
tMenuItem psMenuItem, psCurrentMenuItem; //菜单页里的菜单项，当前菜单页里的菜单项
tMenu psPrevMenu[MAX_MENU_LEVELS];       //
tMenu psCurrentMenu;                     //当前菜单页

/*private functions*/
void IdleFunc(void);
void Menu_test(void);
/*------------------------------ Menu level 3 -------------------------------*/
struct sMenuItem SubMenuItems_1_1[] = {
    /*菜单项名称, 要执行的函数，要执行的函数，下一级*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1_1 = {"     Level 3", SubMenuItems_1_1, COUNT_OF(SubMenuItems_1_1)};

struct sMenuItem SubMenuItems_1_2[] = {
    /*菜单项名称, 要执行的函数，要执行的函数，下一级*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1_2 = {"     Level 3", SubMenuItems_1_2, COUNT_OF(SubMenuItems_1_2)};

/*------------------------------ Menu level 2 -------------------------------*/
struct sMenuItem SubMenuItems_1[] = {
    /*菜单项名称, 要执行的函数，要执行的函数，下一级*/
    {"Item 1", IdleFunc, IdleFunc, &SubMenu_1_1},
    {"Item 2", IdleFunc, IdleFunc, &SubMenu_1_2},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_1 = {"     Level 2", SubMenuItems_1, COUNT_OF(SubMenuItems_1)};

struct sMenuItem SubMenuItems_2[] = {
    /*菜单项名称, 要执行的函数（对应的功能函数），上下动作时的功能，下一级菜单*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_2 = {"     Level 2", SubMenuItems_2, COUNT_OF(SubMenuItems_2)};

struct sMenuItem SubMenuItems_3[] = {
    /*菜单项名称, 要执行的函数（对应的功能函数），上下动作时的功能，下一级菜单*/
    {"Item 1", IdleFunc, IdleFunc, NULL},
    {"Item 2", IdleFunc, IdleFunc, NULL},
    {"Item 3", IdleFunc, IdleFunc, NULL},
    {"Item 4", IdleFunc, IdleFunc, NULL},
    {"Item 5", IdleFunc, IdleFunc, NULL}};
struct sMenu SubMenu_3 = {"     Level 2", SubMenuItems_3, COUNT_OF(SubMenuItems_3)};
/*------------------------------ Menu level 1 -------------------------------*/
struct sMenuItem MainMenuItems[] = {
    /*菜单项名称, 要执行的函数（对应的功能函数），上下动作时的功能，下一级菜单*/
    {"Item One", IdleFunc, IdleFunc, &SubMenu_1},
    {"Item Two", IdleFunc, IdleFunc, &SubMenu_2},
    {"Item Three", IdleFunc, IdleFunc, &SubMenu_3},
    {"Item Four", IdleFunc, IdleFunc, NULL},
    {"Item Five", IdleFunc, IdleFunc, NULL}};
struct sMenu MainMenu = {"     Main menu", MainMenuItems, COUNT_OF(MainMenuItems)};

/**
 * @brief 初始化菜单
*/
void Menu_Init(void)
{
    //当前菜单页
    psCurrentMenu = &MainMenu;
    //上一级菜单
    psPrevMenu[g_nMenuLevel] = psCurrentMenu;
    //当前菜单页里的菜单项
    psMenuItem = MainMenuItems;
}

/**
 * @brief 显示菜单
*/
void DisplayMenu(void)
{
    uint32 line = 0, index = 0;
    tMenuItem psMenuItem2;

    /*黑色填充屏幕*/
    MENU_setScreenColor(BACK_COLOR);
    /*显示菜单标题*/
    MENU_DisplayStringLine(line, psCurrentMenu->pszTitle);
    line++;
    /*显示出当前菜单页所有菜单项*/
    while (!(index >= (psCurrentMenu->nItems)))
    {
        psMenuItem2 = &(psCurrentMenu->psItems[index]);
        MENU_DisplayStringLine(line, psMenuItem2->pszTitle);
        line++;
        index++;
    }

    /*显示选中的菜单项*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, SELECT_COLOR);
    psMenuItem = &(psCurrentMenu->psItems[g_MenuItemIndex]);
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
}

/**
 * @brief 初始化菜单相关设施
*/
void MainMenuInit(void)
{
    /*ips200屏幕初始化,注意这里更改菜单使用的屏幕后，要更改display.h中的宏定义*/
    ips200_init();
    /*LCD屏幕初始化*/
    //lcd_init();
    /*菜单按钮初始化*/
    menuButtonInit();
    /*初始化菜单相关配置*/
    Menu_Init();
    /*显示菜单*/
    DisplayMenu();
}

/**
 * @brief 菜单任务
*/
void MenuTask(void)
{
    uint8 key_event;
    /*获得按键动作*/
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
 * @brief 选中动作
*/
void SelFunc(void)
{
    /*得到当前菜单页中的菜单项*/
    psCurrentMenuItem = psMenuItem;

    /*存在子菜单跳转*/
    if (psMenuItem->psSubMenu != NULL)
    {
        g_nMenuLevel++;
        g_MenuItemIndex = ItemNumb[g_nMenuLevel];
        /*得到当前菜单项的子菜单*/
        psCurrentMenu = psCurrentMenuItem->psSubMenu;
        psMenuItem = &(psCurrentMenu->psItems)[g_MenuItemIndex];
        DisplayMenu();
        psPrevMenu[g_nMenuLevel] = psCurrentMenu;
    }
    /*执行菜单项函数*/
    psCurrentMenuItem->pfMenuFunc();
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), SelFunc, SelFunc, SelFunc);

/**
 * @brief 返回动作
*/
void ReturnFunc(void)
{
    psMenuItem->pfUpDownMenuFunc();

    if (g_nMenuLevel == 0)
        g_nMenuLevel++;

    /*得到上一级菜单*/
    psCurrentMenu = psPrevMenu[g_nMenuLevel - 1];
    psMenuItem = &psCurrentMenu->psItems[0];
    ItemNumb[g_nMenuLevel] = 0;
    g_nMenuLevel--;
    g_MenuItemIndex = ItemNumb[g_nMenuLevel];

    DisplayMenu();
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), ReturnFunc, ReturnFunc, ReturnFunc);

/**
 * @brief 向上
*/
void UpFunc(void)
{
    /*取消选中状态*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, BACK_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*判断下标状态*/
    if (g_MenuItemIndex > 0)
        g_MenuItemIndex--;
    else
        g_MenuItemIndex = psCurrentMenu->nItems - 1;
    /*更新选中状态*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, SELECT_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*被选中的菜单*/
    ItemNumb[g_nMenuLevel] = g_MenuItemIndex;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), UpFunc, UpFunc, UpFunc);

/**
 * @brief 向下
*/
void DownFunc(void)
{
    /*取消选中状态*/
    MENU_drawRectagnleFill(0, (g_MenuItemIndex + 1) * ITEM_H, ITEM_W, (g_MenuItemIndex + 2) * ITEM_H, BACK_COLOR);
    psMenuItem = &psCurrentMenu->psItems[g_MenuItemIndex];
    MENU_DisplayStringLine((g_MenuItemIndex + 1), psMenuItem->pszTitle);
    /*判断下标状态*/
    if (g_MenuItemIndex >= ((psCurrentMenu->nItems) - 1))
        g_MenuItemIndex = 0;
    else
        g_MenuItemIndex++;
    /*更新选中状态*/
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