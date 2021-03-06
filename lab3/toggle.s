	.arch msp430g2553

jt:				;jump table
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.global stateAdvance_
stateAdvance_:				;state
	cmp #5, &state 		;range check
	jhs default		;jump to default
	mov &state, r12	 	;moves state into r12
	add r12, r12		;add r12 into r12 
	mov jt(r12), r0		;start at first in jt



case1:
	call #drawJet
	call #song_play
	mov #1, &redrawScreen
	mov #1, &state
	jmp end

case2:
	mov #0x0000, r12
	mov #0xffff, r13
	mov #0xf800, r14
	mov #0x001f, r15
	call #drawJet
	mov #0, &redrawScreen
	mov #0, &state
	jmp end

case3:
	mov #0xffff, r12
	mov #0x0000, r13
	mov #0x07ff, r14
	mov #0x053f, r15
	call #clearScreen
	mov #0, &redrawScreen
	mov #0, &state
	jmp end

case4:
	call #stopSong
	mov #4, &state
	jmp end

default:		
	jump end


end:
	ret





