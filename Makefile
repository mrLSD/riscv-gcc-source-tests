build64:
	@riscv64-unknown-elf-gcc -Wno-shift-count-overflow -o hello src/hello.c
	@/opt/risc/bin/spike pk hello

build32:
	@riscv32-unknown-elf-gcc -Wno-shift-count-overflow -o hello32 src/hello.c
	@/opt/risc/bin/spike --isa=rv32g pk hello32
