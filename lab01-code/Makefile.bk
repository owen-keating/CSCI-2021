# CSCI 2021 lab Makefile
AN=lab01
CLASS=2021

# -Wno-comment: disable warnings for multi-line comments, present in some tests
CFLAGS = -Wall -Wno-comment -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	hello_c \


all : $(PROGRAMS) 

# cleaning target to remove compiled programs/objects
clean :
	rm -f $(PROGRAMS) *.o

clean-tests :
	rm -rf test-results

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make test                     # run all tests'
	@echo '  > make test-quiz                # run tests that verify quiz answers'
	@echo '  > make test-code                # run tests that verify code is correct'


############################################################
# 'make zip' to create zip file for submission
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


################################################################################
# sole program to build
hello_c : hello_c.c
	$(CC) -o $@ $^

################################################################################
# testing targets
test : test-setup hello_c
	./testy test_lab01.org

test-quiz: test-setup QUESTIONS.txt
	./testy test_lab01.org 1

test-code: test-setup hello_c 
	./testy test_lab01.org 2

test-setup:
	@chmod u+x ./testy

