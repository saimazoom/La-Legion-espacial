;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20170415-
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Thu Apr 01 23:15:43 2021



	MODULE	parser


	INCLUDE "z80_crt0.hdr"


	SECTION	rodata_compiler

._symbol_list
	defw	i_1+0
	defw	i_1+5
	defw	i_1+10
	defw	i_1+15
	defw	i_1+20
	defw	i_1+25
	defw	i_1+30
	defw	i_1+35
	defw	i_1+40
	defw	i_1+45
	defw	i_1+50
	defw	i_1+55
	defw	i_1+60
	defw	i_1+65
	defw	i_1+70
	defw	i_1+75
	defw	i_1+80
	defw	i_1+85
	defw	i_1+90
	defw	i_1+6
	defw	i_1+94
	defw	i_1+98
	defw	i_1+46
	defw	i_1+1
	defw	i_1+102
	defw	i_1+106
	defw	i_1+110
	defw	i_1+114
	defw	i_1+118
	defw	i_1+122
	defw	i_1+126
	defw	i_1+27
	defw	i_1+115
	defw	i_1+103
	defw	i_1+130
	defw	i_1+67
	defw	i_1+22
	defw	i_1+99
	defw	i_1+133
	defw	i_1+12
	defw	i_1+136
	defw	i_1+139
	defw	i_1+82
	defw	i_1+47
	defw	i_1+142
	defw	i_1+7
	defw	i_1+57
	defw	i_1+145
	defw	i_1+148
	defw	i_1+52
	defw	i_1+151
	defw	i_1+37
	defw	i_1+123
	defw	i_1+111
	defw	i_1+154
	defw	i_1+157
	defw	i_1+17
	defw	i_1+160
	defw	i_1+163
	defw	i_1+107
	defw	i_1+166
	defw	i_1+169
	defw	i_1+172
	defw	i_1+175
	defw	i_1+178
	defw	i_1+42
	defw	i_1+181
	defw	i_1+184
	defw	i_1+187
	defw	i_1+190
	defw	i_1+193
	defw	i_1+196
	defw	i_1+87
	defw	i_1+199
	defw	i_1+202
	defw	i_1+205
	defw	i_1+208
	defw	i_1+211
	defw	i_1+214
	defw	i_1+217
	defw	i_1+220
	defw	i_1+223
	defw	i_1+226
	defw	i_1+229
	defw	i_1+232
	defw	i_1+235
	defw	i_1+238
	defw	i_1+241
	defw	i_1+244
	defw	i_1+247
	defw	i_1+250
	defw	i_1+253
	defw	i_1+256
	defw	i_1+259
	defw	i_1+262
	defw	i_1+265
	defw	i_1+268
	defw	i_1+271
	defw	i_1+274
	defw	i_1+277
	defw	i_1+280
	defw	i_1+283
	defw	i_1+286
	defw	i_1+289
	defw	i_1+292
	defw	i_1+295
	defw	i_1+298
	defw	i_1+301
	defw	i_1+304
	defw	i_1+307
	defw	i_1+310
	defw	i_1+313
	defw	i_1+316
	defw	i_1+319
	defw	i_1+322
	defw	i_1+325

	SECTION	code_compiler

	SECTION	data_compiler

._playerPrompt
	defw	i_1+328
	SECTION	code_compiler

	SECTION	data_compiler

._gDEBUGGER
	defm	""
	defb	0


	SECTION	code_compiler

	SECTION	data_compiler

._gGRAPHICSON
	defm	""
	defb	1


	SECTION	code_compiler

	SECTION	data_compiler

._gSOUNDSON
	defm	""
	defb	1


	SECTION	code_compiler

	SECTION	data_compiler

._gINTERRUPTDISABLED
	defm	""
	defb	1


	SECTION	code_compiler

	SECTION	data_compiler

._gSHOWWARNINGS
	defm	""
	defb	1


	SECTION	code_compiler

	SECTION	data_compiler

._ginEND
	defm	""
	defb	0


	SECTION	code_compiler

	SECTION	data_compiler

._ginQUIT
	defm	""
	defb	0


	SECTION	code_compiler

	SECTION	data_compiler

._gENTRY_FOR_DOALL
	defm	""
	defb	0


	SECTION	code_compiler

	SECTION	data_compiler

._verbos_debug_t
	defw	i_1+331
	defb	1
	defw	i_1+339
	defb	2
	defw	i_1+347
	defb	3
	defw	i_1+353
	defb	4
	defw	i_1+361
	defb	5
	defw	i_1+367
	defb	6
	defw	i_1+376
	defb	7
	defw	i_1+383
	defb	8
	defw	i_1+389
	defb	9
	defw	i_1+396
	defb	10
	defw	i_1+403
	defb	11
	defw	i_1+409
	defb	12
	defw	i_1+4
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._adverbios_t
	defw	i_1+416
	defb	2
	defw	i_1+422
	defb	3
	defw	i_1+428
	defb	4
	defw	i_1+434
	defb	5
	defw	i_1+440
	defb	6
	defw	i_1+446
	defb	6
	defw	i_1+4
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._preposiciones_t
	defw	i_1+48
	defb	2
	defw	i_1+172
	defb	2
	defw	i_1+22
	defb	3
	defw	i_1+452
	defb	3
	defw	i_1+67
	defb	4
	defw	i_1+456
	defb	4
	defw	i_1+462
	defb	5
	defw	i_1+468
	defb	6
	defw	i_1+474
	defb	7
	defw	i_1+479
	defb	7
	defw	i_1+485
	defb	8
	defw	i_1+490
	defb	8
	defw	i_1+16
	defb	9
	defw	i_1+80
	defb	10
	defw	i_1+496
	defb	11
	defw	i_1+500
	defb	12
	defw	i_1+506
	defb	13
	defw	i_1+512
	defb	13
	defw	i_1+518
	defb	14
	defw	i_1+524
	defb	15
	defw	i_1+530
	defb	16
	defw	i_1+4
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._pronombres_t
	defw	i_1+241
	defb	2
	defw	i_1+536
	defb	2
	defw	i_1+540
	defb	2
	defw	i_1+545
	defb	2
	defw	i_1+47
	defb	2
	defw	i_1+551
	defb	2
	defw	i_1+555
	defb	2
	defw	i_1+560
	defb	2
	defw	i_1+247
	defb	2
	defw	i_1+566
	defb	2
	defw	i_1+4
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._conjunciones_t
	defw	i_1+570
	defb	2
	defw	i_1+572
	defb	2
	defw	i_1+578
	defb	2
	defw	i_1+584
	defb	2
	defw	i_1+590
	defb	2
	defw	i_1+592
	defb	2
	defw	i_1+594
	defb	2
	defw	i_1+4
	defb	0

	SECTION	code_compiler


._initParser
	ld	hl,_flags
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,255	;const
	push	hl
	call	memset_callee
	ld	hl,_flags+38
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+1
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+30
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+31
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+32
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+58
	ld	(hl),#(1 % 256 % 256)
	ld	hl,_flags
	ld	(hl),#(0 % 256 % 256)
	ld	a,#(1 % 256 % 256)
	ld	(_gDESCRIBE_LOCATION_FLAG),a
	ld	a,#(0 % 256 % 256)
	ld	(_ginEND),a
	ld	hl,_flags+33
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+34
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+44
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+35
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+45
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+36
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+43
	ld	(hl),#(0 % 256 % 256)
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gNUM_OBJECTS),a
.i_17
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_18
	ld	hl,_gNUM_OBJECTS
	ld	a,(hl)
	inc	(hl)
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	a,(hl)
	ld	(_gLAST_OBJECT_NUMBER),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_20
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_19
.i_20
	ld	hl,_flags+1
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_19
	jp	i_17
.i_18
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gNUM_LOC),a
.i_22
	ld	hl,_localidades_t
	push	hl
	ld	hl,(_gNUM_LOC)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(hl)
	and	a
	jp	z,i_23
	ld	hl,_gNUM_LOC
	ld	a,(hl)
	inc	(hl)
	ld	hl,_localidades_t
	push	hl
	ld	hl,(_gNUM_LOC)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_22
.i_23
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gNUM_IMG),a
.i_24
	ld	hl,_imagenes_t
	push	hl
	ld	hl,(_gNUM_IMG)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_25
	ld	hl,_gNUM_IMG
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	jp	i_24
.i_25
	ld	hl,_fzx+1
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_fzx
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	ret



._ParserLoop
	push	bc
	dec	sp
.i_26
	ld	hl,(_ginEND)
	ld	h,0
	call	l_lneg
	jp	nc,i_27
	ld	hl,_flags+33
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+34
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+44
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+35
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+45
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+36
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+43
	ld	(hl),#(0 % 256 % 256)
	ld	a,(_gDESCRIBE_LOCATION_FLAG)
	cp	#(1 % 256)
	jp	nz,i_28
	ld	hl,6	;const
	push	hl
	call	_ACCcls
	pop	bc
	call	_proceso1
	ld	a,(_flags)
	cp	#(1 % 256)
	jp	nz,i_29
	ld	hl,_fzx
	ex	de,hl
	ld	hl,_TextWindow
	ld	a,(hl)
	ld	(de),a
	ld	hl,_fzx+1
	ex	de,hl
	ld	hl,_TextWindow+1
	ld	a,(hl)
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,(_flags+38)
	ld	h,0
	call	_get_loc_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0 % 256	;const
	call	_fontStyle
	ld	hl,_localidades_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	call	_writeText
	call	_newLine
	call	_proceso1_post
	call	_ACClistobj
.i_30
	ld	a,(_flags+58)
	and	a
	jp	z,i_31
	ld	hl,i_1+596
	call	_writeText
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_34
.i_32
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
.i_34
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(10 % 256)
	jp	z,i_33
	jp	nc,i_33
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,_conexiones_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,13
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ex	de,hl
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_36
	jp	nc,i_36
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(0 % 256)
	jp	z,i_36
	jp	c,i_36
	jr	i_37_i_36
.i_36
	jp	i_35
.i_37_i_36
	ld	hl,i_1+3
	call	_writeText
	ld	hl,_nombres_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	call	l_gint	;
	call	_writeText
.i_35
	jp	i_32
.i_33
	call	_newLine
.i_31
	ld	hl,_localidades_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	(hl),#(1 % 256 % 256)
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gDESCRIBE_LOCATION_FLAG),a
	jp	i_38
.i_29
	ld	hl,0 % 256	;const
	call	_writeSysMessage
.i_38
.i_28
	ld	hl,2 % 256	;const
	call	_fontStyle
	call	_getInput
	call	_newLine
	call	_parse
	ld	hl,0 % 256	;const
	call	_fontStyle
	ld	hl,(_gDEBUGGER)
	ld	a,l
	and	a
	jp	nz,i_39
	call	_respuestas
	ld	a,h
	or	l
	call	z,_respuestas_post
.i_40
	call	_proceso2
	ld	hl,_flags+31
	push	hl
	call	_incr16bit
	pop	bc
	jp	i_41
.i_39
	call	_debugger
.i_41
	jp	i_26
.i_27
	inc	sp
	pop	bc
	ret



._ACCNextWord
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
.i_42
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(0 % 256)
	jp	nz,i_44
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(25 % 256)
	jp	z,i_44
	jr	c,i_45_i_44
.i_44
	jp	i_43
.i_45_i_44
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	de,_playerInput
	ld	hl,(_gChar_number)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_playerWord
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(32 % 256)
	jp	z,i_47
	cp	#(13 % 256)
	jp	z,i_47
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(44 % 256)
	jp	z,i_47
	cp	#(46 % 256)
	jp	z,i_47
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(0 % 256)
	jp	nz,i_46
.i_47
	ld	hl,2	;const
	add	hl,sp
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_49
.i_46
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
.i_49
	ld	hl,_gChar_number
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	jp	i_42
.i_43
	ld	hl,_gWord_number
	ld	a,(hl)
	inc	(hl)
	ld	de,_playerWord
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	nz,i_50
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret


.i_50
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_51
	inc	sp
	pop	bc
	ret



._ACCGetWord
	ld	a,#(0 % 256 % 256)
	ld	(_gChar_number),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gWord_number),a
	call	_ACCNextWord
.i_52
	ld	de,(_gWord_number)
	ld	d,0
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_ne
	jp	nc,i_54
	ld	hl,(_playerWord)
	ld	h,0
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_55_i_54
.i_54
	jp	i_53
.i_55_i_54
	call	_ACCNextWord
	jp	i_52
.i_53
	ret



._parse
	ld	hl,_flags+33
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+34
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+44
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+35
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+45
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags+36
	ld	(hl),#(0 % 256 % 256)
	ld	a,#(0 % 256 % 256)
	ld	(_gDEBUGGER),a
	ld	a,#(0 % 256 % 256)
	ld	(_gChar_number),a
	ld	a,#(0 % 256 % 256)
	ld	(_gWord_number),a
	ld	hl,_playerWord
	ld	(hl),#(255 % 256 % 256)
.i_56
	ld	hl,(_playerWord)
	ld	a,l
	and	a
	jp	z,i_57
	call	_ACCNextWord
	ld	a,(_flags+33)
	cp	#(0 % 256)
	jp	nz,i_59
	ld	hl,_verbos_debug_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+33
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_60_i_59
.i_59
	jp	i_58
.i_60_i_59
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDEBUGGER),a
	jp	i_61
.i_58
	ld	a,(_gDEBUGGER)
	cp	#(1 % 256)
	jp	nz,i_63
	ld	a,(_flags+34)
	cp	#(0 % 256)
	jr	z,i_64_i_63
.i_63
	jp	i_62
.i_64_i_63
	ld	hl,_flags+34
	push	hl
	ld	hl,_playerWord
	push	hl
	call	_atoi
	pop	bc
	pop	de
	ld	a,l
	ld	(de),a
	jp	i_65
.i_62
	ld	a,(_gDEBUGGER)
	cp	#(1 % 256)
	jp	nz,i_67
	ld	a,(_flags+44)
	cp	#(0 % 256)
	jr	z,i_68_i_67
.i_67
	jp	i_66
.i_68_i_67
	ld	hl,_flags+44
	push	hl
	ld	hl,_playerWord
	push	hl
	call	_atoi
	pop	bc
	pop	de
	ld	a,l
	ld	(de),a
.i_66
.i_65
.i_61
	ld	a,(_flags+33)
	cp	#(0 % 256)
	jp	nz,i_70
	ld	hl,_verbos_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+33
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_71_i_70
.i_70
	jp	i_69
.i_71_i_70
	ld	a,(_flags+33)
	and	a
	jp	z,i_72
	ld	hl,i_1+614
	call	_writeText
	ld	hl,(_flags+33)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
.i_72
	jp	i_73
.i_69
	ld	a,(_flags+34)
	cp	#(0 % 256)
	jp	nz,i_75
	ld	hl,_nombres_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+34
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_76_i_75
.i_75
	jp	i_74
.i_76_i_75
	ld	a,(_flags+33)
	and	a
	jp	z,i_77
	ld	hl,i_1+616
	call	_writeText
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
.i_77
	jp	i_78
.i_74
	ld	a,(_flags+44)
	cp	#(0 % 256)
	jp	nz,i_80
	ld	hl,_nombres_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+44
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_81_i_80
.i_80
	jp	i_79
.i_81_i_80
	ld	a,(_flags+44)
	and	a
	jp	z,i_82
	ld	hl,i_1+620
	call	_writeText
	ld	hl,(_flags+44)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
.i_82
	jp	i_83
.i_79
	ld	a,(_flags+35)
	cp	#(0 % 256)
	jp	nz,i_85
	ld	hl,_adjetivos_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+35
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_86_i_85
.i_85
	jp	i_84
.i_86_i_85
	ld	a,(_flags+35)
	and	a
	jp	z,i_87
	ld	hl,i_1+624
	call	_writeText
	ld	hl,(_flags+35)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
.i_87
	jp	i_88
.i_84
	ld	a,(_flags+45)
	cp	#(0 % 256)
	jp	nz,i_90
	ld	hl,_adjetivos_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+45
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_91_i_90
.i_90
	jp	i_89
.i_91_i_90
	ld	a,(_flags+45)
	and	a
	jp	z,i_92
	ld	hl,i_1+628
	call	_writeText
	ld	hl,(_flags+45)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
.i_92
.i_89
.i_88
.i_83
.i_78
.i_73
	ld	a,(_flags+34)
	cp	#(20 % 256)
	jp	z,i_94
	jp	nc,i_94
	ld	a,(_flags+33)
	cp	#(0 % 256)
	jr	z,i_95_i_94
.i_94
	jp	i_93
.i_95_i_94
	ld	hl,_flags+33
	ex	de,hl
	ld	hl,_flags+34
	ld	a,(hl)
	ld	(de),a
	ld	hl,_flags+34
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_93
	jp	i_56
.i_57
	ret



._debugger
	ld	hl,(_flags+33)
	ld	h,0
.i_98
	ld	a,l
	cp	#(1% 256)
	jp	z,i_99
	cp	#(2% 256)
	jp	z,i_100
	cp	#(3% 256)
	jp	z,i_101
	cp	#(4% 256)
	jp	z,i_102
	cp	#(5% 256)
	jp	z,i_103
	cp	#(6% 256)
	jp	z,i_104
	cp	#(7% 256)
	jp	z,i_105
	cp	#(8% 256)
	jp	z,i_106
	cp	#(9% 256)
	jp	z,i_109
	cp	#(10% 256)
	jp	z,i_110
	cp	#(12% 256)
	jp	z,i_111
	cp	#(11% 256)
	jp	z,i_112
.i_99
	jp	i_97
.i_100
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	ld	hl,0 % 256	;const
	push	hl
	call	_ACClistat
	pop	bc
	pop	bc
	jp	i_97
.i_101
	ld	hl,(_flags+34)
	ld	h,0
	call	_ACCgoto
	jp	i_97
.i_102
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_flags+34)
	ld	h,0
	call	_get_obj_pos
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	call	_ACCgoto
	jp	i_97
.i_103
	ld	hl,_playerInput
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_flags
	push	hl
	ld	bc,34
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_playerInput
	push	hl
	ld	hl,10	;const
	push	hl
	call	_utoa
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_playerInput
	call	_writeText
	ld	hl,i_1+632
	call	_writeText
	jp	i_97
.i_104
	ld	hl,_flags
	push	hl
	ld	bc,34
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ex	de,hl
	ld	hl,_flags+44
	ld	a,(hl)
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_97
.i_105
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	ld	hl,(_flags+44)
	ld	h,0
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	jp	i_97
.i_106
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	ld	hl,(_flags+44)
	ld	h,0
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_107
	ld	hl,i_1+634
	call	_writeText
	jp	i_108
.i_107
	ld	hl,i_1+642
	call	_writeText
.i_108
	jp	i_97
.i_109
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	ld	hl,(_flags+44)
	ld	h,0
	push	hl
	call	_ACCoset
	pop	bc
	pop	bc
	jp	i_97
.i_110
	ld	hl,(_flags+34)
	ld	h,0
	push	hl
	ld	hl,(_flags+44)
	ld	h,0
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	jp	i_97
.i_111
	ld	hl,_playerInput
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_objetos_t
	push	hl
	ld	hl,(_flags+34)
	ld	h,0
	call	_get_obj_pos
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
	ld	hl,i_1+632
	call	_writeText
	jp	i_97
.i_112
	ld	hl,i_1+650
	call	_writeText
	ld	hl,i_1+665
	call	_writeText
	ld	hl,i_1+680
	call	_writeText
	ld	hl,i_1+693
	call	_writeText
	ld	hl,i_1+708
	call	_writeText
	ld	hl,i_1+720
	call	_writeText
	ld	hl,i_1+739
	call	_writeText
	ld	hl,i_1+759
	call	_writeText
	ld	hl,i_1+779
	call	_writeText
	ld	hl,i_1+800
	call	_writeText
	ld	hl,i_1+821
	call	_writeText
	ld	hl,i_1+834
	call	_writeText
.i_97
	ret



._writeValue
	ld	hl,65524	;const
	add	hl,sp
	ld	sp,hl
	ld	hl,14	;const
	call	l_gintspsp	;
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,10	;const
	push	hl
	call	_utoa
	pop	bc
	pop	bc
	pop	bc
	ld	hl,0	;const
	add	hl,sp
	call	_writeText
	ld	hl,12	;const
	add	hl,sp
	ld	sp,hl
	ret



._buscador
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
.i_113
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	nz,i_114
	ld	hl,8	;const
	call	l_gintspsp	;
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(hl)
	and	a
	jp	nz,i_115
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(1 % 256 % 256)
.i_115
	ld	hl,6	;const
	call	l_gintspsp	;
	ld	hl,10	;const
	call	l_gintspsp	;
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,5	;const
	push	hl
	call	strncmp_callee
	ld	a,h
	or	l
	jp	nz,i_116
	ld	hl,4	;const
	call	l_gintspsp	;
	ld	hl,10	;const
	call	l_gintspsp	;
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_116
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	jp	i_113
.i_114
	ld	hl,4	;const
	call	l_gintspsp	;
	ld	hl,0 % 256	;const
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0 % 256	;const
	pop	bc
	ret



._ACCdesc
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDESCRIBE_LOCATION_FLAG),a
	call	_ACCbreak
	ret



._ACCdone
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDONE_FLAG),a
	ret



._ACCbreak
	ld	a,#(0 % 256 % 256)
	ld	(_gDOALL_FLAG),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gENTRY_FOR_DOALL),a
	ret



._CNDat
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	a,(_flags+38)
	cp	(hl)
	jp	nz,i_117
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_117
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_118
	pop	bc
	ret



._CNDnotat
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_CNDat
	call	l_lneg
	ld	hl,0	;const
	ret



._CNDatgt
	push	hl
	ld	de,(_flags+38)
	ld	d,0
	pop	hl
	push	hl
	ld	h,0
	call	l_ugt
	jp	nc,i_119
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_119
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_120
	pop	bc
	ret



._CNDatlt
	push	hl
	ld	de,(_flags+38)
	ld	d,0
	pop	hl
	push	hl
	ld	h,0
	call	l_ult
	jp	nc,i_121
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_121
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_122
	pop	bc
	ret



._CNDpresent
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_123
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_123
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_124
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_124
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_125
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_125
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	nz,i_127
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsSupporter
	ld	a,h
	or	l
	jp	nz,i_127
	jr	i_128
.i_127
	ld	hl,1	;const
.i_128
	ld	a,h
	or	l
	jp	z,i_129
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_130_i_129
.i_129
	jp	i_126
.i_130_i_129
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsSupporter
	ld	a,h
	or	l
	jp	z,i_131
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_131
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	z,i_133
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_133
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_134_i_133
.i_133
	jp	i_132
.i_134_i_133
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_132
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	z,i_136
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	call	l_lneg
	jr	c,i_137_i_136
.i_136
	jp	i_135
.i_137_i_136
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret


.i_135
.i_126
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	pop	bc
	ret



._CNDabsent
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_CNDpresent
	dec	hl
	ld	a,h
	or	l
	jp	nz,i_138
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_138
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_139
	pop	bc
	ret



._CNDworn
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	call	_getObjectLocation
	ld	de,253	;const
	call	l_eq
	jp	nc,i_140
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_140
	ld	hl,i_1+842
	call	_writeText
	ld	hl,0 % 256	;const
	pop	bc
	ret



._CNDnotworn
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_CNDworn
	dec	hl
	ld	a,h
	or	l
	jp	nz,i_141
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_141
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_142
	pop	bc
	ret



._CNDnotcarr
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_CNDcarried
	dec	hl
	ld	a,h
	or	l
	jp	nz,i_143
	ld	hl,0 % 256	;const
	ret


.i_143
	ld	hl,1 % 256	;const
	ret


.i_144
	ret



._CNDchance
	ret



._CNDtimeout
	ret



._CNDisat
	ld	hl,_objetos_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_145
	ld	hl,1 % 256	;const
	ret


.i_145
	ld	hl,0 % 256	;const
	ret


.i_146
	ret



._CNDisnotat
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_CNDisat
	pop	bc
	pop	bc
	call	l_lneg
	ld	hl,0	;const
	ret



._CNDprep
	ld	hl,43 % 256	;const
	call	_getFlag
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	ld	hl,0	;const
	ret



._CNDsame
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getFlag
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getFlag
	pop	de
	call	l_eq
	ld	hl,0	;const
	ret



._CNDnotsame
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getFlag
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getFlag
	pop	de
	call	l_ne
	ld	hl,0	;const
	ret



._CNDweight
	ret



._ACCinven
	dec	sp
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,254 % 256	;const
	call	_getObjectCountAt
	push	hl
	ld	hl,253 % 256	;const
	call	_getObjectCountAt
	pop	de
	add	hl,de
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,(_flags+1)
	ld	h,0
	call	l_lneg
	jp	nc,i_147
	ld	hl,73 % 256	;const
	call	_writeSysMessage
	inc	sp
	pop	bc
	ret


.i_147
	ld	hl,9 % 256	;const
	call	_writeSysMessage
	ld	hl,2	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_150
.i_148
	ld	hl,2	;const
	add	hl,sp
	inc	(hl)
.i_150
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_149
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,254	;const
	call	l_eq
	jp	nc,i_151
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,18 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	nz,i_153
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,16 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_154
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,2 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_154
	ld	hl,1	;const
	jr	i_155
.i_154
	ld	hl,0	;const
.i_155
	ld	a,h
	or	l
	jp	nz,i_153
	jr	i_156
.i_153
	ld	hl,1	;const
.i_156
	ld	a,h
	or	l
	jp	z,i_152
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_ACClistat
	pop	bc
	pop	bc
.i_152
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_151
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,253	;const
	call	l_eq
	jp	nc,i_157
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,10 % 256	;const
	call	_writeSysMessage
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_157
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,253	;const
	call	l_eq
	jp	c,i_159
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,254	;const
	call	l_eq
	jp	nc,i_158
.i_159
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	call	l_ult
	jp	nc,i_161
	ld	hl,46 % 256	;const
	call	_writeSysMessage
.i_161
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	call	l_eq
	jp	nc,i_162
	ld	hl,47 % 256	;const
	call	_writeSysMessage
.i_162
.i_158
	jp	i_148
.i_149
	ld	hl,48 % 256	;const
	call	_writeSysMessage
	ld	hl,i_1+632
	call	_writeText
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDONE_FLAG),a
	inc	sp
	pop	bc
	ret



._ACCquit
	ld	a,#(1 % 256 % 256)
	ld	(_ginQUIT),a
	ld	hl,12 % 256	;const
	call	_writeSysMessage
	ret



._ACCend
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_ginEND),a
	ret



._ACCok
	ld	hl,15 % 256	;const
	call	_writeSysMessage
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDONE_FLAG),a
	ret



._ACCramsave
	ret



._ACCramload
	ret



._ACCsave
	ret



._ACCload
	ret



._ACCturns
	ld	hl,_flags+32
	ld	h,(hl)
	ld	l,0
	ex	de,hl
	ld	hl,(_flags+31)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,17 % 256	;const
	call	_writeSysMessage
	pop	hl
	push	hl
	push	hl
	call	_writeValue
	pop	bc
	ld	hl,18 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	call	l_gintspsp	;
	ld	hl,1	;const
	pop	de
	call	l_ne
	jp	nc,i_163
	ld	hl,19 % 256	;const
	call	_writeSysMessage
.i_163
	ld	hl,20 % 256	;const
	call	_writeSysMessage
	pop	bc
	ret



._ACCscore
	ld	hl,(_flags+30)
	ld	h,0
	push	hl
	ld	hl,21 % 256	;const
	call	_writeSysMessage
	ld	hl,(_flags+30)
	ld	h,0
	push	hl
	call	_writeValue
	pop	bc
	ld	hl,22 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	call	l_gintspsp	;
	ld	hl,1	;const
	pop	de
	call	l_ne
	jp	nc,i_164
	ld	hl,19 % 256	;const
	call	_writeSysMessage
.i_164
	ld	hl,20 % 256	;const
	call	_writeSysMessage
	pop	bc
	ret



._ACCcls
	ld	hl,6 % 256	;const
	push	hl
	call	_clear_screen
	ld	hl,_fzx
	ex	de,hl
	ld	hl,_TextWindow
	ld	a,(hl)
	ld	(de),a
	ld	hl,_fzx+1
	ex	de,hl
	ld	hl,_TextWindow+1
	ld	a,(hl)
	ld	(de),a
	ld	l,a
	ld	h,0
	ret



._ACCautog
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,(_flags+34)
	ld	h,0
	call	_ACCgetReferredObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_165
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,17 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	nz,i_167
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,21 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	nz,i_167
	jr	i_168
.i_167
	ld	hl,1	;const
.i_168
	ld	a,h
	or	l
	jp	z,i_166
	ld	hl,71 % 256	;const
	call	_writeSysMessage
	call	_ACCdone
	ld	hl,1	;const
	inc	sp
	ret


.i_166
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_ACCget
	ld	hl,1	;const
	inc	sp
	ret


.i_165
	ld	hl,26 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	inc	sp
	ret



._ACCautod
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,254 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_169
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCdrop
	inc	sp
	ret


.i_169
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,253 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_170
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCdrop
	inc	sp
	ret


.i_170
	ld	hl,28 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	inc	sp
	ret



._ACCpause
	ret



._ACCgoto
	push	hl
	ld	hl,_flags+38
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDESCRIBE_LOCATION_FLAG),a
	pop	bc
	ret



._ACCclearexit
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,13	;const
	call	l_ugt
	jp	c,i_172
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,0	;const
	call	l_ult
	jp	nc,i_171
.i_172
	ret


.i_171
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,255 % 256	;const
	push	hl
	call	_setConnection
	pop	bc
	pop	bc
	pop	bc
	ret



._ACCgetexit
	dec	sp
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(13 % 256)
	jp	z,i_174
	jp	nc,i_174
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_getConnection
	pop	bc
	pop	bc
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(0 % 256)
	jp	z,i_176
	jp	c,i_176
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_176
	jr	c,i_177_i_176
.i_176
	jp	i_175
.i_177_i_176
	ld	hl,_localidades_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	inc	sp
	ret


.i_175
.i_174
	ld	hl,255 % 256	;const
	inc	sp
	ret



._ACCsetexit
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(13 % 256)
	jp	z,i_178
	jp	nc,i_178
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	call	_setConnection
	pop	bc
	pop	bc
	pop	bc
.i_178
	ret



._ACCmessage
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_msg_pos
	call	_writeMessage
	call	_ACCnewline
	pop	bc
	ret



._trytoGet
	push	hl
	dec	sp
	ld	de,(_flags+1)
	ld	d,0
	ld	hl,(_flags+37)
	ld	h,d
	call	l_uge
	jp	nc,i_179
	ld	hl,27 % 256	;const
	call	_writeSysMessage
	ld	hl,i_1+632
	call	_writeText
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret


.i_179
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_getLocationObjectsWeight
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectWeight
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,254 % 256	;const
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,253 % 256	;const
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	pop	de
	push	de
	ld	d,0
	ld	hl,(_flags+52)
	ld	h,d
	call	l_ugt
	jp	nc,i_180
	ld	hl,43 % 256	;const
	call	_writeSysMessage
	ld	hl,i_1+632
	call	_writeText
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret


.i_180
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,254 % 256	;const
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,_flags+1
	inc	(hl)
	ld	hl,36 % 256	;const
	call	_writeSysMessage
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_writeObject
	call	_ACCnewline
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret



._ACCget
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	call	_getObjectLocation
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	call	_get_obj_pos
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_182
	cp	#(253 % 256)
	jp	nz,i_181
.i_182
	ld	hl,25 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	call	_ACCnewline
	ld	hl,1 % 256	;const
	pop	bc
	pop	bc
	ret


.i_181
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	call	_loc_here
	call	_get_loc_pos
	pop	de
	call	l_eq
	jp	nc,i_184
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_trytoGet
	ld	a,h
	or	l
	jp	z,i_185
	ld	hl,1 % 256	;const
	pop	bc
	pop	bc
	ret


.i_185
	ld	hl,0 % 256	;const
	pop	bc
	pop	bc
	ret


.i_186
.i_184
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_188
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_189_i_188
.i_188
	jp	i_187
.i_189_i_188
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_trytoGet
	ld	a,h
	or	l
	jp	z,i_190
	ld	hl,1 % 256	;const
	pop	bc
	pop	bc
	ret


.i_190
	ld	hl,0 % 256	;const
	pop	bc
	pop	bc
	ret


.i_191
	jp	i_192
.i_187
	ld	hl,i_1+853
	call	_writeText
	ld	hl,26 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	call	_ACCnewline
	ld	hl,0 % 256	;const
	pop	bc
	pop	bc
	ret


.i_192
	ld	hl,0 % 256	;const
	pop	bc
	pop	bc
	ret



._ACCdrop
	push	hl
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_193
	ld	hl,24 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret


.i_193
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_194
	ld	hl,49 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret


.i_194
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_195
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	call	_get_loc_pos
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,_flags+1
	dec	(hl)
	ld	hl,39 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,i_1+860
	call	_writeText
	call	_ACCdone
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_195
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._ACCdestroy
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	ld	hl,252 % 256	;const
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	pop	bc
	ret



._ACCcreate
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	push	hl
	call	_loc_here
	call	_get_loc_pos
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	pop	bc
	ret



._ACCswap
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_getObjectLocation
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_getObjectLocation
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	pop	bc
	ret



._ACCplace
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_197
	cp	#(253 % 256)
	jp	z,i_197
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(252 % 256)
	jp	z,i_197
	cp	#(255 % 256)
	jp	nz,i_196
.i_197
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	jp	i_199
.i_196
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
.i_199
	ret



._ACCnewline
	call	_newLine
	ret



._ACCwriteText
	ld	de,_flags
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_get_msg_pos
	call	_writeMessage
	ret



._ACCwrite
	push	hl
	call	_writeText
	pop	bc
	ret



._ACCwriteln
	push	hl
	call	_writeText
	call	_newLine
	pop	bc
	ret



._ACCsysmess
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeSysMessage
	pop	bc
	ret



._ACCcopyof
	ret



._ACCcopyoo
	ret



._ACCcopyfo
	ret



._ACCcopyff
	ret



._ACClistat
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectCountAt
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,4	;const
	ld	de,0
	push	de
	push	hl
	call	_getObjectCountAtWithAttr
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,17	;const
	ld	de,0
	push	de
	push	hl
	call	_getObjectCountAtWithAttr
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,3	;const
	add	hl,sp
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,10	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_200
	ld	hl,7	;const
	add	hl,sp
	ld	(hl),#(1 % 256 % 256)
.i_200
	ld	hl,6	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_203
.i_201
	ld	hl,6	;const
	add	hl,sp
	inc	(hl)
.i_203
	ld	hl,6	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_202
	ld	hl,_objetos_t
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,14-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_204
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsNPC
	call	l_lneg
	jp	nc,i_206
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	call	l_lneg
	jp	nc,i_206
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,17 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	call	l_lneg
	jr	c,i_207_i_206
.i_206
	jp	i_205
.i_207_i_206
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(1 % 256)
	jp	z,i_209
	jp	c,i_209
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	dec	hl
	pop	de
	call	l_ule
	jr	c,i_210_i_209
.i_209
	jp	i_208
.i_210_i_209
	ld	hl,46 % 256	;const
	call	_writeSysMessage
.i_208
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	call	l_eq
	jp	nc,i_211
	ld	hl,47 % 256	;const
	call	_writeSysMessage
.i_211
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_213
	pop	de
	push	de
	ld	d,0
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jr	c,i_214_i_213
.i_213
	jp	i_212
.i_214_i_213
	ld	hl,48 % 256	;const
	call	_writeSysMessage
.i_212
.i_205
.i_204
	jp	i_201
.i_202
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret



._ACClistnpc
	ret



._ACClistobj
	ld	hl,(_flags+38)
	ld	h,0
	call	_get_loc_pos
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectCountAt
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,4	;const
	ld	de,0
	push	de
	push	hl
	call	_getObjectCountAtWithAttr
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,17	;const
	ld	de,0
	push	de
	push	hl
	call	_getObjectCountAtWithAttr
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_215
	ld	hl,1 % 256	;const
	call	_writeSysMessage
	ld	hl,(_flags+38)
	ld	h,0
	push	hl
	ld	hl,0 % 256	;const
	push	hl
	call	_ACClistat
	pop	bc
	pop	bc
	call	_newLine
.i_215
	pop	bc
	pop	bc
	ret



._ACCobjat
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_getObjectCountAt
	ld	h,0
	pop	bc
	ret



._ACCmes
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_msg_pos
	call	_writeMessage
	pop	bc
	ret



._ACCweigh
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectWeight
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_setFlag
	pop	bc
	pop	bc
	inc	sp
	ret



._ACCability
	ld	hl,_flags+37
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_flags+52
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	ret



._ACCweight
	ld	hl,254 % 256	;const
	call	_getLocationObjectsWeight
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,253 % 256	;const
	call	_getLocationObjectsWeight
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	pop	de
	push	de
	ld	d,0
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	de,_flags
	ld	hl,7-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	inc	sp
	pop	bc
	ret



._ACCrandom
	ret



._ACCwhato
	ret



._ACCputo
	ret



._ACCnotdone
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDONE_FLAG),a
	ret



._ACCautop
	ret



._ACCautot
	ret



._CNDmove
	ld	de,_flags
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,(_flags+33)
	ld	h,0
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0 % 256	;const
	pop	bc
	ret



._ACCpicture
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_img_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_imagenes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	and	a
	jp	z,i_216
	ld	hl,_imagenes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_setRAMPage
	pop	bc
.i_216
	ld	hl,_imagenes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,16384	;const
	push	hl
	call	dzx7AgileRCS_callee
	ld	hl,_imagenes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	ld	a,h
	or	l
	call	nz,_setRAMBack
.i_217
	inc	sp
	ret



._ACCgraphic
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#( 1 % 256)
	ld	hl,0
	jr	nz,ASMPC+3
	inc	hl
	ld	a,l
	ld	(_gGRAPHICSON),a
	ld	l,a
	ld	h,0
	call	l_lneg
	call	c,_hideGraphicsWindow
.i_218
	ret



._ACCbeep
	ret



._ACCsound
	ret



._CNDozero
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_219
	ld	hl,0 % 256	;const
	ret


.i_219
	ld	hl,1 % 256	;const
	ret



._CNDonotzero
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	dec	hl
	ld	a,h
	or	l
	jp	nz,i_220
	ld	hl,0 % 256	;const
	ret


.i_220
	ld	hl,1 % 256	;const
	ret


.i_221
	ret



._ACCoset
	ld	hl,_objetos_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	push	hl
	call	l_glong
	push	de
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,1
	call	l_asl
	ld	de,0
	call	l_long_or
	pop	bc
	call	l_plong
	ret



._ACCoclear
	ld	hl,65535	;const
	ld	de,65535
	push	de
	push	hl
	ld	hl,0	;const
	add	hl,sp
	push	hl
	call	l_glong
	push	de
	push	hl
	ld	hl,12	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,1
	call	l_asl
	ld	de,0
	call	l_long_xor
	pop	bc
	call	l_plong
	ld	hl,_objetos_t
	push	hl
	ld	hl,10	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	push	hl
	call	l_glong
	push	de
	push	hl
	ld	hl,6	;const
	add	hl,sp
	call	l_glong
	call	l_long_and
	pop	bc
	call	l_plong
	pop	bc
	pop	bc
	ret



._CNDislight
	ret



._CNDisnotlight
	call	_CNDislight
	call	l_lneg
	ld	hl,0	;const
	ret



._ACCversion
	ret



._ACCrestart
	ret



._ACCtranscript
	ret



._ACCanykey
	ld	hl,16 % 256	;const
	call	_writeSysMessage
	call	_waitForAnyKey
	ret



._ACCgetkey
	ret



._CNDobjfound
	ret



._CNDobjnotfound
	ret



._CNDcarried
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	call	_getObjectLocation
	ld	de,253	;const
	call	l_eq
	jp	nc,i_222
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_222
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	call	_getObjectLocation
	ld	de,254	;const
	call	l_eq
	jp	nc,i_223
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_223
	ld	hl,i_1+864
	call	_writeText
	ld	hl,0 % 256	;const
	pop	bc
	ret



._ACConeg
	ret



._findMatchingObject
	push	hl
	dec	sp
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_226
.i_224
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
.i_226
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	ex	de,hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	call	l_ult
	jp	nc,i_225
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(65535 % 256)
	jp	z,i_228
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_getObjectLocation
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_227
.i_228
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(_flags+34)
	cp	(hl)
	jp	nz,i_231
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	a,(hl)
	cp	#(0 % 256)
	jp	z,i_232
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	a,(_flags+35)
	cp	(hl)
	jp	nz,i_231
.i_232
	jr	i_234_i_231
.i_231
	jp	i_230
.i_234_i_231
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	pop	bc
	pop	bc
	ret


.i_230
.i_227
	jp	i_224
.i_225
	ld	hl,255 % 256	;const
	pop	bc
	pop	bc
	ret



._isAccesibleContainer
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsSupporter
	ld	a,h
	or	l
	jp	z,i_235
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_235
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	z,i_237
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	call	l_lneg
	jr	c,i_238_i_237
.i_237
	jp	i_236
.i_238_i_237
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_236
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	z,i_240
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_240
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_241_i_240
.i_240
	jp	i_239
.i_241_i_240
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_239
	ld	hl,0 % 256	;const
	pop	bc
	ret



._ACCgetReferredObject
	push	hl
	ld	hl,255	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,(_flags+34)
	ld	h,0
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	dec	sp
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	nz,i_242
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret


.i_242
	ld	hl,_flags+34
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,254 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_243
	ld	hl,_flags+34
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret


.i_243
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,253 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_244
	ld	hl,_flags+34
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret


.i_244
	ld	hl,2	;const
	add	hl,sp
	push	hl
	call	_loc_here
	call	_get_loc_pos
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_245
	ld	hl,_flags+34
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret


.i_245
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_248
.i_246
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_248
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_247
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_CNDpresent
	ld	a,h
	or	l
	jp	z,i_250
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_isAccesibleContainer
	ld	a,h
	or	l
	jp	nz,i_251
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,18 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	nz,i_251
	jr	i_252
.i_251
	ld	hl,1	;const
.i_252
	ld	a,h
	or	l
	jr	nz,i_253_i_250
.i_250
	jp	i_249
.i_253_i_250
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_254
	ld	hl,_flags+34
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret


.i_254
.i_249
	jp	i_246
.i_247
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret



._getFlag
	push	hl
	ld	de,_flags
	pop	hl
	push	hl
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	pop	bc
	ret



._setFlag
	ld	de,_flags
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	ret



._dropall
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_257
.i_255
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_257
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_256
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,254	;const
	call	l_eq
	jp	nc,i_258
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,(_flags+38)
	ld	h,0
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
.i_258
	jp	i_255
.i_256
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_261
.i_259
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_261
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_260
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectLocation
	ld	de,253	;const
	call	l_eq
	jp	nc,i_262
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,(_flags+38)
	ld	h,0
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
.i_262
	jp	i_259
.i_260
	inc	sp
	ret



._done
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDONE_FLAG),a
	ret



._desc
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gDESCRIBE_LOCATION_FLAG),a
	ret



._loc_here
	ld	hl,(_flags+38)
	ld	h,0
	ret



._get_loc_pos
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
.i_263
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_LOC)
	ld	h,d
	call	l_ult
	jp	nc,i_264
	ld	hl,_localidades_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	e,(hl)
	ld	d,0
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_265
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	ret


.i_265
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_263
.i_264
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._get_obj_pos
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	nz,i_266
	ld	hl,255 % 256	;const
	inc	sp
	pop	bc
	ret


.i_266
.i_267
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_268
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_269
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	ret


.i_269
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_267
.i_268
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._get_img_pos
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
.i_270
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_IMG)
	ld	h,d
	call	l_ult
	jp	nc,i_271
	ld	hl,_imagenes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_272
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	ret


.i_272
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_270
.i_271
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._get_msg_pos
	push	hl
	ld	hl,_mensajes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_get_table_pos
	pop	bc
	pop	bc
	ld	h,0
	pop	bc
	ret



._get_table_pos
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
.i_273
	ld	hl,5	;const
	call	l_gintspsp	;
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(hl)
	and	a
	jp	z,i_274
	ld	hl,5	;const
	call	l_gintspsp	;
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_eq
	jp	nc,i_275
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	ret


.i_275
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_273
.i_274
	ld	hl,0 % 256	;const
	inc	sp
	ret



._getObjectLocation
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_277
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_276
.i_277
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	pop	bc
	ret


.i_276
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	ld	h,0
	pop	bc
	ret


.i_279
	pop	bc
	ret



._setObjectLocation
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_281
	cp	#(253 % 256)
	jp	z,i_281
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(252 % 256)
	jp	z,i_281
	cp	#(255 % 256)
	jp	nz,i_280
.i_281
	ld	hl,_objetos_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_283
.i_280
	ld	hl,_objetos_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
.i_283
	ret



._objectIsSupporter
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	nz,i_284
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_284
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,18 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_285
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_285
	ld	hl,0 % 256	;const
	pop	bc
	ret



._objectIsContainer
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	nz,i_286
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_286
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,2 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_287
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_287
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_288
	ld	hl,0 % 256	;const
	pop	bc
	ret



._objectIsAttr
	ld	hl,_objetos_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	call	l_glong
	push	de
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,1
	call	l_asl
	ld	de,0
	call	l_long_and
	push	de
	push	hl
	ld	hl,0	;const
	ld	d,h
	ld	e,l
	call	l_long_ugt
	jp	nc,i_289
	ld	hl,1	;const
	jp	i_290
.i_289
	ld	hl,0	;const
.i_290
	ld	h,0
	ret



._getObjectWeight
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	call	_objectIsContainer
	ld	a,h	
	or	l
	jp	nz,i_292
	inc	hl
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsSupporter
	ld	a,h
	or	l
	jp	nz,i_292
	jr	i_293
.i_292
	ld	hl,1	;const
.i_293
	ld	a,h
	or	l
	jp	z,i_294
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	pop	hl
	ld	a,h
	or	l
	jr	nz,i_295_i_294
.i_294
	jp	i_291
.i_295_i_294
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
.i_291
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	ret



._getLocationObjectsWeight
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	dec	sp
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_297
	cp	#(253 % 256)
	jp	nz,i_296
.i_297
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_299
.i_296
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,9	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
.i_299
	ld	hl,3	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_302
.i_300
	ld	hl,3	;const
	add	hl,sp
	inc	(hl)
.i_302
	ld	hl,3	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_301
	ld	hl,_objetos_t
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	e,(hl)
	ld	d,0
	pop	hl
	push	hl
	ld	h,0
	call	l_eq
	jp	nc,i_303
	ld	hl,1	;const
	add	hl,sp
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,4	;const
	add	hl,sp
	push	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,5-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_304
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsContainer
	ld	a,h
	or	l
	jp	nz,i_306
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsSupporter
	ld	a,h
	or	l
	jp	nz,i_306
	jr	i_307
.i_306
	ld	hl,1	;const
.i_307
	ld	a,h
	or	l
	jp	z,i_305
	ld	hl,4	;const
	add	hl,sp
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_objetos_t
	push	hl
	ld	hl,9	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
.i_305
.i_304
.i_303
	jp	i_300
.i_301
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	pop	bc
	ret



._getObjectCountAt
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	dec	sp
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(254 % 256)
	jp	z,i_309
	cp	#(253 % 256)
	jp	nz,i_308
.i_309
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_311
.i_308
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
.i_311
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_314
.i_312
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
.i_314
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	ex	de,hl
	ld	hl,(_gNUM_OBJECTS)
	ld	h,0
	call	l_ult
	jp	nc,i_313
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	e,(hl)
	ld	d,0
	pop	hl
	push	hl
	ld	h,0
	call	l_eq
	jp	nc,i_315
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_objectIsNPC
	call	l_lneg
	jp	nc,i_316
	ld	hl,2	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_316
.i_315
	jp	i_312
.i_313
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	pop	bc
	pop	bc
	ret



._getObjectCountAtWithAttr
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_319
.i_317
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_319
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_318
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,12	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	nc,i_321
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	call	l_glong
	ld	h,0
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_322_i_321
.i_321
	jp	i_320
.i_322_i_321
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_320
	jp	i_317
.i_318
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	pop	bc
	ret



._getNPCCountAt
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_325
.i_323
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_325
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gNUM_OBJECTS)
	ld	h,d
	call	l_ult
	jp	nc,i_324
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	nc,i_327
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_objectIsNPC
	ld	a,h
	or	l
	jr	nz,i_328_i_327
.i_327
	jp	i_326
.i_328_i_327
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_326
	jp	i_323
.i_324
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	pop	bc
	pop	bc
	ret



._objectIsNPC
	push	hl
	pop	de
	push	de
	ld	d,0
	ld	hl,(_gLAST_OBJECT_NUMBER)
	ld	h,d
	call	l_ugt
	jp	nc,i_329
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_329
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	call	l_glong
	ld	a,l
	and	3
	ld	l,a
	ld	h,0
	ld	de,0
	ld	a,h
	or	l
	or	d
	or	e
	jp	z,i_330
	ld	hl,1 % 256	;const
	pop	bc
	ret


.i_330
	ld	hl,0 % 256	;const
	pop	bc
	ret


.i_331
	pop	bc
	ret



._writeObject
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,15 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,8 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,11 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,29 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,31 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,5	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	nz,i_332
	ld	hl,i_1+878
	call	_writeText
	inc	sp
	pop	bc
	pop	bc
	pop	bc
	ret


.i_332
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	l_lneg
	jp	nc,i_333
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_334
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_335
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_336
	ld	hl,i_1+1
	call	_writeText
	jp	i_337
.i_336
	ld	hl,i_1+6
	call	_writeText
.i_337
	jp	i_338
.i_335
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_339
	ld	hl,i_1+886
	call	_writeText
	jp	i_340
.i_339
	ld	hl,i_1+891
	call	_writeText
.i_340
.i_338
	jp	i_341
.i_334
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_342
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_343
	ld	hl,i_1+896
	call	_writeText
	jp	i_344
.i_343
	ld	hl,i_1+901
	call	_writeText
.i_344
	jp	i_345
.i_342
	ld	hl,3	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_346
	ld	hl,i_1+905
	call	_writeText
	jp	i_347
.i_346
	ld	hl,i_1+911
	call	_writeText
.i_347
.i_345
.i_341
.i_333
	ld	hl,_objetos_t
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	call	_writeText
	inc	sp
	pop	bc
	pop	bc
	pop	bc
	ret



._newLine
	ld	hl,_fzx
	ex	de,hl
	ld	hl,_TextWindow
	ld	a,(hl)
	ld	(de),a
	ld	hl,_fzx+1
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	de,(_TextWindow+1)
	ld	d,0
	ld	hl,(_TextWindow+1+1+1)
	ld	h,d
	add	hl,de
	dec	hl
	dec	hl
	pop	de
	call	l_ugt
	jp	nc,i_348
	ld	hl,1 % 256	;const
	call	_scrollVTextWindow
	ld	hl,_fzx+1
	dec	(hl)
	ld	l,(hl)
	ld	h,0
.i_348
	ret



._scrollVTextWindow
	push	hl
	ld	hl,(_TextWindow+1)
	ld	h,0
	push	hl
	ld	hl,(_TextWindow)
	ld	h,0
	push	hl
	call	_scrollArriba
	pop	bc
	ret



._CaptionBox
	push	hl
	call	_writeText
	pop	bc
	ret



._writeTextCenter
	ret



._writeTextln
	push	hl
	call	_writeText
	ld	hl,i_1+632
	call	_writeText
	pop	bc
	ret



._writeText
	push	hl
	ld	hl,65260	;const
	add	hl,sp
	ld	sp,hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,25	;const
	add	hl,sp
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,256	;const
	push	hl
	call	memset_callee
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,283	;const
	call	l_gintsp	;
	ld	a,(hl)
	pop	de
	ld	(de),a
.i_349
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	pop	hl
	ld	a,h
	or	l
	jp	z,i_351
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_351
	jr	c,i_352_i_351
.i_351
	jp	i_350
.i_352_i_351
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,283	;const
	call	l_gintspsp	;
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(127 % 256)
	jp	z,i_353
	jp	c,i_353
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
.i_354
	ld	hl,_symbol_list
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,-128
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_356
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_356
	jr	c,i_357_i_356
.i_356
	jp	i_355
.i_357_i_356
	ld	hl,25	;const
	add	hl,sp
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_symbol_list
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,-128
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,5	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,4	;const
	add	hl,sp
	inc	(hl)
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_354
.i_355
	jp	i_358
.i_353
	ld	hl,25	;const
	add	hl,sp
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,4	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_358
	ld	hl,3	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_349
.i_350
	ld	hl,4	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	hl,3	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
.i_359
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	nz,i_360
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,27	;const
	add	hl,sp
	ex	de,hl
	ld	hl,7-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,5	;const
	add	hl,sp
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(32 % 256)
	jp	z,i_362
	cp	#(46 % 256)
	jp	z,i_362
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(94 % 256)
	jp	z,i_362
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_361
.i_362
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	nz,i_364
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(1 % 256 % 256)
.i_364
	ld	hl,4	;const
	add	hl,sp
	inc	(hl)
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(94 % 256)
	jp	z,i_366
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_365
.i_366
	ld	hl,4	;const
	add	hl,sp
	dec	(hl)
	ld	l,(hl)
	ld	h,0
	inc	l
.i_365
	ld	hl,5	;const
	add	hl,sp
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(94 % 256)
	jp	z,i_369
	ld	de,(_fzx)
	ld	d,0
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,(_TextWindow+1+1)
	ld	d,0
	ld	hl,(_TextWindow)
	ld	h,d
	add	hl,de
	pop	de
	call	l_ugt
	jp	nc,i_368
.i_369
	call	_newLine
.i_368
	ld	hl,5	;const
	add	hl,sp
	push	hl
	call	_fzx_puts
	pop	bc
	ld	hl,_fzx
	push	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,8-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,4	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_371
.i_361
	ld	hl,4	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_371
	ld	hl,3	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_359
.i_360
	ld	hl,281	;const
	add	hl,sp
	ld	sp,hl
	pop	bc
	ret



._writeSysMessage
	push	hl
	ld	hl,_mensajesSistema_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	call	l_gint	;
	call	_writeText
	pop	bc
	ret



._writeMessage
	push	hl
	ld	hl,_mensajes_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	call	l_gint	;
	call	_writeText
	pop	bc
	ret



._defineGraphWindow
	ret



._defineTextWindow
	ld	hl,_TextWindow
	push	hl
	ld	hl,10	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_TextWindow+1
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_TextWindow+1+1
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_TextWindow+1+1+1
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	ret



._clearGraphWindow
	ret



._clearTextWindow
	push	bc
	ld	hl,_fzx
	ex	de,hl
	ld	hl,_TextWindow
	ld	a,(hl)
	ld	(de),a
	ld	hl,_fzx+1
	ex	de,hl
	ld	hl,_TextWindow+1
	ld	a,(hl)
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ex	de,hl
	ld	hl,_TextWindow+1
	ld	a,(hl)
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_374
.i_372
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
.i_374
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	de,(_TextWindow+1)
	ld	d,0
	ld	hl,(_TextWindow+1+1+1)
	ld	h,d
	add	hl,de
	dec	hl
	pop	de
	call	l_ult
	jp	nc,i_373
	ld	hl,1	;const
	add	hl,sp
	ex	de,hl
	ld	hl,_TextWindow
	ld	a,(hl)
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_377
.i_375
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
.i_377
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	de,(_TextWindow)
	ld	d,0
	ld	hl,(_TextWindow+1+1)
	ld	h,d
	add	hl,de
	pop	de
	call	l_ult
	jp	nc,i_376
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(1 % 256)
	jp	nz,i_378
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,10	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_clearchar
	pop	bc
	pop	bc
	pop	bc
	jp	i_379
.i_378
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,10	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_set_attr
.i_379
	jp	i_375
.i_376
	jp	i_372
.i_373
	pop	bc
	ret



._clearTextLine
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(31 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_382
.i_380
	ld	hl,0	;const
	add	hl,sp
	dec	(hl)
.i_382
	pop	de
	push	de
	ld	d,0
	ld	hl,9-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_ugt
	jp	nc,i_381
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_clearchar
	pop	bc
	pop	bc
	pop	bc
	jp	i_380
.i_381
	inc	sp
	ret



._gotoxy
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_fzx_setat
	pop	bc
	pop	bc
	ret



._getInput
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,0	;const
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,_playerInput
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,32	;const
	push	hl
	call	memset_callee
	ld	hl,(_TextWindow)
	ld	h,0
	push	hl
	ld	hl,(_fzx+1)
	ld	h,0
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,(_playerPrompt)
	call	_writeText
.i_383
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(13 % 256)
	jp	z,i_385
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(32 % 256)
	jp	z,i_385
	jr	c,i_386_i_385
.i_385
	jp	i_384
.i_386_i_385
	ld	hl,0	;const
	add	hl,sp
	push	hl
	call	_getKey
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(4 % 256)
	jp	z,i_387
	ld	de,_playerInput
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,1	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	jp	i_388
.i_387
	ld	de,_playerInput
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_389
	ld	hl,1	;const
	add	hl,sp
	dec	(hl)
	ld	l,(hl)
	ld	h,0
	inc	l
.i_389
	ld	de,_playerInput
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(hl),#(32 % 256 % 256)
.i_388
	ld	hl,(_TextWindow)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,(_fzx+1)
	ld	h,0
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,_playerInput
	call	_writeText
	call	_waitForNoKey
	jp	i_383
.i_384
	ld	hl,_playerInput
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	add	hl,de
	ld	(hl),#(32 % 256 % 256)
	ld	de,_playerInput
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	pop	bc
	ret



._fontStyle
	push	hl
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_392
	ld	a,l
	cp	#(0% 256)
	jp	z,i_393
	cp	#(1% 256)
	jp	z,i_394
	cp	#(2% 256)
	jp	z,i_395
.i_393
.i_394
.i_395
.i_391
	pop	bc
	ret



._hideGraphicsWindow
	ld	hl,0 % 256	;const
	push	hl
	push	hl
	ld	hl,32 % 256	;const
	push	hl
	ld	hl,24 % 256	;const
	push	hl
	call	_defineTextWindow
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret



._setConnection
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(13 % 256)
	jp	z,i_396
	jp	nc,i_396
	ld	hl,_conexiones_t
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,13
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_localidades_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
.i_396
	ret



._getConnection
	ld	hl,2	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(13 % 256)
	jp	z,i_397
	jp	c,i_397
	ld	hl,255 % 256	;const
	ret


.i_397
	ld	hl,_conexiones_t
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,13
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	dec	hl
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	ld	h,0
	ret



._ACCautow
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,254 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_398
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCwear
	inc	sp
	ret


.i_398
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,253 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_399
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCwear
	inc	sp
	ret


.i_399
	ld	hl,0	;const
	add	hl,sp
	push	hl
	call	_loc_here
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_400
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCwear
	inc	sp
	ret


.i_400
	ld	hl,28 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	inc	sp
	ret



._ACCautor
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,253 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_401
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCremove
	inc	sp
	ret


.i_401
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,254 % 256	;const
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_402
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCremove
	inc	sp
	ret


.i_402
	ld	hl,0	;const
	add	hl,sp
	push	hl
	call	_loc_here
	call	_findMatchingObject
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(255 % 256)
	jp	z,i_403
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	call	_ACCremove
	inc	sp
	ret


.i_403
	ld	hl,23 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	inc	sp
	ret



._ACCremove
	push	hl
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_404
	ld	hl,38 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,254 % 256	;const
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,i_1+860
	call	_writeText
	call	_ACCdone
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_404
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_405
	ld	hl,49 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_405
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_406
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_407
	ld	hl,50 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,i_1+860
	call	_writeText
	call	_ACCdone
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_407
	ld	hl,70 % 256	;const
	call	_writeSysMessage
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_406
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._ACCwear
	push	hl
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_408
	ld	hl,24 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_408
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_409
	ld	hl,49 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_409
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_410
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	call	l_lneg
	jp	nc,i_411
	ld	hl,40 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_411
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,253 % 256	;const
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,37 % 256	;const
	call	_writeSysMessage
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,i_1+860
	call	_writeText
	ld	hl,1 % 256	;const
	inc	sp
	pop	bc
	ret


.i_410
	ld	hl,0 % 256	;const
	inc	sp
	pop	bc
	ret



._ACCputin
	push	bc
	ld	hl,1	;const
	add	hl,sp
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	nz,i_412
	ld	hl,24 % 256	;const
	call	_writeSysMessage
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_writeObject
	ld	hl,i_1+860
	call	_writeText
	ld	hl,0	;const
	pop	bc
	ret


.i_412
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_413
	ld	hl,49 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,0	;const
	pop	bc
	ret


.i_413
	ld	hl,_objetos_t
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_414
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_loc_pos
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,_flags+1
	dec	(hl)
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,18 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_415
	ld	hl,70 % 256	;const
	call	_writeSysMessage
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_writeObject
	ld	hl,i_1+917
	call	_writeText
	jp	i_416
.i_415
	ld	hl,44 % 256	;const
	call	_writeSysMessage
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_writeObject
	ld	hl,i_1+10
	call	_writeText
.i_416
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_writeObject
	ld	hl,51 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,1	;const
	pop	bc
	ret


.i_414
	ld	hl,0	;const
	pop	bc
	ret



._ACCtakeout
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,7	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(253 % 256)
	jp	z,i_418
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	cp	#(254 % 256)
	jp	nz,i_417
.i_418
	ld	hl,25 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	call	_ACCdone
	ld	hl,0	;const
	inc	sp
	ret


.i_417
	ld	hl,_objetos_t
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,11
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_loc_here
	pop	de
	call	l_eq
	jp	nc,i_420
	ld	hl,3	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_get_obj_pos
	push	hl
	ld	hl,18 % 256	;const
	push	hl
	call	_objectIsAttr
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_421
	ld	hl,69 % 256	;const
	call	_writeSysMessage
	jp	i_422
.i_421
	ld	hl,45 % 256	;const
	call	_writeSysMessage
.i_422
	call	_ACCnewline
	ld	hl,0	;const
	inc	sp
	ret


.i_420
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_getObjectWeight
	push	hl
	ld	hl,253 % 256	;const
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	push	hl
	ld	hl,254 % 256	;const
	call	_getLocationObjectsWeight
	pop	de
	add	hl,de
	ex	de,hl
	ld	hl,(_flags+52)
	ld	h,0
	call	l_ugt
	jp	nc,i_423
	ld	hl,43 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,0	;const
	inc	sp
	ret


.i_423
	ld	de,(_flags+1)
	ld	d,0
	ld	hl,(_flags+37)
	ld	h,d
	call	l_ugt
	jp	nc,i_424
	ld	hl,27 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,0	;const
	inc	sp
	ret


.i_424
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,254 % 256	;const
	push	hl
	call	_setObjectLocation
	pop	bc
	pop	bc
	ld	hl,36 % 256	;const
	call	_writeSysMessage
	call	_ACCnewline
	ld	hl,1	;const
	inc	sp
	ret



._incr16bit
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	a,(hl)
	cp	#(255 % 256)
	jp	nz,i_425
	ld	hl,2	;const
	call	l_gintspsp	;
	ld	hl,0 % 256	;const
	pop	de
	ld	a,l
	ld	(de),a
	pop	bc
	pop	hl
	push	hl
	push	bc
	inc	hl
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	ret


.i_425
	pop	bc
	pop	hl
	push	hl
	push	bc
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	ret


	SECTION	rodata_compiler

.i_1
	defm	" la "
	defb	0

	defm	" el "
	defb	0

	defm	" en "
	defb	0

	defm	" con"
	defb	0

	defm	"s de"
	defb	0

	defm	"que "
	defb	0

	defm	"a de"
	defb	0

	defm	" que"
	defb	0

	defm	" est"
	defb	0

	defm	"e la"
	defb	0

	defm	"de l"
	defb	0

	defm	" par"
	defb	0

	defm	"ara "
	defb	0

	defm	"rden"
	defb	0

	defm	"e de"
	defb	0

	defm	"orde"
	defb	0

	defm	"para"
	defb	0

	defm	"entr"
	defb	0

	defm	"de "
	defb	0

	defm	" en"
	defb	0

	defm	" es"
	defb	0

	defm	"as "
	defb	0

	defm	" co"
	defb	0

	defm	" el"
	defb	0

	defm	"a e"
	defb	0

	defm	"es "
	defb	0

	defm	"ent"
	defb	0

	defm	"os "
	defb	0

	defm	"o "
	defb	0

	defm	" d"
	defb	0

	defm	"er"
	defb	0

	defm	"te"
	defb	0

	defm	" p"
	defb	0

	defm	"or"
	defb	0

	defm	" c"
	defb	0

	defm	"na"
	defb	0

	defm	" a"
	defb	0

	defm	"r "
	defb	0

	defm	"do"
	defb	0

	defm	"re"
	defb	0

	defm	" s"
	defb	0

	defm	"as"
	defb	0

	defm	"al"
	defb	0

	defm	"ad"
	defb	0

	defm	" m"
	defb	0

	defm	"os"
	defb	0

	defm	"an"
	defb	0

	defm	"pa"
	defb	0

	defm	" t"
	defb	0

	defm	"ta"
	defb	0

	defm	". "
	defb	0

	defm	"ro"
	defb	0

	defm	" n"
	defb	0

	defm	"ci"
	defb	0

	defm	"ma"
	defb	0

	defm	"un"
	defb	0

	defm	"qu"
	defb	0

	defm	"ve"
	defb	0

	defm	"ie"
	defb	0

	defm	"to"
	defb	0

	defm	"sa"
	defb	0

	defm	"in"
	defb	0

	defm	" u"
	defb	0

	defm	"da"
	defb	0

	defm	"si"
	defb	0

	defm	"lo"
	defb	0

	defm	" o"
	defb	0

	defm	"le"
	defb	0

	defm	"mi"
	defb	0

	defm	"ri"
	defb	0

	defm	"no"
	defb	0

	defm	" r"
	defb	0

	defm	"se"
	defb	0

	defm	"ec"
	defb	0

	defm	"ac"
	defb	0

	defm	"nd"
	defb	0

	defm	"&n"
	defb	0

	defm	"ic"
	defb	0

	defm	"ca"
	defb	0

	defm	"rd"
	defb	0

	defm	"ce"
	defb	0

	defm	"is"
	defb	0

	defm	", "
	defb	0

	defm	"y "
	defb	0

	defm	"po"
	defb	0

	defm	"me"
	defb	0

	defm	"mo"
	defb	0

	defm	"ab"
	defb	0

	defm	"pu"
	defb	0

	defm	"ne"
	defb	0

	defm	"em"
	defb	0

	defm	"io"
	defb	0

	defm	"rt"
	defb	0

	defm	"pe"
	defb	0

	defm	"> "
	defb	0

	defm	";testme"
	defb	0

	defm	";xlista"
	defb	0

	defm	";goto"
	defb	0

	defm	";gonear"
	defb	0

	defm	";flag"
	defb	0

	defm	";setflag"
	defb	0

	defm	";place"
	defb	0

	defm	";attr"
	defb	0

	defm	";sattr"
	defb	0

	defm	";cattr"
	defb	0

	defm	";help"
	defb	0

	defm	";where"
	defb	0

	defm	"rapid"
	defb	0

	defm	"lenta"
	defb	0

	defm	"silen"
	defb	0

	defm	"ruido"
	defb	0

	defm	"cuida"
	defb	0

	defm	"tranq"
	defb	0

	defm	"del"
	defb	0

	defm	"dentr"
	defb	0

	defm	"desde"
	defb	0

	defm	"hacia"
	defb	0

	defm	"tras"
	defb	0

	defm	"detra"
	defb	0

	defm	"bajo"
	defb	0

	defm	"debaj"
	defb	0

	defm	"por"
	defb	0

	defm	"excep"
	defb	0

	defm	"fuera"
	defb	0

	defm	"afuer"
	defb	0

	defm	"delan"
	defb	0

	defm	"entre"
	defb	0

	defm	"encim"
	defb	0

	defm	"los"
	defb	0

	defm	"selo"
	defb	0

	defm	"selos"
	defb	0

	defm	"las"
	defb	0

	defm	"sela"
	defb	0

	defm	"selas"
	defb	0

	defm	"les"
	defb	0

	defm	"y"
	defb	0

	defm	"enton"
	defb	0

	defm	"despu"
	defb	0

	defm	"luego"
	defb	0

	defm	"."
	defb	0

	defm	","
	defb	0

	defm	";"
	defb	0

	defm	"Salidas visibles:"
	defb	0

	defm	"V"
	defb	0

	defm	"N1_"
	defb	0

	defm	"N2_"
	defb	0

	defm	"A1_"
	defb	0

	defm	"A2_"
	defb	0

	defm	"^"
	defb	0

	defm	">>>>> 0"
	defb	0

	defm	">>>>> 1"
	defb	0

	defm	";testme seqid "
	defb	0

	defm	";xlista locid "
	defb	0

	defm	";goto locid "
	defb	0

	defm	";gonear objid "
	defb	0

	defm	";flag flag "
	defb	0

	defm	";setflag flag num "
	defb	0

	defm	";place objid locid "
	defb	0

	defm	";attr objid attrid "
	defb	0

	defm	";sattr objid attrid "
	defb	0

	defm	";cattr objid attrid "
	defb	0

	defm	";where objid"
	defb	0

	defm	";help ^"
	defb	0

	defm	"(Not worn)"
	defb	0

	defm	"ACCget"
	defb	0

	defm	". ^"
	defb	0

	defm	"(Not carried)"
	defb	0

	defm	"ninguno"
	defb	0

	defm	"las "
	defb	0

	defm	"los "
	defb	0

	defm	"una "
	defb	0

	defm	"un "
	defb	0

	defm	"unas "
	defb	0

	defm	"unos "
	defb	0

	defm	" sobre "
	defb	0



; --- Start of Static Variables ---

	SECTION	bss_compiler

._flags	defs	255
._playerInput	defs	32
._playerWord	defs	25
._gWord_number	defs	1
._gChar_number	defs	1
._TextWindow	defs	4
._GraphWindow	defs	4
._gNUM_OBJECTS	defs	1
._gNUM_LOC	defs	1
._gLAST_OBJECT_NUMBER	defs	1
._gNUM_IMG	defs	1
._gDONE_FLAG	defs	1
._gDESCRIBE_LOCATION_FLAG	defs	1
._gIN_RESPONSE	defs	1
._gSUCCESS	defs	1
._gDOALL_FLAG	defs	1
._gPROCESS_IN_DOALL	defs	1
._gCURRENT_PROCESS	defs	1
	SECTION	code_compiler



; --- Start of Scope Defns ---

	EXTERN	strlen
	EXTERN	strcat
	EXTERN	strcmp
	EXTERN	strcpy
	EXTERN	strncat
	EXTERN	strncmp
	EXTERN	strncpy
	EXTERN	strrev
	EXTERN	strchr
	EXTERN	strchrnul
	EXTERN	strrchr
	EXTERN	strrstrip
	EXTERN	strstrip
	EXTERN	strstr
	EXTERN	strrstr
	EXTERN	strtok
	EXTERN	strtok_r
	EXTERN	strtok_s
	EXTERN	strsep
	EXTERN	strpbrk
	EXTERN	strpos
	EXTERN	strcspn
	EXTERN	strspn
	EXTERN	stricmp
	EXTERN	strcasecmp
	EXTERN	strnicmp
	EXTERN	strncasecmp
	EXTERN	strlwr
	EXTERN	strupr
	EXTERN	strlcat
	EXTERN	strlcpy
	EXTERN	memset
	EXTERN	memcpy
	EXTERN	memmove
	EXTERN	memchr
	EXTERN	memrchr
	EXTERN	memcmp
	EXTERN	memswap
	EXTERN	memopi
	EXTERN	memopd
	EXTERN	strdup
	EXTERN	strcat_callee
	EXTERN	strcmp_callee
	EXTERN	strcpy_callee
	EXTERN	strncat_callee
	EXTERN	strncmp_callee
	EXTERN	strncpy_callee
	EXTERN	strchr_callee
	EXTERN	strchrnul_callee
	EXTERN	strrchr_callee
	EXTERN	strrstrip_callee
	EXTERN	strstrip_callee
	EXTERN	strstr_callee
	EXTERN	strrstr_callee
	EXTERN	strtok_callee
	EXTERN	strtok_r_callee
	EXTERN	strsep_callee
	EXTERN	strpbrk_callee
	EXTERN	strpos_callee
	EXTERN	strcspn_callee
	EXTERN	strspn_callee
	EXTERN	stricmp_callee
	EXTERN	strnicmp_callee
	EXTERN	strlcat_callee
	EXTERN	strlcpy_callee
	EXTERN	memset_callee
	EXTERN	memcpy_callee
	EXTERN	memmove_callee
	EXTERN	memchr_callee
	EXTERN	memrchr_callee
	EXTERN	memcmp_callee
	EXTERN	memswap_callee
	EXTERN	memopi_callee
	EXTERN	memopd_callee
	EXTERN	bzero
	EXTERN	bcmp
	EXTERN	bcopy
	EXTERN	index
	EXTERN	rindex
	EXTERN	strset
	EXTERN	strnset
	EXTERN	strcmpi
	EXTERN	strncmpi
	EXTERN	rawmemchr
	PUBLIC	_symbol_list
	EXTERN	_proceso1
	EXTERN	_proceso2
	EXTERN	_proceso1_post
	EXTERN	_proceso2_post
	EXTERN	_respuestas
	EXTERN	_respuestas_post
	PUBLIC	_initParser
	PUBLIC	_ParserLoop
	PUBLIC	_parse
	PUBLIC	_buscador
	PUBLIC	_CNDobjfound
	PUBLIC	_CNDobjnotfound
	PUBLIC	_CNDcarried
	PUBLIC	_CNDpresent
	PUBLIC	_CNDabsent
	PUBLIC	_CNDworn
	PUBLIC	_CNDnotworn
	PUBLIC	_CNDozero
	PUBLIC	_CNDonotzero
	PUBLIC	_CNDweight
	PUBLIC	_CNDisat
	PUBLIC	_CNDisnotat
	PUBLIC	_CNDat
	PUBLIC	_CNDnotat
	PUBLIC	_CNDatgt
	PUBLIC	_CNDatlt
	PUBLIC	_ACCdesc
	PUBLIC	_ACCdone
	PUBLIC	_ACCbreak
	PUBLIC	_ACCdestroy
	PUBLIC	_ACCcreate
	PUBLIC	_ACCget
	PUBLIC	_ACCdrop
	PUBLIC	_ACCremove
	PUBLIC	_ACCwear
	PUBLIC	_ACCgoto
	PUBLIC	_ACCweigh
	PUBLIC	_ACClistat
	PUBLIC	_ACCobjat
	PUBLIC	_ACCoset
	PUBLIC	_ACCoclear
	PUBLIC	_ACConeg
	PUBLIC	_ACClistobj
	PUBLIC	_ACCplace
	PUBLIC	_ACCend
	PUBLIC	_ACCsysmess
	PUBLIC	_ACCnewline
	PUBLIC	_ACCcls
	PUBLIC	_ACCgetReferredObject
	PUBLIC	_ACCputin
	PUBLIC	_ACCtakeout
	PUBLIC	_ACCautop
	PUBLIC	_ACCautot
	PUBLIC	_ACCautor
	PUBLIC	_ACCautow
	PUBLIC	_ACCclearexit
	PUBLIC	_ACCgetexit
	PUBLIC	_ACCsetexit
	PUBLIC	_ACCmessage
	PUBLIC	_ACCmes
	PUBLIC	_ACCwrite
	PUBLIC	_ACCwriteln
	PUBLIC	_writeValue
	PUBLIC	_isAccesibleContainer
	PUBLIC	_findMatchingObject
	PUBLIC	_trytoGet
	PUBLIC	_getFlag
	PUBLIC	_setFlag
	PUBLIC	_done
	PUBLIC	_desc
	PUBLIC	_loc_here
	PUBLIC	_get_obj_pos
	PUBLIC	_get_table_pos
	PUBLIC	_getObjectLocation
	PUBLIC	_getObjectWeight
	PUBLIC	_getLocationObjectsWeight
	PUBLIC	_getObjectCountAt
	PUBLIC	_getObjectCountAtWithAttr
	PUBLIC	_getNPCCountAt
	PUBLIC	_objectIsSupporter
	PUBLIC	_objectIsContainer
	PUBLIC	_objectIsAttr
	PUBLIC	_objectIsNPC
	PUBLIC	_get_loc_pos
	PUBLIC	_get_img_pos
	PUBLIC	_get_msg_pos
	PUBLIC	_writeText
	PUBLIC	_writeTextln
	PUBLIC	_writeSysMessage
	PUBLIC	_writeMessage
	PUBLIC	_writeObject
	PUBLIC	_setObjectLocation
	PUBLIC	_defineGraphWindow
	PUBLIC	_defineTextWindow
	PUBLIC	_clearTextWindow
	PUBLIC	_clearTextLine
	PUBLIC	_clearGraphWindow
	PUBLIC	_gotoxy
	EXTERN	_clearchar
	PUBLIC	_scrollVTextWindow
	PUBLIC	_CaptionBox
	PUBLIC	_writeTextCenter
	PUBLIC	_fontStyle
	PUBLIC	_newLine
	PUBLIC	_getInput
	PUBLIC	_hideGraphicsWindow
	PUBLIC	_debugger
	PUBLIC	_setConnection
	PUBLIC	_getConnection
	PUBLIC	_incr16bit
	EXTERN	dzx7Standard
	EXTERN	dzx7Turbo
	EXTERN	dzx7Mega
	EXTERN	dzx7SmartRCS
	EXTERN	dzx7AgileRCS
	EXTERN	dzx7Standard_callee
	EXTERN	dzx7Turbo_callee
	EXTERN	dzx7Mega_callee
	EXTERN	dzx7SmartRCS_callee
	EXTERN	dzx7AgileRCS_callee
	EXTERN	_putPixel
	EXTERN	_scrollArriba
	EXTERN	___CALLEE__scrollArriba2
	EXTERN	___CALLEE__drawRectangle
	EXTERN	_clsScreen
	EXTERN	___CALLEE__drawGFX
	EXTERN	_waitForAnyKey
	EXTERN	___CALLEE__drawVline
	EXTERN	___CALLEE__drawHline
	EXTERN	___CALLEE__clearchar
	EXTERN	_clear_screen
	EXTERN	_waitForNoKey
	EXTERN	_setRAMPage
	EXTERN	_setRAMBack
	EXTERN	_drawGFX
	EXTERN	_drawSprite
	EXTERN	_randomNumber
	EXTERN	_fzx_setat
	EXTERN	_fzx_putc
	EXTERN	_fzx_puts
	EXTERN	_fzx_write
	EXTERN	_print_string
	EXTERN	_print_char
	EXTERN	_set_attr
	PUBLIC	_flags
	PUBLIC	_playerPrompt
	EXTERN	_fzx
	PUBLIC	_playerInput
	PUBLIC	_playerWord
	PUBLIC	_gWord_number
	PUBLIC	_gChar_number
	PUBLIC	_TextWindow
	PUBLIC	_GraphWindow
	EXTERN	_localidades_t
	EXTERN	_imagenes_t
	EXTERN	_mensajes_t
	EXTERN	_conexiones_t
	EXTERN	_objetos_t
	EXTERN	_nombres_t
	EXTERN	_verbos_t
	EXTERN	_adjetivos_t
	PUBLIC	_gNUM_OBJECTS
	PUBLIC	_gNUM_LOC
	PUBLIC	_gLAST_OBJECT_NUMBER
	PUBLIC	_gNUM_IMG
	PUBLIC	_gDEBUGGER
	PUBLIC	_gGRAPHICSON
	PUBLIC	_gSOUNDSON
	PUBLIC	_gINTERRUPTDISABLED
	PUBLIC	_gSHOWWARNINGS
	PUBLIC	_ginEND
	PUBLIC	_ginQUIT
	PUBLIC	_gDONE_FLAG
	PUBLIC	_gDESCRIBE_LOCATION_FLAG
	PUBLIC	_gIN_RESPONSE
	PUBLIC	_gSUCCESS
	PUBLIC	_gDOALL_FLAG
	PUBLIC	_gPROCESS_IN_DOALL
	PUBLIC	_gENTRY_FOR_DOALL
	PUBLIC	_gCURRENT_PROCESS
	PUBLIC	_verbos_debug_t
	PUBLIC	_adverbios_t
	PUBLIC	_preposiciones_t
	PUBLIC	_pronombres_t
	PUBLIC	_conjunciones_t
	EXTERN	_mensajesSistema_t
	PUBLIC	_ACCNextWord
	PUBLIC	_ACCGetWord
	EXTERN	_atoi
	EXTERN	_utoa
	PUBLIC	_CNDnotcarr
	PUBLIC	_CNDchance
	PUBLIC	_CNDtimeout
	PUBLIC	_CNDprep
	PUBLIC	_CNDsame
	PUBLIC	_CNDnotsame
	PUBLIC	_ACCinven
	PUBLIC	_ACCquit
	PUBLIC	_ACCok
	PUBLIC	_ACCramsave
	PUBLIC	_ACCramload
	PUBLIC	_ACCsave
	PUBLIC	_ACCload
	PUBLIC	_ACCturns
	PUBLIC	_ACCscore
	PUBLIC	_ACCautog
	PUBLIC	_ACCautod
	PUBLIC	_ACCpause
	PUBLIC	_ACCswap
	PUBLIC	_ACCwriteText
	PUBLIC	_ACCcopyof
	PUBLIC	_ACCcopyoo
	PUBLIC	_ACCcopyfo
	PUBLIC	_ACCcopyff
	PUBLIC	_ACClistnpc
	PUBLIC	_ACCability
	PUBLIC	_ACCweight
	PUBLIC	_ACCrandom
	PUBLIC	_ACCwhato
	PUBLIC	_ACCputo
	PUBLIC	_ACCnotdone
	PUBLIC	_CNDmove
	PUBLIC	_ACCpicture
	PUBLIC	_ACCgraphic
	PUBLIC	_ACCbeep
	PUBLIC	_ACCsound
	PUBLIC	_CNDislight
	PUBLIC	_CNDisnotlight
	PUBLIC	_ACCversion
	PUBLIC	_ACCrestart
	PUBLIC	_ACCtranscript
	PUBLIC	_ACCanykey
	PUBLIC	_ACCgetkey
	PUBLIC	_dropall
	EXTERN	_getKey


; --- End of Scope Defns ---


; --- End of Compilation ---
