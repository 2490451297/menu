#include "menu_display.h"
#include "headfile.h"

/**
 * @brief:设置屏幕显示颜色
*/
void MENU_setScreenColor(COLOR color)
{
    #ifdef USE_IPS200
    ips200_clear(color);
    #endif
    #ifdef  USE_TFT
    lcd_clear(color);
    #endif
}

/**
 * @brief:屏幕显示一行信息
*/
void MENU_DisplayStringLine(uint8 line, const char *str)
{
    #ifdef  USE_IPS200
    ips200_showstr(SCREEN_MARGIN, line, str);
    #endif
    #ifdef  USE_TFT
    lcd_showstr(SCREEN_MARGIN, line, str);
    #endif
}

/**
 * @brief:画一个点
*/
void MENU_drwaPoint(uint16 x, uint16 y, COLOR color)
{
    #ifdef  USE_IPS200
    ips200_drawpoint(x, y, color);
    #endif
    #ifdef  USE_TFT
    lcd_drawpoint(x, y, color);
    #endif
}

/**
 * @brief:画水平线
*/
void MENU_HLine(uint16 x_0, uint16 y_0, uint16 x_1, COLOR color)
{
    uint16 temp;
    if (x_0 > x_1)
    {
        temp = x_0;
        x_0 = x_1;
        x_1 = temp;
    }
    do
    {
        MENU_drwaPoint(x_0, y_0, color);
        x_0++;
    } while (x_0 <= x_1);
}

/**
 * @brief:画垂直线
*/
void MENU_RLine(uint16 x_0, uint16 y_0, uint16 y_1, COLOR color)
{
    uint16 temp;
    if (y_0 > y_1)
    {
        temp = y_0;
        y_0 = y_1;
        y_1 = temp;
    }
    do
    {
        MENU_drwaPoint(x_0, y_0, color);
        y_0++;
    } while (y_0 <= y_1);
}

/**
 * @brief：画一块区域
*/
void MENU_drawRectagnleFill(uint16 x_0, uint16 y_0, uint16 x_1, uint16 y_1, COLOR color)
{
    #ifdef USE_IPS200
    uint16 temp;

    if (x_0 > x_1)
    {
        temp = x_0;
        x_0 = x_1;
        x_1 = temp;
    }
    if (y_0 > y_1)
    {
        temp = y_0;
        y_0 = y_1;
        y_1 = temp;
    }

    if (y_0 == y_1)
        MENU_HLine(x_0, y_0, x_1, color);
    if (x_0 == x_1)
        MENU_RLine(x_0, y_0, y_1, color);

    while (y_1 >= y_0)
    {
        MENU_HLine(x_0, y_0, x_1, color);
        y_0++;
    }
    #endif

    #ifdef USE_TFT
    lcd_fill(x_0, y_0, x_1, y_1, color);
    #endif
}
