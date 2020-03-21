

SAMPLES=range\
zip_for_iterables zip_for_tuples\
enumerate_for_iterables enumerate_for_tuples\
map_for_iterables map_for_tuples\
reverse_for_iterables reverse_for_tuples\
in_for_initializer_list in_for_iterable in_for_tuple\
all_any_for_initializer_list all_any_for_iterables all_any_for_tuples\
filter_for_iterables\
chain_for_iterable


EXAMPLE=examples.md

EXE=out

EXECUTABLES=$(patsubst %, %.$(EXE), $(SAMPLES))
RESULTS=$(patsubst %, %.result, $(SAMPLES))


all: $(EXAMPLE)

$(EXAMPLE): $(RESULTS)
	echo '## Examples' >$@
	cat $^ >>$@

%.$(EXE): %.cpp
	g++ -std=c++17 -W -Wall -I.. $< -o $@

%.result: %.$(EXE) %.cpp
	echo '### $*' | sed s/_/\ /g >$@
	echo 'Code\n```cpp' >>$@
	cat $*.cpp >>$@
	echo '```' >>$@
	echo 'Result\n```' >>$@
	./$< >>$@
	echo '```' >>$@

clean:
	rm -f $(EXAMPLE) $(RESULTS) $(EXECUTABLES)