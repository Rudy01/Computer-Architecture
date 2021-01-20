bgndig:
	lodd on:
	stod 4093               ; turn receiver on 
        call rbsywt:            ; call receiver
        lodd 4092               ; get first digit
        subd numoff:            ; subtract ascii offset of 48
        push                    ; Push to stack
nxtdig:
	call rbsywt:            ; loop again to call receiver
        lodd 4092               ; get next digit
        stod nxtchar:          
        subd nl:                ; see if newline was entered
        jzer endnum:            ; if newline, go to endnum
        mult 10                 ; multiply stack val by 10
        lodd nxtchar:           
        subd numoff:            ; subtract ascii offset
        addl 0                  
        stol 0                   
        jump nxtdig:            ; loop until done
