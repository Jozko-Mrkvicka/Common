function Flash(file)
    % clear ConstData
    clear DataRom
    clear SourceCode
    clear RomCode
    clear BUS_UINT16_T

    % Load constants and definitions (instructions, registers, ...).
    Instructions
    % evalin('base', 'Instructions')
    Definitions
    % evalin('base', 'Definitions')
    CharTable_7x7

    % Load a program to be executed (load variables SourceCode and ConstData from source file).
    run(file);
    % evalin('base', file)

    % Compile source code (assembly language) to binary code and "flash" it to ROM.
    % "Flashing" means to assign the RomCode array to particular constants
    % in the Simulink model (ROM memory).
    [RomCode] = Preprocessor(SourceCode, c.ROM_START, c);
    % assignin('base', 'RomConstData', RomConstData);
    assignin('base', 'RomCode', RomCode);
    assignin('base', 'c', c);
end