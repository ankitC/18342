@ hello.S: Hello world! in assembly
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date
#include <bits/swi.h>

	.file	"hello.S"
	.text

	.global	_start
_start:
	adr r0, hello_str
	swi WRITE_SWI
	mov r0, #0
	swi EXIT_SWI


hello_str:
	.ascii "Hello world!\n"
