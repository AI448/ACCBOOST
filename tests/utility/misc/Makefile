TESTS=test_ReferenceArray test_get test_tuple_size test_tuple_element test_apply

RESULTS=$(patsubst %, %.result, $(TESTS))
OUTS=$(patsubst %, %.out, $(TESTS))
DEPENDS=$(patsubst %, %.d, $(TESTS))

CXXFLAGS=-std=c++17 -W -Wall -g -O2 -I../../../ACCBOOST/utility/misc -I../../


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
