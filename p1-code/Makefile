# CSCI 2021 Project 1 Makefile
AN = p1
CLASS = 2021

# -Wno-comment: disable warnings for multi-line comments, present in some tests
CFLAGS = -Wall -Wno-comment -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	banlet_main  \
	banlet_demo \
	test_banlet_funcs1 \
	test_banlet_funcs2 \
	treemap_main \
	test_treemap_verify \


all : $(PROGRAMS) 

# cleaning target to remove compiled programs/objects
clean :
	rm -f $(PROGRAMS) *.o

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-prob2               # run test for problem 2'
	@echo '  > make test-prob2 testnum=5     # run problem 2 test #5 only'


############################################################
# 'make zip' to create p1-code.zip for submission
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


# banlet problem
banlet_main : banlet_main.o banlet_funcs.o banlet_font_standard.o
	$(CC) -o $@ $^

banlet_main.o : banlet_main.c banlet.h
	$(CC) -c $<

banlet_funcs.o : banlet_funcs.c banlet.h
	$(CC) -c $<

banlet_font_standard.o : banlet_font_standard.c banlet.h
	$(CC) -c $<

banlet_demo : banlet_demo.c banlet_font_standard.o
	$(CC) -o $@ $^

test_banlet_funcs1 : test_banlet_funcs1.c banlet_funcs.o banlet_font_standard.o
	$(CC) -o $@ $^

test_banlet_funcs2 : test_banlet_funcs2.c banlet_funcs.o banlet_font_standard.o
	$(CC) -o $@ $^

# treemap problem
treemap_main : treemap_main.o treemap_funcs.o
	$(CC) -o $@ $^

treemap_main.o : treemap_main.c treemap.h
	$(CC) -c $<

treemap_funcs.o : treemap_funcs.c treemap.h
	$(CC) -c $<

test_treemap_verify : test_treemap_verify.c treemap.h
	$(CC) -o $@ $<

# problem targets
prob1 : banlet_funcs.o

prob2 : banlet_main

prob3 : treemap_main test_treemap_verify

# Testing Targets
test : test-prob1 test-prob2 test-prob3

test-prob1 : test_banlet_funcs1
	@chmod u+x testy
	./testy test_banlet1.org $(testnum)

test-prob2 : test_banlet_funcs2 banlet_main
	@chmod u+x testy
	./testy test_banlet2.org $(testnum)

test-prob3 : prob3
	@chmod u+x testy
	./testy test_treemap.org $(testnum) 

clean-tests :
	rm -rf test-results

