@ crt0.S: Execution startup routine
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>

        .file   "crt0.S"
        .text

        .global _start
_start:
        @ Needs more code.
        LDMFD sp!, {r0-r1}
        bl main
        SWI EXIT_SWI

