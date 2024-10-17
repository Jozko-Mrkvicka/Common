function Test_Bit_Multiplexers()
	V1_Address =  [0 0 0 0 1 1 1 1];
	V1_Data =     [0 1 2 3 0 1 2 3];
	V1_Input =    [0:7; V1_Address; V1_Data];
	V1_Expected = [0 1 0 1 0 0 1 1];
	test('Test_Bit_Multiplexer_2_to_1',      V1_Input, V1_Expected);
    test('Test_Bit_Multiplexer_2_to_1_NAND', V1_Input, V1_Expected);

	V2_Address =  [0 0 0 0 0 0 0 0 0 0 0  0  0  0  0  0   1 1 1 1 1 1 1 1 1 1 1  1  1  1  1  1   2 2 2 2 2 2 2 2 2 2 2  2  2  2  2  2   3 3 3 3 3 3 3 3 3 3 3  3  3  3  3  3];
	V2_Data =     [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15];
	V2_Input =    [0:63; V2_Address; V2_Data];
	V2_Expected = [0 1 0 1 0 1 0 1 0 1 0  1  0  1  0  1   0 0 1 1 0 0 1 1 0 0 1  1  0  0  1  1   0 0 0 0 1 1 1 1 0 0 0  0  1  1  1  1   0 0 0 0 0 0 0 0 1 1 1  1  1  1  1  1];
	test('Test_Bit_Multiplexer_4_to_1',      V2_Input, V2_Expected);
    test('Test_Bit_Multiplexer_4_to_1_NAND', V2_Input, V2_Expected);

	num = 57;
	val0 = bitand(bitshift(num, -0), 1);
	val1 = bitand(bitshift(num, -1), 1);
	val2 = bitand(bitshift(num, -2), 1);
	val3 = bitand(bitshift(num, -3), 1);
	val4 = bitand(bitshift(num, -4), 1);
	val5 = bitand(bitshift(num, -5), 1);
	val6 = bitand(bitshift(num, -6), 1);
	val7 = bitand(bitshift(num, -7), 1);
	V3_Address =  [0   1   2   3   4   5   6   7];
	V3_Data =     [num num num num num num num num];
	V3_Input =    [0:7; V3_Address; V3_Data];
	V3_Expected = [val0 val1 val2 val3 val4 val5 val6 val7];
	test('Test_Bit_Multiplexer_8_to_1',      V3_Input, V3_Expected);
	test('Test_Bit_Multiplexer_8_to_1_NAND', V3_Input, V3_Expected);

	num = 57;
	val0 =  bitand(bitshift(num, -0),  1);
	val1 =  bitand(bitshift(num, -1),  1);
	val2 =  bitand(bitshift(num, -2),  1);
	val3 =  bitand(bitshift(num, -3),  1);
	val4 =  bitand(bitshift(num, -4),  1);
	val5 =  bitand(bitshift(num, -5),  1);
	val6 =  bitand(bitshift(num, -6),  1);
	val7 =  bitand(bitshift(num, -7),  1);
	val8 =  bitand(bitshift(num, -8),  1);
	val9 =  bitand(bitshift(num, -9),  1);
	val10 = bitand(bitshift(num, -10), 1);
	val11 = bitand(bitshift(num, -11), 1);
	val12 = bitand(bitshift(num, -12), 1);
	val13 = bitand(bitshift(num, -13), 1);
	val14 = bitand(bitshift(num, -14), 1);
	val15 = bitand(bitshift(num, -15), 1);
	V4_Address =  [0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15];
	V4_Data =     [num num num num num num num num num num num num num num num num];
	V4_Input =    [0:15; V4_Address; V4_Data];
	V4_Expected = [val0 val1 val2 val3 val4 val5 val6 val7 val8 val9 val10 val11 val12 val13 val14 val15];
	test('Test_Bit_Multiplexer_16_to_1',      V4_Input, V4_Expected);
    test('Test_Bit_Multiplexer_16_to_1_NAND', V4_Input, V4_Expected);
end

