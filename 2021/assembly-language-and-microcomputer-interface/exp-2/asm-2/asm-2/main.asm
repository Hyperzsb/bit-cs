.386
.model flat, stdcall
option casemap:none

includelib msvcrt.lib
include msvcrt.inc

.data
num_a_str			byte		200 dup(0)
num_b_str			byte		200 dup(0)
result				dword		405	dup(0)
len_a				dword		0
len_b				dword		0
len_result			dword		0
flag				dword		0
index				dword		0
i					dword		0
j					dword		0
temp				dword		0
msg_1				byte		"Please input numbers: ", 0ah, 0
msg_2				byte		"Number a = ", 0
msg_3				byte		"Number b = ", 0
input_format		byte		"%s", 0
msg_4				byte		"Result = ", 0
output_zero_format	byte		"0", 0
output_sign_format	byte		"-", 0
output_num_format	byte		"%d", 0

.code
start:
	; Input numbers
	invoke		crt_printf, offset msg_1
	invoke		crt_printf, offset msg_2
	invoke		crt_scanf, offset input_format, offset num_a_str
	invoke		crt_printf, offset msg_3
	invoke		crt_scanf, offset input_format, offset num_b_str
	; Get numbers' length
	invoke		crt_strlen, offset num_a_str
	mov			len_a, eax
	invoke		crt_strlen, offset num_b_str
	mov			len_b, eax
	; Judge sign of num a
Judge_sign_a:
	cmp			num_a_str[0], 02dh
	jne			Judge_sign_b
	xor			flag, 1
	mov			i, 0
Move_loop_a:
	mov			eax, len_a
	sub			eax, 1
	cmp			i, eax
	jnl			Move_loop_a_end
	mov			eax, i
	mov			bl, num_a_str[eax+1]
	mov			num_a_str[eax], bl
	add			i, 1
	jmp			Move_loop_a
Move_loop_a_end:
	sub			len_a, 1
	; End of judegement
	; Judge sign of num b
Judge_sign_b:
	cmp			num_b_str[0], 02dh
	jne			Multiply
	xor			flag, 1
	mov			i, 0
Move_loop_b:
	mov			eax, len_b
	sub			eax, 1
	cmp			i, eax
	jnl			Move_loop_b_end
	mov			eax, i
	mov			bl, num_b_str[eax+1]
	mov			num_b_str[eax], bl
	add			i, 1
	jmp			Move_loop_b
Move_loop_b_end:
	sub			len_b, 1
	; End of judegement
	; Start to multiply
Multiply:
	mov			eax, len_b
	sub			eax, 1
	mov			i, eax
Multiply_loop_i:
	cmp			i, 0
	jl			Get_result_len
	mov			eax, len_a
	sub			eax, 1
	mov			j, eax
Multiply_loop_j:
	cmp			j, 0
	jl			Multiply_loop_i_end
	mov			eax, len_b
	sub			eax, i
	mov			ebx, len_a
	sub			ebx, j
	add			eax, ebx
	sub			eax, 2
	mov			index, eax
	xor			eax, eax
	mov			ebx, j
	mov			al, num_a_str[ebx]
	sub			al, '0'
	mov			ebx, i
	mov			ah, num_b_str[ebx]
	sub			ah, '0'
	mul			ah
	mov			ebx, index
	mov			ecx, result[ebx*4]
	add			ecx, eax
	mov			result[ebx*4], ecx

Carry_loop:
	mov			ebx, index
	cmp			result[ebx*4], 10
	jl			Multiply_loop_j_end
	xor			edx, edx
	mov			eax, result[ebx*4]
	mov			ebx, 10
	div			ebx
	mov			ebx, index
	mov			ecx, result[ebx*4+4]
	add			ecx, eax
	mov			result[ebx*4+4], ecx
	mov			result[ebx*4], edx
	add			index, 1
	jmp			Carry_loop
Multiply_loop_j_end:
	sub			j, 1
	jmp			Multiply_loop_j
Multiply_loop_i_end:
	sub			i, 1
	jmp			Multiply_loop_i

Get_result_len:
	mov			eax, 404
	sub			eax, len_result
Result_len_loop:
	cmp			result[eax*4], 0
	jne			Print_result_zero
	cmp			len_result, 404
	jg			Print_result_zero
	add			len_result, 1
	mov			eax, 404
	sub			eax, len_result
	jmp			Result_len_loop	
Print_result_zero:
	mov			eax, 405
	sub			eax, len_result
	mov			len_result, eax
	invoke		crt_printf, offset msg_4
	cmp			len_result, 0
	jne			Print_result_sign
	invoke		crt_printf, offset output_zero_format
	jmp			Return
Print_result_sign:
	cmp			flag, 1
	jne			Print_result
	invoke		crt_printf, offset output_sign_format
Print_result:
	mov			eax, len_result
	sub			eax, 1
	mov			i, eax
Print_result_loop:
	cmp			i, 0
	jl			Return
	mov			eax, i
	invoke		crt_printf, offset output_num_format, result[eax*4]
	sub			i, 1
	jmp			Print_result_loop
Return:
	mov			eax, 0
	ret
end start