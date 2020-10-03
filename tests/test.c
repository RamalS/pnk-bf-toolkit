#include <stdio.h>

#include <uchar.h>
#include <stdint.h>

#define pnk_lengthof(x) (sizeof x / sizeof *x)
#define pnk_range(x) ((struct Range){ x, x + pnk_lengthof(x) - 1})
#define pnk_to_range(b, e) ((struct Range){ b, e })

#define pnk_range_foreach(T, it, element, range)                             \
    for (T const* it = range.cbegin; it != range.cend; ++it) {               \
        T element = *it;
#define pnk_endforeach }

struct Range {
    union {
        struct { void const *cbegin, *cend; };
        struct { void       *begin,  *end;  };
    };
};

static void const*
pnk_bf_interpret(struct Range const program,
                 uint8_t**    const tape_iterator /* out */)
{
    void const* end_of_program = program.cbegin;

    pnk_range_foreach(char32_t, iter, current, program)
    {
        switch (current)
        {
            case '+': **tape_iterator += 1; break;
            case '-': **tape_iterator -= 1; break;
            case '>': *tape_iterator  += 1; break;
            case '<': *tape_iterator  -= 1; break;

            case '[':
                void const* end_of_loop = iter;

                while (**tape_iterator != 0)
                {
                    end_of_loop = pnk_bf_interpret(
                        pnk_to_range(iter + 1, program.cend),
                        tape_iterator
                    );
                }

                iter = end_of_loop;
                break;

            case ']':
                end_of_program = iter;
                goto leave_foreach;

            case '.': putchar(**tape_iterator);       break;
            case ',': **tape_iterator = fgetc(stdin); break;
        }
    } pnk_endforeach

    leave_foreach:
        return end_of_program;
}

int main(int argc, char** argv)
{
    uint8_t tape[30000] = {};
    uint8_t* tape_iterator = tape;
    char32_t const program[] = U"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    pnk_bf_interpret(pnk_range(program), &tape_iterator);
    return 0;
}

