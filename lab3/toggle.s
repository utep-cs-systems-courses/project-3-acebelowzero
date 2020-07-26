	.arch msp430g2553



jt:				;jump table
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.global stateAdvance
stateAdvance:				;state
	cmp #5, &state 		;range check
	jhs default		;jump to default
	mov &state, r12	 	;moves state into r12
	add r12, r12		;add r12 into r12 
	mov jt(r12), r0		;start at first in jt

default:		
	jmp end

case1:
	call #stopSong
	mov #1, &redrawScreen
	mov #1, &state
	jmp end

case2:
	call #stopSong
	mov #0x0000, r12
	mov #0xffff, r13
	mov #0xf800, r14
	mov #0x001f, r15
	call #customShape
	mov #0, &redrawScreen
	mov #0, &state
	jmp end

case3:
	mov #0xffff, r12
	mov #0x0000, r13
	mov #0x07ff, r14
	mov #0x053f, r15
	call #customShape
	call #soundEffect
	mov #0, &state
	jmp end

case4:	
	call #drawCustomString
	mov #4, &state
	jmp end



end:
	ret

	/*state machine to play a song*/
st:				;state
	.word 0

	.text


jumptable:				;jump table
	.word default_
	.word case_1
	.word case_2
	
	.global playSong_
playSong_:
	cmp #3, &st 		;range check
	jmp default_		;jump to default
	mov &st, r12	 	;moves state into r12
	add r12, r12		;add r12 into r12 
	mov jumptable(r12), r0		;start at first in jt

default_:			
	mov #0, r12
	call #buzzer_set_period				

case_1:
	call #playSong
	mov #2, &st
        jmp end_

case_2:
	
	call #stopSong
	mov #1, &st
        jmp end_
	
end_:
	ret		


	
	/*function to stop the music*/
	.global stopSong
stopSong:
	mov #0, r12
	call #buzzer_set_period
	ret



