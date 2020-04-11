TESTS=test_expression_traits test_is_base_template_of test_list_product


RESULTS=$(patsubst %, %.result, $(TESTS))
OUTS=$(patsubst %, %.out, $(TESTS))
DEPENDS=$(patsubst %, %.d, $(TESTS))

CXXFLAGS=-std=c++17 -W -Wall -g -O2 -I../../ACCBOOST/META -I..


all: $(RESULTS)

clean:
	rm -f $(RESULTS) $(OUTS) $(DEPENDS)

.PRECIOUS: $(OUTS) $(DEPENDS)

-include $(DEPENDS)

%.result: %.out
	valgrind --tool=memcheck --leak-check=full ./$< >$@

%.out: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@
	$(CXX) -MM $< $(CXXFLAGS) | sed 's%^.*\.o%$@%g' >$(patsubst %.out, %.d, $@)
