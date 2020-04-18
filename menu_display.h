#ifndef __MENU_DISPLAY_H
#define __MENU_DISPLAY_H

#include "headfile.h"

/*ȷ���˵�ʹ�õ���Ļ:TFT OR IPS200*/
/*��ʹ��tftʱ��һ���������16���ַ�*/
#define USE_IPS200
//#define USE_TFT

#ifdef  USE_IPS200 
#define ITEM_H  16              //�˵���߶�
#define ITEM_W  IPS200_W        //�˵�����
#define MENU_H  IPS200_H        //�˵�ҳ�߶�
#define MENU_W  IPS200_W        //�˵�ҳ���
#define SCREEN_MARGIN   10      //�˵���߾�
#define BACK_COLOR      BLACK   //������ɫ
#define CLEAR_COLOR     BLACK   //������ɫ
#define SELECT_COLOR    RED     //ѡ����ɫ
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

/*������ɫ��������*/
typedef uint16 COLOR;

extern void MENU_setScreenColor(COLOR color);
extern void MENU_DisplayStringLine(uint8 line, const char *str);
extern void MENU_drawRectagnleFill(uint16 x_0, uint16 y_0, uint16 x_1, uint16 y_1, COLOR color);

#endif