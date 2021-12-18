#include <Windows.h> 

                       
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

HWND hedit; // ���������� ���� ����� (������������ � WndProc)

// �������� �������:
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreviousInst, LPSTR lpCommandLine,
    int nCmdShow)
{
    HWND hwnd;  // ��������� ����
    MSG msg;    
    WNDCLASSEX wc; 
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"ClassName";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszMenuName = 0;
   

    RegisterClassEx(&wc);
    hwnd = CreateWindow(wc.lpszClassName, L"HOPE", WS_OVERLAPPEDWINDOW, 100, 100,
        500, 500, NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);


    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
            // ������� �������

    case WM_CREATE: {

            // ����

        HMENU hMenu = CreateMenu();
        AppendMenu(hMenu, MF_POPUP, 2, L"�������� ����");
        SetMenu(hwnd, hMenu);

            // ������

        HWND hbtn = CreateWindow(
            L"BUTTON",
            L"PUSH ME",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 150, 35, hwnd,
            reinterpret_cast <HMENU>(1), // ������������� ������
            NULL, NULL);

        // ����������� �����

        HWND hstatic = CreateWindow(
            L"static",
            L"This text",
            WS_CHILD | WS_VISIBLE,
            300, 300, 150, 20, hwnd, NULL, NULL, NULL);

        // ���� �����

         hedit = CreateWindow(
            L"eDit",
            L"qwerty",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            200, 200, 105, 20, hwnd,
            NULL, NULL, NULL, NULL);

    };
        break;

                  // ��������� ������� ������

    case WM_COMMAND: {
        switch (LOWORD(wp))
        {
        case 1:  // "1" - ������������� ������
        {
            
            MessageBox(NULL, L"press btn", L"App", MB_OK);
            break;
        }
        case 2:  
        {
            CloseWindow(hwnd); // ������������ ����
           // DestroyWindow(hwnd); // �������� ����
            break;
        }
        default:
            break;
        }
        break;
    }



                   // �������� ����
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }

         // ������� �������� ����
   
}