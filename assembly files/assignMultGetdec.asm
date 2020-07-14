			.orig x3000
			JSR MULT
			JSR MULT
			HALT

GETNUM
			;Save R1, R2, and R7
			ST R1, GN_SR1
			ST R2, GN_SR2
			ST R3, GN_SR3
			ST R7, GN_SR7

GNTOP		;Get char
			AND R0, R0, #0
			GETC
			ST R0, CHAR

			;Store ascii values of limits
			LD R1, N48
			LD R2, N57
			LD R3, NNL
			
			;Test if char is a number or a new line character
			ADD R0, R0, R3
			BRZ GNBOTTOM
			LD R0, CHAR
			ADD R0, R0, R2
			BRP GNTOP
			LD R0, CHAR
			ADD R0, R0, R1
			BRN GNTOP
			
GNPRINT		;Print the digit / character that is stored in R0
			LD R0, CHAR
			OUT

GNBOTTOM	;Restore R1 and R2
			LD R0, CHAR
			LD R1, GN_SR1
			LD R2, GN_SR2
			LD R3, GN_SR3
			LD R7, GN_SR7
			
			RET
GN_SR1 		.fill 0
GN_SR2 		.fill 0
GN_SR3		.fill 0
GN_SR7 		.fill 0
CHAR		.fill 0
N48			.fill -48
N57			.fill -57
NNL			.fill -10
			.end
			
MULT
			;Save original values and 
			ST R1, M_SR1
			ST R2, M_SR2
			
			;Test if either numbers are zero
			AND R0, R0, #0
			ADD R0, R0, R1
			BRNP MLOOP
			BRNZP MBOTTOM
			
			
			RET
FNUM		.fill 0
SNUM		.fill 0			