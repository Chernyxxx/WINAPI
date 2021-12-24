#include <Windows.h>



RECT clientRect; // �������������

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
    hwnd = CreateWindow(wc.lpszClassName, L"01_Pen_Brush_Rectangle",
        WS_OVERLAPPEDWINDOW, 100, 100,
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
        case WM_PAINT:
         {
             GetClientRect(hwnd, &clientRect); //�������� ���������� ���������� 
                                               // ������� � ������� �� � 
                                               // RECT clientRect
             PAINTSTRUCT ps;
             HDC hdc = BeginPaint(hwnd, &ps);  //  
                                               // 
              
             // ������� ���������� �������                               

             FillRect(hdc, &clientRect,
                reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
             //
             //     Then we draw the rectangle using Rectangle func.
             //     As result we will get white rectangle with a thin 
             //     black border. 
             //     To make oter thikness or color of border and other
             //     bgcolor we have to define HPEN and HBRUSH objects
             //     and store them to context/stock using func SelectObject.
             //     After that we make rectangle whit customised bgcolor &
             //     borders. 
             //     Then we have to delete HPEN and HBRUSH objects using 
             //     func DeleteObject
             //     If we want to use black or white color of bg & border
             //     or delete borders, we have to use internal macroses
             //     such as WHITE_PEN, BLACK_BRUSH, NULL_PEN, ets.
             //     For that we have to use func GetStockObject, which
             //     returns HGDIOBJ (that is kind of HPEN, HBRUSH).
             //
             //

             // �������� ����� �����
             
             HPEN blue_pen1 = CreatePen(PS_SOLID, 5, RGB(0, 0, 255)); 
                                                                      
             // �������� ����� �������

             HBRUSH hyell_br = CreateSolidBrush(RGB(255, 255, 0));

             // ���������� �������� � ����

             SelectObject(hdc, blue_pen1); 

             // HGDIOBJ white_pen = SelectObject(hdc, GetStockObject(WHITE_PEN));
             SelectObject(hdc, GetStockObject(BLACK_BRUSH));
             
            // SelectObject(hdc, hyell_br);
            
            
             Rectangle(hdc, clientRect.left + 20, clientRect.top + 20,
                 clientRect.right - 20, clientRect.bottom - 20);

             DeleteObject(blue_pen1);
             DeleteObject(hyell_br);


             EndPaint(hwnd, &ps);

         }
         break;

         
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    // ������� �������� ����

}