// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(start)
    //check we are not repeting the same frame.
    @KBD
    D=M
    @input
    D=D-M
    @start
    D;JEQ
    //get the new input
    @KBD
    D=M
    @inputTrue
    D;JGT    
    @input
    M=0 //set color value
    @inputFalse
    0;JMP
(inputTrue)
    //set color value
    @input
    M=-1
(inputFalse)
    //get first pixel
    @SCREEN
    D=A-1
    @pixel
    M=D
(fill)
    //loop paint all pixels
    @pixel
    D=M
    @24576
    D=A-D
    @start
    D;JLE
    @input
    D=M
    @pixel
    AM=M+1
    M=D
    @fill
    0;JMP