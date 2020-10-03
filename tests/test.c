#include <stdio.h>

#include <stdint.h>

#define pnk_lengthof(x) (sizeof x / sizeof *x)
#define pnk_range(x) ((struct Range){ x, x + pnk_lengthof(x) - 1})
#define pnk_to_range(b, e) ((struct Range){ b, e })

#define pnk_range_foreach(T, it, element, range)                             \
    for (T const* it = range.cbegin; it != range.cend; ++it) {               \
        T element = *it;
#define pnk_endforeach }

int main(int argc, char** argv)
{
    uint8_t tape[30000] = {};
    uint8_t* tape_iterator = tape;
    char const program[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    pnk_bf_interpret(program, &tape_iterator);
    return 0;
}

