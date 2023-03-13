# Задание 4. Оценка результатов игры в крестики-нолики

---
## `Использовано`

`accumulate` из numeric

---

## `Что нужно сделать`:

Петя и Вася играли в крестики-нолики и не стёрли результаты своей игры. 
Теперь перед вами табличка 3 × 3, которая осталась после их поединка. 
Вы хотите понять, выиграл ли кто-то из них или они не доиграли.

На вход программе даётся три строки, кодирующие верхнюю, среднюю и нижнюю строчки игрового поля. 
Крестик обозначается символом X (английская заглавная буква X), 
нолик — символом O (заглавная английская буква O), 
пустая клетка — точкой.

Если ввод некорректен, то есть такая таблица не могла получиться в ходе настоящей игры, 
то надо написать в ответ слово Incorrect.

Если таблица корректна и выиграли крестики, то нужно вывести в ответ слова Petya won, 
если нолики — Vanya won. Если они не доиграли или сыграли вничью - надо написать Nobody.
