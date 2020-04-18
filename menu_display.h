#ifndef __MENU_DISPLAY_H
#define __MENU_DISPLAY_H

#include "headfile.h"

/*确定菜单使用的屏幕:TFT OR IPS200*/
/*在使用tft时，一行最多容纳16个字符*/
#define USE_IPS200
//#define USE_TFT

#ifdef  USE_IPS200 
#define ITEM_H  16              //菜单项高度
#define ITEM_W  IPS200_W        //菜单项宽度
#define MENU_H  IPS200_H        //菜单页高度
#define MENU_W  IPS200_W        //菜单页宽度
#define SCREEN_MARGIN   10      //菜单项边距
#define BACK_COLOR      BLACK   //背景颜色
#define CLEAR_COLOR     BLACK   //清屏颜色
#define SELECT_COLOR    RED     //选中颜色
#endif

#ifdef   USE_TFT       
#define ITEM_H  16
#define ITEM_W  TFT_X_MAX
#define MENU_H  TFT_Y_MAX
#define MENU_W  TFT_X_MAX
#define SCREEN_MARGIN   0
#define BACK_COLOR      BLACK
#define CLEAR_COLOR     BLACK
#define SELECT_COLOR    RED
#endif

/*定义颜色数据类型*/
typedef uint16 COLOR;

extern void MENU_setScreenColor(COLOR color);
extern void MENU_DisplayStringLine(uint8 line, const char *str);
extern void MENU_drawRectagnleFill(uint16 x_0, uint16 y_0, uint16 x_1, uint16 y_1, COLOR color);

#endif