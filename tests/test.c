#include <stdio.h>
#include <pnk/bf_toolkit.h>

int main(int argc, char** argv)
{
    unsigned char tape[30000] = {};
    unsigned char* tape_iterator = tape;
    char const program[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    pnk_bf_interpret(program, &tape_iterator);
    return 0;
}

