;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20170415-
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Thu Apr 01 23:15:45 2021



	MODULE	juego_compressed


	INCLUDE "z80_crt0.hdr"


	SECTION	data_compiler

._imagenes_t
	defb	0
	defb	0
	defw	0

	SECTION	code_compiler

	SECTION	data_compiler

._localidades_t
	defw	i_1+0
	defw	i_1+8
	defb	1
	defb	0
	defb	0,0,0,0
	defw	i_1+88
	defw	i_1+97
	defb	2
	defb	0
	defb	0,0,0,0
	defw	i_1+165
	defw	i_1+173
	defb	3
	defb	0
	defb	0,0,0,0
	defw	i_1+261
	defw	i_1+271
	defb	4
	defb	0
	defb	0,0,0,0
	defw	i_1+359
	defw	i_1+368
	defb	5
	defb	0
	defb	0,0,0,0
	defw	i_1+461
	defw	i_1+473
	defb	6
	defb	0
	defb	0,0,0,0
	defw	i_1+517
	defw	i_1+524
	defb	7
	defb	0
	defb	0,0,0,0
	defw	i_1+615
	defw	i_1+622
	defb	8
	defb	0
	defb	0,0,0,0
	defw	i_1+7
	defw	i_1+7
	defb	0
	defb	0
	defb	0,0,0,0

	SECTION	code_compiler

	SECTION	data_compiler

._conexiones_t
	defb	1
	defb	0
	defb	2
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	2
	defb	0
	defb	0
	defb	2
	defb	1
	defb	4
	defb	0
	defb	3
	defb	0
	defb	0
	defb	0
	defb	0
	defb	1
	defb	0
	defb	0
	defb	0
	defb	3
	defb	0
	defb	0
	defb	2
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	4
	defb	2
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	2
	defb	0
	defb	0
	defb	0
	defb	5
	defb	0
	defb	0
	defb	3
	defb	6
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	6
	defb	0
	defb	0
	defb	5
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	7
	defb	0
	defb	0
	defb	6
	defb	8
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	6
	defb	8
	defb	0
	defb	0
	defb	7
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._mensajes_t
	defw	i_1+717
	defb	1
	defw	i_1+770
	defb	2
	defw	i_1+786
	defb	3
	defw	i_1+797
	defb	4
	defw	i_1+813
	defb	5
	defw	i_1+830
	defb	6
	defw	i_1+849
	defb	7
	defw	i_1+871
	defb	8
	defw	i_1+989
	defb	9
	defw	i_1+1045
	defb	10
	defw	i_1+1086
	defb	11
	defw	i_1+1115
	defb	12
	defw	i_1+1170
	defb	13
	defw	i_1+1202
	defb	14
	defw	i_1+1289
	defb	15
	defw	i_1+1350
	defb	16
	defw	i_1+1439
	defb	17
	defw	i_1+1464
	defb	18
	defw	i_1+1474
	defb	19
	defw	i_1+1506
	defb	20
	defw	i_1+1559
	defb	21
	defw	i_1+1648
	defb	22
	defw	i_1+1657
	defb	23
	defw	i_1+1667
	defb	24
	defw	i_1+1704
	defb	25
	defw	i_1+1742
	defb	26
	defw	i_1+1842
	defb	27
	defw	i_1+1861
	defb	28
	defw	i_1+1881
	defb	29
	defw	i_1+1966
	defb	30
	defw	i_1+1995
	defb	30
	defw	i_1+2086
	defb	31
	defw	i_1+2120
	defb	32
	defw	i_1+2155
	defb	33
	defw	i_1+2194
	defb	34
	defw	i_1+2206
	defb	35
	defw	i_1+2260
	defb	36
	defw	i_1+2320
	defb	37
	defw	i_1+2328
	defb	38
	defw	i_1+2371
	defb	39
	defw	i_1+2404
	defb	40
	defw	i_1+2517
	defb	41
	defw	i_1+2550
	defb	42
	defw	i_1+2606
	defb	43
	defw	i_1+2636
	defb	44
	defw	i_1+2706
	defb	45
	defw	i_1+2735
	defb	46
	defw	i_1+2780
	defb	47
	defw	i_1+2811
	defb	48
	defw	i_1+2847
	defb	49
	defw	i_1+2934
	defb	50
	defw	i_1+3069
	defb	51
	defw	i_1+3113
	defb	52
	defw	i_1+3115
	defb	53
	defw	i_1+3132
	defb	54
	defw	i_1+3143
	defb	55
	defw	i_1+3161
	defb	56
	defw	i_1+3178
	defb	57
	defw	i_1+3208
	defb	58
	defw	i_1+3245
	defb	59
	defw	i_1+3323
	defb	60
	defw	i_1+3408
	defb	61
	defw	i_1+3490
	defb	62
	defw	i_1+3600
	defb	63
	defw	i_1+3666
	defb	172
	defw	i_1+3722
	defb	173
	defw	i_1+3744
	defb	174
	defw	i_1+3767
	defb	175
	defw	i_1+3805
	defb	176
	defw	i_1+3854
	defb	177
	defw	i_1+3897
	defb	178
	defw	i_1+3923
	defb	179
	defw	i_1+3946
	defb	180
	defw	i_1+3961
	defb	181
	defw	i_1+3992
	defb	182
	defw	i_1+4038
	defb	183
	defw	i_1+4047
	defb	184
	defw	i_1+4071
	defb	185
	defw	i_1+4109
	defb	186
	defw	i_1+4176
	defb	187
	defw	i_1+4199
	defb	188
	defw	i_1+4222
	defb	189
	defw	i_1+4237
	defb	190
	defw	i_1+4284
	defb	191
	defw	i_1+4303
	defb	192
	defw	i_1+4320
	defb	193
	defw	i_1+4363
	defb	194
	defw	i_1+4387
	defb	195
	defw	i_1+4421
	defb	196

	SECTION	code_compiler

	SECTION	data_compiler

._mensajesSistema_t
	defw	i_1+4433
	defb	0
	defw	i_1+4457
	defb	1
	defw	i_1+4468
	defb	2
	defw	i_1+7
	defb	3
	defw	i_1+7
	defb	4
	defw	i_1+7
	defb	5
	defw	i_1+4484
	defb	6
	defw	i_1+4514
	defb	7
	defw	i_1+4534
	defb	8
	defw	i_1+4544
	defb	9
	defw	i_1+4549
	defb	10
	defw	i_1+4558
	defb	11
	defw	i_1+4570
	defb	12
	defw	i_1+4579
	defb	13
	defw	i_1+4592
	defb	14
	defw	i_1+4601
	defb	15
	defw	i_1+4605
	defb	16
	defw	i_1+4611
	defb	17
	defw	i_1+4620
	defb	18
	defw	i_1+4625
	defb	19
	defw	i_1+4627
	defb	20
	defw	i_1+4631
	defb	21
	defw	i_1+4644
	defb	22
	defw	i_1+4649
	defb	23
	defw	i_1+4663
	defb	24
	defw	i_1+4683
	defb	25
	defw	i_1+4690
	defb	26
	defw	i_1+4704
	defb	27
	defw	i_1+4723
	defb	28
	defw	i_1+4734
	defb	29
	defw	i_1+4749
	defb	30
	defw	i_1+4751
	defb	31
	defw	i_1+4753
	defb	32
	defw	i_1+4760
	defb	33
	defw	i_1+7
	defb	34
	defw	i_1+4763
	defb	35
	defw	i_1+4778
	defb	36
	defw	i_1+4787
	defb	37
	defw	i_1+4794
	defb	38
	defw	i_1+4801
	defb	39
	defw	i_1+4806
	defb	40
	defw	i_1+4818
	defb	41
	defw	i_1+4831
	defb	42
	defw	i_1+4853
	defb	43
	defw	i_1+4873
	defb	44
	defw	i_1+4878
	defb	45
	defw	i_1+4888
	defb	46
	defw	i_1+4890
	defb	47
	defw	i_1+459
	defb	48
	defw	i_1+4893
	defb	49
	defw	i_1+4900
	defb	50
	defw	i_1+7
	defb	51
	defw	i_1+4911
	defb	52
	defw	i_1+4919
	defb	53
	defw	i_1+4930
	defb	54
	defw	i_1+4944
	defb	55
	defw	i_1+4958
	defb	56
	defw	i_1+4983
	defb	57
	defw	i_1+4998
	defb	58
	defw	i_1+5008
	defb	59
	defw	i_1+5030
	defb	60
	defw	i_1+7
	defb	61
	defw	i_1+5045
	defb	62
	defw	i_1+5076
	defb	63
	defw	i_1+5081
	defb	64
	defw	i_1+5086
	defb	65
	defw	i_1+5092
	defb	66
	defw	i_1+5099
	defb	67
	defw	i_1+7
	defb	68
	defw	i_1+5108
	defb	69
	defw	i_1+5128
	defb	70
	defw	i_1+5133
	defb	71
	defw	i_1+5151
	defb	72
	defw	i_1+5168
	defb	73
	defw	i_1+7
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._nombres_t
	defw	i_1+5184
	defb	1
	defw	i_1+471
	defb	1
	defw	i_1+5190
	defb	2
	defw	i_1+4625
	defb	2
	defw	i_1+5194
	defb	3
	defw	i_1+5188
	defb	3
	defw	i_1+5199
	defb	4
	defw	i_1+4647
	defb	4
	defw	i_1+5205
	defb	5
	defw	i_1+5213
	defb	4
	defw	i_1+5215
	defb	6
	defw	i_1+5224
	defb	5
	defw	i_1+5227
	defb	7
	defw	i_1+5235
	defb	7
	defw	i_1+5238
	defb	8
	defw	i_1+5247
	defb	8
	defw	i_1+5253
	defb	9
	defw	i_1+5260
	defb	6
	defw	i_1+5263
	defb	10
	defw	i_1+5269
	defb	6
	defw	i_1+5272
	defb	11
	defw	i_1+5279
	defb	11
	defw	i_1+5285
	defb	12
	defw	i_1+5291
	defb	12
	defw	i_1+5295
	defb	9
	defw	i_1+5301
	defb	9
	defw	i_1+5307
	defb	9
	defw	i_1+5312
	defb	10
	defw	i_1+5318
	defb	10
	defw	i_1+5323
	defb	10
	defw	i_1+5329
	defb	10
	defw	i_1+5335
	defb	10
	defw	i_1+5279
	defb	11
	defw	i_1+5341
	defb	11
	defw	i_1+5347
	defb	11
	defw	i_1+5353
	defb	11
	defw	i_1+5359
	defb	11
	defw	i_1+5365
	defb	11
	defw	i_1+5285
	defb	12
	defw	i_1+5291
	defb	12
	defw	i_1+5371
	defb	12
	defw	i_1+5376
	defb	12
	defw	i_1+5382
	defb	12
	defw	i_1+5333
	defb	14
	defw	i_1+5388
	defb	14
	defw	i_1+5394
	defb	14
	defw	i_1+5398
	defb	15
	defw	i_1+5404
	defb	15
	defw	i_1+5410
	defb	15
	defw	i_1+5416
	defb	16
	defw	i_1+5422
	defb	20
	defw	i_1+5427
	defb	52
	defw	i_1+5434
	defb	54
	defw	i_1+5440
	defb	55
	defw	i_1+5446
	defb	58
	defw	i_1+5452
	defb	59
	defw	i_1+5458
	defb	60
	defw	i_1+5464
	defb	61
	defw	i_1+5468
	defb	61
	defw	i_1+5472
	defb	64
	defw	i_1+5478
	defb	65
	defw	i_1+5483
	defb	65
	defw	i_1+5489
	defb	65
	defw	i_1+5495
	defb	66
	defw	i_1+5501
	defb	67
	defw	i_1+5506
	defb	172
	defw	i_1+5511
	defb	104
	defw	i_1+5517
	defb	69
	defw	i_1+5523
	defb	70
	defw	i_1+5529
	defb	70
	defw	i_1+5534
	defb	70
	defw	i_1+5540
	defb	70
	defw	i_1+5546
	defb	71
	defw	i_1+5552
	defb	71
	defw	i_1+5558
	defb	71
	defw	i_1+5563
	defb	72
	defw	i_1+5365
	defb	95
	defw	i_1+5568
	defb	102
	defw	i_1+5574
	defb	102
	defw	i_1+5579
	defb	102
	defw	i_1+5585
	defb	21
	defw	i_1+5555
	defb	21
	defw	i_1+5591
	defb	21
	defw	i_1+5595
	defb	21
	defw	i_1+5599
	defb	21
	defw	i_1+5604
	defb	21
	defw	i_1+5608
	defb	21
	defw	i_1+5616
	defb	21
	defw	i_1+5620
	defb	21
	defw	i_1+5365
	defb	95
	defw	i_1+5627
	defb	104
	defw	i_1+5511
	defb	104
	defw	i_1+5633
	defb	104
	defw	i_1+5639
	defb	125
	defw	i_1+5645
	defb	132
	defw	i_1+5651
	defb	132
	defw	i_1+5657
	defb	132
	defw	i_1+5663
	defb	135
	defw	i_1+5669
	defb	139
	defw	i_1+5676
	defb	177
	defw	i_1+5683
	defb	178
	defw	i_1+5690
	defb	179
	defw	i_1+5697
	defb	179
	defw	i_1+5703
	defb	180
	defw	i_1+5709
	defb	181
	defw	i_1+5715
	defb	182
	defw	i_1+5376
	defb	182
	defw	i_1+5382
	defb	182
	defw	i_1+5721
	defb	184
	defw	i_1+5727
	defb	184
	defw	i_1+5733
	defb	170
	defw	i_1+5739
	defb	170
	defw	i_1+5745
	defb	183
	defw	i_1+5751
	defb	170
	defw	i_1+7
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._verbos_t
	defw	i_1+5757
	defb	20
	defw	i_1+5763
	defb	20
	defw	i_1+5768
	defb	20
	defw	i_1+5774
	defb	20
	defw	i_1+5779
	defb	20
	defw	i_1+5784
	defb	21
	defw	i_1+5790
	defb	21
	defw	i_1+5795
	defb	21
	defw	i_1+5801
	defb	21
	defw	i_1+5807
	defb	21
	defw	i_1+5812
	defb	23
	defw	i_1+5818
	defb	23
	defw	i_1+5824
	defb	22
	defw	i_1+5830
	defb	23
	defw	i_1+5836
	defb	23
	defw	i_1+5293
	defb	24
	defw	i_1+5842
	defb	24
	defw	i_1+5618
	defb	24
	defw	i_1+5847
	defb	24
	defw	i_1+5853
	defb	24
	defw	i_1+5858
	defb	25
	defw	i_1+5863
	defb	25
	defw	i_1+5867
	defb	26
	defw	i_1+5872
	defb	26
	defw	i_1+5878
	defb	26
	defw	i_1+5884
	defb	26
	defw	i_1+5890
	defb	27
	defw	i_1+5895
	defb	27
	defw	i_1+5901
	defb	28
	defw	i_1+5872
	defb	26
	defw	i_1+5907
	defb	29
	defw	i_1+5895
	defb	27
	defw	i_1+5913
	defb	30
	defw	i_1+5915
	defb	30
	defw	i_1+5921
	defb	30
	defw	i_1+5924
	defb	30
	defw	i_1+5930
	defb	30
	defw	i_1+5936
	defb	31
	defw	i_1+5942
	defb	31
	defw	i_1+5945
	defb	31
	defw	i_1+5951
	defb	31
	defw	i_1+5957
	defb	31
	defw	i_1+5963
	defb	53
	defw	i_1+5969
	defb	53
	defw	i_1+5974
	defb	53
	defw	i_1+5980
	defb	53
	defw	i_1+5986
	defb	32
	defw	i_1+5992
	defb	32
	defw	i_1+5998
	defb	32
	defw	i_1+6004
	defb	54
	defw	i_1+6010
	defb	54
	defw	i_1+6015
	defb	54
	defw	i_1+6020
	defb	54
	defw	i_1+6026
	defb	44
	defw	i_1+6032
	defb	44
	defw	i_1+6036
	defb	44
	defw	i_1+6040
	defb	43
	defw	i_1+6046
	defb	43
	defw	i_1+6051
	defb	43
	defw	i_1+6057
	defb	43
	defw	i_1+6063
	defb	42
	defw	i_1+6068
	defb	42
	defw	i_1+6074
	defb	42
	defw	i_1+6080
	defb	42
	defw	i_1+6086
	defb	55
	defw	i_1+5466
	defb	55
	defw	i_1+6092
	defb	49
	defw	i_1+6098
	defb	46
	defw	i_1+6104
	defb	46
	defw	i_1+6110
	defb	57
	defw	i_1+6116
	defb	57
	defw	i_1+6122
	defb	57
	defw	i_1+6128
	defb	57
	defw	i_1+6133
	defb	57
	defw	i_1+6139
	defb	57
	defw	i_1+6145
	defb	57
	defw	i_1+6151
	defb	57
	defw	i_1+6157
	defb	57
	defw	i_1+6163
	defb	57
	defw	i_1+6169
	defb	57
	defw	i_1+6175
	defb	33
	defw	i_1+6180
	defb	33
	defw	i_1+6185
	defb	33
	defw	i_1+6191
	defb	34
	defw	i_1+6198
	defb	34
	defw	i_1+6205
	defb	38
	defw	i_1+6211
	defb	38
	defw	i_1+6217
	defb	38
	defw	i_1+6223
	defb	38
	defw	i_1+6229
	defb	39
	defw	i_1+6235
	defb	39
	defw	i_1+6241
	defb	39
	defw	i_1+6247
	defb	59
	defw	i_1+6253
	defb	59
	defw	i_1+6259
	defb	59
	defw	i_1+6265
	defb	59
	defw	i_1+6271
	defb	59
	defw	i_1+6277
	defb	59
	defw	i_1+6283
	defb	58
	defw	i_1+6289
	defb	58
	defw	i_1+6293
	defb	58
	defw	i_1+6299
	defb	58
	defw	i_1+6305
	defb	58
	defw	i_1+6310
	defb	60
	defw	i_1+6316
	defb	60
	defw	i_1+6322
	defb	57
	defw	i_1+6328
	defb	61
	defw	i_1+5680
	defb	61
	defw	i_1+6332
	defb	61
	defw	i_1+6337
	defb	61
	defw	i_1+6343
	defb	61
	defw	i_1+6349
	defb	61
	defw	i_1+6354
	defb	61
	defw	i_1+6360
	defb	61
	defw	i_1+6366
	defb	74
	defw	i_1+6372
	defb	74
	defw	i_1+5347
	defb	74
	defw	i_1+6377
	defb	74
	defw	i_1+6383
	defb	74
	defw	i_1+6388
	defb	74
	defw	i_1+5288
	defb	41
	defw	i_1+5503
	defb	41
	defw	i_1+6394
	defb	41
	defw	i_1+6399
	defb	41
	defw	i_1+6404
	defb	41
	defw	i_1+6409
	defb	41
	defw	i_1+5958
	defb	41
	defw	i_1+6415
	defb	41
	defw	i_1+6421
	defb	41
	defw	i_1+6427
	defb	41
	defw	i_1+6432
	defb	41
	defw	i_1+6437
	defb	41
	defw	i_1+6443
	defb	56
	defw	i_1+6447
	defb	56
	defw	i_1+6452
	defb	56
	defw	i_1+6458
	defb	56
	defw	i_1+6464
	defb	56
	defw	i_1+6470
	defb	32
	defw	i_1+6476
	defb	32
	defw	i_1+6482
	defb	32
	defw	i_1+6488
	defb	36
	defw	i_1+6494
	defb	37
	defw	i_1+5398
	defb	62
	defw	i_1+6500
	defb	62
	defw	i_1+5416
	defb	63
	defw	i_1+169
	defb	64
	defw	i_1+6506
	defb	64
	defw	i_1+6511
	defb	64
	defw	i_1+7
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._adjetivos_t
	defw	i_1+6517
	defb	2
	defw	i_1+6523
	defb	3
	defw	i_1+6529
	defb	4
	defw	i_1+6535
	defb	4
	defw	i_1+6541
	defb	5
	defw	i_1+6547
	defb	5
	defw	i_1+6553
	defb	6
	defw	i_1+6558
	defb	6
	defw	i_1+6563
	defb	7
	defw	i_1+6569
	defb	8
	defw	i_1+6575
	defb	8
	defw	i_1+6581
	defb	9
	defw	i_1+6587
	defb	9
	defw	i_1+6593
	defb	10
	defw	i_1+6598
	defb	13
	defw	i_1+6604
	defb	14
	defw	i_1+6610
	defb	12
	defw	i_1+6598
	defb	13
	defw	i_1+6615
	defb	17
	defw	i_1+6621
	defb	15
	defw	i_1+6627
	defb	16
	defw	i_1+6632
	defb	16
	defw	i_1+7
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._objetos_t
	defb	1
	defb	8
	defw	i_1+6638
	defb	65
	defb	10
	defb	1
	defb	0,8,0,128
	defb	2
	defb	3
	defw	i_1+6648
	defb	135
	defb	0
	defb	1
	defb	2,8,0,128
	defb	3
	defb	3
	defw	i_1+6661
	defb	132
	defb	0
	defb	1
	defb	0,1,32,128
	defb	4
	defb	6
	defw	i_1+6674
	defb	52
	defb	0
	defb	1
	defb	0,1,32,0
	defb	5
	defb	3
	defw	i_1+6683
	defb	54
	defb	12
	defb	1
	defb	16,8,32,0
	defb	6
	defb	3
	defw	i_1+6692
	defb	54
	defb	13
	defb	1
	defb	16,8,32,0
	defb	7
	defb	252
	defw	i_1+6701
	defb	179
	defb	0
	defb	1
	defb	0,8,32,0
	defb	8
	defb	252
	defw	i_1+6715
	defb	181
	defb	0
	defb	1
	defb	0,8,32,0
	defb	0
	defb	0
	defw	i_1+7
	defb	0
	defb	0
	defb	0
	defb	0,0,0,0

	SECTION	code_compiler

	SECTION	data_compiler

._ordenador_topics_t
	defw	i_1+6723
	defb	1
	defw	i_1+6728
	defb	2
	defw	i_1+6734
	defb	3
	defw	i_1+6740
	defb	4
	defw	i_1+6743
	defb	4
	defw	i_1+6749
	defb	4
	defw	i_1+6755
	defb	4
	defw	i_1+5517
	defb	5
	defw	i_1+5472
	defb	5
	defw	i_1+6761
	defb	7
	defw	i_1+6767
	defb	7
	defw	i_1+6772
	defb	8
	defw	i_1+6778
	defb	8
	defw	i_1+6784
	defb	9
	defw	i_1+6718
	defb	9
	defw	i_1+6789
	defb	10
	defw	i_1+6795
	defb	11
	defw	i_1+6801
	defb	12
	defw	i_1+6807
	defb	13
	defw	i_1+6813
	defb	14
	defw	i_1+6818
	defb	14
	defw	i_1+6824
	defb	14
	defw	i_1+6830
	defb	14
	defw	i_1+6836
	defb	14
	defw	i_1+5571
	defb	17
	defw	i_1+6842
	defb	17
	defw	i_1+6848
	defb	17
	defw	i_1+6854
	defb	18
	defw	i_1+5582
	defb	18
	defw	i_1+6857
	defb	18
	defw	i_1+5365
	defb	18
	defw	i_1+6863
	defb	19
	defw	i_1+6869
	defb	20
	defw	i_1+6876
	defb	21
	defw	i_1+6881
	defb	22
	defw	i_1+6885
	defb	22
	defw	i_1+6889
	defb	23
	defw	i_1+6894
	defb	23
	defw	i_1+6902
	defb	24
	defw	i_1+6906
	defb	25
	defw	i_1+6910
	defb	25
	defw	i_1+6915
	defb	26
	defw	i_1+6921
	defb	26
	defw	i_1+6927
	defb	26
	defw	i_1+6933
	defb	26
	defw	i_1+6939
	defb	26
	defw	i_1+6945
	defb	27
	defw	i_1+6951
	defb	28
	defw	i_1+6957
	defb	29
	defw	i_1+6964
	defb	29
	defw	i_1+6971
	defb	30
	defw	i_1+6976
	defb	31
	defw	i_1+6982
	defb	32
	defw	i_1+6988
	defb	33
	defw	i_1+6032
	defb	33
	defw	i_1+6994
	defb	33
	defw	i_1+6092
	defb	33
	defw	i_1+7000
	defb	34
	defw	i_1+5365
	defb	35
	defw	i_1+7007
	defb	36
	defw	i_1+5279
	defb	37
	defw	i_1+7013
	defb	38
	defw	i_1+7019
	defb	39
	defw	i_1+7025
	defb	40
	defw	i_1+7030
	defb	40
	defw	i_1+7034
	defb	41
	defw	i_1+5568
	defb	42
	defw	i_1+7040
	defb	43
	defw	i_1+5627
	defb	44
	defw	i_1+7046
	defb	45
	defw	i_1+7054
	defb	46
	defw	i_1+7060
	defb	46
	defw	i_1+7066
	defb	46
	defw	i_1+7072
	defb	47
	defw	i_1+7078
	defb	48
	defw	i_1+7084
	defb	48
	defw	i_1+7090
	defb	48
	defw	i_1+7096
	defb	48
	defw	i_1+7102
	defb	48
	defw	i_1+7108
	defb	50
	defw	i_1+7114
	defb	51
	defw	i_1+7120
	defb	51
	defw	i_1+7126
	defb	52
	defw	i_1+7132
	defb	52
	defw	i_1+7138
	defb	53
	defw	i_1+7144
	defb	54
	defw	i_1+7150
	defb	55
	defw	i_1+7156
	defb	56
	defw	i_1+5483
	defb	57
	defw	i_1+7161
	defb	58
	defw	i_1+7167
	defb	59
	defw	i_1+7174
	defb	60
	defw	i_1+5501
	defb	61
	defw	i_1+7180
	defb	62
	defw	i_1+7186
	defb	63
	defw	i_1+7190
	defb	64
	defw	i_1+7196
	defb	65
	defw	i_1+7202
	defb	66
	defw	i_1+7208
	defb	67
	defw	i_1+7214
	defb	67
	defw	i_1+7220
	defb	67
	defw	i_1+7226
	defb	67
	defw	i_1+7232
	defb	70
	defw	i_1+7238
	defb	71
	defw	i_1+5645
	defb	72
	defw	i_1+5434
	defb	72
	defw	i_1+5651
	defb	72
	defw	i_1+7244
	defb	68
	defw	i_1+6549
	defb	73
	defw	i_1+5663
	defb	74
	defw	i_1+7250
	defb	75
	defw	i_1+7256
	defb	76
	defw	i_1+7262
	defb	77
	defw	i_1+7268
	defb	78
	defw	i_1+7274
	defb	78
	defw	i_1+7279
	defb	78
	defw	i_1+7285
	defb	78
	defw	i_1+7290
	defb	78
	defw	i_1+7296
	defb	79
	defw	i_1+7302
	defb	80
	defw	i_1+7308
	defb	81
	defw	i_1+7314
	defb	81
	defw	i_1+7320
	defb	81
	defw	i_1+7
	defb	0

	SECTION	code_compiler

	SECTION	data_compiler

._mensajes_ordenador_t
	defw	i_1+7326
	defb	1
	defw	i_1+7369
	defb	2
	defw	i_1+7379
	defb	3
	defw	i_1+7403
	defb	4
	defw	i_1+7428
	defb	5
	defw	i_1+7490
	defb	7
	defw	i_1+7525
	defb	8
	defw	i_1+7616
	defb	9
	defw	i_1+7654
	defb	10
	defw	i_1+7697
	defb	11
	defw	i_1+7746
	defb	12
	defw	i_1+7798
	defb	13
	defw	i_1+7897
	defb	14
	defw	i_1+7937
	defb	17
	defw	i_1+7963
	defb	18
	defw	i_1+8002
	defb	19
	defw	i_1+8042
	defb	20
	defw	i_1+8118
	defb	21
	defw	i_1+8244
	defb	22
	defw	i_1+8309
	defb	23
	defw	i_1+8344
	defb	24
	defw	i_1+8465
	defb	25
	defw	i_1+8535
	defb	26
	defw	i_1+8575
	defb	27
	defw	i_1+8599
	defb	28
	defw	i_1+8634
	defb	29
	defw	i_1+8658
	defb	30
	defw	i_1+8685
	defb	31
	defw	i_1+8790
	defb	32
	defw	i_1+8830
	defb	33
	defw	i_1+8867
	defb	34
	defw	i_1+8925
	defb	35
	defw	i_1+8946
	defb	36
	defw	i_1+9001
	defb	37
	defw	i_1+9056
	defb	38
	defw	i_1+9095
	defb	39
	defw	i_1+9116
	defb	40
	defw	i_1+9185
	defb	41
	defw	i_1+9255
	defb	42
	defw	i_1+9332
	defb	43
	defw	i_1+9394
	defb	44
	defw	i_1+9468
	defb	45
	defw	i_1+9562
	defb	46
	defw	i_1+9601
	defb	47
	defw	i_1+9650
	defb	48
	defw	i_1+9682
	defb	50
	defw	i_1+9757
	defb	51
	defw	i_1+9828
	defb	52
	defw	i_1+9923
	defb	53
	defw	i_1+9968
	defb	54
	defw	i_1+10054
	defb	55
	defw	i_1+10085
	defb	56
	defw	i_1+10115
	defb	57
	defw	i_1+10150
	defb	58
	defw	i_1+10174
	defb	59
	defw	i_1+10239
	defb	60
	defw	i_1+10304
	defb	61
	defw	i_1+10364
	defb	62
	defw	i_1+10381
	defb	63
	defw	i_1+10404
	defb	64
	defw	i_1+10428
	defb	65
	defw	i_1+10465
	defb	66
	defw	i_1+10543
	defb	67
	defw	i_1+10651
	defb	70
	defw	i_1+10681
	defb	71
	defw	i_1+10750
	defb	72
	defw	i_1+10834
	defb	68
	defw	i_1+10903
	defb	73
	defw	i_1+10956
	defb	74
	defw	i_1+11014
	defb	78
	defw	i_1+11062
	defb	77
	defw	i_1+11093
	defb	79
	defw	i_1+11132
	defb	80
	defw	i_1+11164
	defb	81
	defw	0
	defb	0

	SECTION	code_compiler


._respuestas
	dec	sp
	ld	a,(_flags+34)
	cp	#(21 % 256)
	jp	nz,i_13
	ld	hl,4 % 256	;const
	call	_CNDatgt
	ld	a,h
	or	l
	jp	z,i_14
	ld	hl,177 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_14
	ld	a,(_flags+33)
	cp	#(33 % 256)
	jp	nz,i_16
	ld	a,(_flags+44)
	cp	#(132 % 256)
	jr	z,i_17_i_16
.i_16
	jp	i_15
.i_17_i_16
	ld	hl,24 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_15
	ld	a,(_flags+33)
	cp	#(34 % 256)
	jp	nz,i_19
	ld	a,(_flags+44)
	cp	#(132 % 256)
	jr	z,i_20_i_19
.i_19
	jp	i_18
.i_20_i_19
	ld	hl,25 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_18
	ld	a,(_flags+33)
	cp	#(39 % 256)
	jp	nz,i_21
	ld	hl,193 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_21
	ld	a,(_flags+33)
	cp	#(38 % 256)
	jp	nz,i_23
	ld	a,(_flags+34)
	cp	#(170 % 256)
	jp	z,i_24
	ld	a,(_flags+44)
	cp	#(104 % 256)
	jp	nz,i_23
.i_24
	jr	i_26_i_23
.i_23
	jp	i_22
.i_26_i_23
	ld	hl,9 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_22
	ld	a,#(0 % 256 % 256)
	ld	(_gChar_number),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gWord_number),a
.i_27
	call	_ACCNextWord
	ld	a,h
	or	l
	jp	z,i_28
	ld	hl,_ordenador_topics_t
	push	hl
	ld	hl,_playerWord
	push	hl
	ld	hl,_flags+67
	push	hl
	call	_buscador
	pop	bc
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_29
	ld	hl,_mensajes_ordenador_t
	push	hl
	push	hl
	ld	hl,(_flags+67)
	ld	h,0
	push	hl
	call	_get_table_pos
	pop	bc
	pop	bc
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	call	l_gint	;
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_29
	jp	i_27
.i_28
	ld	hl,50 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_13
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_30
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jp	nz,i_32
	ld	hl,1 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_33_i_32
.i_32
	jp	i_31
.i_33_i_32
	ld	hl,46 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_31
	ld	a,(_flags+34)
	cp	#(184 % 256)
	jp	nz,i_35
	ld	hl,1 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_36_i_35
.i_35
	jp	i_34
.i_36_i_35
	ld	hl,49 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_34
	ld	a,(_flags+34)
	cp	#(135 % 256)
	jp	nz,i_38
	ld	hl,2 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_39_i_38
.i_38
	jp	i_37
.i_39_i_38
	ld	hl,16 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_37
.i_30
	ld	a,(_flags+33)
	cp	#(58 % 256)
	jp	nz,i_41
	ld	a,(_flags+34)
	cp	#(135 % 256)
	jp	nz,i_41
	ld	hl,2 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_42_i_41
.i_41
	jp	i_40
.i_42_i_41
	ld	hl,2	;const
	push	hl
	call	_CNDnotcarr
	pop	bc
	ld	a,h
	or	l
	jp	z,i_44
	ld	hl,2 % 256	;const
	call	_CNDnotworn
	ld	a,h
	or	l
	jr	nz,i_45_i_44
.i_44
	jp	i_43
.i_45_i_44
	ld	hl,192 % 256	;const
	call	_ACCmessage
	ld	hl,2 % 256	;const
	call	_ACCget
.i_43
.i_40
	ld	a,(_flags+33)
	cp	#(23 % 256)
	jp	nz,i_47
	ld	a,(_flags+34)
	cp	#(135 % 256)
	jp	nz,i_47
	ld	hl,2 % 256	;const
	call	_CNDworn
	ld	a,h
	or	l
	jr	nz,i_48_i_47
.i_47
	jp	i_46
.i_48_i_47
	ld	hl,4 % 256	;const
	call	_CNDatgt
	ld	a,h
	or	l
	jp	z,i_49
	ld	hl,19 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_49
.i_46
	ld	a,(_flags+33)
	cp	#(33 % 256)
	jp	nz,i_51
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jr	z,i_52_i_51
.i_51
	jp	i_50
.i_52_i_51
	ld	hl,48 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_50
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_53
	ld	a,(_flags+34)
	cp	#(67 % 256)
	jp	nz,i_54
	ld	hl,5 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_55
	ld	hl,14 % 256	;const
	call	_ACCmessage
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_55
	ld	hl,6 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_56
	ld	hl,36 % 256	;const
	call	_ACCmessage
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_56
.i_54
	ld	a,(_flags+34)
	cp	#(58 % 256)
	jp	z,i_58
	ld	a,(_flags+34)
	cp	#(59 % 256)
	jp	nz,i_57
.i_58
	ld	hl,5 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_60
	ld	hl,33 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_60
	ld	hl,179 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_61
.i_57
	ld	a,(_flags+34)
	cp	#(60 % 256)
	jp	z,i_63
	ld	a,(_flags+34)
	cp	#(66 % 256)
	jp	nz,i_62
.i_63
	ld	hl,5 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_65
	ld	hl,33 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_65
	ld	hl,178 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_66
.i_62
.i_53
	ld	a,(_flags+33)
	cp	#(46 % 256)
	jp	nz,i_67
	ld	hl,56 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_67
	ld	a,(_flags+33)
	cp	#(44 % 256)
	jp	nz,i_68
	ld	hl,5 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_69
	ld	hl,57 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_69
	ld	hl,56 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_68
	ld	a,(_flags+33)
	cp	#(49 % 256)
	jp	nz,i_70
	ld	hl,5 % 256	;const
	call	_CNDatlt
	ld	a,h
	or	l
	jp	z,i_71
	ld	hl,175 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_71
	ld	hl,176 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_72
.i_70
	ld	a,(_flags+38)
	cp	#(1 % 256)
	jp	nz,i_73
	ld	a,(_flags+33)
	cp	#(36 % 256)
	jp	nz,i_74
	ld	hl,181 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_74
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_75
	ld	a,(_flags+34)
	cp	#(125 % 256)
	jp	nz,i_77
	ld	a,(_flags+35)
	cp	#(15 % 256)
	jr	z,i_78_i_77
.i_77
	jp	i_76
.i_78_i_77
	ld	hl,15 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_76
	ld	a,(_flags+34)
	cp	#(64 % 256)
	jp	nz,i_79
	ld	hl,12 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_79
	ld	a,(_flags+34)
	cp	#(171 % 256)
	jp	nz,i_80
	ld	hl,13 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_80
	ld	a,(_flags+34)
	cp	#(55 % 256)
	jp	nz,i_81
	ld	hl,4 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_81
	ld	a,(_flags+34)
	cp	#(170 % 256)
	jp	nz,i_82
	ld	hl,18 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_82
	ld	a,(_flags+34)
	cp	#(95 % 256)
	jp	z,i_84
	ld	a,(_flags+34)
	cp	#(104 % 256)
	jp	z,i_84
	ld	a,(_flags+34)
	cp	#(183 % 256)
	jp	nz,i_83
.i_84
	ld	hl,8 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_83
	ld	a,(_flags+34)
	cp	#(61 % 256)
	jp	nz,i_86
	ld	hl,10 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_86
	ld	a,(_flags+34)
	cp	#(69 % 256)
	jp	nz,i_87
	ld	hl,11 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_87
.i_75
	ld	a,(_flags+33)
	cp	#(38 % 256)
	jp	nz,i_89
	ld	a,(_flags+34)
	cp	#(170 % 256)
	jp	z,i_90
	ld	a,(_flags+34)
	cp	#(104 % 256)
	jp	nz,i_89
.i_90
	jr	i_92_i_89
.i_89
	jp	i_88
.i_92_i_89
	ld	hl,9 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_88
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_94
	ld	a,(_flags+34)
	cp	#(172 % 256)
	jr	z,i_95_i_94
.i_94
	jp	i_93
.i_95_i_94
	ld	hl,2 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_93
.i_73
	ld	a,(_flags+38)
	cp	#(2 % 256)
	jp	nz,i_96
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_97
	ld	a,(_flags+34)
	cp	#(139 % 256)
	jp	nz,i_98
	ld	hl,i_1+11221
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_98
	ld	a,(_flags+34)
	cp	#(132 % 256)
	jp	nz,i_99
	ld	hl,i_1+11228
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_99
	ld	a,(_flags+34)
	cp	#(55 % 256)
	jp	z,i_101
	ld	a,(_flags+34)
	cp	#(104 % 256)
	jp	nz,i_100
.i_101
	ld	hl,5 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_100
	ld	a,(_flags+34)
	cp	#(61 % 256)
	jp	nz,i_103
	ld	hl,i_1+11235
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_103
.i_97
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_104
	ld	a,(_flags+34)
	cp	#(104 % 256)
	jp	nz,i_105
	ld	hl,1 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_105
	ld	a,(_flags+34)
	cp	#(132 % 256)
	jp	nz,i_106
	ld	hl,3 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_106
	ld	a,(_flags+34)
	cp	#(139 % 256)
	jp	nz,i_107
	ld	hl,4 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_107
.i_104
	ld	hl,1 % 256	;const
	call	_CNDcarried
	ld	a,h
	or	l
	jp	z,i_109
	ld	a,(_flags+71)
	cp	#(0 % 256)
	jr	z,i_110_i_109
.i_109
	jp	i_108
.i_110_i_109
	ld	hl,58 % 256	;const
	call	_ACCmessage
	ld	hl,_flags+71
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	call	_ACCanykey
	ld	hl,59 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_108
.i_96
	ld	a,(_flags+38)
	cp	#(3 % 256)
	jp	nz,i_111
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_113
	ld	a,(_flags+34)
	cp	#(182 % 256)
	jr	z,i_114_i_113
.i_113
	jp	i_112
.i_114_i_113
	ld	hl,_flags+33
	ld	(hl),#(12 % 256 % 256)
.i_112
	ld	a,(_flags+33)
	cp	#(4 % 256)
	jp	nz,i_115
	ld	hl,_flags+33
	ld	(hl),#(12 % 256 % 256)
.i_115
	ld	a,(_flags+33)
	cp	#(3 % 256)
	jp	nz,i_116
	ld	hl,_flags+33
	ld	(hl),#(41 % 256 % 256)
	ld	hl,_flags+34
	ld	(hl),#(172 % 256 % 256)
.i_116
	ld	a,(_flags+33)
	cp	#(23 % 256)
	jp	nz,i_118
	ld	a,(_flags+34)
	cp	#(135 % 256)
	jp	nz,i_118
	ld	hl,2 % 256	;const
	call	_CNDcarried
	ld	a,h
	or	l
	jr	nz,i_119_i_118
.i_118
	jp	i_117
.i_119_i_118
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_120
	ld	hl,19 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_120
.i_117
	ld	a,(_flags+33)
	cp	#(12 % 256)
	jp	nz,i_121
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_122
	ld	hl,24 % 256	;const
	call	_ACCmes
	ld	hl,22 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_122
	ld	hl,2 % 256	;const
	call	_CNDnotworn
	ld	a,h
	or	l
	jp	z,i_123
	ld	hl,19 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_123
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_125
	ld	hl,2 % 256	;const
	call	_CNDworn
	ld	a,h
	or	l
	jr	nz,i_126_i_125
.i_125
	jp	i_124
.i_126_i_125
	ld	hl,5 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_124
.i_121
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_128
	ld	a,(_flags+34)
	cp	#(172 % 256)
	jr	z,i_129_i_128
.i_128
	jp	i_127
.i_129_i_128
	ld	hl,2 % 256	;const
	call	_CNDworn
	ld	a,h
	or	l
	jp	nz,i_131
	ld	hl,2 % 256	;const
	call	_CNDcarried
	ld	a,h
	or	l
	jp	nz,i_131
	jr	i_132
.i_131
	ld	hl,1	;const
.i_132
	ld	a,h
	or	l
	jp	z,i_130
	ld	hl,20 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_130
	ld	hl,2 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_133
.i_127
	ld	a,(_flags+34)
	cp	#(52 % 256)
	jp	z,i_135
	ld	a,(_flags+34)
	cp	#(21 % 256)
	jp	nz,i_134
.i_135
	ld	hl,_flags+34
	ld	(hl),#(132 % 256 % 256)
.i_134
	ld	a,(_flags+33)
	cp	#(33 % 256)
	jp	nz,i_138
	ld	a,(_flags+34)
	cp	#(132 % 256)
	jr	z,i_139_i_138
.i_138
	jp	i_137
.i_139_i_138
	ld	hl,24 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_137
	ld	a,(_flags+33)
	cp	#(34 % 256)
	jp	nz,i_141
	ld	a,(_flags+34)
	cp	#(132 % 256)
	jr	z,i_142_i_141
.i_141
	jp	i_140
.i_142_i_141
	ld	hl,25 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_140
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_143
	ld	a,(_flags+34)
	cp	#(132 % 256)
	jp	z,i_145
	ld	a,(_flags+34)
	cp	#(21 % 256)
	jp	z,i_145
	ld	a,(_flags+34)
	cp	#(183 % 256)
	jp	nz,i_144
.i_145
	ld	hl,21 % 256	;const
	call	_ACCmes
	ld	hl,5 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_147
	ld	hl,23 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_147
	ld	hl,22 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_148
.i_144
	ld	a,(_flags+34)
	cp	#(54 % 256)
	jp	nz,i_149
	ld	a,(_flags+35)
	cp	#(13 % 256)
	jp	nz,i_150
	ld	hl,26 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_150
	ld	a,(_flags+35)
	cp	#(12 % 256)
	jp	nz,i_151
	ld	hl,27 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_151
	ld	hl,172 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_149
.i_143
	ld	a,(_flags+33)
	cp	#(32 % 256)
	jp	nz,i_152
	ld	a,(_flags+34)
	cp	#(54 % 256)
	jp	nz,i_153
	ld	a,(_flags+35)
	cp	#(12 % 256)
	jp	nz,i_154
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_155
	ld	hl,32 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_155
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	ld	hl,30 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_156
.i_154
	ld	a,(_flags+35)
	cp	#(13 % 256)
	jp	nz,i_157
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_158
	ld	hl,28 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_158
	ld	hl,2 % 256	;const
	call	_CNDnotworn
	ld	a,h
	or	l
	jp	z,i_160
	ld	hl,19 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_160
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_ACCoset
	pop	bc
	pop	bc
	ld	hl,29 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_159
.i_157
.i_153
.i_152
.i_111
	ld	a,(_flags+38)
	cp	#(4 % 256)
	jp	nz,i_161
	ld	hl,1 % 256	;const
	call	_CNDcarried
	ld	a,h
	or	l
	jp	z,i_162
	ld	hl,60 % 256	;const
	call	_ACCmessage
	call	_ACCanykey
	ld	hl,61 % 256	;const
	call	_ACCmessage
	call	_ACCanykey
	ld	hl,62 % 256	;const
	call	_ACCmessage
	call	_ACCanykey
	ld	hl,63 % 256	;const
	call	_ACCmessage
	call	_ACCend
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_162
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_163
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jp	nz,i_164
	ld	hl,173 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_164
.i_163
	ld	a,(_flags+33)
	cp	#(20 % 256)
	jp	z,i_166
	ld	a,(_flags+33)
	cp	#(32 % 256)
	jp	nz,i_168
.i_166
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jr	z,i_169_i_168
.i_168
	jp	i_165
.i_169_i_168
	ld	hl,174 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_165
.i_161
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_170
	ld	a,(_flags+38)
	cp	#(5 % 256)
	jp	z,i_172
	ld	a,(_flags+38)
	cp	#(6 % 256)
	jp	nz,i_171
.i_172
	ld	a,(_flags+34)
	cp	#(66 % 256)
	jp	nz,i_174
	ld	hl,7 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_174
	ld	a,(_flags+34)
	cp	#(71 % 256)
	jp	nz,i_175
	ld	hl,178 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_175
	ld	a,(_flags+34)
	cp	#(70 % 256)
	jp	nz,i_176
	ld	hl,179 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_176
	ld	a,(_flags+34)
	cp	#(171 % 256)
	jp	nz,i_177
	ld	hl,11 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_177
.i_171
.i_170
	ld	a,(_flags+38)
	cp	#(5 % 256)
	jp	nz,i_178
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_179
	ld	a,(_flags+34)
	cp	#(67 % 256)
	jp	nz,i_180
	ld	hl,3 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_180
	ld	a,(_flags+34)
	cp	#(102 % 256)
	jp	z,i_182
	ld	a,(_flags+34)
	cp	#(102 % 256)
	jp	z,i_182
	ld	a,(_flags+34)
	cp	#(102 % 256)
	jp	nz,i_181
.i_182
	ld	hl,6 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_181
.i_179
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_184
	ld	a,(_flags+34)
	cp	#(67 % 256)
	jp	nz,i_185
	ld	hl,36 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_185
	ld	a,(_flags+34)
	cp	#(102 % 256)
	jp	nz,i_186
	ld	hl,38 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_186
.i_184
.i_178
	ld	a,(_flags+38)
	cp	#(6 % 256)
	jp	nz,i_187
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_188
	ld	a,(_flags+34)
	cp	#(67 % 256)
	jp	nz,i_189
	ld	hl,5 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_189
.i_188
	ld	a,(_flags+33)
	cp	#(3 % 256)
	jp	nz,i_190
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,41	;const
	call	l_eq
	ld	a,(_flags+34)
	ld	e,a
	ld	d,0
	ld	hl,67	;const
	call	l_eq
.i_190
	ld	a,(_flags+33)
	cp	#(41 % 256)
	jp	nz,i_192
	ld	a,(_flags+34)
	cp	#(67 % 256)
	jr	z,i_193_i_192
.i_192
	jp	i_191
.i_193_i_192
	ld	hl,5 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_191
	ld	a,(_flags+33)
	cp	#(4 % 256)
	jp	z,i_195
	ld	a,(_flags+34)
	cp	#(4 % 256)
	jp	nz,i_194
.i_195
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,11	;const
	call	l_eq
.i_194
	ld	a,(_flags+33)
	cp	#(11 % 256)
	jp	nz,i_197
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_198
	ld	hl,22 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_198
	ld	hl,7 % 256	;const
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_197
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_199
	ld	a,(_flags+34)
	cp	#(102 % 256)
	jp	nz,i_200
	ld	hl,182 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_200
	ld	a,(_flags+34)
	cp	#(52 % 256)
	jp	nz,i_201
	ld	hl,180 % 256	;const
	call	_ACCmes
	ld	hl,8 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_CNDisat
	pop	bc
	pop	bc
	call	l_lneg
	jp	nc,i_202
	ld	hl,39 % 256	;const
	call	_ACCmes
	ld	hl,8 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
.i_202
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_203
	ld	hl,23 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_203
	ld	hl,22 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_204
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_201
	ld	a,(_flags+34)
	cp	#(179 % 256)
	jp	nz,i_206
	ld	hl,7 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_207_i_206
.i_206
	jp	i_205
.i_207_i_206
	ld	hl,41 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_205
	ld	a,(_flags+34)
	cp	#(181 % 256)
	jp	nz,i_209
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_210_i_209
.i_209
	jp	i_208
.i_210_i_209
	ld	hl,7 % 256	;const
	call	_CNDabsent
	ld	a,h
	or	l
	jp	z,i_212
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_213_i_212
.i_212
	jp	i_211
.i_213_i_212
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,40 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_211
	ld	hl,i_1+11251
	call	_writeText
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_208
.i_199
	ld	a,(_flags+33)
	cp	#(33 % 256)
	jp	z,i_215
	ld	a,(_flags+33)
	cp	#(34 % 256)
	jp	nz,i_217
.i_215
	ld	a,(_flags+34)
	cp	#(52 % 256)
	jr	z,i_218_i_217
.i_217
	jp	i_214
.i_218_i_217
	ld	hl,195 % 256	;const
	call	_ACCmessage
	ld	hl,8 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_CNDisat
	pop	bc
	pop	bc
	call	l_lneg
	jp	nc,i_219
	ld	hl,39 % 256	;const
	call	_ACCmes
	ld	hl,8 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
.i_219
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_214
	ld	a,(_flags+33)
	cp	#(64 % 256)
	jp	nz,i_221
	ld	a,(_flags+34)
	cp	#(181 % 256)
	jr	z,i_222_i_221
.i_221
	jp	i_220
.i_222_i_221
	ld	hl,i_1+11285
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_220
	ld	a,(_flags+33)
	cp	#(36 % 256)
	jp	nz,i_223
	ld	hl,_flags+33
	ld	(hl),#(37 % 256 % 256)
.i_223
	ld	a,(_flags+33)
	cp	#(37 % 256)
	jp	nz,i_224
	ld	a,(_flags+44)
	cp	#(0 % 256)
	jp	nz,i_226
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_227_i_226
.i_226
	jp	i_225
.i_227_i_226
	ld	hl,_flags+44
	ld	(hl),#(181 % 256 % 256)
	ld	hl,183 % 256	;const
	call	_ACCmes
.i_225
	ld	a,(_flags+44)
	cp	#(181 % 256)
	jp	nz,i_229
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_230_i_229
.i_229
	jp	i_228
.i_230_i_229
	ld	hl,7 % 256	;const
	call	_CNDabsent
	ld	a,h
	or	l
	jp	z,i_232
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_233_i_232
.i_232
	jp	i_231
.i_233_i_232
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,40 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_231
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jp	z,i_235
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDonotzero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jr	nz,i_236_i_235
.i_235
	jp	i_234
.i_236_i_235
	ld	hl,184 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_234
	ld	a,(_flags+34)
	cp	#(180 % 256)
	jp	nz,i_238
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_239_i_238
.i_238
	jp	i_237
.i_239_i_238
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_CNDozero
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_240
	ld	hl,186 % 256	;const
	call	_ACCmessage
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_ACCoset
	pop	bc
	pop	bc
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,252 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,7 % 256	;const
	push	hl
	call	_ACCsetexit
	pop	bc
	pop	bc
	pop	bc
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,11 % 256	;const
	push	hl
	ld	hl,7 % 256	;const
	push	hl
	call	_ACCsetexit
	pop	bc
	pop	bc
	pop	bc
	call	_ACCanykey
	call	_ACCdesc
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_240
.i_237
	ld	hl,8 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jp	z,i_242
	ld	hl,7 % 256	;const
	call	_CNDpresent
	ld	a,h
	or	l
	jr	nz,i_243_i_242
.i_242
	jp	i_241
.i_243_i_242
	ld	hl,185 % 256	;const
	call	_ACCmes
	ld	hl,_flags+66
	inc	(hl)
	ld	a,(hl)
	cp	#(3 % 256)
	jp	z,i_244
	jp	nc,i_244
	ld	hl,(_flags+66)
	ld	h,0
	ld	de,186
	add	hl,de
	ld	h,0
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_244
	ld	a,(_flags+66)
	cp	#(3 % 256)
	jp	nz,i_245
	ld	hl,189 % 256	;const
	call	_ACCmessage
	call	_ACCanykey
	ld	hl,190 % 256	;const
	call	_ACCmessage
	ld	hl,_flags+66
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_245
	ld	hl,41 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_241
.i_228
.i_224
.i_187
	ld	a,(_flags+38)
	cp	#(7 % 256)
	jp	nz,i_246
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_247
	ld	a,(_flags+34)
	cp	#(178 % 256)
	jp	nz,i_248
	ld	hl,43 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_248
	ld	a,(_flags+34)
	cp	#(60 % 256)
	jp	z,i_250
	ld	a,(_flags+34)
	cp	#(59 % 256)
	jp	z,i_250
	ld	a,(_flags+34)
	cp	#(58 % 256)
	jp	z,i_250
	ld	a,(_flags+34)
	cp	#(176 % 256)
	jp	nz,i_249
.i_250
	ld	hl,44 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_249
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jp	nz,i_252
	ld	hl,191 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_252
.i_247
.i_246
	ld	a,(_flags+33)
	cp	#(20 % 256)
	jp	nz,i_253
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jp	nz,i_254
	ld	a,(_flags+35)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_eq
	jp	nc,i_255
	call	_ACCautog
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_255
	ld	a,(_flags+38)
	cp	#(8 % 256)
	jp	z,i_257
	ld	a,(_flags+38)
	cp	#(7 % 256)
	jp	nz,i_256
.i_257
	ld	hl,194 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_256
.i_254
.i_253
	ld	a,(_flags+38)
	cp	#(8 % 256)
	jp	nz,i_259
	ld	a,(_flags+33)
	cp	#(30 % 256)
	jp	nz,i_260
	ld	a,(_flags+34)
	cp	#(177 % 256)
	jp	nz,i_261
	ld	hl,45 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_261
	ld	a,(_flags+34)
	cp	#(176 % 256)
	jp	nz,i_262
	ld	hl,44 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_262
	ld	a,(_flags+34)
	cp	#(178 % 256)
	jp	nz,i_263
	ld	hl,44 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_263
	ld	a,(_flags+34)
	cp	#(65 % 256)
	jp	nz,i_264
	ld	hl,191 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret


.i_264
.i_260
.i_259
	call	_ACCbreak
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	inc	sp
	ret



._respuestas_post
	push	bc
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,25	;const
	call	l_eq
	jp	nc,i_265
	call	_ACCend
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_265
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,23	;const
	call	l_eq
	jp	nc,i_266
	call	_ACCautor
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_266
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,58	;const
	call	l_eq
	jp	nc,i_267
	call	_ACCautow
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_267
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,30	;const
	call	l_eq
	jp	nc,i_268
	call	_loc_here
	call	_get_loc_pos
	call	_findMatchingObject
	ld	de,255	;const
	ex	de,hl
	call	l_ne
	jp	nc,i_269
	ld	hl,i_1+11313
	call	_writeText
	jp	i_270
.i_269
	ld	hl,i_1+11330
	call	_writeText
.i_270
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_268
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,14	;const
	call	l_eq
	jp	nc,i_271
	call	_ACCinven
	call	_ACCnewline
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_271
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,20	;const
	call	l_eq
	jp	nc,i_272
	call	_ACCautog
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_272
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,21	;const
	call	l_eq
	jp	nc,i_273
	call	_ACCautod
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_273
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,74	;const
	call	l_eq
	jp	nc,i_274
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_274
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,22	;const
	call	l_eq
	jp	nc,i_275
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_275
	ld	a,(_flags+33)
	cp	#(0 % 256)
	jp	z,i_277
	jp	c,i_277
	ld	a,(_flags+33)
	cp	#(13 % 256)
	jp	z,i_277
	jr	c,i_278_i_277
.i_277
	jp	i_276
.i_278_i_277
	ld	hl,1	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,(_flags+38)
	ld	h,0
	call	_get_loc_pos
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,1	;const
	add	hl,sp
	push	hl
	ld	hl,_conexiones_t
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	de,13
	call	l_mult
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,(_flags+33)
	ld	h,0
	dec	hl
	pop	de
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,1	;const
	add	hl,sp
	ld	a,(hl)
	and	a
	jp	z,i_279
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_279
	ld	hl,7 % 256	;const
	call	_ACCsysmess
	call	_ACCbreak
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_280
.i_276
	ld	a,(_flags+33)
	cp	#(24 % 256)
	jp	nz,i_281
	ld	hl,(_flags+38)
	ld	h,0
	call	_ACCgoto
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_281
	ld	a,(_flags+33)
	cp	#(32 % 256)
	jp	z,i_283
	ld	a,(_flags+33)
	cp	#(35 % 256)
	jp	nz,i_282
.i_283
	ld	hl,72 % 256	;const
	call	_ACCsysmess
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_282
	ld	a,(_flags+33)
	cp	#(26 % 256)
	jp	z,i_286
	ld	a,(_flags+33)
	cp	#(28 % 256)
	jp	z,i_286
	ld	a,(_flags+33)
	cp	#(27 % 256)
	jp	z,i_286
	ld	a,(_flags+33)
	cp	#(29 % 256)
	jp	nz,i_285
.i_286
	ld	hl,i_1+11344
	call	_ACCwriteln
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_285
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,62	;const
	call	l_eq
	jp	nc,i_288
	call	_ACCscore
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_288
	ld	a,(_flags+33)
	ld	e,a
	ld	d,0
	ld	hl,63	;const
	call	l_eq
	jp	nc,i_289
	call	_ACCturns
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_289
	ld	a,(_flags+33)
	cp	#(55 % 256)
	jp	nz,i_290
	ld	hl,35 % 256	;const
	call	_writeSysMessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_290
	ld	a,(_flags+33)
	cp	#(43 % 256)
	jp	z,i_292
	ld	a,(_flags+33)
	cp	#(42 % 256)
	jp	nz,i_291
.i_292
	ld	hl,56 % 256	;const
	call	_ACCmessage
	call	_ACCdone
	ld	hl,1	;const
	ld	a,l
	call	l_sxt
	pop	bc
	ret


.i_291
	ld	hl,6 % 256	;const
	call	_ACCsysmess
	call	_newLine
	pop	bc
	ret



._proceso1
	ld	hl,1 % 256	;const
	push	hl
	push	hl
	ld	hl,30 % 256	;const
	push	hl
	ld	hl,10 % 256	;const
	push	hl
	call	_defineTextWindow
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,0 % 256	;const
	push	hl
	push	hl
	call	_clearTextWindow
	pop	bc
	pop	bc
	ld	hl,8 % 256	;const
	call	_CNDat
	ld	a,h
	or	l
	jp	z,i_294
	ld	hl,80 % 256	;const
	push	hl
	ld	hl,0 % 256	;const
	push	hl
	call	_clearTextWindow
	pop	bc
	pop	bc
	ld	hl,15 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	push	hl
	call	_defineTextWindow
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,80 % 256	;const
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	call	_clearTextWindow
	pop	bc
	pop	bc
.i_294
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,11 % 256	;const
	push	hl
	ld	hl,32 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_defineTextWindow
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_flags
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	ret



._proceso1_post
	ld	hl,1 % 256	;const
	call	_CNDat
	ld	a,h
	or	l
	jp	z,i_296
	ld	hl,(_localidades_t+5)
	ld	h,0
	call	l_lneg
	jr	c,i_297_i_296
.i_296
	jp	i_295
.i_297_i_296
	ld	hl,i_1+11381
	call	_ACCwriteln
.i_295
	ret



._proceso2
	ret



._main
	ld	hl,0	;const
	push	hl
	call	_clear_screen
	pop	bc
	call	_initParser
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,8 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,2 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,6 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_ACCoclear
	pop	bc
	pop	bc
	ld	hl,5 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,5 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	call	_ACCoset
	pop	bc
	pop	bc
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,4 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,252 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
	ld	hl,8 % 256	;const
	push	hl
	ld	hl,252 % 256	;const
	push	hl
	call	_ACCplace
	pop	bc
	pop	bc
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
	ld	hl,68 % 256	;const
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	call	_clearTextWindow
	pop	bc
	pop	bc
	ld	hl,13 % 256	;const
	push	hl
	ld	hl,12 % 256	;const
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,i_1+11415
	call	_writeText
	ld	hl,12 % 256	;const
	push	hl
	ld	hl,14 % 256	;const
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,i_1+11423
	call	_writeText
	ld	hl,12 % 256	;const
	push	hl
	ld	hl,15 % 256	;const
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,i_1+11430
	call	_writeText
	ld	hl,9 % 256	;const
	push	hl
	ld	hl,20 % 256	;const
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,i_1+11440
	call	_writeText
.i_298
	call	_getKey
.i_302
	call	l_case
	defw	i_303,50
	defw	i_304,49
	defw	0
	jp	i_301
.i_303
	ld	hl,6 % 256	;const
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	call	_clearTextWindow
	pop	bc
	pop	bc
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	call	_gotoxy
	pop	bc
	pop	bc
	ld	hl,i_1+11460
	call	_writeTextln
	ld	hl,i_1+11466
	call	_writeTextln
	ld	hl,i_1+11478
	call	_writeTextln
	ld	hl,i_1+11487
	call	_writeTextln
	ld	hl,i_1+11525
	call	_writeTextln
	ld	hl,i_1+11560
	call	_writeTextln
	call	_waitForAnyKey
	call	_main
	jp	i_301
.i_304
	ld	hl,6	;const
	push	hl
	ld	hl,1	;const
	push	hl
	call	_clear_screen
	pop	bc
	pop	bc
	ld	hl,_flags+251
	ld	(hl),#(8 % 256 % 256)
	ld	hl,10	;const
	push	hl
	ld	hl,20	;const
	push	hl
	call	_ACCability
	pop	bc
	pop	bc
	ld	hl,1 % 256	;const
	call	_ACCgoto
	call	_ParserLoop
	ld	hl,13 % 256	;const
	call	_writeSysMessage
	ld	hl,_flags+67
	push	hl
	call	_getKey
	pop	de
	ld	a,l
	ld	(de),a
	ld	a,(_flags+67)
	cp	#(121 % 256)
	jp	z,i_306
	ld	a,(_flags+67)
	cp	#(115 % 256)
	jp	z,i_306
	ld	a,(_flags+67)
	cp	#(83 % 256)
	jp	z,i_306
	ld	a,(_flags+67)
	cp	#(89 % 256)
	jp	nz,i_305
.i_306
	call	_main
.i_305
	jp 0
.i_301
	jp	i_298
.i_299
	ret


	SECTION	rodata_compiler

.i_1
	defm	"Pu"
	defb	157

	defm	""
	defb	142

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	""
	defb	0

	defm	"L"
	defb	158

	defm	""
	defb	211

	defm	""
	defb	193

	defm	"rum"
	defb	157

	defm	"o"
	defb	132

	defm	" "
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	"ilu"
	defb	218

	defm	""
	defb	178

	defm	"n"
	defb	129

	defm	""
	defb	238

	defm	""
	defb	157

	defm	""
	defb	142

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	""
	defb	199

	defm	"En"
	defb	129

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	","
	defb	212

	defm	""
	defb	178

	defm	""
	defb	197

	defm	""
	defb	175

	defm	"m"
	defb	157

	defm	""
	defb	134

	defm	" hi"
	defb	181

	defm	""
	defb	162

	defm	"s"
	defb	159

	defm	""
	defb	237

	defm	"at"
	defb	159

	defm	"sob"
	defb	186

	defm	""
	defb	128

	defm	"sup"
	defb	168

	defm	"fi"
	defb	203

	defm	""
	defb	142

	defm	" Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"Nod"
	defb	162

	defm	"c"
	defb	145

	defm	"a"
	defb	173

	defm	""
	defb	0

	defm	"L"
	defb	158

	defm	"m&du"
	defb	215

	defm	""
	defb	132

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	136

	defm	"#n"
	defb	130

	defm	"p"
	defb	163

	defm	"umb"
	defb	170

	defm	""
	defb	199

	defm	"E"
	defb	173

	defm	""
	defb	220

	defm	"d"
	defb	162

	defm	"c"
	defb	145

	defm	""
	defb	190

	defm	""
	defb	131

	defm	""
	defb	223

	defm	""
	defb	198

	defm	""
	defb	131

	defm	""
	defb	129

	defm	""
	defb	238

	defm	""
	defb	157

	defm	""
	defb	142

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	","
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	182

	defm	""
	defb	173

	defm	"o"
	defb	165

	defm	"t"
	defb	159

	defm	"y"
	defb	128

	defm	"bo"
	defb	164

	defm	"ga"
	defb	182

	defm	""
	defb	173

	defm	"sur"
	defb	199

	defm	""
	defb	0

	defm	"Esclusa"
	defb	0

	defm	"En"
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	188

	defm	"e"
	defb	149

	defm	"cucha"
	defb	131

	defm	" i"
	defb	180

	defm	""
	defb	163

	defm	""
	defb	214

	defm	"d"
	defb	191

	defm	""
	defb	128

	defm	"t"
	defb	175

	defm	"m"
	defb	157

	defm	"a gol"
	defb	243

	defm	""
	defb	195

	defm	""
	defb	185

	defm	""
	defb	131

	defm	"t"
	defb	170

	defm	""
	defb	129

	defm	"fu"
	defb	222

	defm	""
	defb	171

	defm	"je"
	defb	199

	defm	"L"
	defb	152

	defm	"sombr"
	defb	152

	defm	"c"
	defb	186

	defm	"a"
	defb	167

	defm	"f"
	defb	175

	defm	"m"
	defb	152

	defm	"s"
	defb	211

	defm	"i"
	defb	165

	defm	"t"
	defb	170

	defm	"s"
	defb	130

	defm	"l"
	defb	158

	defm	"t"
	defb	170

	defm	"je"
	defb	132

	defm	""
	defb	160

	defm	"xp"
	defb	215

	defm	""
	defb	170

	defm	""
	defb	203

	defm	""
	defb	226

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"Bo"
	defb	164

	defm	"g"
	defb	134

	defm	""
	defb	176

	defm	""
	defb	174

	defm	"ga"
	defb	0

	defm	"La z"
	defb	184

	defm	""
	defb	134

	defm	""
	defb	176

	defm	""
	defb	174

	defm	"ga"
	defb	197

	defm	"i"
	defb	163

	defm	"e"
	defb	149

	defm	""
	defb	196

	defm	""
	defb	203

	defm	""
	defb	162

	defm	"sufi"
	defb	203

	defm	""
	defb	157

	defm	"e"
	defb	139

	defm	"a"
	defb	182

	defm	"t"
	defb	163

	defm	""
	defb	164

	defm	"r"
	defb	172

	defm	"eq"
	defb	179

	defm	"+"
	defb	194

	defm	""
	defb	148

	defm	"v%"
	defb	158

	defm	""
	defb	145

	defm	"e"
	defb	139

	defm	"t"
	defb	227

	defm	"u"
	defb	171

	defm	"r"
	defb	165

	defm	""
	defb	199

	defm	"En"
	defb	128

	defm	"sombr"
	defb	152

	defm	"ha"
	defb	233

	defm	"v"
	defb	174

	defm	"i"
	defb	158

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	156

	defm	""
	defb	133

	defm	""
	defb	165

	defm	"p"
	defb	168

	defm	"a"
	defb	167

	defm	"su "
	defb	145

	defm	"ega"
	defb	199

	defm	""
	defb	0

	defm	"Exterior"
	defb	0

	defm	"Me"
	defb	148

	defm	"v"
	defb	179

	defm	"lv"
	defb	159

	defm	"u"
	defb	178

	defm	""
	defb	197

	defm	""
	defb	175

	defm	"m"
	defb	157

	defm	""
	defb	134

	defm	""
	defb	202

	defm	""
	defb	208

	defm	"v"
	defb	159

	defm	"y"
	defb	176

	defm	""
	defb	219

	defm	""
	defb	193

	defm	""
	defb	190

	defm	"e"
	defb	132

	defm	" hi"
	defb	181

	defm	""
	defb	162

	defm	""
	defb	133

	defm	"m"
	defb	159

	defm	"impi"
	defb	146

	defm	"v"
	defb	168

	defm	""
	defb	148

	defm	""
	defb	128

	defm	"di"
	defb	193

	defm	""
	defb	195

	defm	""
	defb	203

	defm	"a"
	defb	199

	defm	"A"
	defb	173

	defm	"o"
	defb	165

	defm	"t"
	defb	159

	defm	"s"
	defb	159

	defm	"di"
	defb	193

	defm	""
	defb	211

	defm	"gu"
	defb	159

	defm	""
	defb	205

	defm	""
	defb	160

	defm	"difi"
	defb	203

	defm	""
	defb	162

	defm	""
	defb	133

	defm	""
	defb	234

	defm	"dr%a"
	defb	188

	defm	""
	defb	168

	defm	""
	defb	128

	defm	""
	defb	145

	defm	""
	defb	191

	defm	""
	defb	134

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n."
	defb	0

	defm	"E"
	defb	180

	defm	""
	defb	170

	defm	""
	defb	213

	defm	""
	defb	182

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n"
	defb	0

	defm	"U"
	defb	178

	defm	""
	defb	192

	defm	"ol"
	defb	142

	defm	""
	defb	192

	defm	"e"
	defb	198

	defm	""
	defb	173

	defm	""
	defb	222

	defm	""
	defb	148

	defm	"cu"
	defb	145

	defm	"a"
	defb	148

	defm	"c"
	defb	171

	defm	"v"
	defb	191

	defm	"a"
	defb	148

	defm	""
	defb	128

	defm	"sup"
	defb	168

	defm	"fi"
	defb	203

	defm	""
	defb	159

	defm	"he"
	defb	171

	defm	"d"
	defb	134

	defm	" Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"Zo"
	defb	178

	defm	" A1"
	defb	0

	defm	"L"
	defb	152

	defm	"m"
	defb	184

	defm	"&"
	defb	209

	defm	""
	defb	178

	defm	"s"
	defb	136

	defm	"a"
	defb	180

	defm	""
	defb	168

	defm	"%"
	defb	152

	defm	""
	defb	186

	defm	"p"
	defb	217

	defm	""
	defb	198

	defm	""
	defb	132

	defm	""
	defb	131

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	""
	defb	156

	defm	"b"
	defb	171

	defm	"nc"
	defb	158

	defm	"c"
	defb	186

	defm	"a"
	defb	167

	defm	"u"
	defb	178

	defm	""
	defb	182

	defm	"tm&sf"
	defb	168

	defm	"a imp"
	defb	168

	defm	"so"
	defb	178

	defm	"l"
	defb	199

	defm	"A"
	defb	173

	defm	"o"
	defb	165

	defm	"t"
	defb	159

	defm	"u"
	defb	167

	defm	""
	defb	194

	defm	"cur"
	defb	162

	defm	"p"
	defb	189

	defm	"ill"
	defb	162

	defm	""
	defb	213

	defm	""
	defb	182

	defm	"cc"
	defb	165

	defm	""
	defb	162

	defm	"a"
	defb	212

	defm	""
	defb	178

	defm	""
	defb	188

	defm	"a"
	defb	151

	defm	""
	defb	201

	defm	"ja."
	defb	0

	defm	"Zo"
	defb	178

	defm	" A2"
	defb	0

	defm	"El"
	defb	172

	defm	""
	defb	189

	defm	"ill"
	defb	162

	defm	"t"
	defb	168

	defm	""
	defb	218

	defm	""
	defb	178

	defm	""
	defb	130

	defm	"u"
	defb	178

	defm	""
	defb	188

	defm	"a"
	defb	151

	defm	""
	defb	237

	defm	"o"
	defb	207

	defm	"d"
	defb	191

	defm	"a ilu"
	defb	218

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	130

	defm	""
	defb	201

	defm	"jo"
	defb	199

	defm	"L"
	defb	152

	defm	"m"
	defb	184

	defm	"&"
	defb	209

	defm	""
	defb	178

	defm	"s"
	defb	136

	defm	"a"
	defb	180

	defm	""
	defb	168

	defm	"%"
	defb	152

	defm	"pr"
	defb	194

	defm	"igu"
	defb	163

	defm	""
	defb	188

	defm	"u"
	defb	176

	defm	"urso"
	defb	131

	defm	""
	defb	192

	defm	"#s"
	defb	131

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	""
	defb	156

	defm	"b"
	defb	171

	defm	"nc"
	defb	158

	defm	"p"
	defb	168

	defm	"f"
	defb	223

	defm	""
	defb	198

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	"o"
	defb	141

	defm	"a"
	defb	185

	defm	"s."
	defb	0

	defm	"ZHL^ E"
	defb	180

	defm	""
	defb	186

	defm	"gam"
	defb	158

	defm	"su"
	defb	172

	defm	"aq"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	130

	defm	"24h"
	defb	199

	defm	"^ (c) 2016"
	defb	232

	defm	"2019 KMBR"
	defb	199

	defm	"R"
	defb	181

	defm	"e"
	defb	189

	defm	""
	defb	159

	defm	"4."
	defb	0

	defm	"N"
	defb	162

	defm	""
	defb	207

	defm	""
	defb	162

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	130

	defm	"p"
	defb	174

	defm	"t"
	defb	227

	defm	"u"
	defb	171

	defm	"r."
	defb	0

	defm	"ZHL b"
	defb	233

	defm	"KMBR"
	defb	0

	defm	"D"
	defb	165

	defm	""
	defb	203

	defm	""
	defb	163

	defm	"d"
	defb	163

	defm	""
	defb	182

	defm	""
	defb	173

	defm	""
	defb	220

	defm	"d"
	defb	162

	defm	"c"
	defb	145

	defm	""
	defb	190

	defm	"."
	defb	0

	defm	"As"
	defb	203

	defm	""
	defb	163

	defm	"d"
	defb	163

	defm	""
	defb	182

	defm	"l"
	defb	172

	defm	"u"
	defb	157

	defm	""
	defb	142

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"E"
	defb	173

	defm	"m&du"
	defb	215

	defm	""
	defb	139

	defm	"a"
	defb	153

	defm	"m"
	defb	195

	defm	"d"
	defb	174

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"."
	defb	0

	defm	"La v%a"
	defb	177

	defm	"#c"
	defb	169

	defm	"a"
	defb	130

	defm	"nu"
	defb	165

	defm	""
	defb	200

	defm	""
	defb	162

	defm	"c"
	defb	189

	defm	"o."
	defb	0

	defm	"La"
	defb	131

	defm	"sol"
	defb	134

	defm	" "
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	"E"
	defb	161

	defm	"u"
	defb	167

	defm	""
	defb	236

	defm	""
	defb	164

	defm	"l"
	defb	162

	defm	"b"
	defb	189

	defm	""
	defb	198

	defm	""
	defb	180

	defm	""
	defb	159

	defm	"n"
	defb	179

	defm	"vo,"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	""
	defb	237

	defm	""
	defb	175

	defm	"d"
	defb	162

	defm	""
	defb	222

	defm	""
	defb	148

	defm	"c"
	defb	174

	defm	"g"
	defb	134

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	"y"
	defb	197

	defm	"od"
	defb	158

	defm	"l"
	defb	194

	defm	""
	defb	153

	defm	"m"
	defb	195

	defm	"d"
	defb	158

	defm	"s"
	defb	159

	defm	""
	defb	186

	defm	""
	defb	190

	defm	"iza"
	defb	167

	defm	"p"
	defb	175

	defm	" voz"
	defb	199

	defm	"En"
	defb	136

	defm	""
	defb	159

	defm	""
	defb	236

	defm	"m"
	defb	157

	defm	"o"
	defb	128

	defm	""
	defb	196

	defm	""
	defb	180

	defm	""
	defb	190

	defm	"l"
	defb	134

	defm	""
	defb	128

	defm	"c"
	defb	184

	defm	"so"
	defb	171

	defm	""
	defb	136

	defm	"#"
	defb	130

	defm	""
	defb	239

	defm	"g"
	defb	201

	defm	"."
	defb	0

	defm	"-F"
	defb	205

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	"m"
	defb	194

	defm	""
	defb	130

	defm	""
	defb	236

	defm	"d"
	defb	162

	defm	""
	defb	146

	defm	"bajo"
	defb	131

	defm	"su"
	defb	236

	defm	""
	defb	199

	defm	"La"
	defb	131

	defm	"sol"
	defb	134

	defm	"b"
	defb	159

	defm	"p"
	defb	168

	defm	"m"
	defb	195

	defm	""
	defb	223

	defm	""
	defb	168

	defm	""
	defb	182

	defm	""
	defb	196

	defm	"g"
	defb	191

	defm	"a -r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"P"
	defb	201

	defm	"vi"
	defb	163

	defm	""
	defb	142

	defm	""
	defb	128

	defm	"c"
	defb	184

	defm	"sol"
	defb	134

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	"s"
	defb	199

	defm	"La"
	defb	131

	defm	"so"
	defb	171

	defm	""
	defb	136

	defm	"#"
	defb	130

	defm	""
	defb	236

	defm	"d"
	defb	162

	defm	""
	defb	146

	defm	"bajo"
	defb	131

	defm	"su"
	defb	236

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"N"
	defb	208

	defm	"v"
	defb	159

	defm	""
	defb	233

	defm	"hi"
	defb	181

	defm	""
	defb	162

	defm	"a 150 C"
	defb	181

	defm	""
	defb	214

	defm	"u"
	defb	161

	defm	"baj"
	defb	162

	defm	"c"
	defb	168

	defm	"o."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	197

	defm	"$r"
	defb	218

	defm	"c"
	defb	162

	defm	"ap"
	defb	163

	defm	""
	defb	152

	defm	"p"
	defb	179

	defm	""
	defb	146

	defm	"evit"
	defb	174

	defm	""
	defb	128

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	146

	defm	"c"
	defb	219

	defm	""
	defb	193

	defm	""
	defb	190

	defm	""
	defb	165

	defm	""
	defb	148

	defm	""
	defb	129

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	" "
	defb	164

	defm	"l"
	defb	139

	defm	""
	defb	237

	defm	""
	defb	219

	defm	"s"
	defb	189

	defm	"."
	defb	0

	defm	"S"
	defb	159

	defm	"f"
	defb	175

	defm	"m"
	defb	195

	defm	""
	defb	130

	defm	"l"
	defb	158

	defm	"g"
	defb	170

	defm	"di"
	defb	157

	defm	""
	defb	156

	defm	"t$r"
	defb	218

	defm	""
	defb	187

	defm	""
	defb	132

	defm	"l"
	defb	139

	defm	""
	defb	237

	defm	""
	defb	219

	defm	""
	defb	210

	defm	""
	defb	132

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"."
	defb	0

	defm	"La "
	defb	178

	defm	"v"
	defb	142

	defm	" "
	defb	186

	defm	"p"
	defb	174

	defm	"t"
	defb	162

	defm	"d"
	defb	184

	defm	""
	defb	146

	defm	"hago"
	defb	128

	defm	"ru"
	defb	198

	defm	""
	defb	199

	defm	"E"
	defb	161

	defm	"u"
	defb	167

	defm	""
	defb	236

	defm	""
	defb	164

	defm	"l"
	defb	162

	defm	""
	defb	211

	defm	"du"
	defb	193

	defm	""
	defb	219

	defm	""
	defb	190

	defm	""
	defb	131

	defm	""
	defb	193

	defm	"rui"
	defb	185

	defm	""
	defb	131

	defm	""
	defb	192

	defm	"&dul"
	defb	194

	defm	""
	defb	136

	defm	"#"
	defb	225

	defm	""
	defb	174

	defm	""
	defb	199

	defm	"H"
	defb	224

	defm	""
	defb	159

	defm	"su"
	defb	197

	defm	""
	defb	170

	defm	"baj"
	defb	162

	defm	"y"
	defb	202

	defm	""
	defb	162

	defm	"s"
	defb	159

	defm	"av"
	defb	168

	defm	"%"
	defb	134

	defm	"m"
	defb	189

	defm	"i"
	defb	191

	defm	""
	defb	152

	defm	""
	defb	207

	defm	"c"
	defb	165

	defm	"."
	defb	0

	defm	"-Co"
	defb	180

	defm	""
	defb	201

	defm	""
	defb	171

	defm	""
	defb	128

	defm	""
	defb	169

	defm	"mp"
	defb	168

	defm	"atu"
	defb	170

	defm	""
	defb	148

	defm	""
	defb	129

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	"i"
	defb	175

	defm	" y"
	defb	130

	defm	"l"
	defb	158

	defm	""
	defb	211

	defm	""
	defb	193

	defm	"rum"
	defb	157

	defm	""
	defb	194

	defm	""
	defb	139

	defm	""
	defb	155

	defm	"vit"
	defb	174

	defm	""
	defb	188

	defm	"u "
	defb	164

	defm	"t"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	162

	defm	"-"
	defb	211

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"E"
	defb	161

	defm	""
	defb	205

	defm	""
	defb	162

	defm	""
	defb	138

	defm	""
	defb	158

	defm	"d"
	defb	158

	defm	"t"
	defb	170

	defm	"je"
	defb	132

	defm	""
	defb	188

	defm	"up"
	defb	168

	defm	"viv"
	defb	163

	defm	""
	defb	203

	defm	"a"
	defb	202

	defm	""
	defb	223

	defm	""
	defb	165

	defm	""
	defb	174

	defm	""
	defb	241

	defm	""
	defb	139

	defm	"a "
	defb	186

	defm	""
	defb	190

	defm	"iz"
	defb	174

	defm	" EVA"
	defb	199

	defm	"E"
	defb	173

	defm	"t"
	defb	170

	defm	"je"
	defb	149

	defm	""
	defb	153

	defm	"mp"
	defb	217

	defm	""
	defb	198

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	"au"
	defb	209

	defm	"m#t"
	defb	227

	defm	""
	defb	162

	defm	"y"
	defb	197

	defm	"i"
	defb	163

	defm	""
	defb	159

	defm	"u"
	defb	178

	defm	""
	defb	182

	defm	"ut"
	defb	184

	defm	"om%"
	defb	134

	defm	""
	defb	216

	defm	"ch"
	defb	162

	defm	"ho"
	defb	170

	defm	"s"
	defb	199

	defm	""
	defb	0

	defm	"Paq"
	defb	179

	defm	"t"
	defb	156

	defm	"a "
	defb	145

	defm	"eg"
	defb	174

	defm	""
	defb	172

	defm	""
	defb	175

	defm	""
	defb	129

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	188

	defm	"o"
	defb	171

	defm	"r."
	defb	0

	defm	"E"
	defb	193

	defm	"#"
	defb	182

	defm	""
	defb	196

	defm	"g"
	defb	191

	defm	"a."
	defb	0

	defm	"N"
	defb	162

	defm	"sob"
	defb	186

	defm	"vivir$"
	defb	130

	defm	"Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	188

	defm	""
	defb	211

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	159

	defm	"p"
	defb	201

	defm	""
	defb	169

	defm	"ct"
	defb	175

	defm	"."
	defb	0

	defm	"-P"
	defb	140

	defm	"evit"
	defb	174

	defm	""
	defb	131

	defm	""
	defb	198

	defm	""
	defb	218

	defm	""
	defb	178

	defm	""
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	164

	defm	"ja"
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	159

	defm	""
	defb	195

	defm	""
	defb	169

	defm	""
	defb	132

	defm	""
	defb	172

	defm	""
	defb	189

	defm	""
	defb	174

	defm	""
	defb	182

	defm	""
	defb	173

	defm	""
	defb	220

	defm	"d"
	defb	162

	defm	"c"
	defb	145

	defm	"a"
	defb	173

	defm	"-t"
	defb	159

	defm	""
	defb	186

	defm	"cu"
	defb	168

	defm	""
	defb	213

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"La"
	defb	149

	defm	"clu"
	defb	210

	defm	""
	defb	188

	defm	"ir"
	defb	207

	defm	""
	defb	139

	defm	"a igua"
	defb	171

	defm	"r"
	defb	128

	defm	"pr"
	defb	165

	defm	"i&"
	defb	167

	defm	""
	defb	145

	defm	"e"
	defb	129

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	" y"
	defb	129

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	"i"
	defb	175

	defm	" "
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	"Se"
	defb	131

	defm	""
	defb	200

	defm	"o"
	defb	171

	defm	""
	defb	131

	defm	""
	defb	129

	defm	"b&"
	defb	209

	defm	""
	defb	167

	defm	""
	defb	201

	defm	"jo"
	defb	139

	defm	"a"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	183

	defm	"y"
	defb	129

	defm	"bot&"
	defb	167

	defm	"v"
	defb	168

	defm	""
	defb	164

	defm	""
	defb	139

	defm	"a"
	defb	182

	defm	"b"
	defb	219

	defm	"r"
	defb	199

	defm	""
	defb	0

	defm	"E"
	defb	193

	defm	"#"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	213

	defm	"."
	defb	0

	defm	"E"
	defb	193

	defm	"#"
	defb	182

	defm	"bi"
	defb	168

	defm	""
	defb	198

	defm	"."
	defb	0

	defm	"-La"
	defb	149

	defm	"clu"
	defb	210

	defm	""
	defb	188

	defm	""
	defb	159

	defm	""
	defb	237

	defm	""
	defb	186

	defm	""
	defb	131

	defm	""
	defb	177

	defm	""
	defb	194

	defm	""
	defb	131

	defm	""
	defb	200

	defm	"ol"
	defb	156

	defm	"m"
	defb	195

	defm	"u"
	defb	190

	defm	""
	defb	156

	defm	"-"
	defb	211

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"-La"
	defb	149

	defm	"clu"
	defb	210

	defm	""
	defb	188

	defm	""
	defb	159

	defm	""
	defb	203

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	131

	defm	""
	defb	177

	defm	""
	defb	194

	defm	""
	defb	131

	defm	""
	defb	200

	defm	"ol"
	defb	156

	defm	"m"
	defb	195

	defm	"u"
	defb	190

	defm	""
	defb	156

	defm	"-"
	defb	211

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"Puls"
	defb	174

	defm	""
	defb	139

	defm	"a"
	defb	182

	defm	"b"
	defb	219

	defm	"r"
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	199

	defm	"^ADVERTENCIA: ANTES DE ABRIR U"
	defm	"SAR EL TRAJE DE SUPERVIVENCIA "
	defm	"EN ENTORNOS HOSTILES."
	defb	0

	defm	"Puls"
	defb	174

	defm	""
	defb	139

	defm	"a"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	"r"
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	"."
	defb	0

	defm	"-La"
	defb	149

	defm	"clu"
	defb	210

	defm	" ya"
	defb	136

	defm	"#"
	defb	182

	defm	"bi"
	defb	168

	defm	""
	defb	198

	defm	"."
	defb	0

	defm	"-Ab"
	defb	219

	defm	""
	defb	163

	defm	""
	defb	185

	defm	""
	defb	153

	defm	"m"
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	155

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	" y"
	defb	182

	defm	""
	defb	231

	defm	""
	defb	171

	defm	"n"
	defb	185

	defm	""
	defb	129

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	"i"
	defb	175

	defm	" -d"
	defb	227

	defm	"e"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	199

	defm	"La"
	defb	153

	defm	"m"
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	155

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	188

	defm	""
	defb	159

	defm	""
	defb	237

	defm	""
	defb	186

	defm	""
	defb	131

	defm	""
	defb	212

	defm	""
	defb	167

	defm	""
	defb	214

	defm	""
	defb	222

	defm	""
	defb	162

	defm	""
	defb	218

	defm	""
	defb	145

	defm	""
	defb	152

	defm	"s"
	defb	159

	defm	"igua"
	defb	171

	defm	"n"
	defb	150

	defm	""
	defb	161

	defm	"pr"
	defb	165

	defm	"i"
	defb	184

	defm	""
	defb	165

	defm	"."
	defb	0

	defm	"-C"
	defb	168

	defm	""
	defb	170

	defm	"n"
	defb	185

	defm	""
	defb	153

	defm	"m"
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	155

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	"- "
	defb	186

	defm	"pi"
	defb	169

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	0

	defm	"U"
	defb	178

	defm	" "
	defb	207

	defm	"z"
	defb	128

	defm	""
	defb	187

	defm	"m"
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	155

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	188

	defm	""
	defb	159

	defm	"ha"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	185

	defm	""
	defb	232

	defm	""
	defb	205

	defm	""
	defb	158

	defm	"ch"
	defb	175

	defm	""
	defb	201

	defm	""
	defb	132

	defm	""
	defb	182

	defm	"ir"
	defb	159

	defm	"a"
	defb	172

	defm	"r"
	defb	165

	defm	"i&"
	defb	167

	defm	"surg"
	defb	163

	defm	""
	defb	166

	defm	""
	defb	137

	defm	"s"
	defb	139

	defm	"e"
	defb	164

	defm	"s"
	defb	139

	defm	"a"
	defb	154

	defm	"im"
	defb	211

	defm	""
	defb	174

	defm	""
	defb	177

	defm	""
	defb	194

	defm	""
	defb	131

	defm	""
	defb	198

	defm	""
	defb	218

	defm	""
	defb	178

	defm	""
	defb	180

	defm	""
	defb	156

	defm	""
	defb	159

	defm	"igua"
	defb	171

	defm	""
	defb	183

	defm	""
	defb	146

	defm	"n"
	defb	179

	defm	"vo"
	defb	128

	defm	"pr"
	defb	165

	defm	"i"
	defb	226

	defm	"."
	defb	0

	defm	"U"
	defb	167

	defm	"p"
	defb	195

	defm	""
	defb	147

	defm	"s"
	defb	159

	defm	""
	defb	237

	defm	"r"
	defb	159

	defm	"y"
	defb	172

	defm	""
	defb	168

	defm	""
	defb	218

	defm	""
	defb	169

	defm	""
	defb	129

	defm	""
	defb	224

	defm	"c"
	defb	165

	defm	""
	defb	162

	defm	"a"
	defb	173

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	"i"
	defb	175

	defm	" "
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"."
	defb	0

	defm	"-La"
	defb	149

	defm	"clu"
	defb	210

	defm	" ya"
	defb	136

	defm	"#"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	213

	defm	" -"
	defb	186

	defm	"p"
	defb	175

	defm	""
	defb	198

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	""
	defb	237

	defm	""
	defb	175

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"Ap"
	defb	163

	defm	""
	defb	152

	defm	""
	defb	205

	defm	""
	defb	158

	defm	""
	defb	218

	defm	"l%"
	defb	235

	defm	""
	defb	200

	defm	"o"
	defb	132

	defm	""
	defb	172

	defm	"l#"
	defb	193

	defm	""
	defb	227

	defm	""
	defb	162

	defm	"y"
	defb	192

	defm	"e"
	defb	198

	defm	""
	defb	173

	defm	"t"
	defb	159

	defm	""
	defb	222

	defm	""
	defb	144

	defm	"n"
	defb	166

	defm	""
	defb	147

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	"."
	defb	0

	defm	"-Fr%"
	defb	162

	defm	"a"
	defb	173

	defm	""
	defb	198

	defm	"c"
	defb	209

	defm	"."
	defb	0

	defm	"Co"
	defb	236

	defm	""
	defb	130

	defm	"u"
	defb	178

	defm	""
	defb	202

	defm	"och"
	defb	159

	defm	""
	defb	194

	defm	"cu"
	defb	170

	defm	""
	defb	188

	defm	""
	defb	190

	defm	"v"
	defb	162

	defm	"p"
	defb	175

	defm	""
	defb	129

	defm	"b"
	defb	219

	defm	"l"
	defb	215

	defm	""
	defb	149

	defm	""
	defb	206

	defm	"iv"
	defb	162

	defm	""
	defb	138

	defm	""
	defb	158

	defm	""
	defb	200

	defm	"ozo"
	defb	132

	defm	" hi"
	defb	181

	defm	""
	defb	162

	defm	""
	defb	133

	defm	""
	defb	165

	defm	"t#"
	defb	167

	defm	""
	defb	228

	defm	"y"
	defb	163

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"La "
	defb	178

	defm	"v"
	defb	159

	defm	""
	defb	236

	defm	"du"
	defb	171

	defm	"r"
	defb	136

	defm	"#"
	defb	225

	defm	""
	defb	174

	defm	" "
	defb	146

	defm	"ZHL"
	defb	199

	defm	"Pi"
	defb	180

	defm	""
	defb	191

	defm	""
	defb	134

	defm	""
	defb	182

	defm	"m"
	defb	174

	defm	"ill"
	defb	162

	defm	"y"
	defb	131

	defm	""
	defb	129

	defm	""
	defb	215

	defm	"g"
	defb	162

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	187

	defm	"m"
	defb	196

	defm	"+%a"
	defb	130

	defm	"g"
	defb	170

	defm	""
	defb	225

	defm	""
	defb	156

	defm	""
	defb	217

	defm	""
	defb	200

	defm	""
	defb	152

	defm	""
	defb	201

	defm	"j"
	defb	189

	defm	"."
	defb	0

	defm	"ZHL 24h"
	defb	0

	defm	"C"
	defb	184

	defm	""
	defb	166

	defm	"if"
	defb	227

	defm	"ult"
	defb	191

	defm	""
	defb	166

	defm	"i"
	defb	193

	defm	""
	defb	211

	defm	"o"
	defb	129

	defm	"p"
	defb	168

	defm	"fi"
	defb	173

	defm	""
	defb	146

	defm	""
	defb	205

	defm	""
	defb	160

	defm	"difi"
	defb	203

	defm	""
	defb	162

	defm	""
	defb	146

	defm	""
	defb	235

	defm	"t"
	defb	190

	defm	""
	defb	148

	defm	""
	defb	128

	defm	"t"
	defb	175

	defm	"m"
	defb	157

	defm	"a"
	defb	199

	defm	""
	defb	0

	defm	"E"
	defb	167

	defm	""
	defb	205

	defm	""
	defb	150

	defm	"t"
	defb	168

	defm	"a"
	defb	173

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	145

	defm	""
	defb	191

	defm	"a b"
	defb	219

	defm	"l"
	defb	151

	defm	"u"
	defb	167

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	"d"
	defb	162

	defm	"num$"
	defb	219

	defm	""
	defb	187

	defm	"."
	defb	0

	defm	"P"
	defb	175

	defm	""
	defb	212

	defm	""
	defb	178

	defm	""
	defb	182

	defm	"b"
	defb	168

	defm	"tu"
	defb	170

	defm	""
	defb	188

	defm	""
	defb	142

	defm	"sliza"
	defb	212

	defm	""
	defb	167

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	"l#s"
	defb	168

	defm	" "
	defb	133

	defm	"t"
	defb	159

	defm	"a"
	defb	238

	defm	""
	defb	180

	defm	"a: TECLEE EL C&DIGO DE ACCESO"
	defb	199

	defm	"TIENE UNA OPORTUNIDAD ANTES DE"
	defm	" SER DESINTEGRADO."
	defb	0

	defm	"U"
	defb	167

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	""
	defb	146

	defm	""
	defb	189

	defm	"p"
	defb	223

	defm	"t"
	defb	162

	defm	"p"
	defb	181

	defm	"igr"
	defb	194

	defm	""
	defb	162

	defm	""
	defb	214

	defm	"gu"
	defb	159

	defm	""
	defb	218

	defm	""
	defb	161

	defm	""
	defb	236

	defm	"vi"
	defb	218

	defm	""
	defb	157

	defm	""
	defb	194

	defm	"."
	defb	0

	defm	"Tod"
	defb	162

	defm	"so"
	defb	167

	defm	""
	defb	228

	defm	"j"
	defb	152

	defm	"b"
	defb	171

	defm	"n"
	defb	228

	defm	""
	defb	132

	defm	""
	defb	197

	defm	"a"
	defb	204

	defm	"+"
	defb	162

	defm	""
	defb	214

	defm	""
	defb	218

	defm	""
	defb	171

	defm	"r"
	defb	199

	defm	"L"
	defb	152

	defm	"m#"
	defb	161

	defm	"g"
	defb	170

	defm	""
	defb	225

	defm	""
	defb	156

	defm	""
	defb	222

	defm	""
	defb	148

	defm	"cu"
	defb	145

	defm	""
	defb	195

	defm	""
	defb	130

	defm	"l"
	defb	194

	defm	""
	defb	136

	defm	"a"
	defb	180

	defm	""
	defb	156

	defm	"m#"
	defb	161

	defm	"baj"
	defb	194

	defm	"."
	defb	0

	defm	"A"
	defb	215

	defm	"ja"
	defb	167

	defm	""
	defb	164

	defm	"c"
	defb	163

	defm	"a"
	defb	132

	defm	""
	defb	172

	defm	"eq"
	defb	179

	defm	"+"
	defb	194

	defm	""
	defb	131

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	""
	defb	156

	defm	"b"
	defb	171

	defm	"n"
	defb	187

	defm	"s."
	defb	0

	defm	"Tod"
	defb	162

	defm	"f"
	defb	205

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	"l"
	defb	199

	defm	"El"
	defb	149

	defm	""
	defb	196

	defm	""
	defb	203

	defm	""
	defb	162

	defm	"sufi"
	defb	203

	defm	""
	defb	157

	defm	"e"
	defb	139

	defm	"a"
	defb	192

	defm	"a"
	defb	180

	defm	""
	defb	163

	defm	""
	defb	168

	defm	""
	defb	150

	defm	"s"
	defb	131

	defm	"di"
	defb	203

	defm	""
	defb	184

	defm	""
	defb	156

	defm	"n"
	defb	223

	defm	""
	defb	165

	defm	""
	defb	174

	defm	"i"
	defb	189

	defm	""
	defb	139

	defm	"a"
	defb	172

	defm	"r"
	defb	165

	defm	""
	defb	168

	defm	"v"
	defb	174

	defm	""
	defb	192

	defm	"at"
	defb	168

	defm	"i"
	defb	190

	defm	""
	defb	156

	defm	"b"
	defb	241

	defm	"l&gi"
	defb	187

	defm	"s."
	defb	0

	defm	"U"
	defb	178

	defm	""
	defb	154

	defm	"ev"
	defb	191

	defm	"a b&"
	defb	207

	defm	""
	defb	213

	defm	" f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	129

	defm	""
	defb	169

	defm	"ch"
	defb	162

	defm	""
	defb	164

	defm	""
	defb	136

	defm	"a"
	defb	188

	defm	"a"
	defb	171

	defm	"."
	defb	0

	defm	"U"
	defb	167

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	159

	defm	"azul"
	defb	131

	defm	""
	defb	212

	defm	""
	defb	167

	defm	"g"
	defb	170

	defm	""
	defb	167

	defm	""
	defb	211

	defm	"d"
	defb	227

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	"p"
	defb	181

	defm	"igr"
	defb	162

	defm	"b"
	defb	241

	defm	"l&gi"
	defb	187

	defm	""
	defb	148

	defm	""
	defb	129

	defm	"f"
	defb	201

	defm	""
	defb	180

	defm	""
	defb	190

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Es"
	defb	169

	defm	""
	defb	149

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	159

	defm	"-susur"
	defb	170

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	130

	defm	"tu"
	defb	216

	defm	"%"
	defb	185

	defm	"."
	defb	0

	defm	"-N"
	defb	162

	defm	"p"
	defb	179

	defm	""
	defb	185

	defm	","
	defb	150

	defm	""
	defb	161

	defm	"di"
	defb	186

	defm	"ctiva"
	defb	132

	defm	""
	defb	128

	defm	""
	defb	240

	defm	"pr"
	defb	165

	defm	"a"
	defb	192

	defm	""
	defb	159

	defm	"l"
	defb	162

	defm	"impid"
	defb	163

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"P"
	defb	181

	defm	"igr"
	defb	162

	defm	"b"
	defb	241

	defm	"l&gi"
	defb	187

	defm	""
	defb	199

	defm	"C"
	defb	184

	defm	"s"
	defb	168

	defm	"v"
	defb	174

	defm	""
	defb	182

	defm	""
	defb	192

	defm	""
	defb	163

	defm	"o"
	defb	132

	defm	" 15"
	defb	176

	defm	""
	defb	181

	defm	""
	defb	214

	defm	"u"
	defb	161

	defm	"baj"
	defb	162

	defm	"c"
	defb	168

	defm	"o"
	defb	199

	defm	"N"
	defb	162

	defm	"m"
	defb	195

	defm	"i"
	defb	238

	defm	""
	defb	171

	defm	""
	defb	183

	defm	""
	defb	214

	defm	""
	defb	167

	defm	"p"
	defb	201

	defm	""
	defb	169

	defm	"c"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	199

	defm	"N"
	defb	162

	defm	""
	defb	237

	defm	""
	defb	219

	defm	"r"
	defb	199

	defm	"N"
	defb	162

	defm	"gol"
	defb	243

	defm	""
	defb	174

	defm	""
	defb	199

	defm	"Mat"
	defb	168

	defm	"ia"
	defb	173

	defm	"fr#gil."
	defb	0

	defm	"-Co"
	defb	175

	defm	"d"
	defb	211

	defm	""
	defb	162

	defm	""
	defb	209

	defm	"d"
	defb	158

	defm	"l"
	defb	158

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	132

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	"P"
	defb	140

	defm	"h"
	defb	237

	defm	""
	defb	171

	defm	"r"
	defb	131

	defm	""
	defb	218

	defm	"go"
	defb	160

	defm	"mp"
	defb	217

	defm	"a:"
	defb	216

	defm	""
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	172

	defm	"a"
	defb	171

	defm	"b"
	defb	170

	defm	""
	defb	176

	defm	""
	defb	171

	defm	""
	defb	207

	defm	""
	defb	199

	defm	"Alg"
	defb	205

	defm	""
	defb	152

	defm	"sug"
	defb	168

	defm	""
	defb	163

	defm	""
	defb	203

	defm	"a"
	defb	132

	defm	""
	defb	172

	defm	"a"
	defb	171

	defm	"br"
	defb	152

	defm	"c"
	defb	171

	defm	"v"
	defb	159

	defm	"s"
	defb	184

	defm	":"
	defb	216

	defm	""
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	182

	defm	"yu"
	defb	213

	defm	","
	defb	216

	defm	""
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	202

	defm	"omb"
	defb	186

	defm	","
	defb	216

	defm	""
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	192

	defm	"i"
	defb	214

	defm	""
	defb	226

	defm	".."
	defb	199

	defm	"-t"
	defb	159

	defm	"r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	146

	defm	"s"
	defb	168

	defm	"vi"
	defb	203

	defm	""
	defb	190

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-Oh"
	defb	232

	defm	"vaya"
	defb	153

	defm	"m"
	defb	162

	defm	"n"
	defb	162

	defm	"p"
	defb	163

	defm	"s$"
	defb	130

	defm	""
	defb	217

	defm	""
	defb	168

	defm	""
	defb	149

	defm	""
	defb	162

	defm	"-d"
	defb	227

	defm	"e"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	131

	defm	" f"
	defb	190

	defm	""
	defb	210

	defm	""
	defb	182

	defm	"d"
	defb	218

	defm	""
	defb	170

	defm	""
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	" "
	defb	0

	defm	"N"
	defb	162

	defm	""
	defb	220

	defm	"t"
	defb	162

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	130

	defm	"p"
	defb	174

	defm	"t"
	defb	227

	defm	"u"
	defb	171

	defm	"r."
	defb	0

	defm	"N"
	defb	191

	defm	"a "
	defb	133

	defm	""
	defb	164

	defm	""
	defb	193

	defm	""
	defb	224

	defm	""
	defb	174

	defm	"."
	defb	0

	defm	"No"
	defb	149

	defm	""
	defb	149

	defm	""
	defb	243

	defm	""
	defb	203

	defm	""
	defb	190

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	""
	defb	165

	defm	""
	defb	195

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"N"
	defb	162

	defm	"su"
	defb	230

	defm	""
	defb	146

	defm	""
	defb	178

	defm	""
	defb	213

	defm	" "
	defb	211

	defm	""
	defb	165

	defm	"p"
	defb	168

	defm	"a"
	defb	185

	defm	"."
	defb	0

	defm	"E"
	defb	173

	defm	"aullid"
	defb	162

	defm	"d"
	defb	147

	defm	"vi"
	defb	157

	defm	""
	defb	162

	defm	"r"
	defb	165

	defm	"u"
	defb	163

	defm	"a"
	defb	148

	defm	""
	defb	129

	defm	"fu"
	defb	222

	defm	""
	defb	171

	defm	"je."
	defb	0

	defm	"-Bu"
	defb	163

	defm	""
	defb	197

	defm	""
	defb	170

	defm	"baj"
	defb	162

	defm	"-apr"
	defb	179

	defm	"ba"
	defb	128

	defm	"voz"
	defb	188

	defm	"at"
	defb	231

	defm	"f"
	defb	223

	defm	"h"
	defb	134

	defm	""
	defb	173

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	199

	defm	" "
	defb	0

	defm	"-Aho"
	defb	170

	defm	""
	defb	149

	defm	""
	defb	192

	defm	"om"
	defb	157

	defm	""
	defb	162

	defm	""
	defb	146

	defm	"p"
	defb	184

	defm	""
	defb	168

	defm	""
	defb	221

	defm	"umb"
	defb	162

	defm	"a M"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	199

	defm	"Baja"
	defb	182

	defm	""
	defb	128

	defm	"bo"
	defb	164

	defm	"g"
	defb	134

	defm	""
	defb	176

	defm	""
	defb	174

	defm	"ga"
	defb	192

	defm	"i"
	defb	145

	defm	""
	defb	152

	defm	""
	defb	186

	defm	""
	defb	211

	defm	"i"
	defb	203

	defm	""
	defb	162

	defm	"l"
	defb	158

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	132

	defm	""
	defb	128

	defm	""
	defb	178

	defm	"v"
	defb	159

	defm	"-d"
	defb	227

	defm	"e"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	131

	defm	""
	defb	172

	defm	""
	defb	186

	defm	"mu"
	defb	170

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"D"
	defb	165

	defm	""
	defb	203

	defm	""
	defb	163

	defm	"d"
	defb	162

	defm	"l"
	defb	194

	defm	""
	defb	149

	defm	"c"
	defb	190

	defm	""
	defb	184

	defm	""
	defb	156

	defm	"a"
	defb	128

	defm	"bo"
	defb	164

	defm	"ga "
	defb	233

	defm	""
	defb	164

	defm	"p"
	defb	194

	defm	"i"
	defb	209

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	159

	defm	"ju"
	defb	180

	defm	""
	defb	162

	defm	"a"
	defb	177

	defm	"o"
	defb	132

	defm	"m#"
	defb	161

	defm	"p"
	defb	163

	defm	"di"
	defb	157

	defm	"e"
	defb	132

	defm	" "
	defb	145

	defm	"ega"
	defb	199

	defm	"A"
	defb	173

	defm	""
	defb	186

	defm	"gr"
	defb	165

	defm	""
	defb	174

	defm	" "
	defb	164

	defm	"scub"
	defb	201

	defm	""
	defb	135

	defm	""
	defb	128

	defm	""
	defb	210

	defm	""
	defb	151

	defm	"s"
	defb	159

	defm	"ha"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"-No"
	defb	149

	defm	" "
	defb	178

	defm	""
	defb	213

	defm	""
	defb	172

	defm	""
	defb	168

	defm	"so"
	defb	178

	defm	"l"
	defb	172

	defm	""
	defb	168

	defm	"o"
	defb	149

	defm	""
	defb	192

	defm	"om"
	defb	157

	defm	""
	defb	162

	defm	""
	defb	146

	defm	""
	defb	186

	defm	""
	defb	203

	defm	"c"
	defb	171

	defm	""
	defb	183

	defm	"-d"
	defb	227

	defm	"e"
	defb	128

	defm	"voz"
	defb	166

	defm	""
	defb	147

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"-"
	defb	192

	defm	"i"
	defb	145

	defm	""
	defb	152

	defm	"t"
	defb	159

	defm	"f"
	defb	190

	defm	""
	defb	171

	defm	"n"
	defb	150

	defm	""
	defb	161

	defm	"pi"
	defb	168

	defm	"n"
	defb	152

	defm	""
	defb	233

	defm	"gol"
	defb	243

	defm	""
	defb	189

	defm	""
	defb	131

	defm	""
	defb	128

	defm	""
	defb	228

	defm	"beza"
	defb	131

	defm	"t"
	defb	170

	defm	""
	defb	129

	defm	"s"
	defb	179

	defm	""
	defb	215

	defm	"."
	defb	0

	defm	"-L"
	defb	162

	defm	"m#"
	defb	161

	defm	"du"
	defb	201

	defm	""
	defb	149

	defm	""
	defb	197

	defm	""
	defb	163

	defm	""
	defb	168

	defm	" "
	defb	133

	defm	""
	defb	186

	defm	""
	defb	203

	defm	"c"
	defb	171

	defm	""
	defb	183

	defm	"su"
	defb	161

	defm	"p"
	defb	208

	defm	"z"
	defb	189

	defm	""
	defb	139

	defm	"a"
	defb	128

	defm	""
	defb	214

	defm	"gui"
	defb	157

	defm	""
	defb	159

	defm	""
	defb	218

	defm	""
	defb	214

	defm	""
	defb	226

	defm	""
	defb	199

	defm	"L"
	defb	217

	defm	"ga"
	defb	167

	defm	"a"
	defb	176

	defm	""
	defb	186

	defm	""
	defb	168

	defm	"s"
	defb	159

	defm	"hum"
	defb	195

	defm	""
	defb	194

	defm	""
	defb	199

	defm	"E"
	defb	167

	defm	"f"
	defb	211

	defm	".."
	defb	199

	defm	"-suspi"
	defb	170

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	192

	defm	"i"
	defb	145

	defm	""
	defb	152

	defm	""
	defb	186

	defm	""
	defb	187

	defm	"g"
	defb	159

	defm	"l"
	defb	158

	defm	"r"
	defb	165

	defm	""
	defb	209

	defm	""
	defb	132

	defm	""
	defb	197

	defm	"u"
	defb	176

	defm	"u"
	defb	168

	defm	""
	defb	234

	defm	""
	defb	131

	defm	""
	defb	212

	defm	""
	defb	178

	defm	" "
	defb	201

	defm	"bof"
	defb	186

	defm	"go"
	defb	178

	defm	"."
	defb	0

	defm	"-C"
	defb	145

	defm	""
	defb	190

	defm	","
	defb	182

	defm	""
	defb	206

	defm	"% Tod C"
	defb	184

	defm	"n"
	defb	175

	defm	" -d"
	defb	227

	defm	"e"
	defb	128

	defm	"voz- Vol"
	defb	207

	defm	"m"
	defb	158

	defm	"a M"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	131

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	199

	defm	"Repit"
	defb	162

	defm	"vol"
	defb	207

	defm	"m"
	defb	194

	defm	""
	defb	131

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"Hay"
	defb	166

	defm	""
	defb	158

	defm	"bot"
	defb	184

	defm	""
	defb	165

	defm	": "
	defb	201

	defm	"j"
	defb	162

	defm	""
	defb	233

	defm	"v"
	defb	168

	defm	""
	defb	164

	defm	""
	defb	199

	defm	"S"
	defb	159

	defm	"utiliz"
	defb	195

	defm	""
	defb	139

	defm	"a"
	defb	176

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	183

	defm	"y"
	defb	182

	defm	"b"
	defb	219

	defm	"r"
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	182

	defm	"l"
	defb	160

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"L"
	defb	158

	defm	""
	defb	214

	defm	"gui"
	defb	157

	defm	""
	defb	156

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	165

	defm	""
	defb	139

	defm	"a "
	defb	145

	defm	"eg"
	defb	174

	defm	"."
	defb	0

	defm	"No"
	defb	149

	defm	""
	defb	192

	defm	"om"
	defb	157

	defm	""
	defb	162

	defm	""
	defb	146

	defm	"jug"
	defb	174

	defm	""
	defb	182

	defm	""
	defb	173

	defm	"Sokob"
	defb	195

	defm	"."
	defb	0

	defm	"-Voo"
	defb	171

	defm	""
	defb	186

	defm	".."
	defb	199

	defm	"ooh"
	defb	216

	defm	"ooh -t"
	defb	142

	defm	"v"
	defb	179

	defm	"lv"
	defb	159

	defm	"cr"
	defb	179

	defm	"l"
	defb	129

	defm	""
	defb	223

	defm	""
	defb	162

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"."
	defb	0

	defm	"-Ca"
	defb	180

	defm	""
	defb	174

	defm	"e,"
	defb	216

	defm	"oh"
	defb	216

	defm	"ooh -i"
	defb	180

	defm	""
	defb	157

	defm	""
	defb	189

	defm	""
	defb	148

	defm	"t"
	defb	184

	defm	""
	defb	174

	defm	" ^ -N"
	defb	147

	defm	"blu"
	defb	166

	defm	"ipi"
	defb	180

	defm	""
	defb	162

	defm	"di blu..."
	defb	0

	defm	"S&"
	defb	215

	defm	""
	defb	149

	defm	"cucho"
	defb	136

	defm	"#t"
	defb	227

	defm	"a"
	defb	199

	defm	"La"
	defb	197

	defm	""
	defb	175

	defm	"m"
	defb	157

	defm	"a i"
	defb	180

	defm	""
	defb	168

	defm	"fi"
	defb	168

	defm	"e"
	defb	130

	defm	"l"
	defb	152

	defm	""
	defb	187

	defm	"m"
	defb	205

	defm	""
	defb	227

	defm	"a"
	defb	203

	defm	""
	defb	184

	defm	""
	defb	165

	defm	"."
	defb	0

	defm	"E"
	defb	193

	defm	"oy"
	defb	148

	defm	""
	defb	128

	defm	"c"
	defb	140

	defm	"ocul"
	defb	198

	defm	","
	defb	202

	defm	""
	defb	162

	defm	""
	defb	207

	defm	""
	defb	162

	defm	"J'pit"
	defb	168

	defm	"."
	defb	0

	defm	"Sat$lit"
	defb	159

	defm	"he"
	defb	171

	defm	"d"
	defb	162

	defm	""
	defb	159

	defm	""
	defb	211

	defm	"h&spi"
	defb	209

	defm	"."
	defb	0

	defm	"La "
	defb	145

	defm	""
	defb	191

	defm	"a"
	defb	182

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n"
	defb	199

	defm	""
	defb	0

	defm	"F"
	defb	205

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	""
	defb	131

	defm	""
	defb	153

	defm	"m"
	defb	195

	defm	""
	defb	185

	defm	""
	defb	132

	defm	" voz"
	defb	182

	defm	""
	defb	173

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	":"
	defb	216

	defm	""
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	176

	defm	""
	defb	171

	defm	""
	defb	207

	defm	"."
	defb	0

	defm	"E"
	defb	161

	defm	"u"
	defb	178

	defm	""
	defb	131

	defm	""
	defb	193

	defm	"ruc"
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	235

	defm	"t#l"
	defb	227

	defm	"a "
	defb	233

	defm	""
	defb	186

	defm	"ct"
	defb	195

	defm	"gu"
	defb	171

	defm	""
	defb	183

	defm	""
	defb	133

	defm	"s"
	defb	159

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	""
	defb	178

	defm	" baj"
	defb	162

	defm	"ti"
	defb	168

	defm	""
	defb	170

	defm	"."
	defb	0

	defm	"("
	defb	163

	defm	""
	defb	129

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	""
	defb	185

	defm	")"
	defb	0

	defm	"La"
	defb	172

	defm	"u"
	defb	168

	defm	"t"
	defb	134

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$"
	defb	167

	defm	"ya"
	defb	136

	defm	"#"
	defb	182

	defm	"bi"
	defb	168

	defm	""
	defb	198

	defm	"."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	"d"
	defb	162

	defm	"s"
	defb	159

	defm	"ilu"
	defb	218

	defm	""
	defb	178

	defm	""
	defb	130

	defm	""
	defb	201

	defm	"jo"
	defb	199

	defm	"CODIGO INCORRECTO."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	"d"
	defb	162

	defm	"s"
	defb	159

	defm	"ilu"
	defb	218

	defm	""
	defb	178

	defm	""
	defb	130

	defm	"v"
	defb	168

	defm	""
	defb	164

	defm	""
	defb	199

	defm	"CODIGO CORRECTO"
	defb	199

	defm	"E"
	defb	173

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	"l#s"
	defb	168

	defm	""
	defb	188

	defm	""
	defb	159

	defm	""
	defb	186

	defm	"pl"
	defb	208

	defm	"ga"
	defb	130

	defm	"su"
	defb	153

	defm	"mp"
	defb	174

	defm	"tim"
	defb	157

	defm	"o."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	"l#s"
	defb	168

	defm	""
	defb	153

	defm	""
	defb	218

	defm	""
	defb	163

	defm	"za"
	defb	182

	defm	""
	defb	176

	defm	""
	defb	190

	defm	""
	defb	157

	defm	""
	defb	174

	defm	""
	defb	222

	defm	"."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	"l#s"
	defb	168

	defm	""
	defb	188

	defm	""
	defb	159

	defm	"p"
	defb	186

	defm	"p"
	defb	140

	defm	"a"
	defb	166

	defm	""
	defb	231

	defm	""
	defb	144

	defm	"r"
	defb	199

	defm	""
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	"l#s"
	defb	168

	defm	""
	defb	166

	defm	""
	defb	231

	defm	""
	defb	144

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"P"
	defb	168

	defm	""
	defb	162

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	188

	defm	"u"
	defb	230

	defm	""
	defb	164

	defm	""
	defb	199

	defm	"U"
	defb	178

	defm	" volut"
	defb	134

	defm	" hum"
	defb	162

	defm	"y"
	defb	182

	defm	"lg"
	defb	205

	defm	""
	defb	152

	defm	"ch"
	defb	231

	defm	"p"
	defb	152

	defm	"surg"
	defb	163

	defm	""
	defb	166

	defm	""
	defb	147

	defm	""
	defb	228

	defm	"+"
	defb	226

	defm	"."
	defb	0

	defm	"S"
	defb	184

	defm	""
	defb	131

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	"e"
	defb	132

	defm	""
	defb	197

	defm	""
	defb	170

	defm	"nsp"
	defb	175

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"("
	defb	187

	defm	"gi"
	defb	163

	defm	"d"
	defb	162

	defm	"a"
	defb	180

	defm	""
	defb	165

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"je)"
	defb	0

	defm	"-L"
	defb	158

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	"m"
	defb	152

	defm	"ya"
	defb	136

	defm	"#n"
	defb	130

	defm	""
	defb	236

	defm	"d"
	defb	162

	defm	""
	defb	146

	defm	"bajo"
	defb	131

	defm	"summ"
	defb	162

	defm	"-t"
	defb	159

	defm	""
	defb	186

	defm	"cu"
	defb	168

	defm	""
	defb	213

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"-S&l"
	defb	162

	defm	"n"
	defb	223

	defm	""
	defb	165

	defm	"it"
	defb	162

	defm	"u"
	defb	167

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	159

	defm	"azul"
	defb	199

	defm	""
	defb	0

	defm	"La"
	defb	188

	defm	"up"
	defb	168

	defm	"fi"
	defb	203

	defm	"e"
	defb	149

	defm	""
	defb	177

	defm	"i"
	defb	210

	defm	","
	defb	188

	defm	"&l"
	defb	162

	defm	"s"
	defb	159

	defm	""
	defb	224

	defm	"tiva"
	defb	131

	defm	""
	defb	129

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"E U R O P A"
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	"d"
	defb	162

	defm	"v"
	defb	168

	defm	" "
	defb	178

	defm	""
	defb	213

	defm	","
	defb	136

	defm	"#"
	defb	192

	defm	"u"
	defb	233

	defm	""
	defb	194

	defm	"cu"
	defb	201

	defm	".^"
	defb	0

	defm	"Tambi$"
	defb	167

	defm	"ha"
	defb	233

	defm	""
	defb	0

	defm	"Esc"
	defb	219

	defm	"b"
	defb	159

	defm	"tu"
	defb	161

	defm	"&"
	defb	141

	defm	""
	defb	156

	defm	"a"
	defb	206

	defm	"%"
	defb	0

	defm	"/C&"
	defb	236

	defm	"? P"
	defb	175

	defm	" fav"
	defb	175

	defm	""
	defb	172

	defm	"r"
	defb	179

	defm	"ba"
	defb	131

	defm	""
	defb	216

	defm	""
	defb	200

	defm	""
	defb	152

	defm	""
	defb	196

	defm	""
	defb	171

	defm	"b"
	defb	170

	defm	"s.^"
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	"d"
	defb	162

	defm	"ir"
	defb	130

	defm	""
	defb	165

	defm	"a"
	defb	166

	defm	"i"
	defb	186

	defm	"c"
	defb	203

	defm	""
	defb	226

	defm	".^"
	defb	0

	defm	""
	defb	191

	defm	"Perd"
	defb	243

	defm	"n?^"
	defb	0

	defm	"L"
	defb	217

	defm	"v"
	defb	162

	defm	""
	defb	0

	defm	"(puesto)"
	defb	0

	defm	"n"
	defb	211

	defm	"g'"
	defb	167

	defm	"obje"
	defb	209

	defm	"."
	defb	0

	defm	"/Segu"
	defb	201

	defm	"? "
	defb	0

	defm	"/J"
	defb	179

	defm	"ga"
	defb	132

	defm	""
	defb	202

	defm	""
	defb	179

	defm	"vo? "
	defb	0

	defm	"Adi"
	defb	243

	defm	"s..."
	defb	0

	defm	"OK^"
	defb	0

	defm	"[...]"
	defb	0

	defm	"H"
	defb	152

	defm	""
	defb	186

	defm	""
	defb	190

	defm	"iz"
	defb	191

	defm	""
	defb	162

	defm	""
	defb	0

	defm	""
	defb	197

	defm	"ur"
	defb	220

	defm	""
	defb	0

	defm	"s"
	defb	0

	defm	".^ "
	defb	0

	defm	"La"
	defb	172

	defm	"u"
	defb	180

	defm	"ua"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	160

	defm	""
	defb	132

	defm	" "
	defb	0

	defm	""
	defb	172

	defm	"u"
	defb	180

	defm	"o"
	defb	0

	defm	"N"
	defb	162

	defm	"l"
	defb	217

	defm	"v"
	defb	162

	defm	""
	defb	238

	defm	""
	defb	165

	defm	""
	defb	209

	defm	""
	defb	149

	defm	"o.^"
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	""
	defb	185

	defm	""
	defb	232

	defm	"ya"
	defb	177

	defm	""
	defb	217

	defm	"vo"
	defb	149

	defm	""
	defb	162

	defm	""
	defb	238

	defm	""
	defb	165

	defm	""
	defb	209

	defm	".^"
	defb	0

	defm	"Ya"
	defb	197

	defm	""
	defb	163

	defm	"g"
	defb	162

	defm	""
	defb	0

	defm	"N"
	defb	162

	defm	""
	defb	207

	defm	"o"
	defb	149

	defm	""
	defb	162

	defm	"p"
	defb	175

	defm	""
	defb	182

	defm	""
	defb	206

	defm	"%.^"
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	"d"
	defb	162

	defm	"l"
	defb	217

	defm	"v"
	defb	174

	defm	""
	defb	192

	defm	"#s"
	defb	153

	defm	"s"
	defb	189

	defm	".^"
	defb	0

	defm	"N"
	defb	162

	defm	"t"
	defb	163

	defm	"go"
	defb	149

	defm	"o.^"
	defb	0

	defm	"P"
	defb	168

	defm	""
	defb	162

	defm	""
	defb	214

	defm	" ya"
	defb	177

	defm	""
	defb	217

	defm	"v"
	defb	162

	defm	""
	defb	238

	defm	""
	defb	165

	defm	""
	defb	209

	defm	""
	defb	0

	defm	"S"
	defb	0

	defm	"N"
	defb	0

	defm	"M"
	defb	225

	defm	"s..."
	defb	0

	defm	"> "
	defb	0

	defm	"E"
	defb	173

	defm	"t"
	defb	208

	defm	"mp"
	defb	162

	defm	"p"
	defb	189

	defm	"a...^"
	defb	0

	defm	"Aho"
	defb	170

	defm	""
	defb	197

	defm	""
	defb	163

	defm	"g"
	defb	162

	defm	""
	defb	0

	defm	"M"
	defb	159

	defm	"p"
	defb	184

	defm	"g"
	defb	162

	defm	""
	defb	0

	defm	"M"
	defb	159

	defm	""
	defb	206

	defm	"it"
	defb	162

	defm	""
	defb	0

	defm	"Dej"
	defb	162

	defm	""
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	"d"
	defb	162

	defm	"p"
	defb	184

	defm	""
	defb	168

	defm	"m"
	defb	159

	defm	""
	defb	0

	defm	"N"
	defb	162

	defm	"p"
	defb	179

	defm	"d"
	defb	162

	defm	""
	defb	206

	defm	"it"
	defb	174

	defm	"m"
	defb	159

	defm	""
	defb	0

	defm	"<T"
	defb	163

	defm	"g"
	defb	162

	defm	""
	defb	164

	defm	"m"
	defb	189

	defm	"i"
	defb	191

	defm	""
	defb	152

	defm	""
	defb	187

	defm	"s"
	defb	189

	defm	""
	defb	130

	defm	"l"
	defb	152

	defm	"m"
	defb	195

	defm	""
	defb	194

	defm	"!"
	defb	0

	defm	"D"
	defb	165

	defm	"g"
	defb	170

	defm	""
	defb	203

	defm	""
	defb	191

	defm	"am"
	defb	157

	defm	""
	defb	159

	defm	"p"
	defb	165

	defm	""
	defb	134

	defm	"m"
	defb	189

	defm	"ia"
	defb	185

	defm	"."
	defb	0

	defm	"Meto"
	defb	0

	defm	"Aho"
	defb	170

	defm	""
	defb	202

	defm	"o"
	defb	136

	defm	"#"
	defb	130

	defm	""
	defb	0

	defm	","
	defb	0

	defm	" "
	defb	233

	defm	""
	defb	0

	defm	"N"
	defb	162

	defm	"t"
	defb	163

	defm	"g"
	defb	162

	defm	""
	defb	0

	defm	"N"
	defb	162

	defm	"l"
	defb	217

	defm	"v"
	defb	162

	defm	""
	defb	238

	defm	""
	defb	165

	defm	"t"
	defb	162

	defm	""
	defb	0

	defm	"Es"
	defb	162

	defm	""
	defb	220

	defm	""
	defb	136

	defm	"#"
	defb	130

	defm	""
	defb	0

	defm	"n"
	defb	211

	defm	"g'"
	defb	167

	defm	"obje"
	defb	209

	defm	""
	defb	0

	defm	"F"
	defb	227

	defm	"h"
	defb	168

	defm	""
	defb	162

	defm	""
	defb	220

	defm	""
	defb	148

	defm	""
	defb	187

	defm	""
	defb	180

	defm	""
	defb	170

	defm	""
	defb	185

	defm	".^"
	defb	0

	defm	"F"
	defb	227

	defm	"h"
	defb	168

	defm	"o"
	defb	153

	defm	"rrup"
	defb	209

	defm	".^"
	defb	0

	defm	"Err"
	defb	175

	defm	" "
	defb	146

	defm	"E/S"
	defb	199

	defm	"F"
	defb	227

	defm	"h"
	defb	168

	defm	""
	defb	162

	defm	"n"
	defb	162

	defm	"g"
	defb	170

	defm	"ba"
	defb	185

	defm	".^"
	defb	0

	defm	"Di"
	defb	186

	defm	"ct"
	defb	175

	defm	"i"
	defb	162

	defm	"ll"
	defb	163

	defm	"o.^"
	defb	0

	defm	"D"
	defb	231

	defm	"c"
	defb	162

	defm	"ll"
	defb	163

	defm	"o."
	defb	0

	defm	"Nombr"
	defb	142

	defm	" f"
	defb	227

	defm	"h"
	defb	168

	defm	""
	defb	162

	defm	"n"
	defb	162

	defm	"v#li"
	defb	185

	defm	".^"
	defb	0

	defm	"Nombr"
	defb	142

	defm	""
	defb	173

	defm	"f"
	defb	227

	defm	"h"
	defb	168

	defm	"o: "
	defb	0

	defm	"/P"
	defb	168

	defm	"d"
	defb	226

	defm	"? P"
	defb	175

	defm	" fav"
	defb	175

	defm	""
	defb	172

	defm	"r"
	defb	179

	defm	"ba"
	defb	131

	defm	""
	defb	216

	defm	""
	defb	200

	defm	""
	defb	152

	defm	""
	defb	196

	defm	""
	defb	171

	defm	"b"
	defb	170

	defm	"s.^"
	defb	0

	defm	"A"
	defb	206

	defm	"% "
	defb	0

	defm	""
	defb	165

	defm	"t# "
	defb	0

	defm	"est"
	defb	225

	defm	"n"
	defb	0

	defm	"D"
	defb	145

	defm	""
	defb	162

	defm	"ha"
	defb	233

	defm	""
	defb	0

	defm	"En"
	defb	203

	defm	""
	defb	204

	defm	" ha"
	defb	233

	defm	""
	defb	0

	defm	"No"
	defb	149

	defm	""
	defb	182

	defm	"lg"
	defb	162

	defm	""
	defb	133

	defm	"p"
	defb	179

	defm	""
	defb	213

	defm	" "
	defb	206

	defm	"it"
	defb	174

	defm	""
	defb	235

	defm	".^"
	defb	0

	defm	"P"
	defb	184

	defm	"g"
	defb	162

	defm	""
	defb	0

	defm	"No"
	defb	149

	defm	""
	defb	182

	defm	"lg"
	defb	162

	defm	""
	defb	133

	defm	"p"
	defb	179

	defm	""
	defb	213

	defm	""
	defb	153

	defm	"g"
	defb	168

	defm	""
	defb	222

	defm	".^"
	defb	0

	defm	"No"
	defb	139

	defm	""
	defb	223

	defm	""
	defb	159

	defm	""
	defb	133

	defm	"p"
	defb	179

	defm	""
	defb	213

	defm	""
	defb	192

	defm	"ov"
	defb	168

	defm	""
	defb	222

	defm	".^"
	defb	0

	defm	"L"
	defb	217

	defm	"vo"
	defb	150

	defm	""
	defb	161

	defm	"m"
	defb	195

	defm	""
	defb	158

	defm	"v"
	defb	224

	defm	"%"
	defb	189

	defm	".^"
	defb	0

	defm	"norte"
	defb	0

	defm	"sur"
	defb	0

	defm	"este"
	defb	0

	defm	"oeste"
	defb	0

	defm	"noreste"
	defb	0

	defm	"w"
	defb	0

	defm	"noroeste"
	defb	0

	defm	"ne"
	defb	0

	defm	"sureste"
	defb	0

	defm	"se"
	defb	0

	defm	"suroeste"
	defb	0

	defm	"suroe"
	defb	0

	defm	"arriba"
	defb	0

	defm	"up"
	defb	0

	defm	"abajo"
	defb	0

	defm	"no"
	defb	0

	defm	"entrar"
	defb	0

	defm	"entra"
	defb	0

	defm	"salir"
	defb	0

	defm	"sal"
	defb	0

	defm	"ascie"
	defb	0

	defm	"subet"
	defb	0

	defm	"sube"
	defb	0

	defm	"bajar"
	defb	0

	defm	"baja"
	defb	0

	defm	"desce"
	defb	0

	defm	"desci"
	defb	0

	defm	"bajat"
	defb	0

	defm	"enter"
	defb	0

	defm	"intro"
	defb	0

	defm	"adent"
	defb	0

	defm	"dentr"
	defb	0

	defm	"inter"
	defb	0

	defm	"exit"
	defb	0

	defm	"fuera"
	defb	0

	defm	"afuer"
	defb	0

	defm	"inven"
	defb	0

	defm	"inv"
	defb	0

	defm	"punto"
	defb	0

	defm	"puntu"
	defb	0

	defm	"conta"
	defb	0

	defm	"turno"
	defb	0

	defm	"todo"
	defb	0

	defm	"puerta"
	defb	0

	defm	"boton"
	defb	0

	defm	"escal"
	defb	0

	defm	"pared"
	defb	0

	defm	"suelo"
	defb	0

	defm	"techo"
	defb	0

	defm	"luz"
	defb	0

	defm	"haz"
	defb	0

	defm	"parab"
	defb	0

	defm	"caja"
	defb	0

	defm	"paque"
	defb	0

	defm	"conte"
	defb	0

	defm	"cielo"
	defb	0

	defm	"nave"
	defb	0

	defm	"nodo"
	defb	0

	defm	"puent"
	defb	0

	defm	"torme"
	defb	0

	defm	"Europ"
	defb	0

	defm	"Luna"
	defb	0

	defm	"Lunas"
	defb	0

	defm	"Satel"
	defb	0

	defm	"Jupit"
	defb	0

	defm	"Jovia"
	defb	0

	defm	"Cara"
	defb	0

	defm	"Lado"
	defb	0

	defm	"almac"
	defb	0

	defm	"mole"
	defb	0

	defm	"edifi"
	defb	0

	defm	"orden"
	defb	0

	defm	"dot"
	defb	0

	defm	"tod"
	defb	0

	defm	"navi"
	defb	0

	defm	"gps"
	defb	0

	defm	"galileo"
	defb	0

	defm	"tom"
	defb	0

	defm	"tomtom"
	defb	0

	defm	"conso"
	defb	0

	defm	"mando"
	defb	0

	defm	"siste"
	defb	0

	defm	"esclu"
	defb	0

	defm	"airlo"
	defb	0

	defm	"compu"
	defb	0

	defm	"traje"
	defb	0

	defm	"bodega"
	defb	0

	defm	"boveda"
	defb	0

	defm	"estant"
	defb	0

	defm	"camara"
	defb	0

	defm	"canon"
	defb	0

	defm	"32768"
	defb	0

	defm	"tecla"
	defb	0

	defm	"exter"
	defb	0

	defm	"etiqu"
	defb	0

	defm	"indic"
	defb	0

	defm	"panta"
	defb	0

	defm	"instr"
	defb	0

	defm	"contr"
	defb	0

	defm	"panel"
	defb	0

	defm	"coger"
	defb	0

	defm	"coge"
	defb	0

	defm	"tomar"
	defb	0

	defm	"toma"
	defb	0

	defm	"take"
	defb	0

	defm	"dejar"
	defb	0

	defm	"deja"
	defb	0

	defm	"solta"
	defb	0

	defm	"suelt"
	defb	0

	defm	"drop"
	defb	0

	defm	"quita"
	defb	0

	defm	"sacat"
	defb	0

	defm	"sacar"
	defb	0

	defm	"desvi"
	defb	0

	defm	"desve"
	defb	0

	defm	"look"
	defb	0

	defm	"mirar"
	defb	0

	defm	"mira"
	defb	0

	defm	"quit"
	defb	0

	defm	"fin"
	defb	0

	defm	"save"
	defb	0

	defm	"graba"
	defb	0

	defm	"salva"
	defb	0

	defm	"guard"
	defb	0

	defm	"load"
	defb	0

	defm	"carga"
	defb	0

	defm	"ramsa"
	defb	0

	defm	"ramlo"
	defb	0

	defm	"x"
	defb	0

	defm	"exami"
	defb	0

	defm	"ex"
	defb	0

	defm	"inspe"
	defb	0

	defm	"obser"
	defb	0

	defm	"decir"
	defb	0

	defm	"di"
	defb	0

	defm	"habla"
	defb	0

	defm	"respo"
	defb	0

	defm	"manda"
	defb	0

	defm	"lanza"
	defb	0

	defm	"tira"
	defb	0

	defm	"tirar"
	defb	0

	defm	"arroj"
	defb	0

	defm	"empuj"
	defb	0

	defm	"apret"
	defb	0

	defm	"pulsa"
	defb	0

	defm	"girar"
	defb	0

	defm	"gira"
	defb	0

	defm	"rota"
	defb	0

	defm	"rotar"
	defb	0

	defm	"escuc"
	defb	0

	defm	"oir"
	defb	0

	defm	"oye"
	defb	0

	defm	"tocar"
	defb	0

	defm	"toca"
	defb	0

	defm	"acari"
	defb	0

	defm	"palpa"
	defb	0

	defm	"oler"
	defb	0

	defm	"huele"
	defb	0

	defm	"olfat"
	defb	0

	defm	"husme"
	defb	0

	defm	"esper"
	defb	0

	defm	"canta"
	defb	0

	defm	"salta"
	defb	0

	defm	"brinc"
	defb	0

	defm	"ataca"
	defb	0

	defm	"agred"
	defb	0

	defm	"matar"
	defb	0

	defm	"mata"
	defb	0

	defm	"asesi"
	defb	0

	defm	"estra"
	defb	0

	defm	"patea"
	defb	0

	defm	"pisot"
	defb	0

	defm	"tortu"
	defb	0

	defm	"noque"
	defb	0

	defm	"lucha"
	defb	0

	defm	"abri"
	defb	0

	defm	"abre"
	defb	0

	defm	"abrir"
	defb	0

	defm	"cerrar"
	defb	0

	defm	"cierra"
	defb	0

	defm	"encen"
	defb	0

	defm	"encie"
	defb	0

	defm	"incen"
	defb	0

	defm	"prend"
	defb	0

	defm	"apaga"
	defb	0

	defm	"extin"
	defb	0

	defm	"sofoc"
	defb	0

	defm	"rompe"
	defb	0

	defm	"parti"
	defb	0

	defm	"parte"
	defb	0

	defm	"quebr"
	defb	0

	defm	"quieb"
	defb	0

	defm	"destr"
	defb	0

	defm	"poner"
	defb	0

	defm	"pon"
	defb	0

	defm	"ponte"
	defb	0

	defm	"ponse"
	defb	0

	defm	"pone"
	defb	0

	defm	"viste"
	defb	0

	defm	"vesti"
	defb	0

	defm	"golpe"
	defb	0

	defm	"dar"
	defb	0

	defm	"dase"
	defb	0

	defm	"darse"
	defb	0

	defm	"darte"
	defb	0

	defm	"dale"
	defb	0

	defm	"darle"
	defb	0

	defm	"ofrec"
	defb	0

	defm	"meter"
	defb	0

	defm	"mete"
	defb	0

	defm	"inser"
	defb	0

	defm	"echa"
	defb	0

	defm	"echar"
	defb	0

	defm	"vete"
	defb	0

	defm	"irte"
	defb	0

	defm	"irse"
	defb	0

	defm	"camin"
	defb	0

	defm	"andar"
	defb	0

	defm	"corre"
	defb	0

	defm	"huir"
	defb	0

	defm	"huye"
	defb	0

	defm	"dirig"
	defb	0

	defm	"lee"
	defb	0

	defm	"leer"
	defb	0

	defm	"leers"
	defb	0

	defm	"leert"
	defb	0

	defm	"leete"
	defb	0

	defm	"mover"
	defb	0

	defm	"mueve"
	defb	0

	defm	"despl"
	defb	0

	defm	"tecle"
	defb	0

	defm	"escri"
	defb	0

	defm	"score"
	defb	0

	defm	"usar"
	defb	0

	defm	"activ"
	defb	0

	defm	"peque"
	defb	0

	defm	"grand"
	defb	0

	defm	"viejo"
	defb	0

	defm	"vieja"
	defb	0

	defm	"nuevo"
	defb	0

	defm	"nueva"
	defb	0

	defm	"duro"
	defb	0

	defm	"dura"
	defb	0

	defm	"bland"
	defb	0

	defm	"corto"
	defb	0

	defm	"corta"
	defb	0

	defm	"largo"
	defb	0

	defm	"larga"
	defb	0

	defm	"azul"
	defb	0

	defm	"verde"
	defb	0

	defm	"negro"
	defb	0

	defm	"rojo"
	defb	0

	defm	"amari"
	defb	0

	defm	"termi"
	defb	0

	defm	"frio"
	defb	0

	defm	"calie"
	defb	0

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	159

	defm	"azul"
	defb	0

	defm	"t"
	defb	170

	defm	"j"
	defb	159

	defm	"pr"
	defb	165

	defm	"u"
	defb	219

	defm	"za"
	defb	185

	defm	""
	defb	0

	defm	""
	defb	187

	defm	"m"
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	134

	defm	""
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	0

	defm	""
	defb	238

	defm	""
	defb	168

	defm	"t"
	defb	134

	defm	""
	defb	192

	defm	"et"
	defb	190

	defm	""
	defb	0

	defm	"bot&"
	defb	167

	defm	""
	defb	201

	defm	"jo"
	defb	0

	defm	"bot&"
	defb	167

	defm	"v"
	defb	168

	defm	""
	defb	164

	defm	""
	defb	0

	defm	""
	defb	228

	defm	"+&"
	defb	167

	defm	""
	defb	146

	defm	"vigi"
	defb	171

	defm	"n"
	defb	203

	defm	"a"
	defb	0

	defm	"teclado"
	defb	0

	defm	"hola"
	defb	0

	defm	"adios"
	defb	0

	defm	"traba"
	defb	0

	defm	"yo"
	defb	0

	defm	"pilot"
	defb	0

	defm	"condu"
	defb	0

	defm	"trans"
	defb	0

	defm	"europ"
	defb	0

	defm	"luna"
	defb	0

	defm	"jovia"
	defb	0

	defm	"jupit"
	defb	0

	defm	"cara"
	defb	0

	defm	"donde"
	defb	0

	defm	"misio"
	defb	0

	defm	"nombr"
	defb	0

	defm	"model"
	defb	0

	defm	"mega"
	defb	0

	defm	"megac"
	defb	0

	defm	"corpo"
	defb	0

	defm	"ciber"
	defb	0

	defm	"cyber"
	defb	0

	defm	"avent"
	defb	0

	defm	"conve"
	defb	0

	defm	"if"
	defb	0

	defm	"ficci"
	defb	0

	defm	"grafi"
	defb	0

	defm	"transi"
	defb	0

	defm	"isla"
	defb	0

	defm	"uto"
	defb	0

	defm	"csg"
	defb	0

	defm	"kmbr"
	defb	0

	defm	"kmbrkat"
	defb	0

	defm	"kno"
	defb	0

	defm	"dla"
	defb	0

	defm	"dela"
	defb	0

	defm	"franc"
	defb	0

	defm	"ingle"
	defb	0

	defm	"itali"
	defb	0

	defm	"alema"
	defb	0

	defm	"caste"
	defb	0

	defm	"tecno"
	defb	0

	defm	"comic"
	defb	0

	defm	"daniel"
	defb	0

	defm	"danixi"
	defb	0

	defm	"obra"
	defb	0

	defm	"favor"
	defb	0

	defm	"jugar"
	defb	0

	defm	"canci"
	defb	0

	defm	"tarar"
	defb	0

	defm	"guille"
	defb	0

	defm	"viaja"
	defb	0

	defm	"codig"
	defb	0

	defm	"centr"
	defb	0

	defm	"zeur"
	defb	0

	defm	"zhl"
	defb	0

	defm	"tierr"
	defb	0

	defm	"tempe"
	defb	0

	defm	"memoria"
	defb	0

	defm	"relax"
	defb	0

	defm	"jorna"
	defb	0

	defm	"vacac"
	defb	0

	defm	"marte"
	defb	0

	defm	"venus"
	defb	0

	defm	"satur"
	defb	0

	defm	"pluto"
	defb	0

	defm	"neptu"
	defb	0

	defm	"mercu"
	defb	0

	defm	"minas"
	defb	0

	defm	"tened"
	defb	0

	defm	"diabl"
	defb	0

	defm	"hierr"
	defb	0

	defm	"nique"
	defb	0

	defm	"sindi"
	defb	0

	defm	"human"
	defb	0

	defm	"opera"
	defb	0

	defm	"ocio"
	defb	0

	defm	"sumin"
	defb	0

	defm	"paquet"
	defb	0

	defm	"recog"
	defb	0

	defm	"estre"
	defb	0

	defm	"sol"
	defb	0

	defm	"solar"
	defb	0

	defm	"sistm"
	defb	0

	defm	"ayuda"
	defb	0

	defm	"mensa"
	defb	0

	defm	"coman"
	defb	0

	defm	"encar"
	defb	0

	defm	"entre"
	defb	0

	defm	"clave"
	defb	0

	defm	"radia"
	defb	0

	defm	"comun"
	defb	0

	defm	"super"
	defb	0

	defm	"prote"
	defb	0

	defm	"sigla"
	defb	0

	defm	"mierd"
	defb	0

	defm	"culo"
	defb	0

	defm	"joder"
	defb	0

	defm	"puta"
	defb	0

	defm	"puton"
	defb	0

	defm	"calla"
	defb	0

	defm	"bodeg"
	defb	0

	defm	"enfri"
	defb	0

	defm	"frigo"
	defb	0

	defm	"conge"
	defb	0

	defm	"-Ho"
	defb	171

	defm	","
	defb	188

	defm	"oy"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	146

	defm	"u"
	defb	178

	defm	" voz"
	defb	192

	defm	"et#l"
	defb	227

	defm	"a."
	defb	0

	defm	"-H"
	defb	189

	defm	""
	defb	198

	defm	""
	defb	172

	defm	""
	defb	201

	defm	""
	defb	180

	defm	"o."
	defb	0

	defm	"-Soy"
	defb	129

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	"m"
	defb	134

	defm	" "
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Er"
	defb	156

	defm	"Tod C"
	defb	184

	defm	"n"
	defb	175

	defm	","
	defb	129

	defm	"pi"
	defb	215

	defm	"t"
	defb	162

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-La"
	defb	197

	defm	""
	defb	175

	defm	"m"
	defb	157

	defm	"a"
	defb	149

	defm	""
	defb	192

	defm	"o"
	defb	164

	defm	""
	defb	170

	defm	""
	defb	213

	defm	""
	defb	199

	defm	"N"
	defb	162

	defm	""
	defb	164

	defm	"b"
	defb	168

	defm	"%a"
	defb	188

	defm	""
	defb	168

	defm	""
	defb	212

	defm	""
	defb	167

	defm	"p"
	defb	201

	defm	"b"
	defb	217

	defm	""
	defb	204

	defm	""
	defb	139

	defm	"a"
	defb	182

	defm	"c"
	defb	230

	defm	""
	defb	164

	defm	"r"
	defb	182

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$"
	defb	167

	defm	"us"
	defb	195

	defm	""
	defb	185

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	142

	defm	""
	defb	172

	defm	""
	defb	201

	defm	""
	defb	169

	defm	"c"
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-E"
	defb	193

	defm	"am"
	defb	194

	defm	""
	defb	148

	defm	""
	defb	129

	defm	""
	defb	210

	defm	"t$lit"
	defb	159

	defm	"Jovi"
	defb	195

	defm	"o"
	defb	199

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"-Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	149

	defm	""
	defb	212

	defm	""
	defb	167

	defm	""
	defb	210

	defm	"t$lit"
	defb	142

	defm	" Jupit"
	defb	168

	defm	""
	defb	199

	defm	"En"
	defb	128

	defm	"c"
	defb	140

	defm	"ilu"
	defb	218

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	172

	defm	""
	defb	175

	defm	" J'pit"
	defb	168

	defm	""
	defb	129

	defm	""
	defb	165

	defm	"p"
	defb	223

	defm	"t#cu"
	defb	215

	defm	""
	defb	149

	defm	""
	defb	188

	defm	"ob"
	defb	168

	defm	"b"
	defb	241

	defm	""
	defb	199

	defm	"P"
	defb	175

	defm	" "
	defb	164

	defm	"sg"
	defb	170

	defm	""
	defb	203

	defm	"a"
	defb	202

	defm	"u"
	defb	165

	defm	""
	defb	200

	defm	"o"
	defb	148

	defm	"c"
	defb	174

	defm	"go"
	defb	149

	defm	""
	defb	148

	defm	""
	defb	128

	defm	"c"
	defb	140

	defm	"ocul"
	defb	198

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	197

	defm	"i"
	defb	163

	defm	""
	defb	159

	defm	"u"
	defb	178

	defm	""
	defb	176

	defm	""
	defb	140

	defm	"s"
	defb	208

	defm	"mpr"
	defb	159

	defm	""
	defb	175

	defm	"i"
	defb	157

	defm	""
	defb	191

	defm	"a ha"
	defb	203

	defm	"a J'pit"
	defb	168

	defm	"."
	defb	0

	defm	"-E"
	defb	193

	defm	"#"
	defb	130

	defm	"u"
	defb	167

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n,"
	defb	148

	defm	""
	defb	129

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	199

	defm	"T"
	defb	163

	defm	"dr#"
	defb	161

	defm	""
	defb	133

	defm	"s"
	defb	190

	defm	"ir"
	defb	131

	defm	""
	defb	136

	defm	"a"
	defb	197

	defm	""
	defb	175

	defm	"m"
	defb	157

	defm	"a"
	defb	199

	defm	""
	defb	0

	defm	"-Ti"
	defb	163

	defm	""
	defb	156

	defm	""
	defb	133

	defm	""
	defb	186

	defm	""
	defb	187

	defm	"g"
	defb	168

	defm	""
	defb	212

	defm	""
	defb	167

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	130

	defm	"Eu"
	defb	201

	defm	""
	defb	196

	defm	" "
	defb	233

	defm	""
	defb	145

	defm	"eg"
	defb	174

	defm	""
	defb	215

	defm	""
	defb	130

	defm	"M"
	defb	174

	defm	"t"
	defb	159

	defm	""
	defb	195

	defm	""
	defb	169

	defm	""
	defb	132

	defm	" 24h -r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	"."
	defb	0

	defm	"-Mi"
	defb	202

	defm	"omb"
	defb	186

	defm	""
	defb	149

	defm	" DOT"
	defb	199

	defm	"Si"
	defb	177

	defm	""
	defb	162

	defm	"p"
	defb	186

	defm	"fi"
	defb	168

	defm	""
	defb	165

	defm	","
	defb	172

	defm	""
	defb	179

	defm	"d"
	defb	156

	defm	"us"
	defb	174

	defm	""
	defb	136

	defm	""
	defb	159

	defm	""
	defb	220

	defm	"mbr"
	defb	159

	defm	"a"
	defb	173

	defm	"h"
	defb	237

	defm	""
	defb	171

	defm	"r"
	defb	131

	defm	""
	defb	218

	defm	"go"
	defb	199

	defm	" "
	defb	0

	defm	"-Soy"
	defb	212

	defm	""
	defb	167

	defm	""
	defb	236

	defm	""
	defb	164

	defm	"l"
	defb	162

	defm	"Cyb"
	defb	168

	defm	"d"
	defb	211

	defm	""
	defb	159

	defm	"1997"
	defb	199

	defm	" Mi"
	defb	172

	defm	""
	defb	201

	defm	"g"
	defb	170

	defm	"m"
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	175

	defm	"igi"
	defb	178

	defm	""
	defb	173

	defm	"f"
	defb	179

	defm	""
	defb	129

	defm	"Dr"
	defb	199

	defm	"Guill"
	defb	168

	defm	"m"
	defb	162

	defm	"Ha"
	defb	167

	defm	""
	defb	164

	defm	""
	defb	128

	defm	"MegaC"
	defb	175

	defm	"p(tm)"
	defb	199

	defm	"Me"
	defb	148

	defm	""
	defb	222

	defm	"+&"
	defb	182

	defm	""
	defb	176

	defm	"a"
	defb	180

	defm	""
	defb	174

	defm	""
	defb	212

	defm	""
	defb	178

	defm	""
	defb	176

	defm	""
	defb	195

	defm	""
	defb	203

	defm	""
	defb	226

	defm	""
	defb	232

	defm	"/"
	defb	206

	defm	"i"
	defb	168

	defm	""
	defb	156

	defm	"o%r"
	defb	171

	defm	"?"
	defb	0

	defm	"-L"
	defb	155

	defm	"mpr"
	defb	165

	defm	"a"
	defb	221

	defm	""
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	210

	defm	"bl"
	defb	142

	defm	" "
	defb	133

	defm	"t' "
	defb	233

	defm	"yo"
	defb	136

	defm	""
	defb	240

	defm	""
	defb	194

	defm	""
	defb	131

	defm	"v"
	defb	168

	defm	"s"
	defb	195

	defm	""
	defb	185

	defm	""
	defb	130

	defm	"Eu"
	defb	201

	defm	""
	defb	196

	defm	"."
	defb	0

	defm	"-Me"
	defb	148

	defm	""
	defb	228

	defm	""
	defb	180

	defm	""
	defb	195

	defm	""
	defb	150

	defm	""
	defb	161

	defm	"av"
	defb	157

	defm	"u"
	defb	170

	defm	"s"
	defb	131

	defm	"v"
	defb	168

	defm	""
	defb	210

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	"l"
	defb	165

	defm	"."
	defb	0

	defm	"-D"
	defb	165

	defm	"c"
	defb	184

	defm	"oz"
	defb	187

	defm	""
	defb	149

	defm	""
	defb	159

	defm	"t$rm"
	defb	211

	defm	"o"
	defb	232

	defm	"/t"
	defb	159

	defm	""
	defb	186

	defm	"fi"
	defb	168

	defm	""
	defb	156

	defm	"a"
	defb	150

	defm	"s"
	defb	131

	defm	"v"
	defb	168

	defm	""
	defb	210

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	"l"
	defb	165

	defm	"?"
	defb	0

	defm	"-No"
	defb	136

	defm	"#"
	defb	167

	defm	"m"
	defb	190

	defm	","
	defb	172

	defm	""
	defb	168

	defm	""
	defb	162

	defm	"n"
	defb	162

	defm	"c"
	defb	186

	defm	""
	defb	162

	defm	""
	defb	133

	defm	"p"
	defb	179

	defm	"d"
	defb	152

	defm	"jug"
	defb	174

	defm	""
	defb	182

	defm	""
	defb	212

	defm	""
	defb	178

	defm	""
	defb	192

	defm	"i"
	defb	145

	defm	""
	defb	189

	defm	""
	defb	131

	defm	"duc"
	defb	165

	defm	"."
	defb	0

	defm	"-No"
	defb	136

	defm	"#"
	defb	192

	defm	""
	defb	190

	defm	","
	defb	172

	defm	""
	defb	168

	defm	"o"
	defb	149

	defm	""
	defb	212

	defm	""
	defb	167

	defm	""
	defb	234

	defm	""
	defb	187

	defm	""
	defb	153

	defm	"r"
	defb	198

	defm	""
	defb	139

	defm	"a"
	defb	192

	defm	"i gu"
	defb	193

	defm	"o"
	defb	199

	defm	"P"
	defb	186

	defm	"fi"
	defb	168

	defm	""
	defb	162

	defm	"'"
	defb	151

	defm	""
	defb	220

	defm	"ch"
	defb	159

	defm	"m#s"
	defb	150

	defm	"rga'"
	defb	232

	defm	""
	defb	133

	defm	"du"
	defb	170

	defm	" "
	defb	205

	defm	""
	defb	152

	defm	"12h "
	defb	146

	defm	"j"
	defb	179

	defm	"g"
	defb	162

	defm	""
	defb	146

	defm	"t"
	defb	208

	defm	"mp"
	defb	162

	defm	""
	defb	186

	defm	""
	defb	190

	defm	"."
	defb	0

	defm	"-P"
	defb	168

	defm	""
	defb	162

	defm	"bu"
	defb	163

	defm	"o"
	defb	232

	defm	"<"
	defb	214

	defm	""
	defb	149

	defm	"a"
	defb	202

	defm	""
	defb	205

	defm	""
	defb	228

	defm	""
	defb	128

	defm	"t"
	defb	168

	defm	"m"
	defb	211

	defm	""
	defb	174

	defm	""
	defb	184

	defm	"!"
	defb	199

	defm	"R"
	defb	223

	defm	"u"
	defb	168

	defm	"d"
	defb	162

	defm	""
	defb	133

	defm	""
	defb	205

	defm	""
	defb	162

	defm	""
	defb	138

	defm	""
	defb	158

	defm	"aut"
	defb	175

	defm	""
	defb	165

	defm	","
	defb	212

	defm	""
	defb	167

	defm	""
	defb	198

	defm	""
	defb	173

	defm	"UTO"
	defb	177

	defm	""
	defb	159

	defm	"hiz"
	defb	162

	defm	"u"
	defb	178

	defm	" vi"
	defb	214

	defm	""
	defb	198

	defm	""
	defb	182

	defm	"l"
	defb	172

	defm	""
	defb	201

	defm	"g"
	defb	170

	defm	"m"
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	133

	defm	"t"
	defb	168

	defm	"m"
	defb	211

	defm	"&"
	defb	197

	defm	"a"
	defb	167

	defm	""
	defb	204

	defm	""
	defb	173

	defm	""
	defb	133

	defm	""
	defb	164

	defm	""
	defb	193

	defm	"ruy"
	defb	168

	defm	"o"
	defb	167

	defm	""
	defb	209

	defm	"d"
	defb	162

	defm	"u"
	defb	167

	defm	"b"
	defb	215

	defm	""
	defb	133

	defm	""
	defb	146

	defm	"ofi"
	defb	203

	defm	""
	defb	178

	defm	"s"
	defb	199

	defm	"P"
	defb	168

	defm	"o"
	defb	149

	defm	"a"
	defb	149

	defm	""
	defb	216

	defm	"t"
	defb	170

	defm	" hi"
	defb	193

	defm	""
	defb	175

	defm	"ia."
	defb	0

	defm	"-Re"
	defb	190

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	"n"
	defb	162

	defm	"t"
	defb	163

	defm	"g"
	defb	162

	defm	"m#"
	defb	161

	defm	""
	defb	213

	defm	"t"
	defb	158

	defm	"sob"
	defb	186

	defm	""
	defb	136

	defm	"a"
	defb	172

	defm	""
	defb	168

	defm	"so"
	defb	178

	defm	""
	defb	199

	defm	"S"
	defb	211

	defm	""
	defb	166

	defm	"ud"
	defb	155

	defm	""
	defb	170

	defm	""
	defb	212

	defm	""
	defb	178

	defm	""
	defb	192

	defm	""
	defb	157

	defm	""
	defb	159

	defm	""
	defb	204

	defm	""
	defb	165

	defm	"t"
	defb	170

	defm	""
	defb	139

	defm	"a"
	defb	149

	defm	""
	defb	228

	defm	"p"
	defb	174

	defm	""
	defb	182

	defm	""
	defb	192

	defm	"i"
	defb	161

	defm	""
	defb	186

	defm	"gi"
	defb	193

	defm	"r"
	defb	194

	defm	"."
	defb	0

	defm	"-U"
	defb	167

	defm	""
	defb	218

	defm	""
	defb	193

	defm	""
	defb	168

	defm	""
	defb	241

	defm	","
	defb	188

	defm	""
	defb	159

	defm	"rum"
	defb	175

	defm	"ea "
	defb	133

	defm	""
	defb	168

	defm	"a"
	defb	212

	defm	""
	defb	167

	defm	""
	defb	174

	defm	""
	defb	163

	defm	""
	defb	133

	defm	""
	defb	201

	defm	"j"
	defb	162

	defm	"mut"
	defb	195

	defm	""
	defb	169

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-U"
	defb	167

	defm	"c"
	defb	181

	defm	"eb"
	defb	170

	defm	"d"
	defb	162

	defm	"aut"
	defb	175

	defm	" "
	defb	146

	defm	"c&"
	defb	218

	defm	"c "
	defb	133

	defm	"vivi&"
	defb	192

	defm	"#"
	defb	132

	defm	""
	defb	166

	defm	""
	defb	194

	defm	""
	defb	203

	defm	""
	defb	157

	defm	""
	defb	158

	defm	"a+"
	defb	194

	defm	""
	defb	199

	defm	"T"
	defb	163

	defm	"%a"
	defb	212

	defm	""
	defb	167

	defm	"c"
	defb	190

	defm	""
	defb	215

	defm	""
	defb	148

	defm	""
	defb	129

	defm	""
	defb	164

	defm	"d"
	defb	162

	defm	""
	defb	198

	defm	""
	defb	167

	defm	""
	defb	164

	defm	"s"
	defb	187

	defm	"mu"
	defb	178

	defm	""
	defb	173

	defm	""
	defb	133

	defm	"fi"
	defb	178

	defm	"lm"
	defb	157

	defm	""
	defb	159

	defm	"mu"
	defb	219

	defm	"&"
	defb	182

	defm	"p"
	defb	171

	defm	""
	defb	193

	defm	""
	defb	191

	defm	""
	defb	162

	defm	"p"
	defb	175

	defm	" $l"
	defb	199

	defm	"E"
	defb	161

	defm	"u"
	defb	167

	defm	"cl#"
	defb	214

	defm	""
	defb	187

	defm	""
	defb	232

	defm	""
	defb	164

	defm	"b"
	defb	168

	defm	"%"
	defb	152

	defm	""
	defb	217

	defm	""
	defb	168

	defm	""
	defb	197

	defm	"o"
	defb	213

	defm	""
	defb	188

	defm	"u"
	defb	216

	defm	"b"
	defb	170

	defm	" v"
	defb	174

	defm	"i"
	defb	152

	defm	""
	defb	207

	defm	"c"
	defb	165

	defm	"."
	defb	0

	defm	"-Un"
	defb	149

	defm	"c"
	defb	219

	defm	"b"
	defb	134

	defm	""
	defb	173

	defm	""
	defb	214

	defm	"gl"
	defb	162

	defm	"XV"
	defb	232

	defm	"g"
	defb	170

	defm	""
	defb	203

	defm	""
	defb	152

	defm	"a $"
	defb	173

	defm	"t"
	defb	163

	defm	""
	defb	240

	defm	""
	defb	158

	defm	"d"
	defb	231

	defm	"p"
	defb	184

	defm	"ibl"
	defb	156

	defm	""
	defb	204

	defm	""
	defb	170

	defm	"vill"
	defb	152

	defm	""
	defb	187

	defm	"m"
	defb	162

	defm	"'Cu"
	defb	195

	defm	""
	defb	185

	defm	""
	defb	153

	defm	"m%"
	defb	135

	defm	"s"
	defb	162

	defm	""
	defb	239

	defm	"g"
	defb	201

	defm	"'"
	defb	130

	defm	"f"
	defb	170

	defm	"nc$s."
	defb	0

	defm	"-L"
	defb	163

	defm	"gu"
	defb	152

	defm	"mu"
	defb	168

	defm	"t"
	defb	189

	defm	""
	defb	232

	defm	"hoy"
	defb	130

	defm	"d%a"
	defb	197

	defm	"o"
	defb	185

	defm	""
	defb	129

	defm	""
	defb	205

	defm	"iv"
	defb	168

	defm	"s"
	defb	162

	defm	"h"
	defb	237

	defm	""
	defb	151

	defm	""
	defb	169

	defm	"c"
	defb	220

	defm	"l"
	defb	171

	defm	""
	defb	220

	defm	"."
	defb	0

	defm	"-La"
	defb	177

	defm	""
	defb	163

	defm	"gua f"
	defb	170

	defm	"nc"
	defb	134

	defm	""
	defb	202

	defm	"u"
	defb	165

	defm	""
	defb	200

	defm	""
	defb	158

	defm	"d%"
	defb	189

	defm	"."
	defb	0

	defm	"-A"
	defb	242

	defm	""
	defb	159

	defm	""
	defb	222

	defm	"cu"
	defb	163

	defm	""
	defb	203

	defm	"a"
	defb	173

	defm	"muy"
	defb	172

	defm	"o"
	defb	238

	defm	""
	defb	171

	defm	"r"
	defb	182

	defm	" fi"
	defb	178

	defm	""
	defb	217

	defm	""
	defb	132

	defm	""
	defb	173

	defm	""
	defb	214

	defm	"gl"
	defb	162

	defm	"XX"
	defb	199

	defm	""
	defb	0

	defm	"-E"
	defb	173

	defm	"r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	210

	defm	"bl"
	defb	142

	defm	""
	defb	128

	defm	""
	defb	235

	defm	"ga"
	defb	153

	defm	"r"
	defb	234

	defm	""
	defb	170

	defm	"ti"
	defb	184

	defm	"."
	defb	0

	defm	"-H"
	defb	237

	defm	""
	defb	217

	defm	""
	defb	236

	defm	""
	defb	132

	defm	""
	defb	154

	defm	"l"
	defb	162

	defm	"cu"
	defb	195

	defm	"d"
	defb	162

	defm	"t"
	defb	168

	defm	"m"
	defb	211

	defm	""
	defb	156

	defm	"tu"
	defb	192

	defm	"i"
	defb	214

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-E"
	defb	161

	defm	"dif%"
	defb	203

	defm	"l"
	defb	154

	defm	"egir,"
	defb	150

	defm	""
	defb	161

	defm	"av"
	defb	157

	defm	"u"
	defb	170

	defm	""
	defb	132

	defm	" "
	defb	169

	defm	"xt"
	defb	162

	defm	"s"
	defb	159

	defm	"volvi"
	defb	168

	defm	"o"
	defb	167

	defm	""
	defb	186

	defm	""
	defb	190

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	""
	defb	234

	defm	""
	defb	238

	defm	""
	defb	171

	defm	"r"
	defb	156

	defm	"a "
	defb	170

	defm	"%z "
	defb	164

	defm	""
	defb	128

	defm	"p"
	defb	201

	defm	"lif"
	defb	168

	defm	"a"
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	146

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	132

	defm	" "
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	130

	defm	"au"
	defb	209

	defm	"m&vil"
	defb	165

	defm	""
	defb	232

	defm	"b"
	defb	174

	defm	"c"
	defb	158

	defm	""
	defb	233

	defm	""
	defb	178

	defm	"v"
	defb	165

	defm	""
	defb	149

	defm	""
	defb	196

	defm	""
	defb	203

	defm	""
	defb	190

	defm	""
	defb	165

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-T"
	defb	159

	defm	"busc"
	defb	174

	defm	"$"
	defb	212

	defm	""
	defb	178

	defm	" "
	defb	186

	defm	""
	defb	190

	defm	"m"
	defb	157

	defm	""
	defb	159

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	""
	defb	165

	defm	"a"
	defb	180

	defm	""
	defb	159

	defm	"u"
	defb	178

	defm	" "
	defb	207

	defm	"z"
	defb	197

	defm	""
	defb	168

	defm	"m"
	defb	211

	defm	""
	defb	165

	defm	""
	defb	128

	defm	""
	defb	218

	defm	""
	defb	214

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-Da"
	defb	231

	defm	"y.."
	defb	199

	defm	"-Co"
	defb	218

	defm	""
	defb	163

	defm	"za"
	defb	182

	defm	""
	defb	148

	defm	"t"
	defb	184

	defm	""
	defb	174

	defm	""
	defb	188

	defm	"i"
	defb	167

	defm	""
	defb	164

	defm	"m"
	defb	189

	defm	"i"
	defb	191

	defm	"a f"
	defb	175

	defm	"tu"
	defb	178

	defm	"."
	defb	0

	defm	"-E"
	defb	173

	defm	""
	defb	211

	defm	"g"
	defb	163

	defm	"i"
	defb	168

	defm	""
	defb	162

	defm	"r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	210

	defm	"bl"
	defb	142

	defm	""
	defb	128

	defm	"i"
	defb	180

	defm	""
	defb	168

	defm	"faz hum"
	defb	195

	defm	""
	defb	134

	defm	""
	defb	177

	defm	""
	defb	158

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	132

	defm	" "
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	"&"
	defb	167

	defm	""
	defb	164

	defm	""
	defb	128

	defm	"Meg"
	defb	224

	defm	""
	defb	175

	defm	"p(tm)"
	defb	0

	defm	"-L"
	defb	162

	defm	""
	defb	133

	defm	"us"
	defb	189

	defm	""
	defb	139

	defm	"a"
	defb	153

	defm	"m"
	defb	205

	defm	""
	defb	227

	defm	""
	defb	174

	defm	""
	defb	169

	defm	""
	defb	131

	defm	""
	defb	218

	defm	"go."
	defb	0

	defm	"-P"
	defb	219

	defm	"m"
	defb	168

	defm	""
	defb	162

	defm	"ha"
	defb	233

	defm	""
	defb	133

	defm	""
	defb	186

	defm	""
	defb	187

	defm	"g"
	defb	168

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	","
	defb	177

	defm	""
	defb	179

	defm	"g"
	defb	162

	defm	"p"
	defb	184

	defm	"dr$"
	defb	221

	defm	"umb"
	defb	162

	defm	"a M"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	199

	defm	"-t"
	defb	159

	defm	""
	defb	186

	defm	"cu"
	defb	168

	defm	""
	defb	213

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	"."
	defb	0

	defm	"-La "
	defb	145

	defm	""
	defb	191

	defm	"a"
	defb	136

	defm	"# ha"
	defb	233

	defm	"fu"
	defb	168

	defm	"a"
	defb	199

	defm	"E"
	defb	161

	defm	"p"
	defb	194

	defm	"ibl"
	defb	159

	defm	""
	defb	133

	defm	"n"
	defb	223

	defm	""
	defb	165

	defm	"it"
	defb	156

	defm	""
	defb	190

	defm	"g'"
	defb	167

	defm	"c&dig"
	defb	162

	defm	""
	defb	146

	defm	""
	defb	224

	defm	"c"
	defb	165

	defm	"o"
	defb	139

	defm	"a "
	defb	145

	defm	""
	defb	174

	defm	"."
	defb	0

	defm	"-N"
	defb	162

	defm	"t"
	defb	163

	defm	"g"
	defb	162

	defm	"n"
	defb	211

	defm	"g'n"
	defb	166

	defm	"a"
	defb	209

	defm	""
	defb	148

	defm	""
	defb	128

	defm	"o"
	defb	141

	defm	" "
	defb	164

	defm	""
	defb	128

	defm	"c"
	defb	145

	defm	"a"
	defb	173

	defm	""
	defb	224

	defm	""
	defb	168

	defm	"c"
	defb	134

	defm	""
	defb	173

	defm	"c&digo."
	defb	0

	defm	"-La"
	defb	176

	defm	""
	defb	145

	defm	"a"
	defb	173

	defm	""
	defb	146

	defm	"ZHL"
	defb	136

	defm	"#"
	defb	148

	defm	""
	defb	128

	defm	"Ti"
	defb	168

	defm	""
	defb	170

	defm	"."
	defb	0

	defm	"-Es"
	defb	128

	defm	""
	defb	240

	defm	"pr"
	defb	165

	defm	""
	defb	134

	defm	" "
	defb	186

	defm	"p"
	defb	174

	defm	"t"
	defb	162

	defm	""
	defb	146

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	165

	defm	""
	defb	130

	defm	"24h "
	defb	133

	defm	"n"
	defb	158

	defm	""
	defb	196

	defm	"ga"
	defb	129

	defm	"s"
	defb	179

	defm	"ld"
	defb	162

	defm	"y"
	defb	150

	defm	""
	defb	161

	defm	"p"
	defb	208

	defm	"z"
	defb	189

	defm	""
	defb	139

	defm	"a"
	defb	188

	defm	"egui"
	defb	183

	defm	""
	defb	186

	defm	"c"
	defb	175

	defm	""
	defb	219

	defm	""
	defb	163

	defm	""
	defb	185

	defm	""
	defb	129

	defm	"Univ"
	defb	168

	defm	"so."
	defb	0

	defm	"-La Ti"
	defb	168

	defm	""
	defb	170

	defm	" fu"
	defb	142

	defm	"v"
	defb	189

	defm	"t"
	defb	191

	defm	""
	defb	134

	defm	"s"
	defb	238

	defm	"$"
	defb	132

	defm	" v"
	defb	174

	defm	"i"
	defb	158

	defm	"a"
	defb	234

	defm	"c"
	defb	190

	defm	"ip"
	defb	214

	defm	"s"
	defb	199

	defm	"Aho"
	defb	170

	defm	""
	defb	149

	defm	""
	defb	212

	defm	""
	defb	167

	defm	"lug"
	defb	174

	defm	""
	defb	188

	defm	""
	defb	190

	defm	"vaje,"
	defb	172

	defm	""
	defb	181

	defm	"igr"
	defb	194

	defm	""
	defb	162

	defm	""
	defb	159

	defm	""
	defb	211

	defm	""
	defb	187

	defm	"m"
	defb	205

	defm	""
	defb	227

	defm	"a"
	defb	185

	defm	"."
	defb	0

	defm	"-H"
	defb	240

	defm	""
	defb	158

	defm	"at"
	defb	168

	defm	""
	defb	219

	defm	"z"
	defb	191

	defm	""
	defb	162

	defm	"c"
	defb	168

	defm	"c"
	defb	134

	defm	""
	defb	128

	defm	""
	defb	145

	defm	""
	defb	191

	defm	"a"
	defb	199

	defm	"Deb"
	defb	156

	defm	"s"
	defb	190

	defm	"ir"
	defb	182

	defm	"l"
	defb	160

	defm	"xt"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	232

	defm	""
	defb	145

	defm	""
	defb	174

	defm	""
	defb	148

	defm	""
	defb	129

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$"
	defb	167

	defm	""
	defb	233

	defm	"volv"
	defb	168

	defm	""
	defb	131

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	139

	defm	"a "
	defb	133

	defm	"p"
	defb	179

	defm	"d"
	defb	152

	defm	"t"
	defb	168

	defm	"m"
	defb	211

	defm	""
	defb	174

	defm	""
	defb	128

	defm	""
	defb	218

	defm	""
	defb	214

	defm	""
	defb	226

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-E"
	defb	167

	defm	"t"
	defb	175

	defm	"n"
	defb	162

	defm	"a 150"
	defb	186

	defm	"C baj"
	defb	162

	defm	"c"
	defb	168

	defm	"o"
	defb	148

	defm	""
	defb	129

	defm	"ext"
	defb	168

	defm	"i"
	defb	175

	defm	""
	defb	199

	defm	"T"
	defb	159

	defm	""
	defb	186

	defm	""
	defb	187

	defm	""
	defb	218

	defm	""
	defb	163

	defm	"d"
	defb	162

	defm	""
	defb	133

	defm	"l"
	defb	217

	defm	"v"
	defb	165

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	142

	defm	""
	defb	188

	defm	"up"
	defb	168

	defm	"vivi"
	defb	163

	defm	""
	defb	203

	defm	"a."
	defb	0

	defm	"-La"
	defb	131

	defm	"sol"
	defb	134

	defm	""
	defb	192

	defm	""
	defb	195

	defm	"d"
	defb	162

	defm	"mu"
	defb	165

	defm	"t"
	defb	170

	defm	""
	defb	129

	defm	""
	defb	165

	defm	"t"
	defb	191

	defm	""
	defb	162

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	"v"
	defb	159

	defm	"y"
	defb	177

	defm	""
	defb	194

	defm	""
	defb	131

	defm	""
	defb	200

	defm	"ol"
	defb	156

	defm	"m"
	defb	195

	defm	"u"
	defb	190

	defm	""
	defb	165

	defm	""
	defb	199

	defm	"Actu"
	defb	190

	defm	"m"
	defb	157

	defm	"e"
	defb	136

	defm	"# "
	defb	164

	defm	""
	defb	210

	defm	"ctiv"
	defb	191

	defm	"a"
	defb	139

	defm	"a"
	defb	182

	defm	"h"
	defb	175

	defm	""
	defb	170

	defm	"r"
	defb	148

	defm	""
	defb	168

	defm	"g%a"
	defb	199

	defm	""
	defb	0

	defm	"-E"
	defb	161

	defm	"n"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	173

	defm	""
	defb	133

	defm	"n"
	defb	162

	defm	""
	defb	186

	defm	"cu"
	defb	168

	defm	"d"
	defb	156

	defm	"much"
	defb	162

	defm	""
	defb	190

	defm	""
	defb	153

	defm	""
	defb	218

	defm	""
	defb	163

	defm	"z"
	defb	162

	defm	""
	defb	146

	defm	"u"
	defb	178

	defm	""
	defb	192

	defm	"i"
	defb	214

	defm	""
	defb	226

	defm	""
	defb	199

	defm	"P"
	defb	168

	defm	""
	defb	162

	defm	"n"
	defb	162

	defm	"t"
	defb	159

	defm	"p"
	defb	186

	defm	"ocu"
	defb	243

	defm	""
	defb	132

	defm	""
	defb	149

	defm	""
	defb	162

	defm	"aho"
	defb	170

	defm	""
	defb	232

	defm	""
	defb	164

	defm	"s"
	defb	238

	defm	"$"
	defb	132

	defm	" "
	defb	205

	defm	""
	defb	152

	defm	"j"
	defb	175

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	132

	defm	" "
	defb	186

	defm	""
	defb	171

	defm	"x"
	defb	197

	defm	"od"
	defb	162

	defm	"volv"
	defb	168

	defm	"#"
	defb	182

	defm	""
	defb	128

	defm	"n"
	defb	175

	defm	"m"
	defb	190

	defm	"id"
	defb	191

	defm	"."
	defb	0

	defm	"-D"
	defb	165

	defm	""
	defb	238

	defm	"$"
	defb	132

	defm	""
	defb	136

	defm	""
	defb	159

	defm	"t"
	defb	170

	defm	"baj"
	defb	162

	defm	""
	defb	234

	defm	"dr#"
	defb	161

	defm	"p"
	defb	189

	defm	""
	defb	174

	defm	" "
	defb	205

	defm	""
	defb	158

	defm	"d%a"
	defb	132

	defm	" "
	defb	186

	defm	""
	defb	171

	defm	"x"
	defb	130

	defm	"M"
	defb	174

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"-Ya"
	defb	188

	defm	""
	defb	237

	defm	""
	defb	165

	defm	","
	defb	129

	defm	"p"
	defb	171

	defm	""
	defb	239

	defm	""
	defb	198

	defm	" "
	defb	201

	defm	"jo"
	defb	199

	defm	"Bu"
	defb	163

	defm	"o,"
	defb	182

	defm	""
	defb	178

	defm	""
	defb	170

	defm	"nj"
	defb	191

	defm	""
	defb	162

	defm	""
	defb	164

	defm	"s"
	defb	146

	defm	""
	defb	133

	defm	""
	defb	187

	defm	"m"
	defb	163

	defm	"z&"
	defb	128

	defm	"t"
	defb	168

	defm	""
	defb	170

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-E"
	defb	161

	defm	""
	defb	235

	defm	"j"
	defb	175

	defm	" "
	defb	133

	defm	"n"
	defb	162

	defm	"s"
	defb	190

	defm	"irs"
	defb	142

	defm	""
	defb	173

	defm	""
	defb	169

	defm	"m"
	defb	134

	defm	""
	defb	128

	defm	""
	defb	218

	defm	""
	defb	214

	defm	""
	defb	226

	defm	""
	defb	199

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	""
	defb	0

	defm	"-D"
	defb	165

	defm	""
	defb	238

	defm	"$"
	defb	132

	defm	""
	defb	128

	defm	""
	defb	186

	defm	""
	defb	187

	defm	"gid"
	defb	134

	defm	"b"
	defb	240

	defm	""
	defb	158

	defm	""
	defb	145

	defm	"eg"
	defb	174

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	""
	defb	148

	defm	""
	defb	129

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	""
	defb	166

	defm	""
	defb	147

	defm	"di"
	defb	237

	defm	""
	defb	215

	defm	""
	defb	199

	defm	"Un"
	defb	134

	defm	""
	defb	150

	defm	""
	defb	161

	defm	""
	defb	204

	defm	"y"
	defb	175

	defm	""
	defb	156

	defm	""
	defb	218

	defm	""
	defb	178

	defm	""
	defb	132

	defm	" Hi"
	defb	168

	defm	"r"
	defb	162

	defm	""
	defb	233

	defm	"N%"
	defb	206

	defm	""
	defb	147

	defm	"d"
	defb	147

	defm	"S"
	defb	231

	defm	""
	defb	169

	defm	""
	defb	204

	defm	" So"
	defb	171

	defm	"r."
	defb	0

	defm	"-Tambi$"
	defb	167

	defm	"s"
	defb	159

	defm	""
	defb	217

	defm	""
	defb	131

	defm	"o"
	defb	230

	defm	""
	defb	153

	defm	""
	defb	236

	defm	""
	defb	129

	defm	"t"
	defb	163

	defm	"ed"
	defb	175

	defm	""
	defb	166

	defm	""
	defb	147

	defm	"di"
	defb	237

	defm	""
	defb	215

	defm	""
	defb	199

	defm	"E"
	defb	161

	defm	"u"
	defb	178

	defm	""
	defb	192

	defm	"i"
	defb	178

	defm	" gob"
	defb	168

	defm	""
	defb	178

	defm	""
	defb	213

	defm	""
	defb	172

	defm	""
	defb	175

	defm	""
	defb	129

	defm	"s"
	defb	211

	defm	"d"
	defb	227

	defm	"at"
	defb	162

	defm	""
	defb	205

	defm	"if"
	defb	227

	defm	""
	defb	191

	defm	""
	defb	162

	defm	""
	defb	146

	defm	"m"
	defb	211

	defm	""
	defb	168

	defm	"%"
	defb	134

	defm	" M"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-E"
	defb	161

	defm	"u"
	defb	167

	defm	""
	defb	235

	defm	""
	defb	198

	defm	""
	defb	173

	defm	""
	defb	237

	defm	""
	defb	205

	defm	""
	defb	213

	defm	""
	defb	180

	defm	""
	defb	159

	defm	"p"
	defb	168

	defm	""
	defb	162

	defm	"muy"
	defb	172

	defm	""
	defb	186

	defm	""
	defb	203

	defm	"a"
	defb	185

	defm	""
	defb	199

	defm	"L"
	defb	162

	defm	"dif%"
	defb	203

	defm	"l"
	defb	149

	defm	""
	defb	188

	defm	"u"
	defb	197

	defm	""
	defb	170

	defm	"nsp"
	defb	175

	defm	""
	defb	169

	defm	","
	defb	172

	defm	"u"
	defb	165

	defm	""
	defb	149

	defm	""
	defb	192

	defm	"uy"
	defb	166

	defm	""
	defb	163

	defm	"s"
	defb	162

	defm	"y"
	defb	176

	defm	"u"
	defb	165

	defm	""
	defb	198

	defm	" b"
	defb	189

	defm	""
	defb	198

	defm	""
	defb	180

	defm	""
	defb	159

	defm	"d"
	defb	211

	defm	""
	defb	168

	defm	"o"
	defb	160

	defm	"xt"
	defb	170

	defm	""
	defb	168

	defm	"l"
	defb	162

	defm	""
	defb	164

	defm	""
	defb	128

	defm	"atm&sf"
	defb	168

	defm	"a"
	defb	148

	defm	""
	defb	128

	defm	"Ti"
	defb	168

	defm	""
	defb	170

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Gobi"
	defb	168

	defm	""
	defb	178

	defm	"n"
	defb	131

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	162

	defm	"du"
	defb	170

	defm	""
	defb	177

	defm	""
	defb	158

	defm	"p"
	defb	186

	defm	""
	defb	203

	defm	"o"
	defb	132

	defm	" v"
	defb	157

	defm	"a y"
	defb	177

	defm	""
	defb	158

	defm	""
	defb	224

	defm	"u"
	defb	168

	defm	""
	defb	185

	defm	""
	defb	132

	defm	""
	defb	188

	defm	"um"
	defb	211

	defm	"i"
	defb	193

	defm	"r"
	defb	194

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-So"
	defb	167

	defm	"t"
	defb	208

	defm	"mp"
	defb	158

	defm	"dif%"
	defb	203

	defm	"l"
	defb	165

	defm	""
	defb	199

	defm	"La hum"
	defb	195

	defm	"id"
	defb	191

	defm	""
	defb	197

	defm	"uv"
	defb	162

	defm	""
	defb	133

	defm	""
	defb	237

	defm	""
	defb	195

	defm	"d"
	defb	184

	defm	""
	defb	174

	defm	""
	defb	128

	defm	"Ti"
	defb	168

	defm	"r"
	defb	134

	defm	"bid"
	defb	162

	defm	"a v"
	defb	174

	defm	"i"
	defb	152

	defm	"gu"
	defb	168

	defm	"r"
	defb	152

	defm	"nuc"
	defb	217

	defm	""
	defb	174

	defm	""
	defb	156

	defm	"y"
	defb	166

	defm	"i"
	defb	222

	defm	"m"
	defb	211

	defm	""
	defb	174

	defm	"s"
	defb	159

	defm	"p"
	defb	175

	defm	""
	defb	129

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	188

	defm	"o"
	defb	171

	defm	"r"
	defb	199

	defm	""
	defb	0

	defm	"-Ya"
	defb	188

	defm	""
	defb	237

	defm	""
	defb	156

	defm	"sum"
	defb	211

	defm	"i"
	defb	193

	defm	"r"
	defb	194

	defm	","
	defb	172

	defm	"aq"
	defb	179

	defm	"t"
	defb	168

	defm	"%a,"
	defb	216

	defm	""
	defb	203

	defm	"o..."
	defb	0

	defm	"-A"
	defb	206

	defm	"% "
	defb	178

	defm	"d"
	defb	134

	defm	""
	defb	216

	defm	""
	defb	203

	defm	"o"
	defb	232

	defm	"ha"
	defb	233

	defm	""
	defb	133

	defm	"t"
	defb	168

	defm	"m"
	defb	211

	defm	""
	defb	174

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"bajo."
	defb	0

	defm	"-Nu"
	defb	165

	defm	""
	defb	200

	defm	""
	defb	162

	defm	"t"
	defb	170

	defm	"bajo"
	defb	130

	defm	"ZHL"
	defb	149

	defm	" "
	defb	145

	defm	"eg"
	defb	174

	defm	""
	defb	177

	defm	""
	defb	158

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	165

	defm	""
	defb	130

	defm	"24h."
	defb	0

	defm	"-S"
	defb	159

	defm	"ha"
	defb	167

	defm	""
	defb	237

	defm	"i"
	defb	168

	defm	"t"
	defb	162

	defm	"v"
	defb	174

	defm	"i"
	defb	152

	defm	""
	defb	218

	defm	""
	defb	178

	defm	"s"
	defb	130

	defm	"M"
	defb	174

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"-Seg'n"
	defb	128

	defm	""
	defb	164

	defm	"sc"
	defb	219

	defm	"p"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	166

	defm	""
	defb	147

	defm	"m"
	defb	163

	defm	""
	defb	210

	defm	"j"
	defb	159

	defm	"s"
	defb	159

	defm	"t"
	defb	170

	defm	"t"
	defb	134

	defm	""
	defb	212

	defm	""
	defb	167

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	142

	defm	" 27cm x 29cm x 30cm "
	defb	133

	defm	"p"
	defb	165

	defm	"a 10Kg"
	defb	199

	defm	""
	defb	0

	defm	"-H"
	defb	240

	defm	""
	defb	158

	defm	"at"
	defb	168

	defm	""
	defb	219

	defm	"za"
	defb	185

	defm	""
	defb	148

	defm	""
	defb	128

	defm	""
	defb	145

	defm	""
	defb	191

	defm	""
	defb	134

	defm	""
	defb	173

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n"
	defb	199

	defm	"Sugi"
	defb	168

	defm	""
	defb	162

	defm	""
	defb	133

	defm	"s"
	defb	190

	defm	"g"
	defb	152

	defm	"ah% fu"
	defb	168

	defm	"a,"
	defb	177

	defm	""
	defb	171

	defm	"m"
	defb	156

	defm	"a"
	defb	128

	defm	""
	defb	238

	defm	""
	defb	168

	defm	""
	defb	198

	defm	" "
	defb	233

	defm	""
	defb	186

	defm	""
	defb	187

	defm	"j"
	defb	189

	defm	""
	defb	129

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"-Vo"
	defb	171

	defm	"m"
	defb	194

	defm	""
	defb	130

	defm	"u"
	defb	178

	defm	" "
	defb	178

	defm	"v"
	defb	142

	defm	" "
	defb	186

	defm	"p"
	defb	174

	defm	"t"
	defb	162

	defm	""
	defb	146

	defm	"tip"
	defb	162

	defm	"T"
	defb	165

	defm	""
	defb	171

	defm	""
	defb	199

	defm	"Es"
	defb	153

	defm	"mp"
	defb	217

	defm	""
	defb	198

	defm	"m"
	defb	157

	defm	"e"
	defb	154

	defm	"$c"
	defb	200

	defm	""
	defb	227

	defm	"a"
	defb	188

	defm	""
	defb	190

	defm	"vo"
	defb	129

	defm	""
	defb	236

	defm	"t"
	defb	175

	defm	""
	defb	172

	defm	"r"
	defb	211

	defm	""
	defb	203

	defm	"p"
	defb	190

	defm	"."
	defb	0

	defm	"-La"
	defb	192

	defm	"#"
	defb	161

	defm	"c"
	defb	168

	defm	""
	defb	228

	defm	""
	defb	178

	defm	""
	defb	149

	defm	" Sol."
	defb	0

	defm	"-Es"
	defb	128

	defm	""
	defb	165

	defm	""
	defb	200

	defm	""
	defb	181

	defm	""
	defb	151

	defm	"pr"
	defb	211

	defm	""
	defb	203

	defm	""
	defb	196

	defm	""
	defb	173

	defm	""
	defb	164

	defm	""
	defb	136

	defm	""
	defb	159

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Es"
	defb	129

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	""
	defb	204

	defm	""
	defb	182

	defm	""
	defb	173

	defm	""
	defb	133

	defm	"p"
	defb	168

	defm	"t"
	defb	163

	defm	""
	defb	223

	defm	"e"
	defb	128

	defm	"Ti"
	defb	168

	defm	""
	defb	170

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Tod"
	defb	158

	defm	"l"
	defb	158

	defm	""
	defb	214

	defm	"s"
	defb	169

	defm	"m"
	defb	189

	defm	""
	defb	130

	defm	"o"
	defb	141

	defm	""
	defb	199

	defm	"Op"
	defb	168

	defm	"am"
	defb	194

	defm	""
	defb	130

	defm	""
	defb	236

	defm	"d"
	defb	162

	defm	""
	defb	146

	defm	"bajo"
	defb	131

	defm	"su"
	defb	236

	defm	"."
	defb	0

	defm	"-P"
	defb	140

	defm	""
	defb	165

	defm	"o"
	defb	136

	defm	"oy"
	defb	182

	defm	""
	defb	206

	defm	"%,"
	defb	139

	defm	"a"
	defb	182

	defm	"yud"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	199

	defm	"Alg"
	defb	205

	defm	""
	defb	152

	defm	""
	defb	196

	defm	""
	defb	171

	defm	"br"
	defb	152

	defm	"c"
	defb	171

	defm	"v"
	defb	159

	defm	""
	defb	133

	defm	"p"
	defb	179

	defm	"d"
	defb	156

	defm	"us"
	defb	174

	defm	""
	defb	188

	defm	""
	defb	184

	defm	":"
	defb	192

	defm	"i"
	defb	214

	defm	""
	defb	226

	defm	""
	defb	232

	defm	"J'pit"
	defb	168

	defm	","
	defb	202

	defm	"omb"
	defb	186

	defm	","
	defb	192

	defm	"o"
	defb	164

	defm	""
	defb	215

	defm	","
	defb	192

	defm	""
	defb	163

	defm	""
	defb	210

	defm	"je..."
	defb	0

	defm	"Te"
	defb	204

	defm	": Env%"
	defb	162

	defm	"urg"
	defb	157

	defm	""
	defb	159

	defm	"a"
	defb	173

	defm	"T"
	defb	163

	defm	"ed"
	defb	175

	defm	" "
	defb	146

	defm	"M"
	defb	174

	defm	""
	defb	169

	defm	""
	defb	199

	defm	"Co"
	defb	180

	defm	""
	defb	163

	defm	"i"
	defb	185

	defm	": Re"
	defb	187

	defm	"gi"
	defb	213

	defm	""
	defb	130

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c$n"
	defb	130

	defm	""
	defb	187

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	189

	defm	""
	defb	130

	defm	"Eu"
	defb	201

	defm	""
	defb	196

	defm	""
	defb	199

	defm	"Us"
	defb	174

	defm	""
	defb	176

	defm	""
	defb	171

	defm	""
	defb	207

	defm	": 32768"
	defb	199

	defm	"Imp"
	defb	175

	defm	"t"
	defb	195

	defm	""
	defb	169

	defm	": Ma"
	defb	180

	defm	""
	defb	163

	defm	""
	defb	168

	defm	""
	defb	182

	defm	" "
	defb	169

	defm	"mp"
	defb	168

	defm	"atu"
	defb	170

	defm	" baj"
	defb	162

	defm	"c"
	defb	168

	defm	"o"
	defb	199

	defm	""
	defb	0

	defm	"-Quiz# haya"
	defb	182

	defm	"lgo"
	defb	148

	defm	""
	defb	129

	defm	"m"
	defb	163

	defm	""
	defb	210

	defm	"j"
	defb	142

	defm	"l"
	defb	148

	defm	"c"
	defb	174

	defm	"go."
	defb	0

	defm	"-No"
	defb	149

	defm	""
	defb	212

	defm	""
	defb	167

	defm	"p"
	defb	201

	defm	"b"
	defb	217

	defm	""
	defb	204

	defm	""
	defb	131

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	142

	defm	""
	defb	188

	defm	"up"
	defb	168

	defm	"viv"
	defb	163

	defm	""
	defb	203

	defm	"a"
	defb	199

	defm	"Si"
	defb	167

	defm	"$l"
	defb	128

	defm	""
	defb	170

	defm	"dia"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	149

	defm	""
	defb	197

	defm	""
	defb	195

	defm	""
	defb	154

	defm	"ev"
	defb	191

	defm	"a "
	defb	133

	defm	"n"
	defb	162

	defm	"vivir%"
	defb	152

	defm	"m#"
	defb	132

	defm	" "
	defb	205

	defm	""
	defb	166

	defm	"%a"
	defb	199

	defm	""
	defb	0

	defm	"-La"
	defb	149

	defm	"clu"
	defb	210

	defm	""
	defb	188

	defm	""
	defb	159

	defm	"op"
	defb	168

	defm	"a"
	defb	192

	defm	""
	defb	195

	defm	"u"
	defb	190

	defm	"m"
	defb	157

	defm	"e"
	defb	199

	defm	"E"
	defb	173

	defm	"bot&"
	defb	167

	defm	"v"
	defb	168

	defm	""
	defb	146

	defm	""
	defb	203

	defm	""
	defb	168

	defm	""
	defb	170

	defm	""
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	" y"
	defb	129

	defm	""
	defb	201

	defm	"jo"
	defb	128

	defm	""
	defb	237

	defm	""
	defb	186

	defm	""
	defb	199

	defm	" A"
	defb	222

	defm	"g'"
	defb	170

	defm	"t"
	defb	159

	defm	""
	defb	138

	defm	""
	defb	217

	defm	"v"
	defb	174

	defm	""
	defb	129

	defm	"t"
	defb	170

	defm	"j"
	defb	142

	defm	""
	defb	188

	defm	"up"
	defb	168

	defm	"viv"
	defb	163

	defm	""
	defb	203

	defm	"a"
	defb	172

	defm	"u"
	defb	165

	defm	""
	defb	209

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Debid"
	defb	162

	defm	"a"
	defb	128

	defm	"fu"
	defb	168

	defm	"t"
	defb	159

	defm	""
	defb	170

	defm	"dia"
	defb	203

	defm	"&"
	defb	167

	defm	"nu"
	defb	165

	defm	""
	defb	200

	defm	""
	defb	152

	defm	""
	defb	187

	defm	"m"
	defb	205

	defm	""
	defb	227

	defm	"a"
	defb	203

	defm	""
	defb	184

	defm	""
	defb	156

	defm	"s&l"
	defb	162

	defm	"f"
	defb	205

	defm	""
	defb	203

	defm	"o"
	defb	178

	defm	"n"
	defb	148

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	"No"
	defb	136

	defm	""
	defb	174

	defm	"$"
	defb	131

	defm	"tig"
	defb	162

	defm	"ah% fu"
	defb	168

	defm	"a"
	defb	199

	defm	""
	defb	0

	defm	"-S"
	defb	184

	defm	""
	defb	150

	defm	""
	defb	161

	defm	""
	defb	214

	defm	"g"
	defb	171

	defm	""
	defb	132

	defm	""
	defb	182

	defm	"ctivid"
	defb	191

	defm	""
	defb	160

	defm	"xt"
	defb	170

	defm	"-"
	defb	207

	defm	"h"
	defb	227

	defm	"u"
	defb	171

	defm	"r"
	defb	199

	defm	"E"
	defb	161

	defm	"cu"
	defb	195

	defm	"d"
	defb	162

	defm	"s"
	defb	190

	defm	""
	defb	165

	defm	""
	defb	130

	defm	""
	defb	218

	defm	""
	defb	214

	defm	"&"
	defb	167

	defm	"fu"
	defb	168

	defm	""
	defb	134

	defm	""
	defb	128

	defm	""
	defb	178

	defm	""
	defb	207

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Lo"
	defb	148

	defm	""
	defb	187

	defm	""
	defb	180

	defm	""
	defb	170

	defm	"r#s"
	defb	148

	defm	""
	defb	128

	defm	""
	defb	165

	defm	"clu"
	defb	210

	defm	""
	defb	177

	defm	"i"
	defb	193

	defm	"o"
	defb	139

	defm	"a"
	defb	188

	defm	"u"
	defb	212

	defm	"so"
	defb	199

	defm	"R"
	defb	223

	defm	"u"
	defb	168

	defm	""
	defb	213

	defm	""
	defb	202

	defm	""
	defb	162

	defm	"s"
	defb	190

	defm	"i"
	defb	183

	defm	""
	defb	164

	defm	""
	defb	128

	defm	""
	defb	178

	defm	"v"
	defb	159

	defm	""
	defb	214

	defm	""
	defb	167

	defm	"l"
	defb	217

	defm	"v"
	defb	174

	defm	"l"
	defb	162

	defm	""
	defb	238

	defm	""
	defb	165

	defm	""
	defb	209

	defm	"."
	defb	0

	defm	"-E"
	defb	210

	defm	""
	defb	182

	defm	""
	defb	230

	defm	"p"
	defb	203

	defm	"&"
	defb	167

	defm	"n"
	defb	162

	defm	"f"
	defb	175

	defm	""
	defb	204

	defm	""
	defb	139

	defm	"t"
	defb	142

	defm	""
	defb	192

	defm	"i b"
	defb	189

	defm	""
	defb	142

	defm	""
	defb	166

	defm	"at"
	defb	194

	defm	""
	defb	199

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	""
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	131

	defm	""
	defb	154

	defm	"eg"
	defb	195

	defm	""
	defb	203

	defm	"a"
	defb	199

	defm	""
	defb	0

	defm	"-Ya"
	defb	188

	defm	""
	defb	237

	defm	""
	defb	165

	defm	","
	defb	139

	defm	"a"
	defb	182

	defm	"c"
	defb	175

	defm	"t"
	defb	174

	defm	""
	defb	172

	defm	"a"
	defb	171

	defm	"b"
	defb	170

	defm	""
	defb	132

	defm	"m"
	defb	189

	defm	"ia"
	defb	185

	defm	""
	defb	150

	defm	"rg"
	defb	189

	defm	""
	defb	199

	defm	""
	defb	0

	defm	"-Si"
	defb	167

	defm	"p"
	defb	201

	defm	"b"
	defb	217

	defm	"m"
	defb	189

	defm	""
	defb	232

	defm	"ya"
	defb	202

	defm	""
	defb	162

	defm	""
	defb	198

	defm	""
	defb	170

	defm	""
	defb	186

	defm	""
	defb	162

	defm	"m"
	defb	189

	defm	""
	defb	199

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	146

	defm	"u"
	defb	167

	defm	""
	defb	234

	defm	"c"
	defb	162

	defm	""
	defb	185

	defm	"li"
	defb	185

	defm	"."
	defb	0

	defm	"-D"
	defb	184

	defm	""
	defb	146

	defm	""
	defb	190

	defm	""
	defb	204

	defm	"c"
	defb	163

	defm	"am"
	defb	158

	defm	"l"
	defb	158

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	165

	defm	""
	defb	139

	defm	"a"
	defb	188

	defm	"u"
	defb	166

	defm	"i"
	defb	193

	defm	""
	defb	219

	defm	"bu"
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	"-T"
	defb	163

	defm	""
	defb	240

	defm	""
	defb	158

	defm	"u"
	defb	167

	defm	"f"
	defb	219

	defm	"g"
	defb	175

	defm	"%f"
	defb	227

	defm	""
	defb	162

	defm	""
	defb	164

	defm	"d"
	defb	227

	defm	""
	defb	191

	defm	""
	defb	162

	defm	"a"
	defb	136

	defm	""
	defb	159

	defm	"tip"
	defb	162

	defm	""
	defb	146

	defm	""
	defb	196

	defm	"q"
	defb	179

	defm	"t"
	defb	165

	defm	""
	defb	199

	defm	"-r"
	defb	165

	defm	"p"
	defb	184

	defm	"d"
	defb	142

	defm	"s"
	defb	238

	defm	"$"
	defb	132

	defm	""
	defb	212

	defm	""
	defb	167

	defm	"b"
	defb	186

	defm	"v"
	defb	159

	defm	""
	defb	214

	defm	"l"
	defb	163

	defm	""
	defb	203

	defm	"o"
	defb	0

	defm	"A"
	defb	173

	defm	"sur."
	defb	0

	defm	"A"
	defb	173

	defm	"o"
	defb	165

	defm	""
	defb	169

	defm	"."
	defb	0

	defm	"P"
	defb	201

	defm	"vi"
	defb	163

	defm	""
	defb	142

	defm	"l"
	defb	172

	defm	"u"
	defb	157

	defm	""
	defb	142

	defm	""
	defb	192

	defm	""
	defb	195

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"E"
	defb	173

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	"d"
	defb	162

	defm	"n"
	defb	162

	defm	"r"
	defb	165

	defm	"p"
	defb	184

	defm	""
	defb	164

	defm	""
	defb	199

	defm	"La"
	defb	172

	defm	"u"
	defb	168

	defm	""
	defb	198

	defm	" ya"
	defb	136

	defm	"#"
	defb	182

	defm	"bi"
	defb	168

	defm	""
	defb	198

	defm	".^"
	defb	0

	defm	"Deb"
	defb	162

	defm	""
	defb	169

	defm	"c"
	defb	217

	defm	""
	defb	174

	defm	""
	defb	128

	defm	""
	defb	187

	defm	""
	defb	180

	defm	""
	defb	170

	defm	""
	defb	222

	defm	"+a"
	defb	153

	defm	"r"
	defb	186

	defm	"c"
	defb	198

	defm	""
	defb	148

	defm	""
	defb	129

	defm	""
	defb	169

	defm	"c"
	defb	171

	defm	""
	defb	185

	defm	"."
	defb	0

	defm	"Deb"
	defb	168

	defm	"%"
	defb	152

	defm	""
	defb	187

	defm	"g"
	defb	168

	defm	""
	defb	149

	defm	""
	defb	162

	defm	"a"
	defb	180

	defm	""
	defb	165

	defm	".^"
	defb	0

	defm	"N"
	defb	162

	defm	"v"
	defb	165

	defm	""
	defb	149

	defm	""
	defb	162

	defm	"p"
	defb	175

	defm	""
	defb	182

	defm	""
	defb	206

	defm	"%.^"
	defb	0

	defm	"N"
	defb	162

	defm	"n"
	defb	223

	defm	""
	defb	165

	defm	"it"
	defb	152

	defm	"c"
	defb	174

	defm	"g"
	defb	174

	defm	" "
	defb	162

	defm	"s"
	defb	190

	defm	"v"
	defb	174

	defm	""
	defb	130

	defm	""
	defb	165

	defm	"t"
	defb	159

	defm	"viaj"
	defb	159

	defm	"-d"
	defb	227

	defm	"e"
	defb	129

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	""
	defb	0

	defm	"E"
	defb	173

	defm	"o"
	defb	141

	defm	""
	defb	191

	defm	""
	defb	175

	defm	" "
	defb	146

	defm	""
	defb	178

	defm	""
	defb	207

	defm	"ga"
	defb	203

	defm	""
	defb	226

	defm	""
	defb	139

	defm	""
	defb	223

	defm	"e"
	defb	136

	defm	""
	defb	174

	defm	""
	defb	197

	defm	"a"
	defb	170

	defm	""
	defb	186

	defm	""
	defb	195

	defm	"d"
	defb	162

	defm	"u"
	defb	178

	defm	""
	defb	176

	defm	""
	defb	195

	defm	""
	defb	203

	defm	""
	defb	226

	defm	"."
	defb	0

	defm	" Z H L "
	defb	0

	defm	"1 Jug"
	defb	174

	defm	""
	defb	0

	defm	"2 Cr$dit"
	defb	194

	defm	""
	defb	0

	defm	"(C) 2019,2021 KMBR "
	defb	0

	defm	"Z H L"
	defb	0

	defm	"C"
	defb	186

	defm	""
	defb	191

	defm	"a"
	defb	172

	defm	""
	defb	175

	defm	" KMBR"
	defb	0

	defm	"R"
	defb	181

	defm	"e"
	defb	189

	defm	""
	defb	159

	defm	"5 ^"
	defb	0

	defm	"Ag"
	defb	170

	defm	""
	defb	164

	defm	""
	defb	203

	defm	""
	defb	218

	defm	""
	defb	157

	defm	""
	defb	158

	defm	"a"
	defb	182

	defm	"a@zdk."
	defb	175

	defm	"g "
	defb	233

	defm	"C"
	defb	174

	defm	"l"
	defb	158

	defm	"S#nchez (UTO)"
	defb	0

	defm	"Compr"
	defb	165

	defm	"i&"
	defb	167

	defm	""
	defb	146

	defm	"gr#fi"
	defb	187

	defm	"s"
	defb	131

	defm	" ZX7"
	defb	172

	defm	""
	defb	175

	defm	" E"
	defb	211

	defm	""
	defb	174

	defm	" Sauk"
	defb	189

	defm	""
	defb	0

	defm	"Rey"
	defb	220

	defm	"ld"
	defb	161

	defm	"fo"
	defb	180

	defm	" b"
	defb	233

	defm	"Da"
	defb	218

	defm	""
	defb	163

	defm	"G"
	defb	0



; --- Start of Static Variables ---

	SECTION	bss_compiler

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
	PUBLIC	_proceso1
	PUBLIC	_proceso2
	PUBLIC	_proceso1_post
	EXTERN	_proceso2_post
	PUBLIC	_respuestas
	PUBLIC	_respuestas_post
	EXTERN	_initParser
	EXTERN	_ParserLoop
	EXTERN	_parse
	EXTERN	_buscador
	EXTERN	_CNDobjfound
	EXTERN	_CNDobjnotfound
	EXTERN	_CNDcarried
	EXTERN	_CNDpresent
	EXTERN	_CNDabsent
	EXTERN	_CNDworn
	EXTERN	_CNDnotworn
	EXTERN	_CNDozero
	EXTERN	_CNDonotzero
	EXTERN	_CNDweight
	EXTERN	_CNDisat
	EXTERN	_CNDisnotat
	EXTERN	_CNDat
	EXTERN	_CNDnotat
	EXTERN	_CNDatgt
	EXTERN	_CNDatlt
	EXTERN	_ACCdesc
	EXTERN	_ACCdone
	EXTERN	_ACCbreak
	EXTERN	_ACCdestroy
	EXTERN	_ACCcreate
	EXTERN	_ACCget
	EXTERN	_ACCdrop
	EXTERN	_ACCremove
	EXTERN	_ACCwear
	EXTERN	_ACCgoto
	EXTERN	_ACCweigh
	EXTERN	_ACClistat
	EXTERN	_ACCobjat
	EXTERN	_ACCoset
	EXTERN	_ACCoclear
	EXTERN	_ACConeg
	EXTERN	_ACClistobj
	EXTERN	_ACCplace
	EXTERN	_ACCend
	EXTERN	_ACCsysmess
	EXTERN	_ACCnewline
	EXTERN	_ACCcls
	EXTERN	_ACCgetReferredObject
	EXTERN	_ACCputin
	EXTERN	_ACCtakeout
	EXTERN	_ACCautop
	EXTERN	_ACCautot
	EXTERN	_ACCautor
	EXTERN	_ACCautow
	EXTERN	_ACCclearexit
	EXTERN	_ACCgetexit
	EXTERN	_ACCsetexit
	EXTERN	_ACCmessage
	EXTERN	_ACCmes
	EXTERN	_ACCwrite
	EXTERN	_ACCwriteln
	EXTERN	_writeValue
	EXTERN	_isAccesibleContainer
	EXTERN	_findMatchingObject
	EXTERN	_trytoGet
	EXTERN	_getFlag
	EXTERN	_setFlag
	EXTERN	_done
	EXTERN	_desc
	EXTERN	_loc_here
	EXTERN	_get_obj_pos
	EXTERN	_get_table_pos
	EXTERN	_getObjectLocation
	EXTERN	_getObjectWeight
	EXTERN	_getLocationObjectsWeight
	EXTERN	_getObjectCountAt
	EXTERN	_getObjectCountAtWithAttr
	EXTERN	_getNPCCountAt
	EXTERN	_objectIsSupporter
	EXTERN	_objectIsContainer
	EXTERN	_objectIsAttr
	EXTERN	_objectIsNPC
	EXTERN	_get_loc_pos
	EXTERN	_get_img_pos
	EXTERN	_get_msg_pos
	EXTERN	_writeText
	EXTERN	_writeTextln
	EXTERN	_writeSysMessage
	EXTERN	_writeMessage
	EXTERN	_writeObject
	EXTERN	_setObjectLocation
	EXTERN	_defineGraphWindow
	EXTERN	_defineTextWindow
	EXTERN	_clearTextWindow
	EXTERN	_clearTextLine
	EXTERN	_clearGraphWindow
	EXTERN	_gotoxy
	EXTERN	_clearchar
	EXTERN	_scrollVTextWindow
	EXTERN	_CaptionBox
	EXTERN	_writeTextCenter
	EXTERN	_fontStyle
	EXTERN	_newLine
	EXTERN	_getInput
	EXTERN	_hideGraphicsWindow
	EXTERN	_debugger
	EXTERN	_setConnection
	EXTERN	_getConnection
	EXTERN	_incr16bit
	EXTERN	_flags
	EXTERN	_playerInput
	EXTERN	_playerWord
	EXTERN	_gWord_number
	EXTERN	_gChar_number
	EXTERN	_L01_img
	EXTERN	_L02_img
	EXTERN	_L03_img
	EXTERN	_L04_img
	EXTERN	_L05_img
	EXTERN	_L06_img
	EXTERN	_L07_img
	EXTERN	_Europa_img
	PUBLIC	_imagenes_t
	PUBLIC	_localidades_t
	PUBLIC	_conexiones_t
	PUBLIC	_mensajes_t
	PUBLIC	_mensajesSistema_t
	PUBLIC	_nombres_t
	PUBLIC	_verbos_t
	PUBLIC	_adjetivos_t
	PUBLIC	_objetos_t
	PUBLIC	_ordenador_topics_t
	PUBLIC	_mensajes_ordenador_t
	EXTERN	_ACCNextWord
	EXTERN	_CNDnotcarr
	EXTERN	_ACCanykey
	EXTERN	_ACCautog
	EXTERN	_ACCinven
	EXTERN	_ACCautod
	EXTERN	_ACCscore
	EXTERN	_ACCturns
	PUBLIC	_main
	EXTERN	_clear_screen
	EXTERN	_getKey
	EXTERN	_waitForAnyKey
	EXTERN	_ACCability


; --- End of Scope Defns ---


; --- End of Compilation ---
