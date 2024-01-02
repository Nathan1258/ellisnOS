//
// Created by Nathan Ellis on 02/01/2024.
//
#include "console.h"
#include "string.h"

static uint16 *g_vga_buffer;
static uint32 g_vga_index;
uint8 g_fore_color = COLOR_WHITE, g_back_color = COLOR_BLACK;

void console_putchar(char ch) {
    if (ch == '\t') {
        for(int i = 0; i < 4; i++) {
            g_vga_buffer[g_vga_index++] = vga_item_entry(' ', g_fore_color, g_back_color);
            vga_set_cursor_pos(cursor_pos_x++, cursor_pos_y);
        }
    } else if (ch == '\n') {
        console_newline();
    } else {
        if (ch > 0) {
            g_vga_buffer[g_vga_index++] = vga_item_entry(ch, g_fore_color, g_back_color);
            vga_set_cursor_pos(++cursor_pos_x, cursor_pos_y);
        }
    }
}

void console_newline() {
    // Check for newline character before rendering
    if (cursor_pos_y >= VGA_HEIGHT - 1) {
        // Scroll the entire screen up by one row
        for (uint32 i = 0; i < VGA_TOTAL_ITEMS - VGA_WIDTH; i++) {
            g_vga_buffer[i] = g_vga_buffer[i + VGA_WIDTH];
        }
        g_vga_index = (cursor_pos_y + 1) * VGA_WIDTH;
        // Update the cursor position
        cursor_pos_x = 0;
        cursor_pos_y = VGA_HEIGHT - 1;
        vga_set_cursor_pos(cursor_pos_x, cursor_pos_y);
    } else {
        // Update the cursor position
        g_vga_index = (cursor_pos_y + 1) * VGA_WIDTH;
        cursor_pos_x = 0;
        ++cursor_pos_y;
        vga_set_cursor_pos(cursor_pos_x, cursor_pos_y);
    }
}

void printf(const char *format, ...) {
    char **arg = (char **)&format;
    int c;
    char buf[32];

    arg++;

    memset(buf, 0, sizeof(buf));
    while ((c = *format++) != 0) {
        if (c != '%')
            console_putchar(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                    for (p2 = p; *p2; p2++)
                        ;
                    for (; p2 < p + pad; p2++)
                        console_putchar(pad0 ? '0' : ' ');
                    while (*p)
                        console_putchar(*p++);
                    break;

                default:
                    console_putchar(*((int *)arg++));
                    break;
            }
        }
    }
}