%.o:%.cpp
	g++ -c -g -o $@ $^

pr01: main.o types.o helper.o thompson_vm.o
	g++ -g -o $@ $^

tests: tests.cpp helper.o types.o
	g++ -g -o $@ $^ -lgtest -lpthread

types.o: types.cpp
helper.o: helper.cpp
thompson_vm.o: thompson_vm.cpp
main.o: main.cpp

.PHONY: clean
clean:
	rm *.o
	rm pr01
	rm tests
