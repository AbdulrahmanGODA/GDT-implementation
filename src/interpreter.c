#include "interpreter.h"
#include "util.h"

char interpreter_buffer[160];
uint32_t interpreter_index = 0;

void interpreter(char c){
    interpreter_buffer[interpreter_index] = c;
    interpreter_index++;
}
char* interpreter_print(){
    return interpreter_buffer+13;
}
void clear_buffer(){
    memorySet(interpreter_buffer, 0, 160);
    interpreter_index = 0;
}