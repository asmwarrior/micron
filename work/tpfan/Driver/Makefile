############################################################################### 
# Custom ThinkPad Fan Control Module
# 
# Copyright (C) 2012, Martin Tang
#
# UNDER GENERAL PUBLIC LICENSE VERSION 3
############################################################################### 

# Configurations
INCLUDE=
ASFLAGS=$(INCLUDE)
CCFLAGS=$(INCLUDE)
CXFLAGS=$(INCLUDE)
FCFLAGS=$(INCLUDE)
LDFLAGS=-lhal -lntoskrnl

# Objectives
OBJECTS=DrvMain.o FanCtrl.o ECCtrl.o
TARGETS=..\Binary\tpfan.sys
DEPENDS=$(OBJECTS:.o=.dep) 

# Build Commands
all : $(TARGETS)

$(TARGETS) : $(OBJECTS) 
	@echo [LD] $@
	@gcc -shared -Wl,--subsystem,native -Wl,--entry,_DriverEntry@8 -nostartfiles -nostdlib $(OBJECTS) -o $(TARGETS) $(LDFLAGS)

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
