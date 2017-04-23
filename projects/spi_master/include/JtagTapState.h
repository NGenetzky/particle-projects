#pragma once

enum class JtagTapState {
    //  All test logic is disabled in this controller state enabling the
    //  normal operation of the IC. The TAP controller state machine is
    //  designed so that, no matter what the initial state of the controller
    //  is, the Test-Logic-Reset state can be entered by holding TMS at high
    //  and pulsing TCK five times. This is why the Test Reset (TRST) pin is
    //  optional.
    TEST_LOGIC_RESET = 0x0
    //  In this controller state, the test logic in the IC is active only if
    //  certain instructions are present. For example, if an instruction
    //  activates the self test, then it is executed when the controller
    //  enters this state. The test logic in the IC is idle otherwise.
    ,RUN_TEST_IDLE   = 0x1

    //  This controller state controls whether to enter the Data Path or the
    //  Select-IR-Scan state.
    ,SELECT_DR  = 0x2
    //  This controller state controls whether or not to enter the Instruction
    //  Path. The Controller can return to the Test-Logic-Reset state
    //  otherwise.
    ,SELECT_IR  = 0x3

    //  In this controller state, the shift register bank in the Instruction
    //  Register parallel loads a pattern of fixed values on the rising edge
    //  of TCK. The last two significant bits must always be "01".
    ,CAPTURE_IR  = 0x4
    //  In this controller state, the instruction register gets connected
    //  between TDI and TDO, and the captured pattern gets shifted on each
    //  rising edge of TCK. The instruction available on the TDI pin is also
    //  shifted in to the instruction register.
    ,SHIFT_IR    = 0x5
    //  This controller state controls whether to enter the Pause-IR state or
    //  Update-IR state.
    ,EXIT1_IR    = 0x6
    //  This state allows the shifting of the instruction register to be
    //  temporarily halted.
    ,PAUSE_IR    = 0x7
    //  This controller state controls whether to enter either the Shift-IR
    //  state or Update-IR state.
    ,EXIT2_IR    = 0x8
    //  In this controller state, the instruction in the instruction register
    //  is latched to the latch bank of the Instruction Register on every
    //  falling edge of TCK. This instruction becomes the current instruction
    //  once it is latched.
    ,UPDATE_IR   = 0x9

    //  In this controller state, the data is parallel-loaded into the data
    //  registers selected by the current instruction on the rising edge of
    //  TCK.
    ,CAPTURE_DR  = 0xA
    //  In this controller state, the data register selected by the current
    //  instruction gets connected between TDI and TDO, and the captured
    //  pattern gets shifted on each rising edge of TCK. The data available on
    //  the TDI pin is also shifted in to the data register.
    ,SHIFT_DR    = 0xB
    //  This controller state controls whether to enter the Pause-DR state or
    //  Update-DR state.
    ,EXIT1_DR    = 0xC
    //  This state allows the shifting of the data register to be temporarily
    //  halted.
    ,PAUSE_DR    = 0xD
    //  This controller state controls whether to enter either the Shift-DR
    //  state or Update-DR state.
    ,EXIT2_DR    = 0xE
    //  In this controller state, the data in the data register is latched to
    //  the latch bank of the data Register on every falling edge of TCK. This
    //  data becomes the current data once it is latched.
    ,UPDATE_DR   = 0xF

}; 
