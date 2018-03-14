print_string:
	pusha
	mov ah, 0x0e
	mov al, [bx]
	int 0x10
	add bx, 0x01
	cmp al, 0
	jne print_string
	popa
	ret

