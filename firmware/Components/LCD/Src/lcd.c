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
void LCD_DrawWelcome() {
    ssd1306_SetCursor(30, 0);
    ssd1306_WriteString("Reflow", Font_11x18, White);
    ssd1306_SetCursor(14, 18);
    ssd1306_WriteString("Hot Plate", Font_11x18, White);
    ssd1306_Line(0, 42, 128, 42, White);
    ssd1306_SetCursor(25, 54);
    ssd1306_WriteString("F/W:", Font_7x10, White);
    ssd1306_SetCursor(59, 54);
    ssd1306_WriteString(FIRMWARE_VERSION, Font_7x10, White);
}

void LCD_DrawMenu() {
    // Header text
    ssd1306_SetCursor(4, 0);
    ssd1306_WriteString("Select a profile:", Font_7x10, White);
}

void LCD_DrawPrompt(LCD_Prompt_Type type) {
    // Loading bar
    static uint32_t shift = 0;
    if(shift <= 40) {
        ssd1306_FillRectangle(0, 0, shift, 3, White);
    } else {
        ssd1306_FillRectangle(shift - 40, 0, shift, 3, White);
    }
    shift = (shift + 4) % (SSD1306_WIDTH + 40);

    if(type == LCD_DONE) {
        ssd1306_SetCursor(36, 19);
        ssd1306_WriteString("Done", Font_11x18, White);
        ssd1306_SetCursor(8, 54);
        ssd1306_WriteString("Press any key...", Font_7x10, White);
    } else if(type == LCD_ABORTED) {
        ssd1306_SetCursor(25, 19);
        ssd1306_WriteString("Aborted", Font_11x18, White);
        ssd1306_SetCursor(8, 54);
        ssd1306_WriteString("Press any key...", Font_7x10, White);
    } else if(type == LCD_ERROR) {
        ssd1306_SetCursor(36, 19);
        ssd1306_WriteString("Error", Font_11x18, White);
        ssd1306_SetCursor(8, 54);
        ssd1306_WriteString("Press any key...", Font_7x10, White);
    } else if(type == LCD_WAITING) {
        ssd1306_SetCursor(25, 16);
        ssd1306_WriteString("Cooling", Font_11x18, White);
        ssd1306_SetCursor(42, 34);
        ssd1306_WriteString("Down", Font_11x18, White);
        ssd1306_SetCursor(25, 54);
        ssd1306_WriteString("Please wait", Font_7x10, White);
    }
}

void LCD_DrawProcessInfo() {
    // Progres bar
    int width = SSD1306_WIDTH * hfsm1.duration / hfsm1.profile_duration / 1000;
    ssd1306_SetCursor(0, 0);
    ssd1306_FillRectangle(0, 0, width, 3, White);

    static char buffer[32];
    static int x = 0;
    static int y = 0;

    // State
    sprintf(buffer, "%s", state_names[hfsm1.stage]);
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
