#include <stdio.h>
#include <assert.h>

#define ADD    "add   %0, %1, %2"
#define DIV    "div    %0, %1, %2"
#define DIVU   "divu   %0, %1, %2"
#define DIVW   "divw   %0, %1, %2"
#define DIVUW  "divuw  %0, %1, %2"
#define REM    "rem    %0, %1, %2"
#define REMU   "remu   %0, %1, %2"
#define REMW   "remw   %0, %1, %2"
#define REMUW  "remuw  %0, %1, %2"
#define MUL    "mul    %0, %1, %2"
#define MULH   "mulh   %0, %1, %2"
#define MULHSU "mulhsu %0, %1, %2"
#define MULW   "mulw   %0, %1, %2"

#define ASM32(instr, val3, val1, val2, msg) ({ \
    int32_t y = val1, z = val2, res = val3, x;\
    asm volatile (instr : "=r" (x) \
       : "r" (y), "r" (z) \
    ); \
    printf("%s\t%X, %X, %X\n", msg, x, y, z); \
    printf("\t%d=%d, %d, %d\n", x, res, y, z); \
    assert(res == x); \
})

#define ASM64(instr, val3, val1, val2, msg) ({ \
    int64_t y = val1, z = val2, res = val3, x;\
    asm volatile (instr : "=r" (x) \
       : "r" (y), "r" (z) \
    ); \
    printf("%s\t%lX, %lX, %lX\n", msg, x, y, z); \
    printf("\t%ld, %ld, %ld\n", res, y, z); \
    assert(res == x); \
})

void add32() {
    printf("\n== ADD32\n");
    ASM32(ADD, 3, 1, 2, "add");
    ASM32(ADD, 2, 0, 2, "add");
    ASM32(ADD, 4, -1, 5, "add");
    ASM32(ADD, -3, -1, -2, "add");
    ASM32(ADD, -1, -1, 0, "add");
    ASM32(ADD, 0x10000, 0xFFFF, 1, "add");
    ASM32(ADD, 0x80000001, 0x7FFFFFFF, 2, "add");
}

void add64() {
    printf("\n== ADD64\n");
    ASM64(ADD, 3, 1, 2, "add");
    ASM64(ADD, 2, 0, 2, "add");
    ASM64(ADD, 4, -1, 5, "add");
    ASM64(ADD, -3, -1, -2, "add");
    ASM64(ADD, -1, 0, -1, "add");
    ASM64(ADD, 0x1FFFF, 0x10000, 0xFFFF, "add");
    ASM64(ADD, 0x80000001, 0x7FFFFFFF, 2, "add");
}

void mul32() {
    printf("\n== MUL32\n");
    ASM32(MUL, 200, 10, 20, "mul");
    ASM32(MUL, -200, -10, 20, "mul");
    ASM32(MUL, -200, 10, -20, "mul");
    ASM32(MUL, 200, -10, -20, "mul");
    ASM32(MUL, 0, -10, 0, "mul");
    ASM32(MUL, 0, 0, 20, "mul");
    ASM32(MUL, 0x80000000, 0x80000000, -1, "mul");
    ASM32(MUL, 0x80000000, 0x80000000, 1, "mul");
    ASM32(MUL, 0, 0x80000000, -10, "mul");
    ASM32(MUL, 0, 0x80000000, 10, "mul");
    ASM32(MUL, -10, 0x7FFFFFFF, 10, "mul");
    ASM32(MUL, -10, 10, 0x7FFFFFFF, "mul");
    ASM32(MUL, 0x80000000, 0x7FFFFFFF, 0x80000000, "mul");
    ASM32(MUL, 1, 0x7FFFFFFF, 0x7FFFFFFF, "mul");
    ASM32(MUL, 0, 0x80000000, 0x80000000, "mul");

    ASM32(MUL, 0x00001200, 0x00007e00, 0xb6db6db7, "mul");
    ASM32(MUL, 0x00001240, 0x00007fc0, 0xb6db6db7, "mul");
    ASM32(MUL, 0x00000000, 0x00000000, 0x00000000, "mul");
    ASM32(MUL, 0x00000001, 0x00000001, 0x00000001, "mul");
    ASM32(MUL, 0x00000015, 0x00000003, 0x00000007, "mul");
    ASM32(MUL, 0x00000000, 0x00000000, 0xffff8000, "mul");
    ASM32(MUL, 0x00000000, 0x80000000, 0x00000000, "mul");
    ASM32(MUL, 0x00000000, 0x80000000, 0xffff8000, "mul");
    ASM32(MUL, 0x0000ff7f, 0xaaaaaaab, 0x0002fe7d, "mul");
    ASM32(MUL, 0x0000ff7f, 0x0002fe7d, 0xaaaaaaab, "mul");
    ASM32(MUL, 0x00000000, 0xff000000, 0xff000000, "mul");
    ASM32(MUL, 0x00000001, 0xffffffff, 0xffffffff, "mul");
    ASM32(MUL, 0xffffffff, 0xffffffff, 0x00000001, "mul");
    ASM32(MUL, 0xffffffff, 0x00000001, 0xffffffff, "mul");
}

void mulh32() {
    printf("\n== MULH32\n");
    ASM32(MULH, 0x00000000, 0x00000000, 0x00000000, "mulh");
    ASM32(MULH, 0x00000000, 0x00000001, 0x00000001, "mulh");
    ASM32(MULH, 0x00000000, 0x00000003, 0x00000007, "mulh");
    ASM32(MULH, 0x00000000, 0x00000000, 0xffff8000, "mulh");
    ASM32(MULH, 0x00000000, 0x80000000, 0x00000000, "mulh");
    ASM32(MULH, 0x00000000, 0x80000000, 0x00000000, "mulh");
//    ASM32(MULH, 0xffff0081, 0xaaaaaaab, 0x0002fe7d, "mulh");
//    ASM32(MULH,  0xffff0081, 0x0002fe7d, 0xaaaaaaab, "mulh");
//    ASM32(MULH,  0x00010000, 0xff000000, 0xff000000, "mulh");
//    ASM32(MULH,  0x00000000, 0xffffffff, 0xffffffff, "mulh");
//    ASM32(MULH,  0xffffffff, 0xffffffff, 0x00000001, "mulh");
//    ASM32(MULH,  0xffffffff, 0x00000001, 0xffffffff, "mulh");
}

void mulhu32() {
    printf("\n== MULHU32\n");
}

void mulhsu32() {
    printf("\n== MULHSU32\n");
}

void mul64() {
    printf("\n== MUL64\n");
    ASM64(MUL, 200, 10, 20, "mul");
    ASM64(MUL, 0x0000000000001200, 0x0000000000007e00, 0x6db6db6db6db6db7, "mul");
    ASM64(MUL, 0x0000000000001240, 0x0000000000007fc0, 0x6db6db6db6db6db7, "mul");
    ASM64(MUL, 0x00000000, 0x00000000, 0x00000000, "mul");
    ASM64(MUL, 0x00000001, 0x00000001, 0x00000001, "mul");
    ASM64(MUL, 0x00000015, 0x00000003, 0x00000007, "mul");
    ASM64(MUL, 0x0000000000000000, 0x0000000000000000, 0xffffffffffff8000, "mul");
    ASM64(MUL, 0x0000000000000000, 0xffffffff80000000, 0x00000000, "mul");
    ASM64(MUL, 0x0000400000000000, 0xffffffff80000000, 0xffffffffffff8000, "mul");
    ASM64(MUL, 0x000000000000ff7f, 0xaaaaaaaaaaaaaaab, 0x000000000002fe7d, "mul");
    ASM64(MUL, 0x000000000000ff7f, 0x000000000002fe7d, 0xaaaaaaaaaaaaaaab, "mul");
}

void mulw64() {
    printf("\n== MULW64\n");
    ASM64(MULW, 0x00000000, 0x00000000, 0x00000000, "mulw");
    ASM64(MULW, 0x00000001, 0x00000001, 0x00000001, "mulw");
    ASM64(MULW, 0x00000015, 0x00000003, 0x00000007, "mulw");

    ASM64(MULW, 0x0000000000000000, 0x0000000000000000, 0xffffffffffff8000, "mulw");
    ASM64(MULW, 0x0000000000000000, 0xffffffff80000000, 0x00000000, "mulw");
    ASM64(MULW, 0x0000000000000000, 0xffffffff80000000, 0xffffffffffff8000, "mulw");
}

void mulh64() {
    printf("\n== MULH64\n");
    ASM64(MULH, 0x00000000, 0x00000000, 0x00000000, "mulh");
    ASM64(MULH, 0x00000000, 0x00000001, 0x00000001, "mulh");
    ASM64(MULH, 0x00000000, 0x00000003, 0x00000007, "mulh");
    ASM64(MULH, 0x0000000000000000, 0x0000000000000000, 0xffffffffffff8000, "mulh");
    ASM64(MULH, 0x0000000000000000, 0xffffffff80000000, 0x00000000, "mulh");
    ASM64(MULH, 0x0000000000000000, 0xffffffff80000000, 0xffffffffffff8000, "mulh");

}

void mulhu64() {
    printf("\n== MULHU64\n");
}

void mulhsu64() {
    printf("\n== MULHSU64\n");
}

void div32() {
    printf("\n== DIV32\n");
    ASM32(DIV, 2, 4, 2, "div");
    ASM32(DIV, 2, 5, 2, "div");
    ASM32(DIV, 3, 6, 2, "div");
    ASM32(DIV, 3, 15, 4, "div");
    ASM32(DIV, 0, 1, 3, "div");
    ASM32(DIV, 0, -1, 3, "div");
    ASM32(DIV, 0, 1, -3, "div");
    ASM32(DIV, -2, 4, -2, "div");
    ASM32(DIV, -2, -4, 2, "div");
    ASM32(DIV, 2, -4, -2, "div");
    ASM32(DIV, 0, 0, 2, "div");
    ASM32(DIV, -1, 2, 0, "div");
    int32_t minSigned = 0x80000000;
    ASM32(DIV, minSigned, minSigned, -1, "div");

    ASM32(DIV, -1 << 31, -1 << 31, -1, "div");
    ASM32(DIV, -1 << 31, -1 << 31, -1, "div");
    ASM32(DIV, -1, -1 << 31, 0, "div");
    ASM32(DIV, -1, 1, 0, "div");
    ASM32(DIV, -1, 0, 0, "div");
}

void divu32() {
    printf("\n== DIVU32\n");
    ASM32(DIVU, 2, 4, 2, "divu");
    ASM32(DIVU, 2, 5, 2, "divu");
    ASM32(DIVU, 3, 6, 2, "divu");
    ASM32(DIVU, 3, 15, 4, "divu");
    ASM32(DIVU, 0, 1, 3, "divu");
    ASM32(DIVU, 0x55555555, -1, 3, "divu");
    ASM32(DIVU, 0, 1, -3, "divu");
    ASM32(DIVU, 0, 4, -2, "divu");
    ASM32(DIVU, 0xFFFFFFFE, -4, 2, "divu");
    ASM32(DIVU, 0, -4, -2, "divu");
    ASM32(DIVU, 0, 0, 2, "divu");
    int32_t maxUnsigned = 0xFFFFFFFF;
    ASM32(DIVU, maxUnsigned, 2, 0, "divu");
    int32_t minSigned = 0x80000000;
    ASM32(DIVU, -1, minSigned, 0, "divu");
    ASM32(DIVU, -5, -10, 2, "divu");

    ASM32(DIVU, -1 << 31, -1 << 31, 1, "divu");
    ASM32(DIVU, 0, -1 << 31, -1, "divu");
    ASM32(DIVU, -1, -1 << 31, 0, "divu");
}

void div64() {
    printf("\n== DIV64\n");
    ASM64(DIV, 3, 20, 6, "div");
    ASM64(DIV, -3, -20, 6, "div");
    ASM64(DIV, -3, 20, -6, "div");
    ASM64(DIV, 3, -20, -6, "div");
    ASM64(DIV, -1 << 63, -1 << 63, 1, "div");
    ASM64(DIV, -1 << 63, -1 << 63, -1, "div");
    ASM64(DIV, -1, -1 << 63, 0, "div");
    ASM64(DIV, -1, 1, 0, "div");
    ASM64(DIV, -1, 0, 0, "div");
}

void divu64() {
    printf("\n== DIVU64\n");
    ASM64(DIVU, 3, 20, 6, "divu");
    ASM64(DIVU, 3074457345618258599, -20, 6, "divu");
    ASM64(DIVU, 0, 20, -6, "divu");
    ASM64(DIVU, 0, -20, -6, "divu");
    ASM64(DIVU, -1 << 63, -1 << 63, 1, "divu");
    ASM64(DIVU, 0, -1 << 63, -1, "divu");
    ASM64(DIVU, -1, -1 << 63, 0, "divu");
    ASM64(DIVU, -1, 1, 0, "divu");
    ASM64(DIVU, -1, 0, 0, "divu");
}

void divw64() {
    printf("\n== DIVW64\n");
    ASM64(DIVW, 3, 20, 6, "divw");
    ASM64(DIVW, -3, -20, 6, "divw");
    ASM64(DIVW, -3, 20, -6, "divw");
    ASM64(DIVW, 3, -20, -6, "divw");
    ASM64(DIVW, -1 << 31, -1 << 31, 1, "divw");
    ASM64(DIVW, -1 << 31, -1 << 31, -1, "divw");
    ASM64(DIVW, -1, -1 << 31, 0, "divw");
    ASM64(DIVW, -1, 1, 0, "divw");
    ASM64(DIVW, -1, 0, 0, "divw");
}

void divuw64() {
    printf("\n== DIVUW64\n");
    ASM64(DIVUW, 3, 20, 6, "divuw");
    ASM64(DIVUW, 0, 20, -6, "divuw");
    ASM64(DIVUW, 0, -20, -6, "divuw");
    ASM64(DIVUW, -1 << 31, -1 << 31, 1, "divuw");
    ASM64(DIVUW, 0, -1 << 31, -1, "divuw");
    ASM64(DIVUW, -1, -1 << 31, 0, "divuw");
    ASM64(DIVUW, -1, 1, 0, "divuw");
    ASM64(DIVUW, -1, 0, 0, "divuw");
}

void rem32() {
    printf("\n== REM32\n");
    ASM32(REM, 2, 20, 6, "rem");
    ASM32(REM, -2, -20, 6, "rem");
    ASM32(REM, 2, 20, -6, "rem");
    ASM32(REM, -2, -20, -6, "rem");
    ASM32(REM, 0, -1 << 31, 1, "rem");
    ASM32(REM, 0, -1 << 31, -1, "rem");
    ASM32(REM, -1 << 31, -1 << 31, 0, "rem");
    ASM32(REM, 1, 1, 0, "rem");
    ASM32(REM, 0, 0, 0, "rem");
}

void remu32() {
    printf("\n== REMU32\n");
    ASM32(REMU, 2, 20, 6, "remu");
    ASM32(REMU, 2, -20, 6, "remu");
    ASM32(REMU, 20, 20, -6, "remu");
    ASM32(REMU, -20, -20, -6, "remu");
    ASM32(REMU, 0, -1 << 31, 1, "remu");
    ASM32(REMU, -1 << 31, -1 << 31, -1, "remu");
    ASM32(REMU, -1 << 31, -1 << 31, 0, "remu");
    ASM32(REMU, 1, 1, 0, "remu");
    ASM32(REMU, 0, 0, 0, "remu");
}

void rem64() {
    printf("\n== REM64\n");
    ASM64(REM, 2, 20, 6, "rem");
    ASM64(REM, -2, -20, 6, "rem");
    ASM64(REM, 2, 20, -6, "rem");
    ASM64(REM, -2, -20, -6, "rem");
    ASM64(REM, 0, -1 << 63, 1, "rem");
    ASM64(REM, 0, -1 << 63, -1, "rem");
    ASM64(REM, -1 << 63, -1 << 63, 0, "rem");
    ASM64(REM, 1, 1, 0, "rem");
    ASM64(REM, 0, 0, 0, "rem");
}

void remu64() {
    printf("\n== REMU64\n");
    ASM64(REMU, 2, 20, 6, "remu");
    ASM64(REMU, 2, -20, 6, "remu");
    ASM64(REMU, 20, 20, -6, "remu");
    ASM64(REMU, -20, -20, -6, "remu");
    ASM64(REMU, 0, -1 << 63, 1, "remu");
    ASM64(REMU, -1 << 63, -1 << 63, -1, "remu");
    ASM64(REMU, -1 << 63, -1 << 63, 0, "remu");
    ASM64(REMU, 1, 1, 0, "remu");
    ASM64(REMU, 0, 0, 0, "remu");
}

void remw64() {
    printf("\n== REMW64\n");
    ASM64(REMW, 2, 20, 6, "remw");
    ASM64(REMW, -2, -20, 6, "remw");
    ASM64(REMW, 2, 20, -6, "remw");
    ASM64(REMW, -2, -20, -6, "remw");

    ASM64(REMW, 0, -1 << 31, 1, "remw");
    ASM64(REMW, 0, -1 << 31, -1, "remw");

    ASM64(REMW, -1 << 31, -1 << 31, 0, "remw");
    ASM64(REMW, 1, 1, 0, "remw");
    ASM64(REMW, 0, 0, 0, "remw");
    ASM64(REMW, 0xfffffffffffff897, 0xfffffffffffff897, 0, "remw");
}

void remuw64() {
    printf("\n== REMUW64\n");
    ASM64(REMUW, 2, 20, 6, "remuw");
    ASM64(REMUW, 2, -20, 6, "remuw");
    ASM64(REMUW, 20, 20, -6, "remuw");
    ASM64(REMUW, -20, -20, -6, "remuw");
    ASM64(REMUW, 0, -1 << 31, 1, "remuw");
    ASM64(REMUW, -1 << 31, -1 << 31, -1, "remuw");
    ASM64(REMUW, -1 << 31, -1 << 31, 0, "remuw");
    ASM64(REMUW, 1, 1, 0, "remuw");
    ASM64(REMUW, 0, 0, 0, "remuw");
}

int main() {
    printf("RISC-V\n==========================\n");
    add32();
    add64();

    div32();
    divu32();

    rem32();
    remu32();

    div64();
    divu64();
    divw64();
    divuw64();

    rem64();
    remu64();
    remw64();
    remuw64();

    mul32();
    mulh32();
    mulhu32();
    mulhsu32();

    mul64();
    mulw64();
    mulh64();
    mulhu64();
    mulhsu64();

    return 0;
}
