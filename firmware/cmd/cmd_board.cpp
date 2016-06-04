
#include "cmd.h"
#include "board.h"

const int CMD_BOARD_START = 500;

int cmd_board_setup(){
    int i = CMD_BOARD_START;
    cmd_set(i++, "led_on", led_on);
    cmd_set(i++, "led_off", led_off);
    cmd_set(i++, "reset", reset_board);
    return i-CMD_BOARD_START;
}
