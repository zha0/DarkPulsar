##
## Constructs DarkPulsar
##

CC_X64 := x86_64-w64-mingw32-gcc
CC_X86 := i686-w64-mingw32-gcc
DLLX64 := darkpulsar.x64.dll
DLLX86 := darkpulsar.x86.dll

CFLAGS := -Os -s -shared -Qn -nostdlib -flto
LFLAGS := -Wl,--exclude-all-symbols,--enable-stdcall-fixup
LINKER := -lkernel32

all: $(DLLX64) $(DLLX86)

clean:
	rm -rf $(DLLX64) $(DLLX86)

$(DLLX64):
	$(CC_X64) -o $@ source/*.c $(LFLAGS),-eDllMain $(CFLAGS) $(LINKER)

$(DLLX86):
	$(CC_X86) -o $@ source/*.c $(LFLAGS),-e_DllMain@12 $(CFLAGS) $(LINKER)
