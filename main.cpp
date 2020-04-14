#include <windows.h>
#include <stdlib.h>

//Define Variables in global scope
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define HELP_MENU 4
#define JOB_APPLICATION 5
#define LEAVE_APPLICATION 6
#define EVENT_INVITATION 7

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
HWND hName, hOut, hLogo, hMainWindow, hSubject, hRecipient, hPortal, hRole, hInstitute, hMarks, hStream, hStartdate, hEnddate, hEvent, hTime, hCompany, hPlace, hUrCompany;

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
    hMainWindow = CreateWindowW(L"myWindowClass", L"LETTERS AND APPLICATIONS", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 10, 1000, 800, NULL, NULL, NULL, NULL);
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
        case HELP_MENU:
            {
                wchar_t help[1000] = L"In this application, all you have to do is enter the details and click the desired button. An application prototype will be displayed in the message box according to the button you pressed. This application can be further developed by including various formats of applications and letters. PS: Bugs to be fixed: 1. On clicking any generate button, the application doesn't get displayed in the message box at once; the message box has to be clicked twice to display the text. 2. The application isn't responsive according to screen size yet";
                MessageBoxW(NULL, help, L"HELP!", MB_OK);
                break;
            }
        case JOB_APPLICATION:
            char name[30], subject[200], recipient[50], portal[100], role[100], institute[100], stream[100], marks[10], out[1000];

            GetWindowText(hName, name, 30);
            GetWindowText(hSubject, subject, 200);
            GetWindowText(hRecipient, recipient, 50);
            GetWindowText(hPortal, portal, 100);
            GetWindowText(hRole, role, 100);
            GetWindowText(hInstitute, institute, 100);
            GetWindowText(hStream, stream, 100);
            GetWindowText(hMarks, marks, 10);

            if(strcmp(name, "")==0)
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

            strcpy(out, "Subject: ");
            strcat(out, subject);
            strcat(out, "\n");
            strcat(out, "Dear ");
            strcat(out, recipient);
            strcat(out, ",\n");
            strcat(out, "This is regarding your post on ");
            strcat(out, portal);
            strcat(out, " about a vacancy in your company for the role of ");
            strcat(out, role);
            strcat(out, ". Please accept my application for the same. \n");
            strcat(out, "Here is a brief about myself. I have completed ");
            strcat(out, stream);
            strcat(out, " from ");
            strcat(out, institute);
            strcat(out, ". I secured ");
            strcat(out, marks);
            strcat(out, " in my final exams.\n");
            strcat(out, "During my studies, I participated in various tech fests and also won various medals in inter-university competitions.\nI am confident that I have the skills to excel at your dynamic organisation. I have always dreamed of being a part of your company due to the development opportunities you provide. I request you to give me an opportunity to learn and grow at your esteemed firm through this job role.\nPlease refer to my resume and cover letter, attached with the email, for detailed information.\nThank You.\nYours sincerely,\n");
            strcat(out, name);
            strcat(out, "\nMobile: \nEmail ID:");

            SetWindowText(hOut, out);
            break;
        case LEAVE_APPLICATION:
            char startdate[20], enddate[20];
            GetWindowText(hName, name, 30);
            GetWindowText(hRecipient, recipient, 50);
            GetWindowText(hStartdate, startdate, 20);
            GetWindowText(hEnddate, enddate, 20);

            if(strcmp(name, "")==0)
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

            strcpy(out, "Subject: Application for Casual Leave\n");
            strcat(out, "Dear ");
            strcat(out, recipient);
            strcat(out, ",\n I am writing to you to let you know that I have an important personal matter to attend at my hometown due to which I will not be able to come to the office from ");
            strcat(out, startdate);
            strcat(out, " to ");
            strcat(out, enddate);
            strcat(out, "\n");
            strcat(out, "I have discussed and delegated my tasks to my colleagues & have instructed them to call me for any help during my absence.I will be obliged if you consider my application for approval.\n");
            strcat(out, "Yours Sincerely,\n");
            strcat(out, name);

            SetWindowText(hOut, out);
            break;
        case EVENT_INVITATION:
            char company[100], time[30], event[100], place[100], yourCompany[100];
            GetWindowText(hCompany, company, 100);
            GetWindowText(hEvent, event, 100);
            GetWindowText(hTime, time, 30);
            GetWindowText(hPlace, place, 100);
            GetWindowText(hUrCompany, yourCompany, 100);
            strcpy(out, "From \n");
            strcat(out, name);
            strcat(out, "To \n");
            strcat(out, recipient);
            strcat(out, "Subject: Business Event Invitation Letter.\nDear _____(Sir or Madam),");
            strcat(out, "It is a pleasure to invite you to attend the ");
            strcat(out, event);
            strcat(out, " located at ");
            strcat(out, place);
            strcat(out, " on ");
            strcat(out, startdate);
            strcat(out, " at ");
            strcat(out, time);
            strcat(out, ".\n As one of ");
            strcat(out, company);
            strcat(out, " esteemed business associates, it would be our honour to have your presence at this auspicious event. It is also an opportunity to thank you  for the splendid business partnership that both companies have enjoyed over the past years.I do hope that you will be able to confirm your attendance to this invitation on or before ");
            strcat(out, enddate);
            strcat(out, " by just mailing us at our official email ID. \nLooking forward to your presence at this celebration,\nYours truly,\n");
            strcat(out, name);
            strcat(out, yourCompany);

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
    AppendMenu(hMenu, MF_STRING, HELP_MENU, "Help");
    SetMenu(hWnd, hMenu);
}

//function for adding static and edit controls to main window
void AddControls(HWND hWnd)
{
    //CreateWindowW(L"static", L"Enter text here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd, NULL, NULL, NULL);
    //hEdit = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);
    //CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD, 200, 204, 100, 50, hWnd, (HMENU)CHANGE_TITLE, NULL, NULL);

    CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Subject: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hSubject = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Recipient: ", WS_VISIBLE | WS_CHILD, 100, 130, 98, 38, hWnd, NULL, NULL, NULL);
    hRecipient = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 130, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Portal: ", WS_VISIBLE | WS_CHILD, 100, 170, 98, 38, hWnd, NULL, NULL, NULL);
    hPortal = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 170, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Role: ", WS_VISIBLE | WS_CHILD, 100, 210, 98, 38, hWnd, NULL, NULL, NULL);
    hRole = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 210, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Institute: ", WS_VISIBLE | WS_CHILD, 100, 250, 98, 38, hWnd, NULL, NULL, NULL);
    hInstitute = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 250, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Stream: ", WS_VISIBLE | WS_CHILD, 100, 290, 98, 38, hWnd, NULL, NULL, NULL);
    hStream = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 290, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Marks: ", WS_VISIBLE | WS_CHILD, 100, 330, 98, 38, hWnd, NULL, NULL, NULL);
    hMarks = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 330, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Start Date (leave): ", WS_VISIBLE | WS_CHILD, 400, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hStartdate = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 50, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"End Date (leave): ", WS_VISIBLE | WS_CHILD, 400, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hEnddate = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 90, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Event (invitation): ", WS_VISIBLE | WS_CHILD, 400, 130, 98, 38, hWnd, NULL, NULL, NULL);
    hEvent = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 130, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Time (invitation): ", WS_VISIBLE | WS_CHILD, 400, 170, 98, 38, hWnd, NULL, NULL, NULL);
    hTime = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 170, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Company Name: ", WS_VISIBLE | WS_CHILD, 400, 210, 98, 38, hWnd, NULL, NULL, NULL);
    hCompany = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 210, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Venue: ", WS_VISIBLE | WS_CHILD, 400, 250, 98, 38, hWnd, NULL, NULL, NULL);
    hPlace = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 250, 98, 38, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Your Company: ", WS_VISIBLE | WS_CHILD, 400, 290, 98, 38, hWnd, NULL, NULL, NULL);
    hUrCompany = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 500, 290, 98, 38, hWnd, NULL, NULL, NULL);

    //CreateWindowW(L"Static", L"Age: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    //hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Job Application", WS_VISIBLE | WS_CHILD, 100, 380, 110, 38, hWnd, (HMENU)JOB_APPLICATION, NULL, NULL);
    CreateWindowW(L"Button", L"Leave", WS_VISIBLE | WS_CHILD, 220, 380, 110, 38, hWnd, (HMENU)LEAVE_APPLICATION, NULL, NULL);
    CreateWindowW(L"Button", L"Invitation", WS_VISIBLE | WS_CHILD, 340, 380, 110, 38, hWnd, (HMENU)EVENT_INVITATION, NULL, NULL);
   // CreateWindowW(L"Button", L"Job Application", WS_VISIBLE | WS_CHILD, 340, 380, 110, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
    //CreateWindowW(L"Button", L"Job Application", WS_VISIBLE | WS_CHILD, 460, 380, 110, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 100, 430, 470, 200, hWnd, NULL, NULL, NULL);
    //hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
    //SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
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
