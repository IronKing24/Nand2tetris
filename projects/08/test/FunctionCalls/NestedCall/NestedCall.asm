@256
D=A
@SP
M=D
@Sys.init$ret1752335495
D=A
@SP
A=M
M=D
@SP
M=M+1
@R1
D=M
@SP
A=M
M=D
@SP
M=M+1
@R2
D=M
@SP
A=M
M=D
@SP
M=M+1
@R3
D=M
@SP
A=M
M=D
@SP
M=M+1
@R4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@5
D=D-A
@ARG
M=D
@Sys.init
0;JMP
(Sys.init$ret1752335495)
(END)
@END
0;JMP
//function Sys.init
(Sys.init)
//PUSH CONSTANT 4000
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 0
@SP
AM=M-1
D=M
@R3
M=D
//PUSH CONSTANT 5000
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 1
@SP
AM=M-1
D=M
@R4
M=D
//call Sys.main
@Sys.main$ret948776191
D=A
@SP
A=M
M=D
@SP
M=M+1
@R1
D=M
@SP
A=M
M=D
@SP
M=M+1
@R2
D=M
@SP
A=M
M=D
@SP
M=M+1
@R3
D=M
@SP
A=M
M=D
@SP
M=M+1
@R4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@5
D=D-A
@ARG
M=D
@Sys.main
0;JMP
(Sys.main$ret948776191)
//POP TEMP 1
@SP
AM=M-1
D=M
@R6
M=D
(Sys.init$LOOP)
//goto LOOP
@Sys.init$LOOP
0;JMP
//function Sys.main
(Sys.main)
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
//PUSH CONSTANT 4001
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 0
@SP
AM=M-1
D=M
@R3
M=D
//PUSH CONSTANT 5001
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 1
@SP
AM=M-1
D=M
@R4
M=D
//PUSH CONSTANT 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP LOCAL 1
@LCL
D=M
@1
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
//PUSH CONSTANT 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP LOCAL 2
@LCL
D=M
@2
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
//PUSH CONSTANT 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP LOCAL 3
@LCL
D=M
@3
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
//PUSH CONSTANT 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1
//call Sys.add12
@Sys.add12$ret1334311595
D=A
@SP
A=M
M=D
@SP
M=M+1
@R1
D=M
@SP
A=M
M=D
@SP
M=M+1
@R2
D=M
@SP
A=M
M=D
@SP
M=M+1
@R3
D=M
@SP
A=M
M=D
@SP
M=M+1
@R4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@6
D=D-A
@ARG
M=D
@Sys.add12
0;JMP
(Sys.add12$ret1334311595)
//POP TEMP 0
@SP
AM=M-1
D=M
@R5
M=D
//PUSH LOCAL 0
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH LOCAL 1
@LCL
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH LOCAL 2
@LCL
D=M
@2
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH LOCAL 3
@LCL
D=M
@3
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH LOCAL 4
@LCL
D=M
@4
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//add
@SP
AM=M-1
D=M
@SP
AM=M-1
M=D+M
@SP
M=M+1
//add
@SP
AM=M-1
D=M
@SP
AM=M-1
M=D+M
@SP
M=M+1
//add
@SP
AM=M-1
D=M
@SP
AM=M-1
M=D+M
@SP
M=M+1
//add
@SP
AM=M-1
D=M
@SP
AM=M-1
M=D+M
@SP
M=M+1
//return
@LCL
D=M
@R14
M=D
@5
A=D-A
D=M
@R15
M=D
@ARG
D=M
@0
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R14
AM=M-1
D=M
@R4
M=D
@R14
AM=M-1
D=M
@R3
M=D
@R14
AM=M-1
D=M
@R2
M=D
@R14
AM=M-1
D=M
@R1
M=D
@R15
A=M
0;JMP
//function Sys.add12
(Sys.add12)
//PUSH CONSTANT 4002
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 0
@SP
AM=M-1
D=M
@R3
M=D
//PUSH CONSTANT 5002
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1
//POP POINTER 1
@SP
AM=M-1
D=M
@R4
M=D
//PUSH ARGUMENT 0
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH CONSTANT 12
@12
D=A
@SP
A=M
M=D
@SP
M=M+1
//add
@SP
AM=M-1
D=M
@SP
AM=M-1
M=D+M
@SP
M=M+1
//return
@LCL
D=M
@R14
M=D
@5
A=D-A
D=M
@R15
M=D
@ARG
D=M
@0
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R14
AM=M-1
D=M
@R4
M=D
@R14
AM=M-1
D=M
@R3
M=D
@R14
AM=M-1
D=M
@R2
M=D
@R14
AM=M-1
D=M
@R1
M=D
@R15
A=M
0;JMP