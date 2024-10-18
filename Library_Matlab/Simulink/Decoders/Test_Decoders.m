function Test_Decoders()
	Input_V1 =    [0:3; 0 1 2 3];
	Expected_V1 = [     1 2 4 8];
	test('Test_Decoder_2_to_4',  Input_V1, Expected_V1);

	Input_V2 =    [0:7; 0 1 2 3  4  5  6   7];
	Expected_V2 = [     1 2 4 8 16 32 64 128];
	test('Test_Decoder_3_to_8',  Input_V2, Expected_V2);

	Input_V3 =    [0:15; 0 1 2 3  4  5  6   7   8   9   10   11   12   13    14    15];
	Expected_V3 = [      1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768];
	test('Test_Decoder_4_to_16', Input_V3, Expected_V3);

	Input_V4 =    [0:31; 0 1 2 3  4  5  6   7   8   9   10   11   12   13    14    15    16     17     18     19      20      21      22      23       24       25       26        27        28        29         30         31];
	Expected_V4 = [      1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608 16777216 33554432 67108864 134217728 268435456 536870912 1073741824 2147483648];
	test('Test_Decoder_5_to_32', Input_V4, Expected_V4);
end
