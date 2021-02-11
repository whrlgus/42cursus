			global		_ft_strcmp

			section		.text
_ft_strcmp:
			mov			rax, 0
check:
			mov			al, BYTE [rdi]
			mov			bl, BYTE [rsi]
			cmp			al, 0
			je			exit
			cmp			bl, 0
			je			exit
			cmp			al, bl
			jne			exit
			inc			rdi
			inc			rsi
			jmp			check
exit:
			movzx		rax, al
			movzx		rbx, bl
			sub			rax, rbx
			ret
