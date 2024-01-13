## QT smart calculator

Implemented in order to study the QT framework, reverse Polish notation.

The calculator implements an application data separation scheme - [MVC](https://developer.mozilla.org/en-US/docs/Glossary/MVC )

Implemented only for linux and macOS systems.

The norms of [Google style c++] have been observed(https://google.github.io/styleguide/cppguide.html )


## model

The model is represented by three files with the extension `cc`:
* [Polish notation](#Polish-notation);
* deposit calculator;
* a credit calculator.


### Polish notation

It is represented as a class `PolishNotation`?, which accepts a string, can return it in the reverse Polish notation and is able to calculate it as a result of `double`

For more detailed documentation, see the [polish_notation_cpp] repository(https://github.com/JoKeRooo7/polish_notation_cpp )

### Credit Calculator

Implemented a class that counts values in accordance with the [credit calculator] website(#https://calcus.ru/kreditnyj-kalkulyator )


### Deposit Calculator 

Implemented a class that counts deposits in **the current year** according to the [Deposit Calculator] website(#https://calcus.ru/kalkulyator-vkladov )


## controller

Implemented as a class `calculator_controller.cc `. It is needed to link the code between the view and the model, it also catches exceptions from `polish_notation.cc `. 


## view

It is represented by inherited classes from the `QT' libraries for processing button signals and displaying information.


## Assembly

The assembly is carried out using the `Makefile`, it is enough to be in this directory and write `make install` in the terminal, it will create a folder `build` and it will contain an application ready to run.
