#include <stdio.h>	
#include <assert.h>
#include "bsp.h"	

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

#define ASM32(instr, val1, val2, val3, msg) ({ \
    int32_t y = val1, z = val2, res = val3, x;\
    asm volatile (instr : "=r" (x) \
       : "r" (y), "r" (z) \
    ); \
    printf("%s %X, %X, %X\n", msg, x, y, z); \
    printf("\t%d=%d, %d, %d\n", x, res, y, z); \
    assert(res == x); \
})

#define ASM64(instr, val1, val2, val3, msg) ({ \
    int64_t y = val1, z = val2, res = val3, x;\
    asm volatile (instr : "=r" (x) \
       : "r" (y), "r" (z) \
    ); \
    printf("%s %lX, %lX, %lX\n", msg, x, y, z); \
    printf("\t%ld, %ld, %ld\n", x, y, z); \
    assert(res == x); \
})

void fnAdd64(int64_t y, int64_t z, int64_t res)
{
    int64_t x, q;
    asm volatile ("\
        add %1, %2, %3; \
        beq %1, %4, pass; \
        addi %0, x0, 20; \
        jal done; \
        pass: addi %0, x0, 10; \
        done: nop;"
       : "=r" (x), "=r" (q)
       : "r" (y), "r" (z), "r" (res)
    );
    printf("add64 %lX, %lX, %lX\n", q, y, z);
    printf("      %ld, %ld, %ld\n", q, y, z);
    assert(x == 10);
}

void add32() {
    printf("\n== ADD32\n");
    ASM32(ADD, 1, 2, 3, "add");
    ASM32(ADD, 0, 2, 2, "add");
    ASM32(ADD, -1, 5, 4, "add");
    ASM32(ADD, -1, -2, -3, "add");
    ASM32(ADD, -1, 0, -1, "add");
    ASM32(ADD, 0xFFFF, 1, 0x10000, "add");
    ASM32(ADD, 0x7FFFFFFF, 2, 0x80000001, "add");
}

void add64() {
    printf("\n== ADD64\n");
    ASM64(ADD, 1, 2, 3, "add");
    ASM64(ADD, 0, 2, 2, "add");
    ASM64(ADD, -1, 5, 4, "add");
    ASM64(ADD, -1, -2, -3, "add");
    ASM64(ADD, -1, 0, -1, "add");
    ASM64(ADD, 0xFFFF, 1, 0x10000, "add");
    ASM64(ADD, 0x7FFFFFFF, 2, 0x80000001, "add");
}

void mul32() {
    printf("\n== MUL32\n");
    ASM32(MUL, 10, 20, 200, "mul");
    ASM32(MUL, -10, 20, -200, "mul");
    ASM32(MUL, 10, -20, -200, "mul");
    ASM32(MUL, -10, -20, 200, "mul");
    ASM32(MUL, -10, 0, 0, "mul");
    ASM32(MUL, 0, 20, 0, "mul");
    ASM32(MUL, 0x80000000, -1, 0x80000000, "mul");
    ASM32(MUL, 0x80000000, 1, 0x80000000, "mul");
    ASM32(MUL, 0x80000000, -10, 0, "mul");
    ASM32(MUL, 0x80000000, 10, 0, "mul");
    ASM32(MUL, 0x7FFFFFFF, 10, -10, "mul");
    ASM32(MUL, 0x7FFFFFFF, -10, 10, "mul");
    ASM32(MUL, 0x7FFFFFFF, 0x80000000, 0x80000000, "mul");
    ASM32(MUL, 0x7FFFFFFF, 0x7FFFFFFF, 1, "mul");
    ASM32(MUL, 0x80000000, 0x80000000, 0, "mul");
}

void mulh32() {
    printf("\n== MULH32\n");
}

void mulhu32() {
    printf("\n== MULHU32\n");
}

void mulhsu32() {
    printf("\n== MULHSU32\n");
}

void mul64() {
    printf("\n== MUL64\n");
    ASM32(MUL, 10, 20, 200, "mul");
}

void mulw64() {
    printf("\n== MULW64\n");
}

void mulh64() {
    printf("\n== MULH64\n");
}

void mulhu64() {
    printf("\n== MULHU64\n");
}

void mulhsu64() {
    printf("\n== MULHSU64\n");
}

void div32() {
    printf("\n== DIV32\n");
    ASM32(DIV, 4, 2, 2, "div");
    ASM32(DIV, 5, 2, 2, "div");
    ASM32(DIV, 6, 2, 3, "div");
    ASM32(DIV, 15, 4, 3, "div");
    ASM32(DIV, 1, 3, 0, "div");
    ASM32(DIV, -1, 3, 0, "div");
    ASM32(DIV, 1, -3, 0, "div");
    ASM32(DIV, 4, -2, -2, "div");
    ASM32(DIV, -4, 2, -2, "div");
    ASM32(DIV, -4, 2, -2, "div");
    ASM32(DIV, -4, -2, 2, "div");
    ASM32(DIV, 0, 2, 0, "div");
    ASM32(DIV, 2, 0, -1, "div");
    int32_t minSigned = 0x80000000;
    ASM32(DIV, minSigned, -1, minSigned, "div");
}

void divu32() {
    printf("\n== DIVU32\n");
}

void div64() {
    printf("\n== DIV64\n");
}

void divu64() {
    printf("\n== DIVU64\n");
}

void divw64() {
    printf("\n== DIVW64\n");
}

void divuw64() {
    printf("\n== DIVUW64\n");
}

void rem32() {
    printf("\n== REM32\n");
}

void remu32() {
    printf("\n== REMU32\n");
}

void rem64() {
    printf("\n== REM64\n");
}

void remu64() {
    printf("\n== REMU64\n");
}

void remw64() {
    printf("\n== REMW64\n");
}

void remuw64() {
    printf("\n== REMUW64\n");
}

int main()	
{	
    uint64_t core = current_coreid();	
    printf("Core %ld Hello world\n\n", core);	

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

    while(1);	
}
