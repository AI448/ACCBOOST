TESTS=test_zip test_enumerate test_range test_map test_reverse test_chain test_chain_from_iterable

RESULTS=$(patsubst %, %.result, $(TESTS))
OUTS=$(patsubst %, %.out, $(TESTS))
DEPENDS=$(patsubst %, %.d, $(TESTS))

CXXFLAGS=-std=c++17 -W -Wall -g -O2 -I../../../ACCBOOST/utility/range -I../..


all: $(RESULTS)

clean:
	rm -f $(RESULTS) $(OUTS) $(DEPENDS)

.PRECIOUS: $(OUTS) $(DEPENDS)

-include $(DEPENDS)

%.result: %.out
	valgrind --tool=memcheck --leak-check=full ./$< >$@
	cat $@

%.out: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@
	$(CXX) -MM $< $(CXXFLAGS) | sed 's%^.*\.o%$@%g' >$(patsubst %.out, %.d, $@)
