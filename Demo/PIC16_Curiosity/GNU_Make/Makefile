# Wang Ge, this is -*- makefile -*-
#---------------------------------------------------------------------------
#  Copyright 2016 Wang Ge
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#---------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# MCU name
MCU = 16F1619

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Target file name (without extension).
TARGET = blinking

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = ./obj

# List EQX Kernel source files here.
EQXINC = ../../../Include \
         ../../../Ports/PIC16
EQXSRC = ../../../Source/eqx.c \
         ../../../Source/event_queue.c \
		 ../../../Source/vtimer.c

# List MCC source files here.
MCCINC = ../MPLABX/mcc_generated_files
MCCSRC = ../MPLABX/mcc_generated_files/adc.c \
		 ../MPLABX/mcc_generated_files/eusart.c \
		 ../MPLABX/mcc_generated_files/interrupt_manager.c \
		 ../MPLABX/mcc_generated_files/mcc.c \
		 ../MPLABX/mcc_generated_files/pin_manager.c \
		 ../MPLABX/mcc_generated_files/tmr0.c

# List C source files here.
INC = ..
SRC = main.c

# List C++ source files here. (C++ dependencies are automatically generated.)
CPPSRC =

# List Assembler source files here.
ASRC =

#============================================================================

# Define programs and commands.
CC = xc8

#============================================================================
all: xcversion

xcversion:
	@$(CC) --ver
