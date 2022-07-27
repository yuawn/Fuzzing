# Lesson 06 - Integrate custom LLVM Pass into AFL++

integration.diff
```diff
diff --git a/GNUmakefile.llvm b/GNUmakefile.llvm
index 685964b7..9f309c08 100644
--- a/GNUmakefile.llvm
+++ b/GNUmakefile.llvm
@@ -308,7 +308,7 @@ ifeq "$(TEST_MMAP)" "1"
 endif
 
 PROGS_ALWAYS = ./afl-cc ./afl-compiler-rt.o ./afl-compiler-rt-32.o ./afl-compiler-rt-64.o 
-PROGS        = $(PROGS_ALWAYS) ./afl-llvm-pass.so ./SanitizerCoveragePCGUARD.so ./split-compares-pass.so ./split-switches-pass.so ./cmplog-routines-pass.so ./cmplog-instructions-pass.so ./cmplog-switches-pass.so ./afl-llvm-dict2file.so ./compare-transform-pass.so ./afl-ld-lto ./afl-llvm-lto-instrumentlist.so ./SanitizerCoverageLTO.so
+PROGS        = $(PROGS_ALWAYS) ./afl-llvm-pass.so ./SanitizerCoveragePCGUARD.so ./split-compares-pass.so ./split-switches-pass.so ./cmplog-routines-pass.so ./cmplog-instructions-pass.so ./cmplog-switches-pass.so ./afl-llvm-dict2file.so ./compare-transform-pass.so ./afl-ld-lto ./afl-llvm-lto-instrumentlist.so ./SanitizerCoverageLTO.so ./afl-demo-pass.so ./afl-demo-rt.o
 
 # If prerequisites are not given, warn, do not build anything, and exit with code 0
 ifeq "$(LLVMVER)" ""
@@ -436,6 +436,9 @@ endif
 afl-llvm-dict2file.so:	instrumentation/afl-llvm-dict2file.so.cc instrumentation/afl-llvm-common.o | test_deps
 	$(CXX) $(CLANG_CPPFL) -shared $< -o $@ $(CLANG_LFL) instrumentation/afl-llvm-common.o
 
+afl-demo-pass.so:	instrumentation/afl-demo-pass.so.cc instrumentation/afl-llvm-common.o | test_deps
+	$(CXX) $(CLANG_CPPFL) -shared $< -o $@ $(CLANG_LFL)
+
 .PHONY: document
 document:
 	$(CLANG_BIN) -D_AFL_DOCUMENT_MUTATIONS $(CFLAGS_SAFE) $(CPPFLAGS) $(CLANG_CFL) -O3 -Wno-unused-result -fPIC -c instrumentation/afl-compiler-rt.o.c -o ./afl-compiler-rt.o
@@ -453,6 +456,9 @@ document:
 	@printf "[*] Building 64-bit variant of the runtime (-m64)... "
 	@$(CC) $(CLANG_CFL) $(CFLAGS_SAFE) $(CPPFLAGS) -O3 -Wno-unused-result -m64 -fPIC -c $< -o $@ 2>/dev/null; if [ "$$?" = "0" ]; then echo "success!"; else echo "failed (that's fine)"; fi
 
+./afl-demo-rt.o: instrumentation/afl-demo-rt.o.c
+	$(CC) $(CLANG_CFL) $(CFLAGS_SAFE) $(CPPFLAGS) -O3 -Wno-unused-result -fPIC -c $< -o $@
+
 .PHONY: test_build
 test_build: $(PROGS)
 	@echo "[*] Testing the CC wrapper and instrumentation output..."
@@ -475,6 +481,7 @@ install: all
 	@if [ -f ./afl-cc ]; then set -e; install -m 755 ./afl-cc $${DESTDIR}$(BIN_PATH); ln -sf afl-cc $${DESTDIR}$(BIN_PATH)/afl-c++; fi
 	@rm -f $${DESTDIR}$(HELPER_PATH)/afl-llvm-rt*.o $${DESTDIR}$(HELPER_PATH)/afl-gcc-rt*.o
 	@if [ -f ./afl-compiler-rt.o ]; then set -e; install -m 755 ./afl-compiler-rt.o $${DESTDIR}$(HELPER_PATH); fi
+	@if [ -f ./afl-demo-rt.o ]; then set -e; install -m 755 ./afl-demo-rt.o $${DESTDIR}$(HELPER_PATH); fi
 	@if [ -f ./afl-lto ]; then set -e; ln -sf afl-cc $${DESTDIR}$(BIN_PATH)/afl-lto; ln -sf afl-cc $${DESTDIR}$(BIN_PATH)/afl-lto++; ln -sf afl-cc $${DESTDIR}$(BIN_PATH)/afl-clang-lto; ln -sf afl-cc $${DESTDIR}$(BIN_PATH)/afl-clang-lto++; install -m 755 ./afl-llvm-rt-lto*.o ./afl-llvm-lto-instrumentlist.so $${DESTDIR}$(HELPER_PATH); fi
 	@if [ -f ./afl-ld-lto ]; then set -e; install -m 755 ./afl-ld-lto $${DESTDIR}$(BIN_PATH); fi
 	@if [ -f ./afl-compiler-rt-32.o ]; then set -e; install -m 755 ./afl-compiler-rt-32.o $${DESTDIR}$(HELPER_PATH); fi
diff --git a/include/envs.h b/include/envs.h
index 25b792fa..bbe9a99e 100644
--- a/include/envs.h
+++ b/include/envs.h
@@ -226,6 +226,7 @@ static char *afl_environment_variables[] = {
     "AFL_USE_QASAN",
     "AFL_PRINT_FILENAMES",
     "AFL_PIZZA_MODE",
+    "AFL_DEMO",
     NULL
 
 };
diff --git a/src/afl-cc.c b/src/afl-cc.c
index 2667ae28..7da0b89c 100644
--- a/src/afl-cc.c
+++ b/src/afl-cc.c
@@ -57,6 +57,7 @@ static u8 * lto_flag = AFL_CLANG_FLTO, *argvnull;
 static u8   debug;
 static u8   cwd[4096];
 static u8   cmplog_mode;
+static u8   demo_mode;
 u8          use_stdin;                                             /* dummy */
 static int  passthrough;
 // static u8 *march_opt = CFLAGS_OPT;
@@ -699,6 +700,23 @@ static void edit_params(u32 argc, char **argv, char **envp) {
 
     }
 
+
+    if (demo_mode) {
+
+#if LLVM_MAJOR >= 11
+      cc_params[cc_par_cnt++] = "-fexperimental-new-pass-manager";
+      cc_params[cc_par_cnt++] = alloc_printf(
+          "-fpass-plugin=%s/afl-demo-pass.so", obj_path);
+#else
+      cc_params[cc_par_cnt++] = "-Xclang";
+      cc_params[cc_par_cnt++] = "-load";
+      cc_params[cc_par_cnt++] = "-Xclang";
+      cc_params[cc_par_cnt++] =
+          alloc_printf("%s/afl-demo-pass.so", obj_path);
+#endif
+
+    }
+
     // cc_params[cc_par_cnt++] = "-Qunused-arguments";
 
     if (lto_mode && argc > 1) {
@@ -1100,6 +1118,9 @@ static void edit_params(u32 argc, char **argv, char **envp) {
         if (lto_mode)
           cc_params[cc_par_cnt++] =
               alloc_printf("%s/afl-llvm-rt-lto.o", obj_path);
+        if (demo_mode)
+          cc_params[cc_par_cnt++] =
+              alloc_printf("%s/afl-demo-rt.o", obj_path);
         break;
 
       case 32:
@@ -2153,6 +2174,8 @@ int main(int argc, char **argv, char **envp) {
   if (!be_quiet && cmplog_mode)
     printf("CmpLog mode by <andreafioraldi@gmail.com>\n");
 
+  demo_mode = !!getenv("AFL_DEMO");
+
 #if !defined(__ANDROID__) && !defined(ANDROID)
   ptr = find_object("afl-compiler-rt.o", argv[0]);
 
```

Fuzz the program
```shell
afl-fuzz -i input -o output -- ./program
```

File input
```shell
afl-clang-lto -w -DFILE program.c -o program_file_input
afl-fuzz -i input -o output -- ./program_file_input @@
```

Build AFL++ with new LLVM Pass
```shell
git clone -b 4.01c --depth 1 https://github.com/AFLplusplus/AFLplusplus.git

git -C AFLplusplus apply ../integration.diff
cp llvm-pass/* AFLplusplus/instrumentation

cd AFLplusplus
make LLVM_CONFIG=llvm-config-14
```

Compile target program with custom instrumentation
```shell
AFL_DEMO=1 ./AFLplusplus/afl-clang-lto -w program.c -o program_custom_instrumented
```

Fuzz
```shell
afl-fuzz -i input -o output -- ./program_custom_instrumented
```