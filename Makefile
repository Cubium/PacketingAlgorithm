sources := $(wildcard *.cpp) lodepng/lodepng.cpp
headers := $(wildcard *.hpp)
binary = transfer
debug_flags = -O0 -Wall -Wextra -Werror -lz
check_flags = -Wall -Wextra -Werror -fsyntax-only
release_flags = -Ofast -lz
std = -std=c++11

$(binary): $(sources) $(headers)
	c++ $(debug_flags) $(std) $(sources) -o $(binary)

.Phony: release, debug, run, fmt, edit, clean, check

release: $(sources) $(headers)
	c++ $(release_flags) $(std) $(sources) -o $(binary)

debug: $(sources) $(headers)
	c++ $(debug_flags) $(std) $(sources) -o $(binary)

run: $(binary)
	@ ./$(binary) 

fmt: check
	clang-format -style=WebKit -i $(sources) $(headers)

edit:
	nvim -p $(sources) $(headers) Makefile

clean:
	$(RM) $(binary) $(archive)

check:
	c++ $(check_flags) $(std) $(sources)

$(archive): $(sources) $(headers) Makefile
	zip $(archive) $(sources) $(headers) Makefile input.txt Readme.txt
