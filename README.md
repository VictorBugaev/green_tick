# Реализация библиотек
## my_math - math.h
## my_string - string.h
## my_cat_and_grep - 
  cat Использование
  `cat [OPTION] [FILE]...` 
  cat Опции
  | № | Опции | Описание |
  | ------ | ------ | ------ |
  | 1 | -b (GNU: --number-nonblank) | нумерует только непустые строки |
  | 2 | -e предполагает и -v (GNU only: -E то же самое, но без применения -v) | также отображает символы конца строки как $  |
  | 3 | -n (GNU: --number) | нумерует все выходные строки |
  | 4 | -s (GNU: --squeeze-blank) | сжимает несколько смежных пустых строк |
  | 5 | -t предполагает и -v (GNU: -T то же самое, но без применения -v) | также отображает табы как ^I |
  
  grep Использование
  `grep [options] template [file_name]`
  grep Опции
  | № | Опции | Описание |
  | ------ | ------ | ------ |
  | 1 | -e | Шаблон |
  | 2 | -i | Игнорирует различия регистра.  |
  | 3 | -v | Инвертирует смысл поиска соответствий. |
  | 4 | -c | Выводит только количество совпадающих строк. |
  | 5 | -l | Выводит только совпадающие файлы.  |
  | 6 | -n | Предваряет каждую строку вывода номером строки из файла ввода. |
  | 7 | -h | Выводит совпадающие строки, не предваряя их именами файлов. |
  | 8 | -s | Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах. |
  | 9 | -f file | Получает регулярные выражения из файла. |
  | 10 | -o | Печатает только совпадающие (непустые) части совпавшей строки. |
  
## my_decimal
Тип Decimal представляет десятичные числа в диапазоне от положительных 79,228,162,514,264,337,593,543,950,335 до отрицательных 79,228,162,514,264,337,593,543,950,335. Значение Decimal по умолчанию равно 0. Decimal подходит для финансовых расчетов, которые требуют большого количества значимых целых и дробных цифр и отсутствия ошибок округления. Этот тип не устраняет необходимость округления. Скорее, сводит к минимуму количество ошибок из-за него.
Когда результат деления и умножения передается методу округления, результат не страдает от потери точности.
Decimal число - это значение с плавающей точкой, состоящее из знака, числового значения, где каждая цифра находится в диапазоне от 0 до 9, и коэффициента масштабирования, который указывает положение десятичной точки, разделяющей целые и дробные части числового значения.
Двоичное представление Decimal состоит из 1-разрядного знака, 96-разрядного целого числа и коэффициента масштабирования, используемого для деления 96-разрядного целого числа и указания того, какая его часть является десятичной дробью. Коэффициент масштабирования неявно равен числу 10, возведенному в степень в диапазоне от 0 до 28. Следовательно, двоичное представление Decimal имеет вид ((от -2^96 до 2^96) / 10^(от 0 до 28)), где -(2^96-1) равно минимальному значению, а 2^96-1 равно максимальному значению.
Коэффициент масштабирования также может сохранять любые конечные нули в Decimal. Эти конечные нули не влияют на значение в арифметических операциях или операциях сравнения.
