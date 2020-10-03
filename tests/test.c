#include <stdio.h>
#include <uchar.h>
#include <wchar.h>

#define pnk_lengthof(x) (sizeof x / sizeof *x)
#define pnk_range(x) ((struct Range){ x, x + pnk_lengthof(x) - 1})                                                                       \

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

static char32_t const*
pnk_bf_while(struct Range const r, /* out */unsigned char** const pointer_ref)
{
    char32_t const* loop_end = r.cbegin;

    while (**pointer_ref != 0)
    {
        pnk_range_foreach(char32_t, it, current, r)
        {
            switch (current)
            {
                case '+': **pointer_ref += 1; break;
                case '-': **pointer_ref -= 1; break;
                case '>': *pointer_ref  += 1; break;
                case '<': *pointer_ref  -= 1; break;
                case '[':
                    it = pnk_bf_while(
                        (struct Range){ it + 1, r.cend },
                        pointer_ref
                    );
                    break;
                case ']':
                    loop_end = it;
                    goto leave_foreach;
                case '.': putchar(**pointer_ref);       break;
                case ',': **pointer_ref = fgetc(stdin); break;
            }
        }
        pnk_endforeach

        leave_foreach: ;
    }

    return loop_end;
}

static unsigned char
pnk_bf_interpret(struct Range r)
{
    static unsigned char program_tape[30000] = {};
    unsigned char* pointer = program_tape;

    pnk_range_foreach(char32_t, it, current, r)
    {
        switch (current)
        {
            case '+': *pointer += 1; break;
            case '-': *pointer -= 1; break;
            case '>': pointer += 1;  break;
            case '<': pointer -= 1;  break;
            case '[':
                it = pnk_bf_while(
                    (struct Range){ it + 1, r.cend },
                    &pointer
                );
                break;
            case '.': putchar(*pointer);       break;
            case ',': *pointer = fgetc(stdin); break;
        }
    }
    pnk_endforeach

    return *pointer;
}

int main(int argc, char** argv)
{
    char32_t const program[] = U"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    int result = pnk_bf_interpret(pnk_range(program));
    return 0;
}

