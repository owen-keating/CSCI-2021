# CSCI 2021 Project 4 Makefile
AN = p4
CLASS = 2021

# url and files for sanity checks
URL = https://www-users.cse.umn.edu/~kauffman/2021
CHECK_FILES = \
	matvec.h matvec_util.c sumdiag_base.c sumdiag_benchmark.c sumdiag_print.c data.c \
	search_funcs.c search.h \
	test_sumdiag.org test_search_benchmark.org testy


CFLAGS = -Wall -Werror -g -Og
# CFLAGS = -Wall -g -O3
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	sumdiag_print \
	sumdiag_benchmark \
	search_benchmark \

all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o vgcore.* 
	rm -rf sanity

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make prob1 testnum=5          # run problem 1 test #5 only'
	@echo '  > make test-prob2               # run test for problem 2'
	@echo '  > make test                     # run all tests'
	@echo '  > make sanity-check             # check that provided files are up to date / unmodified'
	@echo '  > make sanity-restore           # restore provided files to current norms'

############################################################
# 'make zip' to create p2-code.zip for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

################################################################################
# sanity targets
sanity-dir :
	@rm -rf sanity
	@mkdir -p sanity
	@cd sanity && wget -q $(URL)/$(AN)-code.zip && unzip -qq $(AN)-code.zip && mv $(AN)-code/* .

sanity-check : sanity-dir
	@cd sanity; n=0; \
	  for f in $(CHECK_FILES); do diff -q $$f ../$$f; ((n += $$?)); done;  \
	  if ((n>0)); then echo 'ERROR: Stock Files Changed, Run `make sanity-restore` to fix this'; else echo 'Stock Files Sane'; fi

sanity-restore : sanity-dir
	@mkdir -p sanity-backups
	@cd sanity && n=0 && \
	  for f in $(CHECK_FILES); do cp --backup=numbered ../$$f ../sanity-backups; mv $$f ..; done && \
	  echo 'Restored original files, backed up copies in directory sanity-backups'

################################################################################
# build .o files from corresponding .c files
%.o : %.c
	$(CC) -c $<

################################################################################
# Matrix diagonal summing optimization problem
sumdiag_print : sumdiag_print.o matvec_util.o sumdiag_base.o sumdiag_optm.o
	$(CC) -o $@ $^

sumdiag_benchmark : sumdiag_benchmark.o matvec_util.o sumdiag_base.o sumdiag_optm.o
	$(CC) -o $@ $^ -lm

################################################################################
# Search Algorithm Problem
search_benchmark : search_benchmark.o search_funcs.o
	$(CC) -o $@ $^

################################################################################
# Testing Targets
test: test-prob1 test-prob2

test-setup :
	@chmod u+rx testy

test-prob1: sumdiag_benchmark sumdiag_print test-setup
	./testy test_sumdiag.org 

test-prob2: search_benchmark test-setup
	./testy test_search_benchmark.org $(testnum)

clean-tests :
	rm -rf test-results


