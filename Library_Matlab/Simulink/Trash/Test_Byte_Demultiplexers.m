function Test_Byte_Demultiplexers()
	% V1_Address =  [ 0      1];
	% V1_Data =     [57     57];
	% V1_Input =    [0:1; V1_Address; V1_Data];
	% V1_Expected = [ 0 57,
	%                57  0];
	% test('Test_Byte_Demultiplexer_1_to_2',  V1_Input, V1_Expected);


	% V2_Address =  [  0   1   2   3];
	% V2_Data =     [ 57  57  57  57];
	% V2_Input =    [0:3; V2_Address; V2_Data];
	% V2_Expected = [0  0  0 57,
	%                0  0 57  0,
	%                0 57  0  0,
	%                57 0  0  0];
	% test('Test_Byte_Demultiplexer_1_to_4',  V2_Input, V2_Expected);


	% V3_Address =  [ 0  1  2  3  4  5  6  7];
	% V3_Data  =    [57 57 57 57 57 57 57 57];
	% V3_Input =    [0:7; V3_Address; V3_Data];
	% V3_Expected = [ 0  0  0  0  0  0  0 57,
	%                 0  0  0  0  0  0 57  0,
	%                 0  0  0  0  0 57  0  0,
	%                 0  0  0  0 57  0  0  0,
	%                 0  0  0 57  0  0  0  0,
	%                 0  0 57  0  0  0  0  0,
	%                 0 57  0  0  0  0  0  0,
	%                57  0  0  0  0  0  0  0];
	% test('Test_Byte_Demultiplexer_1_to_8',  V3_Input, V3_Expected);


	V4_Address =  [ 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15];
	V4_Data  =    [57 57 57 57 57 57 57 57 57 57 57 57 57 57 57 57];
	V4_Input =    [0:15; V4_Address; V4_Data];
	V4_Expected = [[ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 57];
                   [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0 57  0];
                   [ 0  0  0  0  0  0  0  0  0  0  0  0  0 57  0  0];
                   [ 0  0  0  0  0  0  0  0  0  0  0  0 57  0  0  0];
                   [ 0  0  0  0  0  0  0  0  0  0  0 57  0  0  0  0];
                   [ 0  0  0  0  0  0  0  0  0  0 57  0  0  0  0  0];
                   [ 0  0  0  0  0  0  0  0  0 57  0  0  0  0  0  0];
                   [ 0  0  0  0  0  0  0  0 57  0  0  0  0  0  0  0];
	               [ 0  0  0  0  0  0  0 57  0  0  0  0  0  0  0  0];
	               [ 0  0  0  0  0  0 57  0  0  0  0  0  0  0  0  0];
	               [ 0  0  0  0  0 57  0  0  0  0  0  0  0  0  0  0];
	               [ 0  0  0  0 57  0  0  0  0  0  0  0  0  0  0  0];
	               [ 0  0  0 57  0  0  0  0  0  0  0  0  0  0  0  0];
	               [ 0  0 57  0  0  0  0  0  0  0  0  0  0  0  0  0];
	               [ 0 57  0  0  0  0  0  0  0  0  0  0  0  0  0  0];
	               [57  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]];
	test('Test_Byte_Demultiplexer_1_to_16',  V4_Input, V4_Expected);

end

