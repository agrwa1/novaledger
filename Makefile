
run: build
	@./build/main

build:
	@gcc ./main.cpp -o ./build/main
