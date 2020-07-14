		.orig x3000
		LD R1, N97
		
		;get char
		AND R0, R0, #0
		GETC
		ADD R0, R0, R1
		BRNP END
		LEA R0, HELLO
		PUTS
END		HALT		
HELLO 	.stringz "HELLO"		
N97 	.fill -97
		.end

