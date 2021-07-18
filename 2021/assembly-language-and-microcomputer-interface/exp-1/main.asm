; Use 386 
.386
.model flat, stdcall
option casemap:none

includelib msvcrt.lib
include msvcrt.inc

.data
target			dword		0
num_a			dword		0
num_b			dword		0
num_c			dword		0
num_d			dword		0
input_msg		byte		"Please input your target number: ", 0
input_format	byte		"%d", 0
output_msg		byte		"%d = %d^2 + %d^2 + %d^2 + %d^2", 0ah, 0

.code
start:
	; Print some msgs
	invoke		crt_printf, offset input_msg
	invoke		crt_scanf, offset input_format, offset target
	; Start loops
	; Loop a
	mov			num_a, 0
Loop_a:
	mov			eax, num_a
	mul			num_a
	cmp			eax, target
	jg			Return
	; Loop b
	mov			eax, num_a
	mov			num_b, eax
Loop_b:
	mov			eax, num_b
	mul			num_b
	cmp			eax, target
	jg			Loop_a_inc
	; Loop c
	mov			eax, num_b
	mov			num_c, eax
Loop_c:
	mov			eax, num_c
	mul			num_c
	cmp			eax, target
	jg			Loop_b_inc
	; Loop d
	mov			eax, num_c
	mov			num_d, eax
Loop_d:
	mov			eax, num_d
	mul			num_d
	cmp			eax, target
	jg			Loop_c_inc
	xor			ebx, ebx
	mov			eax, num_a
	mul			num_a
	add			ebx, eax
	mov			eax, num_b
	mul			num_b
	add			ebx, eax
	mov			eax, num_c
	mul			num_c
	add			ebx, eax
	mov			eax, num_d
	mul			num_d
	add			ebx, eax
	cmp			ebx, target
	je			Return
	add			num_d, 1
	jmp			Loop_d
Loop_c_inc:
	add			num_c, 1
	jmp			Loop_c
Loop_b_inc:
	add			num_b, 1
	jmp			Loop_b
Loop_a_inc:
	add			num_a, 1
	jmp			Loop_a
Return:
	; Finish
	invoke		crt_printf, offset output_msg, target, num_a, num_b, num_c, num_d
	mov			eax, 0
	ret 
end start
