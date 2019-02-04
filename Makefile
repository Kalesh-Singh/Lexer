%.o:%.cpp
	g++ -c -g -o $@ $^

main: main.o types.o helper.o thompson_vm.o
	g++ -g -o $@ $^

types.o: types.cpp
helper.o: helper.cpp
thompson_vm.o: thompson_vm.cpp
main.o: main.cpp

.PHONY: clean
clean:
	rm *.o
	rm main
