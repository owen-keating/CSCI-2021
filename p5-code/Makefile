# CSCI 2021 Project 5 Makefile
AN = p5
CLASS = 2021

# url and files for sanity checks
URL = https://www-users.cse.umn.edu/~kauffman/2021
CHECK_FILES = test_findfunc.org testy

CFLAGS = -Wall -Werror -g -Og -Wno-unused-result  -Wno-unused-variable
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	findfunc


all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o vgcore.* a.out

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make test-prob1 testnum=5     # run problem 1 test #5 only'
	@echo '  > make test                     # run all tests'
	@echo '  > make sanity-check             # check that provided files are up to date / unmodified'
	@echo '  > make sanity-restore           # restore provided files to current norms'

############################################################
# 'make zip' to create project zip for submission
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

############################################################
# findfunc problem
findfunc : findfunc.c
	$(CC) -o $@ $^

############################################################
# TESTING TARGETS
test-setup :
	@chmod u+rx testy

test: findfunc test-setup
	./testy test_findfunc.org $(testnum)

clean-tests : clean
	rm -rf test-results


