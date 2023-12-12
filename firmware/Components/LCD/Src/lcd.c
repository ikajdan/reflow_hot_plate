/**
 ******************************************************************************
 * @file           : lcd.c
 * @brief          : LCD library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "ssd1306.h"
#include "fsm.h"
#include <string.h>
#include <stdio.h>

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const char *state_names[] = {
        "Preheat",
        "Soak",
        "Reflow",
        "Cooldown",
        "Idle"
};

/* Public variables ----------------------------------------------------------*/
bool LCD_REDRAW = false;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void LCD_ShowWelcome() {
    ssd1306_SetCursor(30, 0);
    ssd1306_WriteString("Reflow", Font_11x18, White);
    ssd1306_SetCursor(14, 18);
    ssd1306_WriteString("Hot Plate", Font_11x18, White);
    ssd1306_Line(0, 42, 128, 42, White);
    ssd1306_SetCursor(25, 54);
    ssd1306_WriteString("F/W:", Font_7x10, White);
    ssd1306_SetCursor(59, 54);
    ssd1306_WriteString(FIRMWARE_VERSION, Font_7x10, White);
    ssd1306_UpdateScreen();
}

void LCD_ShowProgresBar() {
    int width = SSD1306_WIDTH * hfsm1.duration / hfsm1.profile_duration / 1000;
    ssd1306_SetCursor(0, 0);
    ssd1306_FillRectangle(0, 0, width, 3, White);
}

void LCD_ShowProcessInfo() {
    static char buffer[32];
    static int x = 0;
    static int y = 0;

    // State
    sprintf(buffer, "%s", state_names[hfsm1.state]);
    x = SSD1306_WIDTH / 2 - strlen(buffer) * 7 / 2;
    y = 7;
    ssd1306_SetCursor(x, y);
    ssd1306_WriteString(buffer, Font_7x10, White);

    // Temperature
    sprintf(buffer, "%.1f ~C", hfsm1.temperature);
    x = SSD1306_WIDTH / 2 - strlen(buffer) * 11 / 2;
    y = (SSD1306_HEIGHT + 4) / 2 - 18 / 2;
    ssd1306_SetCursor(x, y);
    ssd1306_WriteString(buffer, Font_11x18, White);

    // Profile name
    sprintf(buffer, "%s", hfsm1.name);
    x = SSD1306_WIDTH / 2 - strlen(buffer) * 7 / 2;
    y = SSD1306_HEIGHT - 10;
    ssd1306_SetCursor(x, y);
    ssd1306_WriteString(buffer, Font_7x10, White);
}

void LCD_ScheduleRedraw() {
    LCD_REDRAW = true;
}
