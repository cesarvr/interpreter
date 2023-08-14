# Writing A Simple Interpreter In C++

Just learning about langauge theory and implementation by following the steps of the ["Crafting Interpreters"](https://craftinginterpreters.com/) book. 



## Tests

In order to make this easier I just following a test driven approach that can be followed [here](https://github.com/cesarvr/interpreter/tree/main/tests). To run them just get `cmake` using: 

```sh 
 brew install cmake

```

And run: 

```sh

cmake . # On the root folder.
```

Then run make:

```sh 
make   
```

I'm using the [catch2 test framwork](https://github.com/catchorg/Catch2) to generate a test binary that you can run using: 

```sh 
./lox_test
``` 

