############################################################################### 
# General Purpose Makefile
# 
# Copyright (C) 2010, Martin Tang
############################################################################### 

# Configurations
INCLUDE=
ASFLAGS=$(INCLUDE) -O2
CCFLAGS=$(INCLUDE) -O2
CXFLAGS=$(INCLUDE) -O2
FCFLAGS=$(INCLUDE) -O2
LDFLAGS=

# Objectives
OBJECTS=CWinApp.o CWnd.o LoadToolbar.o
TARGETS=libwfc.a
DEPENDS=$(OBJECTS:.o=.dep) 

# Build Commands
all : $(TARGETS)

$(TARGETS) : $(OBJECTS) 
	@echo [LD] $@
	@ar cr $@ $^

debug: all
	@echo [DB] $(TARGETS)
	@gdb $(TARGETS)

run: all 
	@echo [EX] $(TARGETS)
	@$(TARGETS)

clean:  
	@echo [RM] $(OBJECTS) $(TARGETS)
	@del $(DEPENDS) $(OBJECTS) $(TARGETS)

# Standard Procedures
%.dep : %.s 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.dep : %.c 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.dep : %.m 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.dep : %.cpp 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.dep : %.f 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.dep : %.rc 
	@cpp $(INCLUDE) -MM -MT $(@:.dep=.o) -o $@ $< 

%.o : %.s 
	@echo [AS] $<
	@as $(ASFLAGS) -o $@ $< 

%.o : %.c 
	@echo [CC] $<
	@gcc $(CCFLAGS) -c -o $@ $< 

%.o : %.m 
	@echo [OC] $<
	@gcc $(CCFLAGS) -c -o $@ $< 

%.o : %.cpp 
	@echo [CX] $<
	@g++ $(CXFLAGS) -c -o $@ $< 

%.o : %.f 
	@echo [FC] $<
	@g77 $(FCFLAGS) -c -o $@ $< 

%.o : %.rc 
	@echo [RC] $<
	@windres $< $@ 

-include $(DEPENDS)
