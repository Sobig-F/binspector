program_source = src
compile_dir = out

all: clean
	mkdir $(compile_dir)
	gcc -Wall -Werror -Wextra $(program_source)/main.c -o $(compile_dir)/binspector

clean:
	rm -rf $(compile_dir)