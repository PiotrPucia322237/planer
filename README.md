# Planer

Program zawiera zadania (Task) do wykonania.
Użytkownik może dodawać nowe zadania i zmieniać ich status wykonania.
Jeżeli ilość godzin roboczych pozostałych do terminu wykonania zadania zbliża się do oczekiwanego czasu pracy zadania, program ostrzeże o tym użytkownika.
Użytkownik może również zmienić ilość swoich godzin roboczych oraz zaznaczyć czy pracuje w weekendy.
Przy wywoływaniu programu, użytkownik może podać nazwę pliku w którym mają być przechowywane zadania dla przyszłych wykonań programu.

Zadanie zawiera:

- Nazwę
- status dokonania
- opis (opcjonalnie)
- termin (t_time)
- oczekiwany czas wykonania (w godzinach)

Ustawienia:

- ile godzin dziennie może zostać poświęconych zadaniom (0-24)
- czy użytkownik pracuje w weekendy

Elementy do dodania:

- instrukcja; przykłady
- uwagi, wnioski (np. jak można rozszerzyć program)

## Wzorzec projektowy Singleton

Ze strony [https://refactoring.guru/pl/design-patterns/singleton](https://refactoring.guru/pl/design-patterns/singleton), dostęp 19.01.2026 11:43:

- **Singleton** jest kreacyjnym wzorcem projektowym, który pozwala zapewnić istnienie wyłącznie jednej instancji danej klasy. Ponadto daje globalny punkt dostępowy do tejże instancji.
- Wszystkie implementacje wzorca Singleton współdzielą poniższe dwa etapy:
- - Ograniczenie dostępu do domyślnego konstruktora przez uczynienie go prywatnym, aby zapobiec stosowaniu operatora `new` w stosunku do klasy Singleton.
  - Utworzenie statycznej metody kreacyjnej, która będzie pełniła rolę konstruktora. Za kulisami, metoda ta wywoła prywatny konstruktor, aby utworzyć instancję obiektu i umieści go w polu statycznym klasy. Wszystkie kolejne wywołania tej metody zwrócą już istniejący obiekt.

## Struktura danych

### Klasa Settings (ustawienia)

- instance - statyczny wskaźnik do zmiennej klasy Settings
- workHours - zmienna całkowitoliczbowa mówiąca o tym ile godzin użytkownik pracuje tygodniowo, zaopatrzona metodami getWorkHours() i setWorkHours(int)
- workWeekends - zmienna logiczna prawda/fałsz mówiąca o tym czy użytkownik pracuje w weekendy, zaopatrzona metodami getWorkWeekends() i setWorkWeekends(bool)
- Settings() - **prywatny** konstruktor wczytujący dane z pliku tekstowego settings.babam do aktualnej instancji, lub tworzący go z ustawieniami domyślnymi w przypadku braku tego pliku
- setSettings(int, bool) - metoda ustawiająca zmienne workHours i workWeekends dla aktualnej instancji
- saveSettings() - metoda zapisująca dane aktualnej instancji do pliku tekstowego settings.babam
- getInstance() - **statyczna** metoda, która zwraca zmienną instance, inicjując ją w przypadku jej braku

### Klasa Task (zadanie)

- name - zmienna tekstowa zawierająca nazwę zadania, zaopatrzona metodami getName i setName
- description - zmienna tekstowa zawierająca opis zadania, zaopatrzona metodami getDescription i setDescription
- dueDate - zmienna typu time_t zawierająca termin zadania, zaopatrzona metodami getDueDate i setDueDate
- expectedTime - zmienna zmiennoprzecinkowa zawierająca oczekiwany czas wykonania zadania, zaopatrzona metodami getExpectedTime i setExpectedTime
- isCompleted - zmienna logiczna prawda/fałsz zawierająca status dokonania zadania, zaopatrzona metodami getIsCompleted i setIsCompleted
- Task(std::string, time_t, double, std::string = "", bool = 0) - konstruktor klasy, ustawiający dane aktualnego zadania zależnie od parametrów
- printTask() - metoda robocza wypisująca dane o zadaniu do konsoli
- workHoursLeft() - metoda zwracająca ilość godzin roboczych pozostałych do terminu zakończenia zadania

## Wczytywanie danych

### Ustawienia

- inicjalizacja zmiennej typu std::fstream o nazwie file, z wartościami konstruktora "settings.babam" oraz std::ios::in
- jeżeli file.good() jest prawdą:
  - inicjalizacja zmiennych _workHours oraz _workWeekends
  - wykonanie operacji wczytania ze streamu file do zmiennych kolejno _workHours oraz _workWeekends
  - zamknięcie pliku

### Zadania

- jeżeli został podany argument:

  - inicjalizacja zmiennej typu std::fstream o nazwie file, z wartością konstruktora wczytaną z argumentu wejściowego oraz std::ios::in
  - jeżeli file.good() jest prawdą:

    - inicjalizacja zmiennej tekstowej name
    - pętla pod warunkiem sukcesu operacji czytania linii ze źródła file do zmiennej name:
      - inicjalizacja zmiennych description, dueDate, expectedTime, isCompleted
      - wczytanie linii ze źródła file do zmiennej description
      - wczytanie wartości kolejno do zmiennych dueDate, expectedTime, isCompleted
      - wczytanie linii ze źródła file aby przejść do kolejnej linii
      - stworzenie nowego obiektu klasy Task na podstawie danych name, dueDate, expectedTime, description, isCompleted
      - dodanie tego obiektu do wektora tasks
    - zamknięcie pliku

## Zapis danych

### Ustawienia

- inicjalizacja zmiennej typu std::fstream o nazwie file, z wartościami konstruktora "settings.babam" oraz std::ios::out
- jeżeli file.good() jest prawdą:
  - zapis do pliku file wartości kolejno: workHours, '\n', workWeekends, '\n'.
  - zamknięcie pliku

### Zadania

- jeżeli został podany argument:
- - inicjalizacja zmiennej typu std::fstream o nazwie file, z wartością konstruktora wczytaną z argumentu wejściowego oraz std::ios::out
  - jeżeli file.good() jest prawdą:
  - - pętla po kolei wywołująca się dla każdego elementu wektora tasks:
      - zapis do pliku file wartości kolejno: task.getName(), task.getDescription(), task.getDueDate(), task.getExpectedTime(), task.getIsCompleted()
    - zamknięcie pliku

## Algorytmy

### Settings::Settings()

- inicjalizacja zmiennej file, przygotowanie do czytania pliku settings.babam
- jeżeli plik się nie otworzył:
- - zamknięcie pliku
  - otwarcie pliku do wypisu
  - zapisanie danych domyślnych
  - zamknięcie pliku
  - otwarcie pliku do czytania
- wczytanie dwóch kolejnych danych z pliku
- zamknięcie pliku
- zapis danych do zmiennych aktualnej instancji pliku

### Settings::saveSettings()

- wywołanie metody Settings::getInstance jako gwarancja że instancja klasy istnieje
- otwarcie pliku wyjściowego settings.babam
- jeżeli plik się otworzył:
  - zapis danych
  - zamknięcie pliku

### Task::workHoursLeft()

- inicjalizacja zmiennej zmiennoprzecinkowej whl (work hours left)
- inicjalizacja zmiennej now typu time_t, wypełnienie jej aktualną datą
- inicjalizacja zmiennych workHours i workWeekends, pobranych z Settings::getInstance()
- inicjalizacja zmiennej hl (hours left), wypełnienie jej różnicą czasu pomiędzy zmienną aktualnej instancji dueDate oraz now podzielonej przez 3600
- inicjalizacja zmiennej weeksLeft, wypełnienie jej ilorazem hl, 24, oraz 7
- wypełnienie zmiennej whl iloczynem zmiennych weeksLeft, workHours, oraz zależnie od zmiennej workWeekends albo 7 albo 5 - weeksLeft to zmienna stałoliczbowa, więc wszelki nadmiar zostaje "ucięty"
- odjęcie od zmiennej hl iloczynu 24, 7 oraz zmiennej weeksLeft
- inicjalizacja zmiennej stałoliczbowej daysLeft, wypełnienie jest ilorazem hl oraz 24
- inicjalizacja zmiennej typu time_t temp, wypełnienie jej sumą now oraz 60\*60\*24 (jutrzejszy dzień)
- inicjalizacja zmiennej typu tm helperDate, wypełnienie jej zmienną temp
- inicjalizacja zmiennej typu tm dueDateTM, wypełnienie jej zmienną dueDateTM
- ustawienie godziny, minuty i sekundy helperDate danymi z dueDateTM
- pętla działająca jeżeli różnica czasu helperDate oraz now jest mniejsza niż iloczyn daysLeft, 60, 60, i 24:
  - jeżeli workWeekends jest prawdą lub jeżeli helperDate.tm_wday jest pomiędzy 1 a 5 (jest dniem roboczym):
    - dodanie do whl zmiennej workHours
  - zmiana wartości helperDate na kolejny dzień
- jeżeli workWeekends jest prawdą lub jeżeli helperDate.tm_wday jest pomiędzy 1 a 5 (jest dniem roboczym):
  - dodanie do zmiennej whl ilości godzin pozostałych ostatniego dnia lub zmiennej workHours, zależnie od tego która wartość jest mniejsza
- inicjalizacja zmiennej typu tm nowTM danymi na podstawie zmiennej temp
- jeżeli workWeekends jest prawdą lub jeżeli nowTM.tm_wday jest pomiędzy 1 a 5 (jest dniem roboczym):
  - dodanie do zmiennej whl ilości godzin pozostałych dzisiejszego dnia lub zmiennej workHours, zależnie od tego która wartość jest mniejsza
- zwrócenie zmiennej whl

## Wnioski

- program zrobiony w strukturze wygodnej do rozszerzenia o nowe funkcjonalności, np. możliwość "łączenia" zadań - sprowadza się to do dodania ich czasów wykonania
