			global		_ft_strcpy

			section		.text
_ft_strcpy:
			push		rdi
check:
			mov			al, BYTE [rsi]
			mov			BYTE [rdi], al
			cmp			al, 0
			je			exit
			inc			rdi
			inc			rsi
			jmp			check

exit:
			pop			rax
			ret
