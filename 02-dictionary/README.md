# Lesson 02 - Improve code coverage using dictionary

Add a dictionary
```shell
echo '"ABC"' > dictionary.dict
```

Pass the roadblock
```
afl-fuzz -i input -o output -x dictionary.dict -- ./program
```

Divide and conquer: split comparison statement
```c
#ifndef SPLIT

    if (!strcmp(input, "ABC")) {

        BUG();

#else

    if (input[0] == 'A') {
        if (input[1] == 'B')
             if (input[2] == 'C')
                BUG();

#endif
    }
```

```
afl-fuzz -i input -o output -- ./program_split
```

AFL++ dictionaries
```
AFLplusplus/dictionaries/
/usr/local/share/afl/dictionaries/
```