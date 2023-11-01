/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "stm32h735g_discovery.h"
#include "stm32h735g_discovery_conf.h"
#include "stm32h735g_discovery_lcd.h"
#include "stm32h735g_discovery_ts.h"
#include "stm32h7xx_hal.h"
#include <stdint.h>

#include "printer.h"
#include "stm_slint_platform.h"


extern "C" {
extern void SystemClock_Config(void);
extern uint32_t InitTouchScreen(void);
extern void MPU_Config(void);
extern void CPU_CACHE_Enable(void);
}

int main(void) {

  uint32_t lcd_width, lcd_height, i, j;

  /* Configure the MPU attributes as Write Through for external HYPERRAM*/
  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();
  /* STM32H7xx HAL library initialization:
      - Systick timer is configured by default as source of time base, but user
        can eventually implement his proper time base source (a general purpose
        timer for example or other time source), keeping in mind that Time base
        duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
        handled in milliseconds basis.
      - Set NVIC Group Priority to 4
      - Low Level Initialization
    */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure LED1 and LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);

  /*##-1- LCD Configuration ##################################################*/
  BSP_LCD_InitEx(0, LCD_ORIENTATION_LANDSCAPE, LCD_PIXEL_FORMAT_RGB565,
                 LCD_DEFAULT_WIDTH, LCD_DEFAULT_HEIGHT);

  /* Get the LCD width and height */
  BSP_LCD_GetXSize(0, &lcd_width);
  BSP_LCD_GetYSize(0, &lcd_height);

  BSP_LCD_DisplayOn(0);
  BSP_LCD_SetActiveLayer(0, 0);

  /* Clear the LCD */
  for (i = 0; i < lcd_height; i++) {
    for (j = 0; j < lcd_width; j++) {
      *((unsigned short *)(LCD_LAYER_1_ADDRESS) + i * lcd_width + j) =
          LCD_COLOR_RGB565_YELLOW;
    }
  }

  InitTouchScreen();

  init_slint(LCD_LAYER_0_ADDRESS, LCD_LAYER_1_ADDRESS, LCD_DEFAULT_WIDTH,
             LCD_DEFAULT_HEIGHT);
  BSP_LED_On(LED1);
  run_printer();
  BSP_LED_On(LED2);

  while (1) {
    ;
  }
}