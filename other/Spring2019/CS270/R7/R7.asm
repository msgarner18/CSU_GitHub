; Recitation 7
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR mirror           ; call function
                HALT

; Parameter and return value
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                               ; Mirrors bits 7:0 to 15:8
                                     ; ~20 lines of assembly code
 
                LD R0,Param          ;Load parameter into register 0
          
                AND R1, R1, #0       ;Make a copy of register 0 to register 1, which stores the result
                ADD R1, R0, R1

                LD R2, Mask          ;Load Mask into register 2

                AND R1, R2, R1       ;Use the Mask to clear bits 15:8 in the result
                
                AND R2, R2, #0       ;initialize R2 to 1-source mask
                ADD R2, R2, #1

                AND R3, R3, #0       ;initialize R3 to 1-destination mask
                ADD R3, R3, #1
 
                AND R4, R4, #0       ;this is counter
                ADD R4, R4, #8
                                     ;shift R3 left 8 bits
                LEFTSHIFT ADD R3,R3,R3 
                          ADD R4, R4, #-1
                BRp LEFTSHIFT

                AND R4, R4, #0       ;counter
                ADD R4, R4, #8

                LOOP AND R5, R0, R2
                     BRz SKIP
                     ADD R1, R3, R1      ;checks if bit in source mask =1. If so, jump to ADDBIT
SKIP                 ADD R2, R2, R2  ;shift source Mask left
                     ADD R3, R3, R3  ;shift destination Mask left
                     ADD R4, R4, #-1 ;decrement counter
                BRp LOOP
                     
                 
                ST R1,Result         ; store result
                RET

                 
;--------------------------------------------------------------------------
               .END

