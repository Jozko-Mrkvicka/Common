function Test_Memory_Blocks()
	Select =   [0 0  0 0  1 1  1 1];
	data =     [0 0  1 1  0 0  1 1];
	Clock =    [1 0  1 0  1 0  1 0];
	Expected = [0 0  0 0  0 0  0 1];
	Input =    [0:7; Select; data; Clock];
	test('Test_Memory_Block_Bit', Input, Expected);


	% SelRaw =   [0 0  1 1  0 0  1 1  0 0  1 1  0 0  1 1  0 0  1 1  0 0  1 1  0 0  1 1  0 0  1 1];
	% SelCol =   [0 0  0 0  1 1  1 1  0 0  0 0  1 1  1 1  0 0  0 0  1 1  1 1  0 0  0 0  1 1  1 1];
	% data =     [0 0  0 0  0 0  0 0  1 1  1 1  1 1  1 1  0 0  0 0  0 0  0 0  1 1  1 1  1 1  1 1];
	% Write =    [0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  1 1  1 1  1 1  1 1  1 1  1 1  1 1  1 1];
	% Clock =    [1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0  1 0];
	% Expected = [0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 0  0 1];
	% Input =    [0:31; SelRaw; SelCol; data; Write; Clock];
	% test('Test_Memory_Block_GBit', Input, Expected);


	Select =   [0 0  1 1  0 0  1 1    0   0    1   1    0   0    1    1];
	Write =    [0 0  0 0  1 1  1 1    0   0    0   0    1   1    1    1];
	data =     [0 0  0 0  0 0  0 0  257 257  257 257  257 257  257  257];
	Clock =    [1 0  1 0  1 0  1 0    1   0    1   0    1   0    1    0];
	Expected = [0 0  0 0  0 0  0 0    0   0    0   0    0   0    0  257];
	Input =    [0:15; Select; Write; data; Clock];
	test('Test_Memory_Block_Word', Input, Expected);


%                           clear             clear                              clear            
	% SelRaw =    [1 1   1 1   1 1   0 0   1 1   1 1       1     1       1     1    1 1       0     0       1     1];
	% SelCol =    [4 4   4 4   0 0   4 4   0 0   0 0       4     4       4     4    0 0       4     4       0     0];
	% BitAccess = [0 0   0 0   0 0   0 0   0 0   0 0       1     1       1     1    0 0       1     1       1     1];
	% Write =     [0 0   1 1   1 1   1 1   1 1   1 1       0     0       1     1    1 1       1     1       1     1];
	% data =      [7 7   7 7   0 0   7 7   7 7   0 0   65535 65535   65535 65535    0 0   65535 65535   65535 65535];
	% Clock =     [1 0   1 0   1 0   1 0   1 0   1 0       1     0       1     0    1 0       1     0       1     0];
	% Expected =  [0 0   0 7   7 0   0 0   0 7   7 0       0     0       0    16   16 0       0     0       0     1];
	% Input =     [0:21; SelRaw; SelCol; BitAccess; Write; data; Clock];
	% test('Test_Memory_Block_Word_VRAM_Data_Out', Input, Expected);


	% SelRaw =    [ 1  1    1  1       1     1    1  1];
	% SelCol =    [ 0  0    5  5       7     7    6  6];
	% BitAccess = [ 0  0    0  0       1     1    1  1];
	% Write =     [ 1  1    0  0       1     1    0  0];
	% data =      [32 32    0  0   65535 65535    0  0];
	% Clock =     [ 1  0    1  0       1     0    1  0];
	% Expected =  [ 0  0    1  1       0     1    0  0];
	% Input =     [0:7; SelRaw; SelCol; BitAccess; Write; data; Clock];
	% test('Test_Memory_Block_Word_VRAM_Get_Pixel', Input, Expected);
end

