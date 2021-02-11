			global		_ft_strlen

			section		.text
_ft_strlen:
			mov			rax, -1

check:
			inc			rax
			cmp			BYTE [rdi + rax], 0
			jne			check
			ret

