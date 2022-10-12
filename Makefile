run:
	@gcc index.c && ./a.out

read:
	@gcc index.c && ./a.out print

clean-debug:
	@rm debug.txt

debug:
	@cat debug.txt