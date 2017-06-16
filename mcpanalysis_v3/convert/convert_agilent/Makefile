
BinToASCII:
	gcc -o BinToASCII BinToASCII.c

# combine "sipmt70ch1.text" "sipmt70ch3.text" into outfile   = "sipmt70_1and3.text"
combine:
	time python  combine.py

run:
	time BinToASCII sipmt70ch1.bin sipmt70ch1.text

help:
	@echo make BinToASCII
	@echo example: BinToASCII input.bin output.text
