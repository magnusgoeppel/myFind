#include <iostream>
#include <algorithm>
#include <dirent.h>
#include <sys/wait.h>

using namespace std;

// Konvertiert beide Strings zu Kleinbuchstaben und vergleicht sie
bool caseInsensitiveMatch(string string1, string string2)
{
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);

    return string1 == string2;
}

void searchFile(bool recursive, bool caseInsensitive, string path, string filename)
{
    // Pointer auf das Verzeichnis
    DIR *dir;
    // Pointer auf den Verzeichniseintrag
    dirent *entry;

    // Wenn das Verzeichnis nicht geöffnet werden kann
    if ((dir = opendir(path.c_str())) == NULL)
    {
        // Gib eine Fehlermeldung aus
        perror("Failed to open directory");
        return;
    }

    // Durchlaufe alle Verzeichniseinträge (Gehe einen Eintrag weiter)
    while ((entry = readdir(dir)) != NULL)
    {
        // Speichere den aktuellen Eintrag
        string currentFile = entry -> d_name;

        // Wenn der Eintrag ein Verzeichnis ist
        if (entry -> d_type == DT_DIR)
        {
            // Wenn es sich nicht um das aktuelle oder das übergeordnete Verzeichnis handelt und wird rekursiv gesucht
            if (recursive && currentFile != "." && currentFile != "..")
            {
                // Rekursiv suchen
                searchFile(recursive, caseInsensitive, path + "/" + currentFile, filename);
            }
        }
        else
        {
            // Groß- und Kleinschreibung nicht beachten
            if (caseInsensitive)
            {
                if (caseInsensitiveMatch(currentFile, filename))
                {
                    cout << getpid() << ": " << filename << ": " << path + "/" + currentFile << endl;
                }
            }
            // Normale Suche
            else
            {
                if (currentFile == filename)
                {
                    cout << getpid() << ": " << filename << ": " << path + "/" + currentFile << endl;
                }
            }

        }
    }
    // Schließe das Verzeichnis
    closedir(dir);
}


// argc: Anzahl der Argumente; argv: string Array mit den Argumenten
int main(int argc, char *argv[])
{
    // [-R]
    bool recursive = false;
    // [-i]
    bool caseInsensitive = false;
    // searchpath
    string searchPath;
    // filename1 [filename2] … [filenameN]
    vector<string> filenames;

    // Variable um die Optionen [-R] und [-i] zu prüfen
    int option;

    // Geht alle Argumente durch und prüft ob [-R] oder [-i] gesetzt sind.
    while ((option = getopt(argc, argv, "Ri")) != -1)
    {
        switch (option)
        {
            // Rekursiv suchen
            case 'R':
                recursive = true;
                break;

            // Groß- und Kleinschreibung nicht beachten
            case 'i':
                caseInsensitive = true;
                break;

            // Fehlermeldung bei falscher Optionen Eingabe
            default:
                cerr << "Usage: /.myfind [-R] [-i] searchpath filename1 [filename2] … [filenameN]" << endl;
                // Beende das Programm mit Fehlercode
                exit(EXIT_FAILURE);
        }
    }
    // optind: Argmumente nach den Optionen

    // Wenn optind kleiner als argc ist
    if (optind < argc)
    {
        // Aktuelles Argument ist der searchpath
        searchPath = argv[optind];
        // Gehe zum nächsten Argument (filename1)
        ++optind;

        while (optind < argc)
        {
            // Speichere das filename Argument in den Vector
            filenames.push_back(argv[optind]);
            // Gehe zum nächsten Argument (filename wenn vorhanden)
            ++optind;
        }
    }

    // Für alle filenames im Vector
    for (int i = 0; i < filenames.size(); ++i)
    {
        // Erstelle einen Kindprozess
        pid_t pid = fork();

        // Wenn der Kindprozess erfolgreich erstellt wurde
        if (pid == 0)
        {
            // Suche nach dem filename
            searchFile(recursive, caseInsensitive, searchPath, filenames[i]);
            // Beende den Kindprozess erfolgreich
            exit(EXIT_SUCCESS);
        }
        // Wenn die Erstellung des Kindprozesses fehlgeschlagen ist
        else if (pid < 0)
        {
            // Gib eine Fehlermeldung aus
            perror("Fork failed");
            // Beende das Programm mit Fehlercode
            exit(EXIT_FAILURE);
        }
    }
    // Warte bis alle Kinderprozesse beendet sind, verhindert Zombieprozesse
    while (wait(NULL) > 0);

    return 0;
}