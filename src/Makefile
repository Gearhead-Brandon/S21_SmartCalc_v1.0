CC = gcc
FLAGS = #-Wall -Werror -Wextra --std=c11
LIBS = -lcheck -lsubunit -lm -lgcov
FUNC_FILES_C = *.c backend/*.c backend/calculation_functions/*.c frontend/*.c 
FUNC_FILES_C_CALC = backend/calculation_functions/*.c stack.c queue.c backend/init.c
FUNC_FILES_O = *.o
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBNAME = smartcalc_lib.a
GLFLAGS = --coverage
EXCLUDE = --exclude "unit_tests/*" --exclude "backend/init.c" --exclude "queue.c" --exclude "stack.c"
GTKFLAGS = `pkg-config --cflags gtk4`
GTKLIBS = `pkg-config --libs gtk4`

all: install

latex_file = file.tex

# dvi2: $(latex_file)
# 	pdflatex $(latex_file)

peer: 
	make gcov_open

build_object_files_with_gcov:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) $(GTKFLAGS) -c $(FUNC_FILES_C_CALC) $(GTKLIBS)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

build_object_files:
	$(CC) $(FLAGS) $(GTKFLAGS) -c $(FUNC_FILES_C) $(GTKLIBS)

install: build_object_files
	$(CC) $(GTKFLAGS) $(FLAGS) $(FUNC_FILES_O) -o calculator -lm $(GTKLIBS)
	if [ ! -d "~/out" ]; then \
		mkdir out  ; \
		mv calculator out; \
	fi
	make clean
	./out/calculator

uninstall:
	rm -rf out 
	
smartcalc_lib.a:
	$(CC) $(FLAGS)  $(GTKFLAGS) -c $(FUNC_FILES_C_CALC) $(GTKLIBS)
	make build_library
	rm -rf *.o

test: smartcalc_lib.a
	$(CC) unit_tests/polish_notation_test.c -L. $(LIBNAME) $(CHECKFLAGS)  $(GTKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o polish_notation_test $(GTKLIBS)
	$(CC) unit_tests/annuity_type_test.c -L. $(LIBNAME) $(CHECKFLAGS) $(GTKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o annuity_type_test $(GTKLIBS)
	$(CC) unit_tests/differentiated_type_test.c -L. $(LIBNAME)  $(CHECKFLAGS) $(GTKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o differentiated_type_test $(GTKLIBS)
	$(CC) unit_tests/deposit_test.c -L. smartcalc_lib.a $(CHECKFLAGS) $(GTKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o deposit_test $(GTKLIBS)
	make start_tests

start_tests:
	./polish_notation_test
	./annuity_type_test
	./differentiated_type_test
	./deposit_test

gcov_report: build_object_files_with_gcov build_library test
	gcov $(FUNC_FILES_C_CALC) 
	~/.local/bin/gcovr -r . $(EXCLUDE) --html --html-details -o s21_smart_calc.html

gcov_open: 
	make gcov_report
	google-chrome s21_smart_calc.html

dvi:
	google-chrome doc/html/index.html

dist:
	tar -cf calc.tar --directory=out calculator

clean:
	rm -f *.o *.out *.tar
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.a calculator
	rm -f *.info
	rm -f *.html
	rm -f *_test
	rm -f *.css

rebuild:
	make clean
	make

del: clean
	rm -rf *.c *.h unit_tests/*.c frontend/*.c frontend/*.css
	rm -rf backend/*.c backend/calculation_functions/*.c
	rm -rf out/calculator
	rmdir unit_tests frontend backend/calculation_functions backend out