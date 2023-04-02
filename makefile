all: 
	g++ cpu/cpu.cpp cpu/main.cpp common/stack.cpp common/text.cpp -o cpu.out
	g++ asm/asm.cpp asm/main.cpp common/text.cpp -o asm.out