TOPTARGETS := all clean
LESSON_FOLDERS=00-fuzzing 01-sanitizer 02-dictionary 03-parallel_fuzzing 04-persistent_mode 05-LLVM_Pass 06-AFLpp_LLVM_Pass_integration 07-KLEE_symbolic_execution

$(TOPTARGETS): $(LESSON_FOLDERS)
$(LESSON_FOLDERS):
	make -C $@ $(MAKECMDGOALS)
	
.PHONY: $(TOPTARGETS) $(LESSON_FOLDERS)