FinalExecutable=dist

Compiler_Linux=g++
Compiler_Windows=i686-w64-mingw32-g++
INCLUDED_LIBRARRYS=-lsfml-graphics -lsfml-window -lsfml-system

compile_execute:
	$(Compiler_Linux) *.cpp -o build/$(FinalExecutable) $(INCLUDED_LIBRARRYS)
	build/$(FinalExecutable)

compile:
	$(Compiler_Linux) *.cpp -o build/$(FinalExecutable) $(INCLUDED_LIBRARRYS)

execute:
	build/$(FinalExecutable)
