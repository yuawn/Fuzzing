#!/bin/bash

tmux start-server

tmux new-session -d -s fuzzing_session -n Shell1 -d "/bin/bash -i"
tmux send-keys -t fuzzing_session:0 \
    "afl-fuzz -M main -i input -o sync_output -- ./program" ENTER

tmux new-window -t fuzzing_session:1 "/bin/bash -i"
tmux send-keys -t fuzzing_session:1 \
    "afl-fuzz -S fuzzer01 -i input -o sync_output -- ./program_asan" ENTER

tmux new-window -t fuzzing_session:2 "/bin/bash -i"
tmux send-keys -t fuzzing_session:2 \
    "afl-fuzz -S fuzzer02 -i input -o sync_output -- ./program_ubsan" ENTER

tmux new-window -t fuzzing_session:3 "/bin/bash -i"
tmux send-keys -t fuzzing_session:3 \
    "afl-fuzz -S fuzzer03 -i input -o sync_output -c 0 -- ./program_cmplog" ENTER

tmux new-window -t fuzzing_session:4 "/bin/bash -i"
tmux send-keys -t fuzzing_session:4 \
    "afl-fuzz -S fuzzer04 -i input -o sync_output -c 0 -l 2AT -- ./program_cmplog" ENTER

tmux new-window -t fuzzing_session:5 "/bin/bash -i"
tmux send-keys -t fuzzing_session:5 \
    "afl-fuzz -S fuzzer05 -i input -o sync_output -- ./program_laf" ENTER

tmux new-window -t fuzzing_session:6 "/bin/bash -i"
tmux send-keys -t fuzzing_session:6 \
    "afl-fuzz -S fuzzer06 -i input -o sync_output -- ./program_laf" ENTER
