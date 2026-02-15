TARGET = none

AF=
CC = gcc
# Define the path to the data-structures folder
DS_DIR = ../data-structures
# Add both local and data-structures include folders to the compiler path
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC -I inc -I $(DS_DIR)/inc
LDFLAGS = -L. $(addprefix -l,$(patsubst %.o, %, $(DEPENDENCIES_OBJ))) $(AF) -Wl,-rpath=.

SRC = src/
INC = inc/
TST = test/

ifneq ($(TARGET),none)
# Automatically find the source file whether it is in the local folder or the data-structures folder
DEPENDENCIES = $(shell $(CC) -MM $(wildcard $(SRC)$(TARGET).c $(DS_DIR)/$(SRC)$(TARGET).c) $(CFLAGS))
DEPENDENCIES_SRC = $(shell echo $(subst $(TARGET).o: ,,$(patsubst %.h, %.c,$(subst inc,src,$(DEPENDENCIES)))))
DEPENDENCIES_OBJ = $(shell basename -a $(patsubst %.c, %.o,$(DEPENDENCIES_SRC)))
endif

DEBUG = 1
SUBLIB = 0

.PHONY: clean cleano cleanall release debug all test

ifeq ($(SUBLIB), 0)
$(TARGET).out: lib$(TARGET).so $(TARGET)_test.o
	@$(CC) $(TARGET)_test.o -o $@ $(LDFLAGS)
	@echo $@ Compiled Successfuly!
endif

lib$(TARGET).so: $(DEPENDENCIES_OBJ)
	@$(CC) -shared -o $@ $< $(LDFLAGS)
	@echo $@ Library File Created!
						
$(TARGET).o: 
ifeq ($(DEBUG), 1)
	@$(CC) -c $(wildcard $(SRC)$(TARGET).c $(DS_DIR)/$(SRC)$(TARGET).c) -g $(CFLAGS) 
else
	@$(CC) -c $(wildcard $(SRC)$(TARGET).c $(DS_DIR)/$(SRC)$(TARGET).c) -DNDEBUG -O3 $(CFLAGS) 
endif
	@echo $@ Object File Created!
	
$(TARGET)_test.o: $(TST)$(TARGET)_test.c
	@$(CC) -c $(TST)$(TARGET)_test.c -g $(CFLAGS) 

%.o: 
	@make -s TARGET=$(patsubst %.o,%,$@) SUBLIB=1

cleanall:
	@rm -f *.o *.so *.out
	@echo All files Removed Successfuly!
	
clean:
	@rm -f *.o *.so 
	@echo Object files and libraries Removed Successfuly!

cleano:
	@rm -f *.o 
	@echo All Object files Removed Successfuly!

release: 
	@make -s TARGET=$(TARGET) DEBUG=0

debug: $(TARGET).out

all: release lib$(TARGET).so
	@make -s cleano