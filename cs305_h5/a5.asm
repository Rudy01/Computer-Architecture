addnms:	     lodd on:		; start xtmr with on value of 8
	            stod 4095
	            call xbsywt:
	            loco str1:	; load prompt string
	            call nextw:	; print string with nextw
	            call bgndig: ; get input
	            lodd binum:	 ; load binum input
	            stod sum:	 ; store result in sum
	            loco str1:	 ; prompt user again
	            call nextw:	 ; print string
	            call bgndig: ; get user input
	            lodd binum:	 ; load second number
	            addd sum:	 ; add second number to first
	            stod sum:	 ; store result in sum result
	            jneg overflow: ; if the sum is negative, handle overflow
	            loco str2:	   ; load sum string
	            call nextw:	   ; print string
	            call convert:  ; convert number back to ascii
	            loco 0	   ; no error so return 0
	            halt
bgndig:	     lodd on:		; turn receiver on
	            stod 4093	; turn receiver on
	            call rbsywt: ; call receiver
	            lodd 4092	 ; get first digit
	            subd numoff: ; subtract ascii offset of 48
	            push	 ; Push to stack
nxtdig:	     call rbsywt:	 ; loop again to call receiver
	            lodd 4092	 ; get next digit
	            stod nxtchar:
	            subd nl:	; see if newline was entered
	            jzer endnum: ; if newline, go to endnum
	            ; mult 10    ; 10 multiply stack val by 10
	            lodd nxtchar:
	            subd numoff: ; subtract ascii offset
	            addl 0
	            stol 0
	            jump nxtdig: ; loop until done
endnum:	     pop		 ; get final number
	            stod binum:	 ; store in binum
	            loco 0
	            retn	; Done so return.
overflow:	   loco str3:	; load overflow prompt
	            call nextw:	; display to screen
	            lodd cneg1:	; load -1 into ac to signify error
	            halt
convert:	    lodd on:	; turn on transmitter
	            stod 4095	;
	            lodd cneg1:	; push all 1s onto stack
	            push	;
	            lodd c10:	;
	            push	; push 10 onto stack
	            jump answer:
answer:	     lodd sum:		; load final sum
	            jzer printAns: ; jump to print when done
	            lodd c10:	   ;
	            push	   ; push 10 onto stack
	            lodd sum:	   ;
	            push	   ; push answer onto stack
	            ; div          ; answer / mask
	            pop		   ; pop result into ac
	            stod sum:	   ; store in final sum
	            pop		   ;
	            insp 2	   ; clean the stack
	            addd numoff:   ; convert back to ascii
	            push	   ; push result to stack
	            jump answer:   ; go until done
printAns:	   pop		   ;
	            jneg done:	   ; if negative, done printing
	            stod 4094	   ; put ac into xtmr buffer
	            call xbsywt:   ; wait until done
	            jump printAns: ; print next char

	;;  The following functions were given by Professor Hendrickson in order to get two input numbers and print the prompt string

nextw:	      pshi
	            addd one:
	            stod pstr:
	            pop
	            jzer crnl:
	            stod 4094
	            push
	            subd c255:
	            jneg crnl:
	            call sb:
	            insp 1
	            push
	            call xbsywt:
	            pop
	            stod 4094
	            call xbsywt:
	            lodd pstr:
	            jump nextw:
crnl:	       lodd cr:
	            stod 4094
	            call xbsywt:
	            lodd nl:
	            stod 4094
	            call xbsywt:
	            retn
xbsywt:	     lodd 4095
	            subd c10:
	            jneg xbsywt:
	            retn
rbsywt:	     lodd 4093
	            subd c10:
	            jneg rbsywt:
	            retn
sb:	         loco 8
loop1:	      jzer finish:
	            subd one:
	            stod lpcnt:
	            lodl 1
	            jneg add1:
	            addl 1
	            stol 1
	            lodd lpcnt:
	            jump loop1:
add1:	       addl 1
	            addd one:
	            stol 1
	            lodd lpcnt:
	            jump loop1:
finish:	     lodl 1
	            retn

done:	       retn


	.LOC 200
cneg1:	      -1
one:	         1
numoff:	     48
c255:	      255
nxtchar:	     0
binum:	       0
sum:	         0
lpcnt:	       0
pstr:	        0
on:	          8
c10:	       10
nl:	         10
cr:	         13
str1:	  "Please enter a 1-5 digit number followed by enter"
str2:	  "The sum of these integers is: "
str3:	  "Overflow, no sum possible"
	
