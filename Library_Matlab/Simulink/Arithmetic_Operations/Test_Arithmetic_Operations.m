function Test_Arithmetic_Operations()

	% Test Bit Adder.
	DataIn_2 =   [0 0 1 1 0 0 1 1];                                            % Data A in.
	DataIn_1 =   [0 1 0 1 0 1 0 1];                                            % Data B in.
	DataIn_0 =   [0 0 0 0 1 1 1 1];                                            % Carry in.
	Input    =   [0:7; DataIn_2; DataIn_1; DataIn_0];                          % First vector is a time vector.

	Expected_1 = [0 1 1 0 1 0 0 1];                                            % Expected Data output.
	Expected_0 = [0 0 0 1 0 1 1 1];                                            % Expected Carry output.

	test('Test_Arithmetic_Operation_Bit_Adder_Data_Out',  Input, Expected_1);  % Test Data outputput.
	test('Test_Arithmetic_Operation_Bit_Adder_Carry_Out', Input, Expected_0);  % Test Carry bit outputput.


	% Test Word Adder.
	DataIn_1 =   [0 25 54 65534 65535 65535 65535];                             % Data A in.
	DataIn_0 =   [0  1 36     1     1 65534 65535];                             % Data B in.
	Input    =   [0:6; DataIn_1; DataIn_0];                                     % First vector is a time vector.

	Expected_1 = [0 26 90 65535     0 65533 65534];                             % Expected Data output.
	Expected_0 = [0  0  0     0     1     1     1];                             % Expected Carry output.

	test('Test_Arithmetic_Operation_Word_Adder_Data_Out',  Input, Expected_1);  % Test Data outputput.
	test('Test_Arithmetic_Operation_Word_Adder_Carry_Out', Input, Expected_0);  % Test Carry bit outputput.


	% Test Bit Comparator.
	DataIn_4 =   [0 1 0 1 0 1 0 1 0 1 0 1];                                            % Data A in.
	DataIn_3 =   [0 0 1 1 0 0 1 1 0 0 1 1];                                            % Data B in.
	DataIn_2 =   [1 1 1 1 0 0 0 0 0 0 0 0];                                            % A>B in.
	DataIn_1 =   [0 0 0 0 1 1 1 1 0 0 0 0];                                            % A=B in.
	DataIn_0 =   [0 0 0 0 0 0 0 0 1 1 1 1];                                            % A<B in.
	Input    =   [0:11; DataIn_4; DataIn_3; DataIn_2; DataIn_1; DataIn_0];             % First vector is a time vector.

	Expected_2 = [1 1 0 1 0 1 0 0 0 1 0 0];                                            % Expected A>B output.
	Expected_1 = [0 0 0 0 1 0 0 1 0 0 0 0];                                            % Expected A=B output.
	Expected_0 = [0 0 1 0 0 0 1 0 1 0 1 1];                                            % Expected A<B output.

	test('Test_Arithmetic_Operation_Bit_Comparator_Greater_Than', Input, Expected_2);  % Test A>B output.
	test('Test_Arithmetic_Operation_Bit_Comparator_Equal',        Input, Expected_1);  % Test A=B output.
	test('Test_Arithmetic_Operation_Bit_Comparator_Less_Than',    Input, Expected_0);  % Test A<B output.


	% Test Word Comparator.
	DataIn_1 =   [0 1 0 1 65535 65535     0 65535 65534];                               % Data A in.
	DataIn_0 =   [0 0 1 1     0 65535 65535 65534 65535];                               % Data B in.
	Input    =   [0:8; DataIn_1; DataIn_0];                                             % First vector is a time vector.

    Expected_4 = [0 1 0 0     0     0     1     1     0];                               % Expected (int)A>B output.
    Expected_3 = [0 0 1 0     1     0     0     0     1];                               % Expected (int)A<B output.
	Expected_2 = [0 1 0 0     1     0     0     1     0];                               % Expected (uint)A>B output.
	Expected_1 = [0 0 1 0     0     0     1     0     1];                               % Expected (uint)A<B output.
    Expected_0 = [1 0 0 1     0     1     0     0     0];                               % Expected A=B output.

	test('Test_Arithmetic_Operation_Word_Comparator_Signed_Greater_Than',   Input, Expected_4);  % Test (int)A>B output.
    test('Test_Arithmetic_Operation_Word_Comparator_Signed_Less_Than',      Input, Expected_3);  % Test (int)A<B output.
    test('Test_Arithmetic_Operation_Word_Comparator_Unsigned_Greater_Than', Input, Expected_2);  % Test (uint)A>B output.
	test('Test_Arithmetic_Operation_Word_Comparator_Unsigned_Less_Than',    Input, Expected_1);  % Test (uint)A<B output.
    test('Test_Arithmetic_Operation_Word_Comparator_Equal',                 Input, Expected_0);  % Test A=B output.
end

