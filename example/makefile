
compile: compile-libs
	clang++ -o example ./main.cc -I../include/ -L../ -l:nashalib.a -L../seegul/ -l:seegul.a 

link-output: run
	ld -m elf_i386 -s -o output output.o


disa: link-output
	objdump -d output

compile-libs:
	cd ../seegul && make build-lib

clean:
	rm -rf ./example ./output ./output.o ./temp.out
run: compile
	./example