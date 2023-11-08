# Writing A Simple Lox Interpreter In C++

Just learning about programming language theory and implementation by following the steps of the ["Crafting Interpreters"](https://craftinginterpreters.com/) book. 



## Tests

In order to make this easier I just following a test driven approach [here](https://github.com/cesarvr/interpreter/tree/main/tests). 

To build the project and run the test first get `cmake` using: 

```sh 
 brew install cmake

```

And then run ``cmake`` and ``make``: 

```sh

cmake . # On the root folder.
make 
```

I'm using the [catch2 test framwork](https://github.com/catchorg/Catch2) to generate a test binary that you can run using: 

```sh 
./lox_test
``` 

