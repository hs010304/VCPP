#include <windows.h>

// 전역 변수 선언
POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;

RECT rect_user = { 5, 5, 10, 10 }; // 사용자 사각형의 초기 위치와 크기
RECT rect_target = { 50, 50, 150, 150 }; // 목표 사각형의 초기 위치와 크기

// 두 사각형이 겹치는지 확인하는 함수
int RectIntersect(const RECT* rect1, const RECT* rect2)
{
    return rect1->left < rect2->right && rect1->right > rect2->left &&
        rect1->top < rect2->bottom && rect1->bottom > rect2->top;
}

// 윈도우 프로시저 함수
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; // hdc를 직접 선언

    // 브러시 선언 및 초기화
    HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255)); // 사용자 사각형 브러시 (파란색)
    HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255)); // 목표 사각형 브러시 (보라색)
    HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255)); // 화면 지우기 브러시 (흰색)
    const wchar_t* text = L"도착 !!!"; // 출력할 텍스트

    switch (uMsg)
    {
    case WM_KEYDOWN:
        isKeyPressed = 1;
        if (wParam == VK_RIGHT)
        {
            rect_user.left += 1; // 오른쪽 화살표 키 누르면 사용자 사각형을 오른쪽으로 이동
            rect_user.right += 1;
        }
        else if (wParam == VK_LEFT)
        {
            rect_user.left -= 1; // 왼쪽 화살표 키 누르면 사용자 사각형을 왼쪽으로 이동
            rect_user.right -= 1;
        }
        else if (wParam == VK_DOWN)
        {
            rect_user.top += 1; // 아래쪽 화살표 키 누르면 사용자 사각형을 아래로 이동
            rect_user.bottom += 1;
        }
        else if (wParam == VK_UP)
        {
            rect_user.top -= 1; // 위쪽 화살표 키 누르면 사용자 사각형을 위로 이동
            rect_user.bottom -= 1;
        }
        InvalidateRect(hwnd, NULL, TRUE); // 화면을 갱신하기 위한 요청
        break;

    case WM_PAINT:
        hdc = GetDC(hwnd); // 화면 그리기를 위해 hdc 얻기

        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush_target);
        Rectangle(hdc, rect_target.left, rect_target.top, rect_target.right, rect_target.bottom); // 목표 사각형 그리기
        SelectObject(hdc, hOldBrush);

        HBRUSH hOldBrushUser = (HBRUSH)SelectObject(hdc, hBrush_user);
        Rectangle(hdc, rect_user.left, rect_user.top, rect_user.right, rect_user.bottom); // 사용자 사각형 그리기
        SelectObject(hdc, hOldBrushUser);

        if (RectIntersect(&rect_user, &rect_target))
        {
            TextOut(hdc, 10, 10, text, lstrlen(text)); // 사용자와 목표 사각형이 겹치면 텍스트 출력
        }

        ReleaseDC(hwnd, hdc); // hdc 해제
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd); // 창 닫기
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // 프로그램 종료 메시지 전송
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    // 사용한 브러시들을 삭제
    DeleteObject(hBrush_user);
    DeleteObject(hBrush_target);
    DeleteObject(hBrush_eraser);

    return S_OK;
}

#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    // 윈도우 클래스 선언.
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));    // 모두 0으로 초기화.

    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;

    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        return -1;  // 예외 처리
    }

    // Window viewport 영역 조정
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // 윈도우 생성
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007032 윤형식"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );

    // 오류 검사.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);

    }

    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW);  // 창 표시
    UpdateWindow(hwnd); // 창 업데이트

    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 메시지 처리.
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // 메시지 해석
            TranslateMessage(&msg);
            // 메시지 처리 함수로 전달
            DispatchMessage(&msg);
        }
    }

    // 윈도우 클래스 등록 해제
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    // 종료 메시지 반환
    return (int)msg.wParam;
}
