function Test_Byte_Multiplexers()
	% Address =  [  0   1];
	% Data1 =    [ 57  57];
	% Data0 =    [206 206];
	% Input =    [0:1; Address; Data1; Data0];
	% Expected = [206  57];
	% test('Test_Byte_Multiplexer_2_to_1', Input, Expected);


	Select =   [  1   2];
	Data1 =    [ 57  57];
	Data0 =    [206 206];
	Input =    [0:1; Select; Data1; Data0];
	Expected = [206  57];
	test('Test_Byte_Multiplexer_2_to_1', Input, Expected);


	% Address =  [  0   1   2   3];
	% Data3 =    [ 57  57  57  57];
	% Data2 =    [206 206 206 206];
	% Data1 =    [128 128 128 128];
	% Data0 =    [ 10  10  10  10];
	% Input =    [0:3; Address; Data3; Data2; Data1; Data0];
	% Expected = [ 10 128 206  57];
	% test('Test_Byte_Multiplexer_4_to_1', Input, Expected);


	Select =   [  1   2   4   8];
	Data3 =    [ 57  57  57  57];
	Data2 =    [206 206 206 206];
	Data1 =    [128 128 128 128];
	Data0 =    [ 10  10  10  10];
	Input =    [0:3; Select; Data3; Data2; Data1; Data0];
	Expected = [ 10 128 206  57];
	test('Test_Byte_Multiplexer_4_to_1', Input, Expected);


	% Address =  [  0   1   2   3   4   5   6   7];
	% Data7 =    [153 153 153 153 153 153 153 153];
	% Data6 =    [232 232 232 232 232 232 232 232];
	% Data5 =    [ 44  44  44  44  44  44  44  44];
	% Data4 =    [105 105 105 105 105 105 105 105];
	% Data3 =    [ 57  57  57  57  57  57  57  57];
	% Data2 =    [206 206 206 206 206 206 206 206];
	% Data1 =    [128 128 128 128 128 128 128 128];
	% Data0 =    [ 10  10  10  10  10  10  10  10];
	% Input =    [0:7; Address; Data7; Data6; Data5; Data4; Data3; Data2; Data1; Data0];
	% Expected = [ 10 128 206  57 105  44 232 153];
	% test('Test_Byte_Multiplexer_8_to_1', Input, Expected);


	Select =   [  1   2   4   8  16  32  64 128];
	Data7 =    [153 153 153 153 153 153 153 153];
	Data6 =    [232 232 232 232 232 232 232 232];
	Data5 =    [ 44  44  44  44  44  44  44  44];
	Data4 =    [105 105 105 105 105 105 105 105];
	Data3 =    [ 57  57  57  57  57  57  57  57];
	Data2 =    [206 206 206 206 206 206 206 206];
	Data1 =    [128 128 128 128 128 128 128 128];
	Data0 =    [ 10  10  10  10  10  10  10  10];
	Input =    [0:7; Select; Data7; Data6; Data5; Data4; Data3; Data2; Data1; Data0];
	Expected = [ 10 128 206  57 105  44 232 153];
	test('Test_Byte_Multiplexer_8_to_1', Input, Expected);
end

