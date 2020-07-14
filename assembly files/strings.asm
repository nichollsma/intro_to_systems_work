.orig x3000
JSR TOUPPER
JSR TOUPPER
PUTS
HALT

TOUPPER
			;save registers
			ST R0, TU_SR0
			ST R1, TU_SR1
			ST R2, TU_SR2
			ST R3, TU_SR3
			ST R4, TU_SR4
			
			;Store ascii values of limits
			LD R2, N97
			LD R3, N122
			LD R4, N32
			
			;get first char
			AND R1, R1, #0
			LDR R1, R0, #0			
			ST R1, CHAR
			
COMP		;test if char is a lowercase letter or 0
			ADD R1, R1, #0
			BRZ STOP
			ADD R1, R1, R2
			BRN GET
			LD R1, CHAR
			ADD R1, R1, R3
			BRP GET
			
			;change to upper
			LD R1, CHAR
			ADD R1, R1, R4
			STR R1, R0, #0
			
GET			;get next character
			ADD R0, R0, #1
			LDR R1, R0, #0
			ST R1, CHAR
			BRNZP COMP
			
STOP		;end of file
			LD R0, TU_SR0
			LD R1, TU_SR1
			LD R2, TU_SR2
			LD R3, TU_SR3
			LD R4, TU_SR4
			RET
TU_SR0		.fill 0
TU_SR1		.fill 0
TU_SR2		.fill 0
TU_SR3		.fill 0
TU_SR4		.fill 0
CHAR		.fill 0
N97			.fill -97
N122		.fill -122
N32			.fill -32
			.end
