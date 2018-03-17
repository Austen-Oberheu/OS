#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

char terminalArray[VGA_WIDTH][VGA_HEIGHT];

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

/* Note the use of the volatile keyword to prevent the compiler from eliminating dead stores. */
volatile uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n' )
	{
		terminal_column = 0;
		terminal_row += 1;
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row += 1;
		if (++terminal_row == VGA_HEIGHT)
		{
			/*const size_t index = terminal_row * VGA_WIDTH + terminal_column;

			for (size_t i = 0; i < terminal_buffer[index]; i++)
			{
				terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
			}
*/
			/*terminal_row = 0;
			terminal_column = 0;
			for (size_t y = 0; y < VGA_HEIGHT; y++)
			{
				for (size_t x = 0; x < VGA_WIDTH; x++)
				{
					terminalArray[x][y] = terminalArray[x][y + 1];
					terminal_putchar(terminalArray[x][y]);
				}
			}*/
		}
			
	}

	terminalArray[terminal_column][terminal_row] = c;


}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

extern "C"
{
	void kernel_main(void)
	{

		/* Initialize terminal interface */
		terminal_initialize();

		/* Newline support is left as an exercise. */
		terminal_writestring("Hello, kernel World!1 \n");
		terminal_writestring("This is the next line.2 \n");
		terminal_writestring("Hello, kernel World!3 \n");
		terminal_writestring("This is the next line.4 \n");
		terminal_writestring("Hello, kernel World!5 \n");
		terminal_writestring("This is the next line.6 \n");
		terminal_writestring("Hello, kernel World!7 \n");
		terminal_writestring("This is the next line.8 \n");
		terminal_writestring("Hello, kernel World!9 \n");
		terminal_writestring("This is the next line.10 \n");
		terminal_writestring("Hello, kernel World!11 \n");
		terminal_writestring("This is the next line.12 \n");
		terminal_writestring("Hello, kernel World!13 \n");
		terminal_writestring("This is the next line.14 \n");
		terminal_writestring("Hello, kernel World!15 \n");
		terminal_writestring("This is the next line.16 \n");
		terminal_writestring("Hello, kernel World!17 \n");
		terminal_writestring("This is the next line.18 \n");
		terminal_writestring("Hello, kernel World!19 \n");
		terminal_writestring("This is the next line.20 \n");
		terminal_writestring("Hello, kernel World!21 \n");
		terminal_writestring("This is the next line.22 \n");
		terminal_writestring("Hello, kernel World!23 \n");
		terminal_writestring("This is the next line.24 \n");
		terminal_writestring("Hello, kernel World!25 \n");
		terminal_writestring("This is the next line.26 \n");
		terminal_writestring("Hello, kernel World!27 \n");
		terminal_writestring("This is the next line.28 \n");
		terminal_writestring("Hello, kernel World!29 \n");
		terminal_writestring("This is the next line.30 \n");
		terminal_writestring("THIS IS THE FINAL LINE.31");
	}
}