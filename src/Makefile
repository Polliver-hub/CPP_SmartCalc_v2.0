.PHONY: all install uninstall clean dvi dist tests

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17 -lgtest -lgtest_main --coverage
OS = $(shell uname -s)
PROJECT_NAME = SmartCalc
APP = app
BUILD = build
REPORT = report
DOCUMENTATION = documentation
DIST = dist

all: install

install:
	@echo "Installing start..."
	@mkdir -p ../$(BUILD)
	@cmake -B ../$(BUILD)
	@cd ../$(BUILD) && make
	@mkdir -p ../app
ifeq ($(OS), Darwin)
	@mv ../$(BUILD)/$(PROJECT_NAME).app ../$(APP)
else
	@mv ../$(BUILD)/$(PROJECT_NAME) ../$(APP)/$(PROJECT_NAME).app
endif
	@open ../$(APP)/$(PROJECT_NAME).app
	@rm -rf ../$(BUILD)
	@echo "Installing success"

tests:
	@echo "Tests start..."
	@$(CXX) model/*.cc unit_tests/tests.cc -o test $(CXX_FLAGS)
	@./test
	@-mv *.gc* model
	@echo "Tests done"

gcov_report: tests
	@echo "Make report..."
	@mkdir -p $(REPORT)
	@lcov -t ./test -o $(REPORT)/test.info --no-external -c -d model
	@genhtml -o $(REPORT)/report_html $(REPORT)/test.info
	@echo "Report is complete"
	@open $(REPORT)/report_html/index.html

uninstall:
	@echo "Uninstalling start..."
	@rm -rf ../$(APP)
	@echo "Uninstalling success"

dvi:
	@doxygen Doxyfile
	@open ../documentation/html/index.html

dist: clean
	@mkdir -p ../$(DIST)
	tar -cvzf ../$(DIST)/source_code.tar.gz .

style:
	@clang-format -i -style=google $(shell find . \( -name "*.cc" -or -name "*.h" \))

clean:
	@echo "Cleaning..."
	@rm -rf $(REPORT) model/*.gc* test ../$(BUILD)* ../$(DIST) logs ../$(DOCUMENTATION) *user *.gc*
	@echo "Clean is done"
