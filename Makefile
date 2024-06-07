kernel_source_files := $(shell find src/impl/kernel -name *.cpp)
kernel_object_files := $(patsubst src/impl/kernel/%.cpp, build/kernel/%.o, $(kernel_source_files))

kernel_asm_source_files := $(shell find src/impl/kernel -name *.asm)
kernel_asm_object_files := $(patsubst src/impl/kernel/%.asm, build/kernel/%.o, $(kernel_asm_source_files))

x86_64_c_source_files := $(shell find src/impl/x86_64 -name *.cpp)
x86_64_c_object_files := $(patsubst src/impl/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/impl/kernel/%.cpp
	mkdir -p $(dir $@) && \
	g++ -c -I src/intf -ffreestanding -fpermissive $(patsubst build/kernel/%.o, src/impl/kernel/%.cpp, $@) -o $@

$(kernel_object_files): build/kernel/%.o : src/impl/kernel/**/*.cpp
	mkdir -p $(dir $@) && \
	g++ -c -I src/intf -ffreestanding -fpermissive $(patsubst build/kernel/%.o, src/impl/kernel/%.cpp, $@) -o $@

$(kernel_asm_object_files): build/kernel/%.o : src/impl/kernel/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/kernel/%.o, src/impl/kernel/%.asm, $@) -o $@

$(x86_64_c_object_files): build/x86_64/%.o : src/impl/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	g++ -c -I src/intf -ffreestanding -fpermissive $(patsubst build/x86_64/%.o, src/impl/x86_64/%.cpp, $@) -o $@

$(x86_64_asm_object_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files) $(kernel_asm_object_files) $(x86_64_asm_object_files)
	mkdir -p dist/x86_64 && \
	ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) $(kernel_asm_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso targets/x86_64/iso
