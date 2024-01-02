//
// Created by Nathan Ellis on 02/01/2024.
//

#include "vga.h"

#ifndef ELLISNOS_CONSOLE_H
#define ELLISNOS_CONSOLE_H

static uint8 cursor_pos_x = 0, cursor_pos_y = 0;

void console_putchar(char ch);
void printf(const char *format, ...);
void console_newline();

#endif //ELLISNOS_CONSOLE_H
