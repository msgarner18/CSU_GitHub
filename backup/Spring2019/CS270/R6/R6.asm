; Recitation 6
; Author:      Mark Garner
; Date:        9/28/18
; Email:       markshanegarner@gmail.com
; Class:       CS270
;
; Description: Implements integer (16-bit) addition, subtraction, and
;              multiplication.
;
;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!
                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine (option 0)
                .FILL IntSub         ; Address of IntSub routine (option 1)
                .FILL IntMul         ; Address of IntMul routine (option 2)

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
IntAdd          LD R0, Param1                     ; R0 <- &Param1 
                LD R1, Param2                     ; R1 <- &Param2
                ADD R0, R0, R1                    ; R0 <- R1+R0
                ST R0, Result                     ;store R0 into Result
                                     ; DON'T USE REGISTERS 5, 6, or 7!
                RET
;------------------------------------------------------------------------------
IntSub          LD R0, Param1        ;R0 <- &Param1
                LD R1, Param2        ;R1 <- &Param2
                NOT R1, R1           ;R1 <- ~R1
                ADD R1, R1, #1         ;R1 <- R1+1
                ADD R0, R0, R1       ;R0 <- R0+R1
                ST R0,Result         ;store R0 into result
                                     ; Solution has ~6 instructions
                                     ; DON'T USE REGISTERS 5, 6, or 7!
                RET

;------------------------------------------------------------------------------
IntMul          AND R2, R2, #0       ;initialize sum to 0
                LD R0, Param1        ;R0 <- &Param1
                LD R1, Param2        ;R1 <- &Param2
                NOT R3, R0
                ADD R3, R3, #1     
                ADD R2, R2, R3

                Loop ADD R2, R2, R0   ;R3 <- R3+R0
                    ADD R1, R1,#-1    ;R2 <- R2-1
                BRzp Loop               ;Repeat if R2 != 0
                ST R2, Result
                                     ; Solution has ~9 instructions
                                     ; DON'T USE REGISTERS 5, 6, or 7!
                RET

;------------------------------------------------------------------------------
               .END








