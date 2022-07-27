all:
	clang-11 maze.c -o maze
	clang-11 -DKLEE -emit-llvm -c maze.c

clean:
	rm -rf maze maze.bc klee-*

# clang-11 -DKLEE -emit-llvm -c -g -O1 -Xclang -disable-llvm-passes maze.c
# clang-11 -DKLEE -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone maze.c
# clang-11 maze.c -lkleeRuntest -o maze_replay
# ssssddddwwaawwddddssssddwwww