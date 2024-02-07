# myfind

Das `myfind` Programm ist ein benutzerdefiniertes Kommandozeilentool, das zum Suchen von Dateien innerhalb eines bestimmten Verzeichnisses und optional in dessen Unterverzeichnissen verwendet wird. Es unterstützt die Suche nach einem oder mehreren Dateinamen und bietet die Möglichkeit, die Suche unabhängig von der Groß- und Kleinschreibung durchzuführen sowie rekursiv in Unterverzeichnissen zu suchen.

## Funktionen

- Suche nach einem oder mehreren Dateinamen in einem spezifizierten Verzeichnis.
- Optionale rekursive Suche in Unterverzeichnissen.
- Optionale Suche unabhängig von der Groß- und Kleinschreibung.

## Abhängigkeiten

Das Programm nutzt Standardbibliotheken von C++ und erfordert keine externen Abhängigkeiten. Es ist kompatibel mit Unix-basierten Systemen aufgrund der Verwendung von systemnahen Aufrufen wie `fork()`, `opendir()`, `readdir()` und `closedir()`.

## Kompilierung

Zum Kompilieren des Programms navigieren Sie in das Verzeichnis, in dem sich `main.cpp` befindet, und führen Sie den folgenden Befehl aus:
```bash
g++ -o myfind main.cpp
```

Dies kompiliert den Quellcode und erzeugt eine ausführbare Datei namens `myfind`.

## Ausführung

Um das Programm auszuführen, verwenden Sie die folgende Syntax:
```bash
./myfind [-R] [-i] searchpath filename1 [filename2] … [filenameN]
```

Optionen:
- `-R`: Aktiviert den rekursiven Modus, um in Unterverzeichnissen zu suchen.
- `-i`: Führt eine Groß-/Kleinschreibung-unabhängige Suche durch.

Argumente:
- `searchpath`: Der Pfad, in dem nach den Dateien gesucht werden soll.
- `filename1 [filename2] … [filenameN]`: Die Namen der Dateien, nach denen gesucht werden soll.
