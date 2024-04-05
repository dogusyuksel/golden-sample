MYSTRING = asdasd
MYSUBSTRING = asp

ifneq ($(findstring $(MYSUBSTRING),$(MYSTRING)),$(MYSUBSTRING))
	RESULT = "does not contain"
else
	RESULT = "contain"
endif

all:
	@echo 'RESULT $(RESULT)'

.PHONY:  all
