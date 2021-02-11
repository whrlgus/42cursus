https://cs.lmu.edu/~ray/notes/nasmtutorial/

### 어셈블리 hello world 출력

- `hello.s` 파일

```assembly
          global    start

          section   .text
start:   mov       rax, 0x02000004                  ; system call for write
          mov       rdi, 1                  ; file handle 1 is stdout
          mov       rsi, message            ; address of string to output
          mov       rdx, 13                 ; number of bytes
          syscall                           ; invoke operating system to do the write
          mov       rax, 0x02000001                 ; system call for exit
          xor       rdi, rdi                ; exit code 0
          syscall                           ; invoke operating system to exit

          section   .data
message:  db        "Hello, World", 10      ; note the newline at the end
```

- 컴파일 및 링크, 실행

```bash
brew install nasm
nasm -fmacho64 hello.s && ld -e start -static hello.o && ./a.out
```

https://stackoverflow.com/a/65570963



