; Author: Fritz Sieker
;
; ------------------------------------------------------------------------
; Begin reserved section - do not change ANYTHING is this section

               .ORIG x3000
               BR Main

option         .BLKW 1          ; select routine to test
data1          .BLKW 1          ; use ONLY for testing
data2          .BLKW 1          ; use ONLY for testing

stackBase      .FILL X4000      ; initial sttack pointer

Main           LD R6,stackBase  ; initialize stack pointer
               LD R0,option     ; select routine to test
               BRZ printNum ; option = 0 means test printNum

               ADD R0,R0,#-1
               BRZ getDigit ; option = 1 means test getDidit

               ADD R0,R0,#-1
               BRZ divRem   ; option = 2 means test divRem

               HALT             ; invalid option if here

testPrintNum                    ; call printNum(x, base)
               LD R0,data2
               PUSH R0          ; push base argument
               LD R0,data1
               PUSH R0          ; push value argument
               JSR printNum
               ADD R6,R6,#2     ; caller clean up 2 parameters
               BR endTest

testGetDigit                    ; call getChar(val)
               LD R0,data1
               PUSH R0          ; push argument (val to convert to ASCII)
               JSR getDigit     ; 
               POP R0           ; get the corresponding character
               ADD R6,R6,#1     ; caller clean up 1 parameter
               OUT              ; print the digit
               NEWLN
               BR endTest

testDivRem                      ; call divRem(num, denom, *quotient, *remainder)
               LEA R0,data2     ; get pointer to remainder (&data2)
               PUSH R0
               LEA R0,data1     ; get pointer to quotient (&data1)
               PUSH R0
               LD R0,data2
               PUSH R0          ; push demoninator
               LD R0,data1
               PUSH R0          ; push numerator
               JSR divRem       ; call routine
               ADD R6,R6,#4     ; caller clean up 4 parameters

endTest        LEA R0,endMsg
               PUTS
theEnd         HALT             ; look at data1/data2 for quotient/remainder

                                ; useful constants
endMsg         .STRINGz "\nTest complete!\n"

negSign        .FILL    x2D     ; ASCII '-'
digits         .STRINGZ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; up to base 36

; end reserved section

; ------------------------------------------------------------------------
; Author: your name goes here
; ------------------------------------------------------------------------
;
; C declaration: char getDigit (int val);

getDigit                        ; callee setup
               ADD R6, R6, #-1  ; make space for return value
               PUSH R7          ; save return address
               PUSH R5          ; save caller's frame pointer
               ADD R5, R6, #-1  ; set frame pointer to address of the first local
                                ; no local variables in this stack

                                ; code for getDigit        
               LEA R0, digits   ; point to start of string
               LDR R1, R5, #4   ; access given variable
               ADD R1, R1, R0   ; get address
               LDR R1, R1, #0   ; get value from address

                                ; callee cleanup
               STR R1, R5, #3   ; Store return value 
                                ; no local variables to remove
               POP R5           ; POP caller's frame pointer
               POP R7           ; POP return address

               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void divRem(int num, int denom, int*quotient, int*remainder);

divRem                           ; callee setup
                                 ; no return vals?
               PUSH R7
               PUSH R5
               ADD R5, R6, #-1  ; set frame pointer to address of first local
               ADD R6, R6, #-1  ; make space for locals

                                ; code for dicRem (divRem)?
               ;LDR R0, R5, #3  ; set R0 to numerator
               LDR R1, R5, #4   ; set R1 to denominator
               
               NOT R1, R1       ; R1 = negated denominator
               ADD R1, R1, #1
               PUSH R1          ; PUSH negdenominator
               AND R2, R2, #0   ; set R2 to 0
               LDR R4, R5, #3   ; set total to 0

               DIVIDE ADD R2, R2, #1
                      ADD R4, R4, R1
               BRp DIVIDE

               ADD R2, R2, #-1
               LDR R1, R5, #4
               ADD R4, R4, R1

               LDR R0, R5, #5   ; load R0 with pointer to remainder
               STR R2, R0, #0
               LDR R0, R5, #6   ; load R0 with pointer to quotient
               STR R4, R0, #0
                      
                                ; callee cleanup
                                ; STR return value
               ADD R6, R6, #1   ; remove 1 local variable
               POP R5           
               POP R7

               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void printNum (int val, int base);

printNum                        ; callee setup
                                ; no return val for this func
               PUSH R7          ; save return address
               PUSH R5          ; save caller's frame pointer
               ADD R5, R6, #-1  ; set frame pointer to address of first local
               ADD R6, R6, #-2  ; make space for two locals

                                ; code for printNum
               LDR R0, R5, #3   ; x
               OUT
               LDR R1, R5, #4   ; base

               ;LEA R2, R2       ; PUSH remainder pointer
               ;PUSH R2          
               ;LEA R2, R3       ; PUSH quotient pointer
               ;PUSH R2
               ;PUSH R1
               ;PUSH R0
               ;JSR divRem
                                ; no return val
               ADD R6, R6, #2   ; remove both local variables
               POP R5           
               POP R7
                                ; callee cleanup
               RET              ; return
; ------------------------------------------------------------------------
               .END
