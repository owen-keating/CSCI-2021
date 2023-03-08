# CSCI 2021 Project 2 Makefile

AN = p2
CLASS = 2021

# -Wno-comment: disable warnings for multi-line comments, present in some tests
CFLAGS = -Wall -Wno-comment -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	batt_main \
	test_batt_update \
	puzzlebox   \


all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make prob1 testnum=5          # run problem 1 test #5 only'
	@echo '  > make test-prob2               # run test for problem 2'
	@echo '  > make test                     # run all tests'


############################################################
# 'make zip' to create p2-code.zip for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

################################################################################
# battery problem
prob1 : batt_main

batt_main : batt_main.o batt_update.o batt_sim.o
	$(CC) -o $@ $^

batt_main.o : batt_main.c batt.h
	$(CC) -c $<

batt_sim.o : batt_sim.c batt.h
	$(CC) -c $<

batt_update.o : batt_update.c batt.h
	$(CC) -c $<

test_batt_update : test_batt_update.o batt_sim.o batt_update.o
	$(CC) -o $@ $^

test_batt_update.o : test_batt_update.c
	$(CC) -c $<

################################################################################
# debugging problem
prob2 : puzzlebox

puzzlebox.o : puzzlebox.c
	$(CC) -c $<

puzzlebox : puzzlebox.o
	$(CC) -o $@ $^

################################################################################
# Testing Targets
test-setup :
	@chmod u+rx testy

test: test-prob1 test-prob2

test-prob1: test-setup prob1 test_batt_update
	./testy test_batt_update.org $(testnum)

test-prob2 : puzzlebox
	./puzzlebox input.txt

clean-tests : 
	rm -rf test-results/ 


