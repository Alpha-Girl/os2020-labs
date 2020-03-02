ASM_FLAGS= -m32 --pipe -Wall -fasm -g -O1 -fno-stack-protector

multibootHeader.bin: multiboot.S
	gcc -c ${ASM_FLAGS} multiboot.S -o multibootHeader.o
	ld -n -T multibootHeader.ld multibootHeader.o -o multibootHeader.bin

clean:
	rm -rf ./multibootHeader.bin ./multibootHeader.o
