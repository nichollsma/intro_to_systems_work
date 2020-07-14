			.orig x3000
			JSR GETNUM
			JSR GETNUM
			HALT

GETNUM
			;Save R1, R2, and R7
			ST R1, GN_SR1
			ST R2, GN_SR2
			ST R7, GN_SR7

TOP			;Get char
			AND R0, R0, #0
			GETC
			ST R0, CHAR

			;Store ascii values of limits
			LD R1, N48
			LD R2, N57
			
			;Test if char is a number
			ADD R0, R0, R2
			BRP TOP
			LD R0, CHAR
			ADD R0, R0, R1
			BRN TOP

			;Restore R1 and R2
			LD R1, GN_SR1
			LD R2, GN_SR2
			LD R7, GN_SR7
			
			RET
GN_SR1 		.fill 0
GN_SR2 		.fill 0
GN_SR7 		.fill 0
CHAR		.fill 0
N48			.fill -48
N57			.fill -57
			.end