#include <stdio.h>
#include <pnk/bf_toolkit.h>

int main(void)
{
    char const program[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    char unsigned tape[30000] = {};
    char unsigned* tape_iterator = tape;
    pnk_bf_interpret(program, &tape_iterator/* out */);
}

