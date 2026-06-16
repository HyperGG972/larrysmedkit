#include <stdint.h>

void kernel_main(void) {
	volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

	for (int i = 0; i < 80 * 25; i++) {
		vga_buffer[i] = 0x0F20;
	}

	const char* message = "Welcome to Larry's Med Kit v0.2 - Still in bare metal";
	for (int i = 0; message[i] != '\0'; i++) {

	    vga_buffer[i] = (0x0F << 8) | message[i];

	}
}	
