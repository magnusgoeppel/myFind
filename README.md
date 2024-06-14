# myFind

The `myfind` program is a custom command-line tool designed for searching files within a specified directory and optionally in its subdirectories. It supports searching for one or more filenames and offers the ability to perform case-insensitive searches as well as recursive searches in subdirectories.

## Features

- Search for one or more filenames in a specified directory.
- Optional recursive search in subdirectories.
- Optional case-insensitive search.

## Dependencies

The program uses standard C++ libraries and requires no external dependencies. It is compatible with Unix-based systems due to the use of system calls such as `fork()`, `opendir()`, `readdir()`, and `closedir()`.

## Compilation

To compile the program, navigate to the directory containing `main.cpp` and execute the following command:

```bash
g++ -o myfind main.cpp
```

This compiles the source code and generates an executable file named `myfind`.

## Execution

To run the program, use the following syntax:

```bash
./myfind [-R] [-i] searchpath filename1 [filename2] … [filenameN]
```

### Options:

- `-R`: Enables recursive mode to search in subdirectories.
- `-i`: Performs a case-insensitive search.

### Arguments:

- `searchpath`: The path where the files should be searched.
- `filename1 [filename2] … [filenameN]`: The names of the files to search for.
