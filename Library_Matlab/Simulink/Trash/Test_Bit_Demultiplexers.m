function Test_Bit_Demultiplexers()
	% V1_Address =  [0 1 0 1];
	% V1_Data =     [0 0 1 1];
	% V1_Input =    [0:3; V1_Address; V1_Data];
	% V1_Expected = [0 0 1 2];
	% test('Test_Bit_Demultiplexer_1_to_2',  V1_Input, V1_Expected);

	% V2_Address =  [0 1 2 3 0 1 2 3];
	% V2_Data =     [0 0 0 0 1 1 1 1];
	% V2_Input =    [0:7; V2_Address; V2_Data];
	% V2_Expected = [0 0 0 0 1 2 4 8];
	% test('Test_Bit_Demultiplexer_1_to_4',  V2_Input, V2_Expected);

	% V3_Address =  [0 1 2 3 4 5 6 7 0 1 2 3 4  5  6  7];
	% V3_Data =     [0 0 0 0 0 0 0 0 1 1 1 1 1  1  1  1];
	% V3_Input =    [0:15; V3_Address; V3_Data];
	% V3_Expected = [0 0 0 0 0 0 0 0 1 2 4 8 16 32 64 128];
	% test('Test_Bit_Demultiplexer_1_to_8',  V3_Input, V3_Expected);

	V4_Address =  [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 1 2 3 4  5  6  7   8   9   10   11   12   13   14    15];
	V4_Data =     [0 0 0 0 0 0 0 0 0 0 0  0  0  0  0  0  1 1 1 1 1  1  1  1   1   1   1    1    1    1    1     1 ];
	V4_Input =    [0:31; V4_Address; V4_Data];
	V4_Expected = [0 0 0 0 0 0 0 0 0 0 0  0  0  0  0  0  1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768];
	test('Test_Bit_Demultiplexer_1_to_16', V4_Input, V4_Expected);
end

