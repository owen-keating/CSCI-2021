# CSCI 2021 lab Makefile
AN = lab12
CLASS = 2021

# set to -O1 for tuning on login01
CFLAGS = -Wall -Werror -g -O1
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	func_v_macro


all: $(PROGRAMS)

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'
	@echo '  > make test                     # run all automated tests'
	@echo '  > make clean-tests              # remove all test results'

############################################################
# 'make zip' to create zip file for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

################################################################################
# Code targets

func_v_macro.s : func_v_macro.c
	$(CC) -S $<

# optional removal of no-op instruction for old gcc versions
# sed -i 's/endbr64//g' $@

func_v_macro.o : func_v_macro.s
	$(CC) -c $<

func_v_macro : func_v_macro.o matvec_util.o
	$(CC) -o $@ $^

################################################################################
# testing targets
test-setup :
	@chmod u+rx testy test_quiz_filter

test : test-setup $(PROGRAMS)
	./testy test_$(AN).org

test-quiz: test-setup QUESTIONS.txt
	./testy test_$(AN).org 1

test-code : test-setup $(PROGRAMS)
	./testy test_$(AN).org 2

clean:
	rm -f func_v_macro.s *.o $(PROGRAMS)

clean-tests:
	rm -rf test-results/

