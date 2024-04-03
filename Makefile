# Compiler
CC = arm-none-eabi-gcc

# Compiler flags
CFLAGS = -mcpu=cortex-m0 -mthumb -O0 -Wall -fdata-sections -ffunction-sections -g -gdwarf-2
CFLAGS += -DSTM32C031xx  # Define your target microcontroller if needed
CFLAGS += -I./System/Inc -I./Core/Inc  # Include directories for header files

# Linker flags
LDFLAGS = -Wl,--gc-sections  # Garbage collect unused sections

#Header Files
HEADS = -ISystem/Inc/
HEADS += -ICore/Inc/

# Source files
SRCS = $(wildcard *.c)  # Include all C source files in the current directory
SRCS += $(wildcard System/Src/*.c)  # Include additional source files from System/Src
SRCS += $(wildcard Core/Src/*.c)    # Include additional source files from Core/Src

$(info SRCS: $(SRCS))

# Object files directory
OBJDIR = build

# Object files
OBJS = $(patsubst %.c,$(OBJDIR)/%.o, $(notdir $(SRCS)))
$(info OBJS: $(OBJS))

# Output file
TARGET = build/as608_test.elf

# Rule to build the target
$(TARGET):	$(OBJS)
	$(CC) $(OBJS) --specs=nosys.specs $(HEADS) $(CFLAGS) $(LDFLAGS) -o $@

# Rule to compile C source files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Rule to compile C source files
$(OBJDIR)/%.o: System/Src/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: Core/Src/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Rule to create object files directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to clean the build
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: clean
