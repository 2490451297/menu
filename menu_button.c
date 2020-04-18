#include "menu_button.h"

/**
 * @brief 按键初始化
 * 
*/
void menuButtonInit(void)
{
    gpio_init(UP_BUTTON, GPI, 0, GPIO_PIN_CONFIG);
    gpio_init(DOWN_BUTTON, GPI, 0, GPIO_PIN_CONFIG);
    gpio_init(SURE_BUTTON, GPI, 0, GPIO_PIN_CONFIG);
    gpio_init(CANCEL_BUTTON, GPI, 0, GPIO_PIN_CONFIG);
}

/**
 * @brief 按键中断初始化
*/
void menuButtonIRQInit(void)
{
    gpio_interrupt_init(UP_BUTTON, RISING, GPIO_INT_CONFIG);
    gpio_interrupt_init(DOWN_BUTTON, RISING, GPIO_INT_CONFIG);
    gpio_interrupt_init(SURE_BUTTON, RISING, GPIO_INT_CONFIG);
    gpio_interrupt_init(CANCEL_BUTTON, RISING, GPIO_INT_CONFIG);
}

/**
 * @brief 按键按下事件
*/
uint8 menuPressEvent(void)
{
    static uint8 button_status_flag = 1;
    if (button_status_flag && (gpio_get(UP_BUTTON) == 0 || gpio_get(DOWN_BUTTON) == 0 || gpio_get(SURE_BUTTON) == 0 || gpio_get(CANCEL_BUTTON) == 0))
    {
        systick_delay_ms(1);
        button_status_flag = 0;

        if (gpio_get(UP_BUTTON) == 0)
            return BUTTON_UP_EVENT;
        else if (gpio_get(DOWN_BUTTON) == 0)
            return BUTTON_DOWN_EVENT;
        else if (gpio_get(SURE_BUTTON) == 0)
            return BUTTON_SURE_EVENT;
        else if (gpio_get(CANCEL_BUTTON) == 0)
            return BUTTON_CANCEL_EVENT;
    }
    else
    {
        if (gpio_get(UP_BUTTON) == 1 && gpio_get(DOWN_BUTTON) == 1 && gpio_get(SURE_BUTTON) == 1 && gpio_get(CANCEL_BUTTON) == 1)
            button_status_flag = 1;
    }
    return 0;
}
