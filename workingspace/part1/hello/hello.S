@ hello.S: Hello world! in assembly
@
@ Authors: Group Member 1 <aanklesh>
@          Group Member 2 <jitenm>
	   Group Member 3 <achheda>
@ Date:    Thu Oct 10 4:50:40

#include <bits/swi.h>
#include <bits/fileno.h>
	.file	"hello.S"
	.text

	.global	_start
_start:
	mov r0, #STDOUT_FILENO		@STDOUT
	adr r1, hello_str 	@Passing the string
	mov r2, #hello_size	@Passing the size
	swi WRITE_SWI		@man 2 write
	mov r0, #0		@EXIT_STATUS
	swi EXIT_SWI


hello_str:
	.ascii "Hello world!\n"
	.set hello_size, .-hello_str
