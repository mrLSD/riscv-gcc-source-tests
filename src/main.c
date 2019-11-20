#include <stdio.h>	
#include <assert.h>
#include "bsp.h"	

#define DIV "div %0, %1, %2"
#define ADD "add %0, %1, %2"

#define ASM32(instr, val1, val2, val3, msg) ({ \
    int32_t y = val1, z = val2, res = val3, x;\
    asm volatile (instr : "=r" (x) \
       : "r" (y), "r" (z) \
    ); \
    printf("%s %X, %X, %X\n", msg, x, y, z); \
    printf("    %d, %d, %d\n", x, y, z); \
    assert(res == x); \
})

void add64(int64_t y, int64_t z, int64_t res)
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
    ASM32(ADD, 1, 2, 3, "add");
    ASM32(ADD, 0, 2, 2, "add");
    ASM32(ADD, -1, 5, 4, "add");
    ASM32(ADD, -1, -2, -3, "add");
    ASM32(ADD, -1, 0, -1, "add");
    ASM32(ADD, 0xFFFF, 1, 0x10000, "add");
    ASM32(ADD, 0x7FFFFFFF, 2, 0x80000001, "add");
}

void div32() {
    printf("\n== DIV\n");
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
}

int main()	
{	
    uint64_t core = current_coreid();	
    printf("Core %ld Hello world\n\n", core);	

    add32();
    add64(1, 2, 3);
    add64(0, 2, 2);
    add64(-1, 5, 4);
    add64(-1, -2, -3);
    add64(-1, 0, -1);
    add64(0xFFFF, 1, 0x10000);
    add64(0x7FFFFFFF, 2, 0x80000001);
    div32();
    while(1);	
}
