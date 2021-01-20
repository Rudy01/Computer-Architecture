addnms:
	lodd on:            ; start xtmr with on value of 8
        stod 4095    
        call xbsywt:             
        loco str1:          ; load prompt string
        call nextw:         ; print string with nextw
        call bgndig:        ; get input
        lodd binum:         ; load binum input
        stod sum:           ; store result in sum
        loco str1:          ; prompt user again
        call nextw:         ; print string
        call bgndig:        ; get user input
        lodd binum:         ; load second number
        addd sum:           ; add second number to first
        stod sum:           ; store result in sum result
        jneg overflow:      ; if the sum is negative, handle overflow
        loco str2:          ; load sum string
        call nextw:         ; print string
        call convert:       ; convert number back to ascii
        loco 0              ; no error so return 0
        halt
