#	Configuaration
CC := gcc
Extension := .c

#	C Source Code
Source := ../SRC

#	Build Folder
Build := ../bin/

#	Build Target
Target := out
Flags := -O2 -g -Wall -Wextra

#	Binary
BinFolder := ../
BinName := c_mandel
Bin := $(BinName).$(Target)
BinPath := $(BinFolder)$(Bin)

#	Loading in file locations
Sources := 									\
	$(wildcard $(Source)**/**$(Extension))	\
	$(wildcard $(Source)*$(Extension))
Objects := 													   	\
	$(patsubst $(Source)%$(Extension), $(Build)%.o, $(Sources))

#	Build Executable Binary
build: $(Objects)
	@echo [INFO] Creating Executable Binary [$(Target)] ...
	@$(CC) -fPIC -o $(BinPath) $^ -lm
	@echo [INFO] [$(Bin)] Created!

$(Build)%.o: $(Source)%$(Extension)
	@echo [CC] $<
	@mkdir -p $(@D)
	@$(CC) -fPIC $< -c -o $@ 	\
		$(Flags)	

#	Reset Build Environment
.PHONEY: clean
clean:
	@rm -rf $(Build)
	@rm -rf $(DEPS)
	@rm $(BinPath)

