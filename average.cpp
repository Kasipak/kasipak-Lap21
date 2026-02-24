#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hEdit1, hEdit2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    wc.hbrBackground = CreateSolidBrush(RGB(220, 0, 120)); // สีชมพูสด

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "MyWindowClass",
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // ล็อกขนาด
        500, 200,
        250, 200,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void ShowResult(HWND hwnd, char op)
{
    char text1[100], text2[100];
    GetWindowText(hEdit1, text1, 100);
    GetWindowText(hEdit2, text2, 100);

    double num1 = atof(text1);
    double num2 = atof(text2);
    double result = 0;

    if(op == '+') result = num1 + num2;
    if(op == '-') result = num1 - num2;
    if(op == '*') result = num1 * num2;
    if(op == '/') {
        if(num2 == 0) {
            MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK);
            return;
        }
        result = num1 / num2;
    }

    char output[100];
    sprintf(output, "%f", result);

    MessageBox(hwnd, output, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:

        CreateWindow("STATIC", "Please input two numbers",
                     WS_VISIBLE | WS_CHILD,
                     25, 20, 200, 20,
                     hwnd, NULL, NULL, NULL);

        hEdit1 = CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     50, 50, 150, 25,
                     hwnd, (HMENU)ID_EDIT1, NULL, NULL);

        hEdit2 = CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     50, 85, 150, 25,
                     hwnd, (HMENU)ID_EDIT2, NULL, NULL);

        CreateWindow("BUTTON", "+",
                     WS_VISIBLE | WS_CHILD,
                     40, 120, 35, 30,
                     hwnd, (HMENU)ID_ADD, NULL, NULL);

        CreateWindow("BUTTON", "-",
                     WS_VISIBLE | WS_CHILD,
                     80, 120, 35, 30,
                     hwnd, (HMENU)ID_SUB, NULL, NULL);

        CreateWindow("BUTTON", "*",
                     WS_VISIBLE | WS_CHILD,
                     120, 120, 35, 30,
                     hwnd, (HMENU)ID_MUL, NULL, NULL);

        CreateWindow("BUTTON", "/",
                     WS_VISIBLE | WS_CHILD,
                     160, 120, 35, 30,
                     hwnd, (HMENU)ID_DIV, NULL, NULL);

        break;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case ID_ADD: ShowResult(hwnd, '+'); break;
        case ID_SUB: ShowResult(hwnd, '-'); break;
        case ID_MUL: ShowResult(hwnd, '*'); break;
        case ID_DIV: ShowResult(hwnd, '/'); break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
