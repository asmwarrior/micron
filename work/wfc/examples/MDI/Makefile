############################################################################### 
# General Purpose Makefile
# 
# Copyright (C) 2010, Martin Tang
############################################################################### 

# Configurations
INCLUDE=-I.
ASFLAGS=$(INCLUDE) -g
CCFLAGS=$(INCLUDE) -g
CXFLAGS=$(INCLUDE) -g
FCFLAGS=$(INCLUDE) -g
LDFLAGS=-mwindows -lwfc -lgdi32 -lcomctl32

# Objectives
OBJECTS=Application\CMDIApp.o \
				MainFrame\CMainFrame.o \
				MainFrame\CAboutDlg.o \
				ChildWnd\CChildWnd.o \
				Resources\Resource.o
TARGETS=MDIApp.exe
DEPENDS=$(OBJECTS:.o=.dep) 

# Build Commands
all : $(TARGETS)

$(TARGETS) : $(OBJECTS) 
	@echo [LD] $@
	@g++ -o $@ $^ $(LDFLAGS)

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
