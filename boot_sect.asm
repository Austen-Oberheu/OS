[bits 16]
[org 0x7c00]

mov bp, 0x9000
mov sp, bp
mov bx, MSG_REAL_MODE
call print_string
call switch_to_pm

;jmp $

;mov [BOOT_DRIVE], dl

;mov bp, 0x8000
;mov sp, bp

;mov bx, 0x9000
;mov dh, 5
;mov dl, [BOOT_DRIVE]
;call disk_load


;jmp $

%include "print_string.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
;%include "print_hex.asm"
;%include "disk_load.asm"
%include "switch_to_pm.asm"

[bits 32]

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	
	jmp $

HELLO_MSG:
	db 'Booting OS', 0
BOOT_DRIVE:
	db 0
MSG_REAL_MODE:
	db 'Started in 16-bit Real Mode', 0
MSG_PROT_MODE:
	db 'Successfully landed in 32-bit Protected Mode', 0

times 510-($-$$) db 0

dw 0xaa55

;times 256 dw 0xdada
;times 256 dw 0xface