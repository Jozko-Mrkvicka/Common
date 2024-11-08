%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Keyboard interrupt system test
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global gDebug
debug = true;

fprintf('Test_IRQ_Keyboard ')
Compile ROM_Test_IRQ_Keyboard_Main
Compile ROM_Test_IRQ_Keyboard_Handler
clear RomCode
Flash(ROM_Test_IRQ_Keyboard_Main,    c.ROM_START)
Flash(ROM_Test_IRQ_Keyboard_Handler, c.IRQ_KEYBOARD)

fprintf('Executing... ')
result = false;
pause('on');

% Release button, start simulation and keep it running for couple of
% cycles. We will end up at the end of the program (address 0x0002) in the infinite
% loop waiting for a keypress.
c.IRQ_Keyboard_Test = 0;
set_param('Computer', 'SimulationCommand', 'start');
set_param('Computer', 'SimulationCommand', 'pause');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');

% Press button for few cycles until program jumps to the keyboard interrupt
% handler.
c.IRQ_Keyboard_Test = 1;
set_param('Computer', 'SimulationCommand', 'update');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');

% Once we are in the handler, release button and wait for program to return
% back to main function.
c.IRQ_Keyboard_Test = 0;
set_param('Computer', 'SimulationCommand', 'update');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');
set_param('Computer', 'SimulationCommand', 'step');

% Stop simulation
set_param('Computer', 'SimulationCommand', 'stop');
c.IRQ_Keyboard_Test = 0;

if ((0xABBA == gp_reg_00) && (0x0002 == program_counter))
    result = true;
end

if ((true == gDebug) || (false == result))
    print_output_values();
end

if (true == result)
    fprintf('Passed\n', result)
else
    fprintf('Failed\n', result)
end
