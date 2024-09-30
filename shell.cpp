// MAIN CRAPS
#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <utime.h>
#include <map>

#include <typeinfo>
// DATASTRUCTURES
#include <unordered_map>
using namespace std;
// #include <colordlg.h>
// FG Colors
const short black = 0x0000;
const short blue = 0x0001;
const short green = 0x0002;
const short cyan = (FOREGROUND_BLUE | FOREGROUND_GREEN);
const short red = 0x0004;
const short magneta = (FOREGROUND_RED | FOREGROUND_BLUE);
const short yellow = (FOREGROUND_RED | FOREGROUND_GREEN);
const short white = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#define FOREGROUND_INTENSITY 0x0008; // Brightens

// BG Colors
const short BLACK = 0x0000;
const short BLUE = 0x0010;
const short GREEN = 0x0020;
const short CYAN = (BACKGROUND_BLUE | BACKGROUND_GREEN);
const short RED = 0x0040;
const short MAGENTA = (BACKGROUND_RED | BACKGROUND_BLUE);
const short YELLOW = (BACKGROUND_RED | BACKGROUND_GREEN);
const short WHITE = (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
#define BACKGROUND_INTENSITY = 0x0080 // Brightens

// MY INCLUDES
// #include "includes/catcraps.cpp"

// ETC
// #include <random> //not used

// ADD COMMAND HERE
enum Commands
{
    ENTER,
    SAY,
    CD,
    LS,
    SYS,
    CLS,
    TOUCH,
    UNKNOWN,
    OPEN,
    MAN,
    PWD,
    CAT,
    MKDIR,
    GOOGLE
};

// map<string, string> loadThemeConfig(const string& filename) {
//     map<string, string> config;
//     ifstream file(filename);
//     string line;

//     while (getline(file, line)) {
//         if (line.empty() || line[0] == '[' || line[0] == '#') continue; // Ignore empty lines and section headers

//         size_t delimiterPos = line.find('=');
//         if (delimiterPos != string::npos) {
//             string key = line.substr(0, delimiterPos);
//             string value = line.substr(delimiterPos + 1);

//             key.erase(key.find_last_not_of(" \n\r\t") + 1);
//             value.erase(value.find_last_not_of(" \n\r\t") + 1);

//             config[key] = value;
//         }
//     }

//     return config;
// }

// void writeDefaultThemeConfig(const string &filename)
// {
//     ofstream themeFile(filename);

//     themeFile << "[General]" << endl;
//     themeFile << "shelltag = HEHECAT ⚙️  " << endl;
//     themeFile << endl;

//     themeFile << "[Colors]" << endl;
//     themeFile << "background = BLACK" << endl;
//     themeFile << "shell_tag_color = green" << endl;
//     themeFile << "shell_arguments = magneta" << endl;
//     themeFile << "paths = yellow" << endl;
//     themeFile << "manual = cyan" << endl;

//     // themeFile << "[Fonts]" << endl;
//     // themeFile << "font_size = 14" << endl;
//     // themeFile << "font_style = monospace" << endl;

//     themeFile.close();
// }

// bool fileExists(const string &filename)
// {
//     ifstream file(filename);
//     return file.good();
// }

class Theme
{
public:
    string shelltag = "⚙️  ";

    short background = YELLOW;

    short shell_tag_color = green;
    short shell_arguments = magneta;
    short paths = white;
    short manual = cyan;
    short list = yellow;
    short error = red;
    short help = green;

    // void setColorTheme(short background, short shell_tag_color, short shell_arguments, short paths, short manual)
    // {
    //     this->background = background;
    //     this->shell_tag_color = shell_tag_color;
    //     this->shell_arguments = shell_arguments;
    //     this->paths = paths;
    //     this->manual = manual;
    // }
};
Theme theme;

// AND HERE
Commands enumit(const string &inString)
{

    static const unordered_map<string, Commands> commandMap = {
        {"SAY", SAY},
        {"say", SAY},
        {"CLS", CLS},
        {"cls", CLS},
        {"CD", CD},
        {"cd", CD},
        {"LS", LS},
        {"ls", LS},
        {"SYS", SYS},
        {"sys", SYS},
        {"OPEN", OPEN},
        {"open", OPEN},
        {"MAN", MAN},
        {"man", MAN},
        {"help", MAN},
        {"HELP", MAN},
        {"PWD", PWD},
        {"pwd", PWD},
        {"google", GOOGLE},
        {"GOOGLE", GOOGLE},
        {"CAT", CAT},
        {"cat", CAT},
        {"", ENTER},
        {"MKDIR", MKDIR},
        {"mkdir", MKDIR},
        {"TOUCH", TOUCH},
        {"touch", TOUCH}};

    auto it = commandMap.find(inString);
    return it != commandMap.end() ? it->second : UNKNOWN;
}

// FUNC DECLARATION
void current();
void pwd();
void cat(); // system info
void touch(const string &filename);
void manual();
void faces();
void cleanup();
void setcolor(WORD color);
void clear(const short line);
void open(const string &path);
void changedir(const string &path);
void mkdir(const string &path);
void listfiles(const string &directory);
// void writeDefaultThemeConfig(const string& filename);
void commandHandler(const Commands &command, const vector<string> &arguments);

Commands enumit(string const &inString);
bool fileExists(const string &filename);
// map<string, string> loadThemeConfig(const string& filename);

int main()
{
    setcolor(theme.background);
    // Theme theme;
    // string filename = "theme.ini";
    // Now theme is loaded with either default or saved values
    atexit(cleanup);
    srand(static_cast<unsigned int>(time(0)));
    string curdir = "";
    string input;

    while (true)
    {
        system("chcp 65001 > nul");
        setcolor(theme.shell_tag_color);
        current();
        cout << theme.shelltag;
        system("chcp 437 > nul");
        setcolor(theme.shell_arguments);
        getline(cin, input);

        if (input == ";")
            break;

        istringstream stream(input);
        string command;
        vector<string> arguments;
        stream >> command;
        string arg;
        while (stream >> arg)
        {
            arguments.push_back(arg);
        }

        commandHandler(enumit(command), arguments);
    }

    return 0;
}

void cleanup()
{
    system("chcp 437 > nul");
    cout << "doin some shiii..." << endl;
    Sleep(500);
}

void setcolor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void commandHandler(const Commands &command, const vector<string> &arguments)
{
    string directory;
    string syscmd = "";
    string search = "";
    switch (command)
    {
    case ENTER:
        break;
    case CD:
        setcolor(theme.paths);
        if (!arguments.empty())
        {
            if (arguments[0] == "-h")
            {
                setcolor(theme.help);
                cout << "Usage: CD <Directory name>\nchanges current folder/directory\n";
                break;
            }
            changedir(arguments[0]);
        }
        else
        {
            cout << "YOU FORGOT WHERE TO GO\n";
        }
        break;
    case SAY:
        if (arguments.empty())
        {
            cout << "idk what to say..\n";
            Sleep(2000);
            cout << "um..\n";
            Sleep(2000);
            cout << "hello!\n";
            break;
        }
        else
        {
            if (arguments[0] == "-h")
            {
                setcolor(theme.help);
                cout << "Usage: SAY <good things u wanna say>\nsays good things that you wanna say!\n";
                break;
            }
            for (size_t i = 0; i < arguments.size(); i++)
            {
                cout << arguments[i] << " ";
            }
            cout << "\n";
            break;
        }

    case MKDIR:
        if(!arguments.empty()){
            for (size_t i = 0; i < arguments.size(); i++)
            {
                mkdir(arguments[i]);
            }
        }
        else{
            cout<<"please spacify name of dir";
        }

    case CLS:
        if (arguments.empty())
        {
            clear(-1);
        }
        else if (arguments[0] == "-h")
        {
            setcolor(theme.help);
            cout << "Usage: CLS <Directory name>\nclears your vision\n";
            break;
        }
        else if (arguments[0] == "l")
        {
            clear(1);
        }

        break;
    case LS:
        setcolor(theme.list);
        if (arguments.empty())
        {
            directory = ".";
        }
        else
        {
            if (arguments[0] == "-h")
            {
                setcolor(theme.help);
                cout << "Usage: ls (optional)<Directory name>\nLists specified directory files(if it wants to)\n";
                break;
            }
            directory = arguments[0];
        }
        listfiles(directory);
        cout << endl;
        break;
    case TOUCH:
        setcolor(theme.paths);
        if (arguments[0] == "-h")
        {
            setcolor(theme.help);
            cout << "Usage: touch <Filename.extention>\nif u are bored it Creates a new life\n";
            break;
        }
        else
        {
            for (size_t i = 0; i < arguments.size(); i++)
                touch(arguments[i]);
        }
        break;

    case MAN:
        setcolor(theme.manual);
        manual();
        break;

    case SYS:
        if (arguments[0] == "-h")
        {
            setcolor(theme.help);
            cout << "Usage: SYS <system command>\nperforms system commands that may not be supported by my shell\n";
            break;
        }
        if (arguments.empty())
        {
            cout << "Please specify the system command eg. echo hello world";
        }
        else
        {
            for (size_t i = 0; i < arguments.size(); i++)
            {
                syscmd.append(arguments[i]);
                syscmd.append(" ");
            }

            const char *syscmdchar = syscmd.c_str();

            system(syscmdchar);
        }
        break;

    case OPEN:
        if (arguments.empty())
        {
            open(".");
        }
        else
        {
            if (arguments[0] == "-h")
            {
                setcolor(theme.help);
                cout << "Usage: open (optional)<path>\nopens directory IN YOUR FILE EXPLORER\n";
                break;
            }
            open(arguments[0]);
        }
        break;

    case CAT:
        cat();
        // if(arguments[0] == "-h"){
        //     setcolor(theme.help);
        //     cout<<"Usage: cat\nbasically neofetch for this shell\n";
        //     break;
        // }
        // else{
        //     cat();
        // }
        break;

    case GOOGLE:
        if (arguments.empty())
        {
            system("start https://www.google.com");
        }
        else
        {
            if(arguments[0] == "-h"){
                setcolor(theme.help);
                cout<<"Usage: google (optional)<feeling luckey asf>\nopens google serches the result if specified\n";
                break;
        }
            search = "start https://www.google.com/search?q=";
            if (arguments.size() < 2)
            {
                search.append(arguments[0]);
                cout << search;
                system(search.c_str());
            }
            else
            {
                for (size_t i = 0; i < arguments.size(); i++)
                {
                    search.append(arguments[i]);
                    if (i != arguments.size())
                    {
                        search.append("+");
                    }
                }
                system(search.c_str());
            }
        }
        cout << endl;
        break;

    case PWD:
        setcolor(theme.list);
        pwd();
        break;

    case UNKNOWN: // alredy handling unknown commands so won't reach default but who knows?
        cout << "use";
        setcolor(green);
        cout << " man";
        setcolor(magneta);
        cout << " or";
        setcolor(green);
        cout << " help";
        setcolor(magneta);
        cout << " for help\nthis shell is not currently supporting that command\nif its a system command then you can use> sys <ur command>\n";
        break;

    default:
        cout << "YOU HAVE ENCOUNTERED A GOD LVL UNREACHABLE ERROR \nhere take a trophy \ntell me tf did you write lol\n";
        break;
    }
}

void current()
{

    char buffer[MAX_PATH];

    DWORD length = GetCurrentDirectory(MAX_PATH, buffer);

    if (length > 0)
    {
        // usin \ to get current dir
        char *currentDirName = strrchr(buffer, '\\');
        if (currentDirName != nullptr)
        {
            cout << string(currentDirName + 1);
        }
    }
}
void listfiles(const string &directory)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directory + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        setcolor(theme.error);
        cerr << "Directory not found." << endl;
        return;
    }
    do
    {
        cout << findFileData.cFileName << endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void changedir(const string &path)
{
    if (SetCurrentDirectory(path.c_str()))
    {
        cout << "Directory changed to " << path << endl;
    }
    else
    {
        setcolor(theme.error);
        cerr << "Error changing directory." << endl;
    }
}

void clear(const short line)
{

    if (line == -1)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD charWritten;
        DWORD charsWritten;
        DWORD consoleSize;
        consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        COORD coordScreen = {0, 0};

        FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coordScreen, &charsWritten);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coordScreen, &charsWritten);
        SetConsoleCursorPosition(hConsole, coordScreen);
    }
    else
    {
        cout << "NEH";
        // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        // GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        // int consoleWidth = consoleInfo.dwSize.X;

        // // Move the cursor to the previous line
        // COORD cursorPosition = {0, consoleInfo.dwCursorPosition.Y - 1};

        // SetConsoleCursorPosition(hConsole, cursorPosition);

        // // Clear the previous line by overwriting with spaces
        // // cout << "                                       ";

        // for (size_t i = 0; i < consoleWidth; i++)
        // {
        //     cout<<" ";
        // }

        // cursorPosition = {0, consoleInfo.dwCursorPosition.Y - 1};
        // SetConsoleCursorPosition(hConsole, cursorPosition);
        // for (size_t i = 0; i < consoleWidth; i++)
        // {
        //     cout<<" ";
        // }

        // Clear the previous line by overwriting with spaces

        // Move the cursor back to the start of the line to write new content
        // SetConsoleCursorPosition(hConsole, cursorPosition);
        // COORD cursorPosition = {0, csbi.dwCursorPosition.Y - 1};
        // SetConsoleCursorPosition(hConsole, cursorPosition);
        // cout << "                                       ";
        // SetConsoleCursorPosition(hConsole, cursorPosition);
    }
}

void open(const string &path)
{
    ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void touch(const string &filename)
{

    struct stat buffer;
    bool fileExists = (stat(filename.c_str(), &buffer) == 0);

    if (!fileExists)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            setcolor(theme.error);
            cerr << "Error: Could not create file " << filename << endl;
        }
        else
        {
            cout << "File created: " << filename << endl;
        }
    }
    else
    {

        if (utime(filename.c_str(), nullptr) != 0)
        {
            cout << "Error: Could not update the timestamp for " << filename << endl;
        }
        else
        {
            cout << "Timestamp updated: " << filename << endl;
        }
    }
}
// MY FUNC CRAPS
void manual()
{
    // cout<<typeof(B);
    setcolor(theme.manual);
    setcolor(theme.help);
    cout << "\t_________________________________________" << endl;
    cout << "\tcatshell Manual Help whatever you call it" << endl
         << endl;
    cout << "This Terminal can Perform following commands:" << endl
         << endl;
    setcolor(theme.error);
    cout << "Basic  :" << endl;
    setcolor(theme.help);
    cout << "CD";
    setcolor(theme.manual);
    cout << "\tUsage: cd <Directory name>                        Changes ur life...I mean directory not that other shit" << endl;
    setcolor(theme.help);
    cout << "LS";
    setcolor(theme.manual);
    cout << "\tUsage: ls (optional)<Directory name>              Lists specified directory files(if it wants to)" << endl;
    setcolor(theme.help);
    cout << "PWD";
    setcolor(theme.manual);
    cout << "\tUsage: PWD                                        use if you have memoryloss or amnesia" << endl;
    setcolor(theme.help);
    cout << "TOUCH";
    setcolor(theme.manual);
    cout << "\tUsage: touch <Filename.extention>                 if u are bored it Creates a new life" << endl;
    setcolor(theme.help);
    cout << "MKDIR";
    setcolor(theme.manual);
    cout << "\tUsage: MKDIR <Foldername>                         creates new directory" << endl;
    setcolor(theme.help);
    cout << "CLS";
    setcolor(theme.manual);
    cout << "\tUsage: CLS                                        clears your shitty vision" << endl;
    setcolor(theme.help);
    cout << "MAN";
    setcolor(theme.manual);
    cout << "\tUsage: man                                        opens this manual like u did't just do that" << endl<< endl;

    setcolor(theme.error);
    cout << "\nCatshell  :" << endl;
    setcolor(theme.help);
    cout << ";";
    setcolor(theme.manual);
    cout << "\tUsage: ;                                          You can get out of this worldly cycle of  misery" << endl;
    setcolor(theme.help);
    cout << "SAY";
    setcolor(theme.manual);
    cout << "\tUsage: say <good things u wanna say>              say all the good things you wanna say!" << endl;
    setcolor(theme.help);
    cout << "OPEN";
    setcolor(theme.manual);
    cout << "\tUsage: open (optional)<path>                      opens directory IN YOUR FILE EXPLORER" << endl;
    setcolor(theme.help);
    cout << "GOOGLE";
    setcolor(theme.manual);
    cout << "\tUsage: google (optional)<feeling luckey asf>      opens google serches the result if specified" << endl;
    setcolor(theme.help);
    cout << "CAT";
    setcolor(theme.manual);
    cout << "\tUsage: cat                                        basically neofetch for this shell" << endl;
    setcolor(theme.help);
    cout << "SYS";
    setcolor(theme.manual);
    cout << "\tUsage: SYS <system command>                       performs system commands that may not be supported by my shell" << endl;
    cout << endl
         << endl;
}

// void faces()
// {
//     int min = 0;
//     int max = 4;
//     int rn = min + rand() % (max - min + 1);
//     switch (rn)
//     {
//     case 0:
//         cout << "(=^.^=) $> ";
//         break;

//     case 1:
//         cout << "(=^o^=) $> ";
//         break;
//     case 2:
//         cout << "(=^-^=) $> ";
//         break;
//     case 3:
//         cout << "(=O.O=) $> ";
//         break;
//     case 4:
//         cout << "(=q.p=) $> ";
//         break;
//     default:
//         cout << "$> " << endl;
//         break;
//     }
// }


void mkdir(const string &path) {
    LPCSTR directory = path.c_str();

    if (CreateDirectory(directory, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        cout << "Directory created successfully or already exists!" <<endl;
    } else {
        cerr << "Failed to create directory. Error: " << GetLastError() <<endl;
    }
}


void printWindowsVersion()
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi))
    {
        cout << "Windows Version: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << " (Build " << osvi.dwBuildNumber << ")" << std::endl;
    }
}

void cat()
{
    setcolor(magneta);
    cout << "\t /\\_/\\  ";
    printWindowsVersion();
    // cout<<endl;
    cout << "\t( ^.^ ) " << "SHELL: CATSHELL" << endl;
    cout << "\t > ^ <  " << endl;
}

void pwd()
{
    char buffer[MAX_PATH];

    DWORD length = GetCurrentDirectory(MAX_PATH, buffer);

    if (length > 0)
    {
        cout << buffer << endl;
    }
    else
    {
        setcolor(theme.error);
        cerr << "Error getting current directory." << endl;
    }
}