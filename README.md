# Kanban-Board


![Kanban Board](https://user-images.githubusercontent.com/80910359/117806905-366fd980-b25b-11eb-9c1c-1dc3276ca359.png)
*Diagram UML*

Aplikacja została wykonana w ramach zajęć laboratoryjnych *Programowanie w C++*.

Projekt polega na utworzeniu i symulowaniu pracy z organizerem zadań zwanym *Kanban Board* lub też kojarzonym z wyrażeniem „To do – Doing – Done”. `Student` – użytkownik – posiada `Tablicę`, która zawiera poszczególne `Kolumny` wzorowane na *Kanban Board*. Składają się one z obiektów typu `Zadanie`. `Kolumna` jest klasą bazową, a `ToDo`, `Doing` oraz `Done` klasami pochodnymi dziedziczącymi po niej. `Student` ma możliwość dodawania `Zadań` do swojej `Tablicy` wraz z terminami, opisem i ustawieniem przypomnienia. Może także przenosić `Zadania` pomiędzy `Kolumnami` oraz wyeksportować zebrane dane do pliku .csv. Aplikacja posiada funkcję odczytu informacji z pliku. Dane w poszczególnych `kolumnach` są sortowane tak, aby zadania o najkrótszym terminie znajdowały się na samej górze.

Aplikacja wymaga korekt w zakresie pisowni znaków polskich oraz oprogramowania eksportu do pliku dat zakończenia zadań. Również uwzględnianie lat przestępnych wymaga poprawy. Perspektywą dalszego rozwoju aplikacji jest dodanie interfejsu graficznego.
