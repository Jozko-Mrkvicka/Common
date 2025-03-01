function Test_Control_Input_Check()
	V1_Select   = [0 1 2 3];
	V1_Input    = [0:3; V1_Select];
	V1_Expected = [0 0 0 1];
	test('Test_Control_Input_Check_2', V1_Input, V1_Expected);

  	V2_Select   = [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15];
	V2_Input    = [0:15; V2_Select];
	V2_Expected = [0 0 0 1 0 1 1 1 0 1  1  1  1  1  1  1];
	test('Test_Control_Input_Check_4', V2_Input, V2_Expected);

    V3_Select   = [0 1 2 4 8 16 32 64 128 5 6 7 9 10 11 12 13 14 15 27 39 44 53 76 81 97 150 185 225 240 255];
    V3_Input    = [0:30; V3_Select];
    V3_Expected = [0 0 0 0 0  0  0  0   0 1 1 1 1  1  1  1  1  1  1  1  1  1  1  1  1  1   1   1   1   1   1];
    test('Test_Control_Input_Check_8', V3_Input, V3_Expected);
end

