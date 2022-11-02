; P5 Assignment
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine     (option 0)
                .FILL IntSub         ; Address of IntSub routine     (option 1)
                .FILL IntMul         ; Address of IntMul routine     (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine   (option 3)
                .FILL LeftShift      ; Address of LeftShift routine  (option 4)
                .FILL RightShift     ; Address of RightShift routine (option 5)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
Option          .FILL #0             ; Which function to call
Param1          .BLKW 1              ; Space to specify first parameter
Param2          .BLKW 1              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd          LD R0, Param1        
                LD R1, Param2
                ADD R0, R1, R0
                ST R0, Result
                                     ; Your code goes here (~4 lines)
                RET
;------------------------------------------------------------------------------
                
IntSub          LD R0, Param1
                LD R1, Param2
                NOT R1, R1
                ADD R1, R1, #1 
                ADD R0, R0, R1
                ST R0, Result
                                     ; Your code goes here (~6 lines)
                RET
;------------------------------------------------------------------------------
IntMul          AND R2, R2, #0
                LD R0, Param1
                LD R1, Param2
                NOT R3, R0
                ADD R3, R3, #1
                ADD R2, R2, R3
       
                LOOP ADD R2, R2, R0
                     ADD R1, R1, #-1
                BRzp LOOP
                ST R2, Result
                                     ; Your code goes here (~9 lines)
                RET
;------------------------------------------------------------------------------
BinaryOr        LD R0, Param1
                LD R1, Param2
                NOT R0, R0
                NOT R1, R1
                AND R0, R1, R0
                NOT R0, R0
                ST R0, Result
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
LeftShift       LD R0, Param1
                LD R1, Param2
                AND R2, R2, #0

                SHIFTLEFT ADD R0, R0, R0
                     ADD R1, R1, #-1
                BRp SHIFTLEFT
                ST R0, Result
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
RightShift      LD R0, Param1
                LD R1, Param2
                AND R4, R4, #0
                ADD R4, R4, #1           
                NOT R4, R4

                ANDWITHZERO AND R0, R0, R4              ;make right-most bit equal 0
                            AND R3, R3, #0
                            DIVIDEBYTWO ADD R3, R3, #1
                                        ADD R0, R0, #-2
                            BRp DIVIDEBYTWO
                            ADD R0, R0, R3
                            ADD R1, R1, #-1
                BRp ANDWITHZERO
                ST R0, Result
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~16 lines)
                RET
;------------------------------------------------------------------------------
               .END 
