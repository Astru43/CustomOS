
CC = i686-elf-gcc
CFLAGS = -ffreestanding -g -Wall -Wextra

OBJDIR = build
OBJS = start.o kernel.o vga.o
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

.PHONY: clean


$(OBJDIR)/kernel.bin: $(OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) -nostdlib -T linker.ld $^ -o $@ -lgcc

$(OBJDIR)/%.o: %.s
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@

$(OBJS) : $(OBJDIR)

$(OBJDIR):
	mkdir build

clean:
	rm -r build
