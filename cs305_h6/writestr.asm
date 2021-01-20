convert:
	lodd on:
	stod 4095               ; 
        lodd cneg1:             ; push all 1s onto stack
        push                    ; 
        lodd c10:              ; 
        push                    ; push 10 onto stack
        jump answer:            
answer:
	lodd sum:               ; load final sum
        jzer printAns:          ; jump to print when done
        lodd c10:              ; 
        push                    ; push 10 onto stack
        lodd sum:               ; 
        push                    ; push answer onto stack
        div                     ; answer / mask
        pop                     ; pop result into ac
        stod sum:               ; store in final sum
        pop                     ; 
        insp 2                  ; clean the stack
        addd numoff:            ; convert back to ascii
        push                    ; push result to stack
        jump answer:            ; go until done
printAns:
	pop                     ; 
        jneg done:              ; if negative, done printing
        stod 4094               ; put ac into xtmr buffer
        call xbsywt:            ; wait until done
        jump printAns:          ; print next char

