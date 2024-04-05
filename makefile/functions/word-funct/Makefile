MYSTRING = aaa  bsd asd asd asd asd bsd
Nth = $(word 2, $(MYSTRING))
# $(wordlist 2, 3, $(MYSTRING)) where 2 si starting and 3 is ending index
# $(words text) -> Returns the number of words in text. Thus, the last word of text is $(word $(words text),text).

all:
	@echo 'RESULT $(Nth)'

.PHONY:  all
