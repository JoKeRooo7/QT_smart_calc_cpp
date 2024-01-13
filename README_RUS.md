## QT smart calculator

Реализован с целью изучения фреймворка QT, обратной польской нотации.

В калькуляторе реализована схема разделения данных приложения - [MVC](https://developer.mozilla.org/en-US/docs/Glossary/MVC)

Реализован только для linux и macOS систем.

Соблюдены нормы [Google style c++](https://google.github.io/styleguide/cppguide.html)


## model

Модель представлена тремя файлами с расширением `сс`:
* [польской нотацией](#польская-нотация);
* депозитным калькулятором;
* кредитным калькулятором.


### Польская нотация

Представлена в виде класса `PolishNotation`?, которая принимает строку, может вернуть ее в обратнйо польской записи и способна посчитать ее в виде резульата `double`

Для более подробной документации, смотрите репозиторий [polish_notation_cpp](https://github.com/JoKeRooo7/polish_notation_cpp)

### Кредитный калькулятор

Реализован класс, который считает значения в соостветсвии с сайтом [кредитного клаькулятора](#https://calcus.ru/kreditnyj-kalkulyator)


### Депозитный калькулятор 

Реализован класс, который считает в **текущем году** вклады в соответствии с сайтом [Калькулятора вкладов](#https://calcus.ru/kalkulyator-vkladov)


## controller

Реализован в виде класса `calculator_controller.cc`. Нужен для связи кода между view и model, также отлавливает исключения из `polish_notation.cc`. 


## view

Представлен наследуемыми классами из библиотек `QT` для обработки сигналов с кнопок и отображения информации.


## Cборка

Сборка осуществляется с помощью `Makefile`, достоаточно находиться в данной директории и написать `make install` в терминале, он создаст папку `build` и в ней будет находиться готовое для запуска приложение.