#include <windows.h>
#include <stdlib.h>

//Define Variables in global scope
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
//#define CHANGE_TITLE 4

//the main window procedure prototype
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

//prototypes for other functions
void AddMenus(HWND);
void AddControls(HWND);
void loadImages();
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);

//window handlers
HWND hName, hAge, hOut, hLogo, hMainWindow;

HMENU hMenu;
HBITMAP hLogoImage;
//HWND hEdit;

//the main() function equivalent
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    //specifications for the window
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    //error handling if window is not created
    if(!RegisterClassW(&wc))
        return -1;

    //registering dialog box
    registerDialogClass(hInst);

    //handler for main window to be used by other functions
    hMainWindow = CreateWindowW(L"myWindowClass", L"MY WINDOW", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);
   // MessageBoxW(NULL, L"HELLO", L"HI", MB_OK);

   //message returned when some button is pressed or menu is opened
    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//the main window procedure. defines how the buttons should work etc
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int val;

    //message returned is checked using switch statement
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case FILE_MENU_EXIT:
            val = MessageBoxW(hWnd, L"Do you really want to exit?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
            if(val == IDYES)
            {
               DestroyWindow(hWnd);
            }
            else if(val == IDNO)
            {
                //Add your function
            }
            break;
        case FILE_MENU_NEW:
            displayDialog(hWnd);
            MessageBeep(MB_ICONINFORMATION);
            break;
        case GENERATE_BUTTON:
            char name[30], age[10], out[50];

            GetWindowText(hName, name, 30);
            GetWindowText(hAge, age, 10);

            if(strcmp(name, "")==0 ||  strcmp(age, "")==0)
            {
                val = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);
                switch(val)
                {
                case IDABORT:
                    DestroyWindow(hWnd);
                    break;
                case IDRETRY:
                    return 0;
                case IDIGNORE:
                    break;
                }
            }

            strcpy(out, name);
            strcat(out, " is ");
            strcat(out, age);
            strcat(out, " years old.");

            SetWindowText(hOut, out);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
       // case CHANGE_TITLE:
          // wchar_t text[100];
          // GetWindowTextW(hEdit, text, 100);
          // SetWindowTextW(hWnd, text);
          // break;
        }
    case WM_CREATE:
        //loadImages();
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

//function for adding menu bar in window
void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    //AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, "Change Title");
    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");
    SetMenu(hWnd, hMenu);
}

//function for adding static and edit controls to main window
void AddControls(HWND hWnd)
{
    //CreateWindowW(L"static", L"Enter text here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd, NULL, NULL, NULL);
    //hEdit = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);
    //CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD, 200, 204, 100, 50, hWnd, (HMENU)CHANGE_TITLE, NULL, NULL);

    CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Age: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD, 150, 140, 98, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
}

//function for loading images
void loadImages()
{
    hLogoImage = (HBITMAP)LoadImageW(NULL, L"preloader.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
    if (!hLogo)
    {
      MessageBoxW(NULL, L"bad bitmap", L"mytitle", MB_OK);
    }
}

//dialog box procedure, defines how buttons and menus should work in dialog box
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case 1:
            EnableWindow(hMainWindow, true);
            DestroyWindow(hWnd);
            break;
        }
    case WM_CLOSE:
        EnableWindow(hMainWindow, true);
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

//function for defining dialog box
void registerDialogClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};

    dialog.hbrBackground = (HBRUSH)COLOR_3DDKSHADOW;
    dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
}

//function for displaying dialog box
void displayDialog(HWND hWnd)
{
    HWND hDlg = CreateWindowW(L"myDialogClass", L"Dialog", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Close", WS_VISIBLE | WS_CHILD, 20, 20, 100, 40, hDlg, (HMENU)1, NULL, NULL);
    EnableWindow(hWnd, false);
}
