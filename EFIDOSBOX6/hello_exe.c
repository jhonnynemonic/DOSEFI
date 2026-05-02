#pragma aux print_msg = \
    "mov ah,09h" \
    "int 21h" \
    parm [dx];

void print_msg(const char *msg);

int main() {
    print_msg("HOLA DESDE EXE$");
    return 0;
}
