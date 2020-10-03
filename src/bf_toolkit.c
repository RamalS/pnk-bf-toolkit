#include <stdio.h>

#include <pnk/bf_toolkit.h>

void const* pnk_bf_interpret(char            const program[const static 8],
                             unsigned char** const tape_iterator)
{
    void const* end_of_program = program;

    for (char const* it = program; *it != 0; ++it)
    {
        switch (*it)
        {
            case '+': **tape_iterator += 1; break;
            case '-': **tape_iterator -= 1; break;
            case '>': *tape_iterator  += 1; break;
            case '<': *tape_iterator  -= 1; break;
            case '[':
                void const* end_of_loop = it;
                while (**tape_iterator > 0)
                    end_of_loop = pnk_bf_interpret(it + 1, tape_iterator);
                it = end_of_loop;
                break;
            case ']': end_of_program = it; goto leave;
            case '.': putchar(**tape_iterator);       break;
            case ',': **tape_iterator = fgetc(stdin); break;
        }
    }

leave:
    return end_of_program;
}