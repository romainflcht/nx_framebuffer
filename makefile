# _ FILES ______________________________________________________________________
TARGET        = main
ELF_NAME      = nx_framebuffer
NRO_NAME      = $(ELF_NAME)

ROMFS_NAME    = romfs.img


# _ DIRECTORIES ________________________________________________________________
SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes
LIBS_DIR = libs
BIN_DIR  = bin

ROMFS_DIR = romfs

# _ FILES ______________________________________________________________________
SRCS = main.c font.c framebuffer.c graphic.c input.c timer.c
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))


# _ COMPILER OPT _______________________________________________________________
ARCH          = -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
LIBS          = -lnx -lcbmp

CC            = aarch64-none-elf-gcc

COMPILE_FLAGS = -I$(INCS_DIR)                            \
                -I$(DEVKITPRO)/libnx/include             \
                -I$(DEVKITPRO)/portlibs/switch/include   \
                -g -Wall -Werror -O2 -ffunction-sections \
                $(ARCH)

LINK_FLAGS    = -L$(DEVKITPRO)/libnx/lib                 \
                -L$(LIBS_DIR)                            \
                -march=armv8-a+crc+crypto                \
                -mtune=cortex-a57                        \
                -specs=$(DEVKITPRO)/libnx/switch.specs   \
                $(LIBS)

# _ FTP ________________________________________________________________________
FTP_URL  := ftp://192.168.1.27
FTP_PORT := 5000


# _ FONT _______________________________________________________________________
RED      = \e[31m
GREEN    = \e[32m
YELLOW   = \e[33m
BLUE     = \e[34m
MAGENTA  = \e[35m
CYAN     = \e[36m
WHITE    = \e[37m

RST      = \e[0m
BOLD     = \e[1m
CLEAR    = \e[2J
CUR_HOME = \e[H


all: $(BIN_DIR)/$(NRO_NAME).nro

# FTP FILE TRANSFERT TO THE NINTENDO SWITCH. 
install : all
	@lftp $(FTP_URL) -p $(FTP_PORT) -e "put $(BIN_DIR)/$(NRO_NAME).nro ; exit"

# ENCAPSULATION PROCEDURE (CONVERT .ELF TO .NRO FILE). 
$(BIN_DIR)/$(NRO_NAME).nro: $(BIN_DIR)/$(ELF_NAME) $(BIN_DIR)/$(ROMFS_NAME)
	@echo "\n$(BLUE)~ENCAPSULATE $(RST)$(BOLD)$<.elf$(RST)$(BLUE) TO NINTENDO SWITCH ROM $(RST)$(BOLD)$@$(RST)"
	@elf2nro $<.elf $@ --romfs=$(BIN_DIR)/$(ROMFS_NAME)
	@echo "$(GREEN)-> FINISHED!$(RST)"

# GENERATE ROMFS IMG TO INCLUDE DURING ENCAPSULATION. 
$(BIN_DIR)/$(ROMFS_NAME): 
	@echo "\n$(BLUE)~GENERATING ROMFS $(RST)$(BOLD)$@$(RST)$(BLUE) FROM $(RST)$(BOLD)$(ROMFS_DIR)$(RST)"
	@build_romfs $(ROMFS_DIR) $(BIN_DIR)/$(ROMFS_NAME)

# LINKING ALL OBJECTS FILE FROM OBJS DIRECTORY. 
$(BIN_DIR)/$(ELF_NAME): $(OBJS) | mkdir_bin
	@echo "\n$(RED)--SOURCES FILE FOUND : $(RST)$(BOLD)$(SRCS)$(RST)"
	@echo "$(YELLOW)--OBJECTS FILE FOUND : $(RST)$(BOLD)$(OBJS)$(RST)"
	@echo "\n$(CYAN)~LINKING $(RST)$(BOLD)$<$(RST)$(CYAN) TO EXECUTABLE TARGET $(RST)$(BOLD)$@$(RST)"
	@$(CC) $^ -o $@.elf $(COMPILE_FLAGS) $(LINK_FLAGS)
	@echo "$(GREEN)-> FINISHED!$(RST)"

# COMPILING SOURCES FROM SRCS DIRECTORY. 
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | mkdir_obj
	@echo "$(MAGENTA)~COMPILING $(RST)$(BOLD)$<$(RST)$(MAGENTA) TO $(RST)$(BOLD)$@$(RST)"
	@$(CC) -c $< -o $@ $(COMPILE_FLAGS)

# COMPILING SOURCES FROM MAIN DIRECTORY. 
$(OBJS_DIR)/$(TARGET).o: $(TARGET).c | mkdir_obj
	@echo "$(MAGENTA)~COMPILING $(WHITE)$(BOLD)$<$(RST)$(MAGENTA) TO $(RST)$(BOLD)$@$(RST)"
	@$(CC) -c $< -o $@ $(COMPILE_FLAGS)

mkdir_obj: 
	@mkdir -p $(OBJS_DIR)

mkdir_bin: 
	@mkdir -p $(BIN_DIR)

clean:
	@echo "$(BOLD)$(RED)~ CLEANING BIN DIRECTORY... ~"
	@rm -f $(BIN_DIR)/*.elf $(BIN_DIR)/*.nro $(BIN_DIR)/*.img 
	@echo "$(BOLD)$(GREEN)~ DONE ~"

	@echo "$(BOLD)$(RED)~ CLEANING OBJS DIRECTORY... ~"
	@rm -rf $(OBJS_DIR)
	@echo "$(BOLD)$(GREEN)~ DONE ~"

.PHONY: all clean mkdir_obj mkdir_bin 