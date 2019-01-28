FinalExecutable=dist_linux

Compiler_Linux=g++
INCLUDED_LIBRARRYS=-lsfml-graphics -lsfml-window -lsfml-system

compile_execute:
	$(Compiler_Linux) source/*.cpp -o build/$(FinalExecutable) $(INCLUDED_LIBRARRYS)
	build/$(FinalExecutable)

compile:
	$(Compiler_Linux) source/*.cpp -o build/$(FinalExecutable) $(INCLUDED_LIBRARRYS)

execute:
	build/$(FinalExecutable)
