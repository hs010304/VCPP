#include "yuhanCG.h"

// 마우스 버튼 상태 변수
BOOL isMouseLButtonPressed = FALSE;
BOOL isMouseRButtonPressed = FALSE;

// 도형 모드 상태 변수
BOOL isRec = FALSE;
BOOL isCircle = FALSE;
BOOL isBonoBono = FALSE;
BOOL isRyan = FALSE;
BOOL isCube = TRUE;
BOOL blink = TRUE;

// 마우스 클릭 시작점과 끝점 변수
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startPoint1 = { 0 };
POINT endPoint1 = { 0 };
POINT center;

// 기타 변수
int radius = 0;
double xlength = 0, ylength = 0, left = 0, top = 0, right = 0, bottom = 0;
RECT Rect1;

// 커서 설정
static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        RECT rc;
        rc = { 16, 90, 777, 465 };

        // 특정 영역에 마우스가 있을 때 크로스커서를, 그 외의 경우에 화살커서를 설정
        if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
        {
            SetCursor(hCrossCursor);
            return TRUE;
        }
        else
        {
            SetCursor(hArrowCursor);
            return TRUE;
        }
    }
    break;

    case WM_COMMAND:
        // 버튼 클릭에 따라 도형 모드 설정
        if (LOWORD(wParam) == 1)
        {
            isRec = TRUE;
            isCircle = FALSE;
            isBonoBono = FALSE;
            isRyan = FALSE;
            isCube = FALSE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 2)
        {
            isRec = FALSE;
            isCircle = TRUE;
            isBonoBono = FALSE;
            isRyan = FALSE;
            isCube = FALSE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 3) {
            isRec = FALSE;
            isCircle = FALSE;
            isBonoBono = TRUE;
            isRyan = FALSE;
            isCube = FALSE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4)
        {
            isRec = FALSE;
            isCircle = FALSE;
            isBonoBono = FALSE;
            isRyan = TRUE;
            isCube = FALSE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 5)
        {
            isRec = FALSE;
            isCircle = FALSE;
            isBonoBono = FALSE;
            isRyan = FALSE;
            isCube = TRUE;
            SetFocus(hwnd);
        }

        break;

    case WM_LBUTTONDOWN:
    {
        // 현재 마우스 커서의 위치를 얻어옴
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        // 특정 영역에서 왼쪽 마우스 버튼이 눌릴 때 시작점 설정
        RECT clientRect = { 16, 90, 800 - 32, 480 - 56 };

        if (PtInRect(&clientRect, pt))
        {
            // 시작점 및 중심점 설정
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            center.x = LOWORD(lParam);
            center.y = HIWORD(lParam);

            // 왼쪽 마우스 버튼이 눌린 상태로 설정
            isMouseLButtonPressed = TRUE;
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        // 왼쪽 마우스 버튼 떼어질 때 끝점 설정 및 화면 갱신
        endPoint = { LOWORD(lParam), HIWORD(lParam) };
        isMouseLButtonPressed = 0;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        if (isRec)
        {

            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };

            // 사각형 모드에서 우클릭시 시작점 설정
            if (PtInRect(&Rect1, clientPoint)) {
                startPoint1 = endPoint1 = clientPoint;
                isMouseRButtonPressed = 1;
            }
        }
        if (isCircle)
        {

            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };

            // 원 모드에서 우클릭시 시작점 설정
            isMouseRButtonPressed = 1;
            startPoint1 = endPoint1 = clientPoint;
        }
    }
    break;

    case WM_RBUTTONUP:
    {
        // 우클릭 떼어질 때 상태 초기화
        isMouseRButtonPressed = 0;
    }
    break;
    case WM_MOUSEMOVE:
    {

        if (isMouseLButtonPressed)
        {
            // 왼쪽 마우스 드래그 중일 때 계산 및 화면 갱신
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc = { 16, 90, 780, 464 };
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
            }
            int deltaX = LOWORD(lParam) - center.x;
            int deltaY = HIWORD(lParam) - center.y;


            radius = static_cast<int>(sqrt(deltaX * deltaX + deltaY * deltaY));

            // 화면 갱신
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isRec && isMouseRButtonPressed)
        {
            // 우클릭 드래그 중일 때 계산 및 화면 갱신
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc = { 16, 90, 780, 464 };
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                endPoint1.x = LOWORD(lParam);
                endPoint1.y = HIWORD(lParam);
            }

            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // 사각형의 위치 조정 및 화면 갱신
            OffsetRect(&Rect1, deltaX, deltaY);
            startPoint1 = endPoint1;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isCircle && isMouseRButtonPressed)
        {
            // 우클릭 드래그 중일 때 원의 반지름 조정 및 화면 갱신
            int deltaX = LOWORD(lParam) - center.x;
            int deltaY = HIWORD(lParam) - center.y;


            radius += (deltaX > 0) ? 5 : -5;
            if (radius < 0)
            {
                radius = 0;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_KEYDOWN:
        // 스페이스바를 누르면 깜빡임 효과를 비활성화하고 화면을 갱신
        if (wParam == VK_SPACE) {
            blink = FALSE;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        // 스페이스바를 뗄 때 깜빡임 효과를 다시 활성화하고 화면을 갱신
        if (wParam == VK_SPACE) {
            blink = TRUE;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        // 화면을 그리기 위한 작업을 수행하는 부분
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc = { 16, 90, 776, 464 };

        // 백그라운드를 흰색으로 칠함
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &rc, whiteBrush);
        DeleteObject(whiteBrush);

        GetClientRect(hwnd, &rc);

        // 사각형 그리기
        if (isRec && !isMouseRButtonPressed)
        {
            Rect1.left = min(startPoint.x, endPoint.x);
            Rect1.top = min(startPoint.y, endPoint.y);
            Rect1.right = max(startPoint.x, endPoint.x);
            Rect1.bottom = max(startPoint.y, endPoint.y);
            DrawRectangle(hwnd, hdc, Rect1.left, Rect1.top, Rect1.right, Rect1.bottom);
        }

        // 사각형이 그려진 상태에서 오른쪽 마우스 버튼이 눌렸을 때 파란색으로 채우기
        if (isMouseRButtonPressed && isRec)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);


            HBRUSH BlueBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &Rect1, BlueBrush);
            DeleteObject(BlueBrush);
        }

        // 원 그리기
        if (isCircle)
        {
            DrawCircle(hwnd, hdc, radius, center);
        }

        // Bonobono 그리기
        if (isBonoBono)
        {
            DrawBonoBono(hwnd, hdc, blink);
        }

        // 외곽선 그리기
        int left1 = 16;
        int top1 = 90;
        int right1 = rc.right - 16;
        int bottom1 = rc.bottom - 16;

        RECT rect1 = { left1, top1, right1, bottom1 };
        FrameRect(hdc, &rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));

        // 내부 외곽선 그리기
        int left2 = 8;
        int top2 = 8;
        int right2 = rc.right - 8;
        int bottom2 = rc.bottom - 8;

        RECT rect2 = { left2, top2, right2, bottom2 };
        FrameRect(hdc, &rect2, (HBRUSH)GetStockObject(BLACK_BRUSH));

        // Ryan 그리기
        if (isRyan)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            left = min(startPoint.x, endPoint.x);
            top = min(startPoint.y, endPoint.y);
            right = max(startPoint.x, endPoint.x);
            bottom = max(startPoint.y, endPoint.y);

            DrawRyan(hwnd, hdc, left, top, right, bottom);
        }

        // Cube 그리기
        if (isCube)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            left = min(startPoint.x, endPoint.x);
            top = min(startPoint.y, endPoint.y);
            right = max(startPoint.x, endPoint.x);
            bottom = max(startPoint.y, endPoint.y);

            DrawCube(hwnd, hdc, left, top, right, bottom);
        }
        ReleaseDC(hwnd, hdc);

    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    const wchar_t WINDOW_NAME[] = L"202007032 윤형식";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    LPCTSTR cursor = IDC_HAND;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,

        CW_USEDEFAULT, CW_USEDEFAULT, 810, 520,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonSpacing = 12;
    int leftMargin = 24;

    CreateWindow(TEXT("BUTTON"), TEXT("Box"), WS_VISIBLE | WS_CHILD, leftMargin - 8, 16, buttonWidth, buttonHeight, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Circle"), WS_VISIBLE | WS_CHILD, leftMargin - 4 + buttonWidth + buttonSpacing + 1, 16, buttonWidth, buttonHeight, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Bonobono"), WS_VISIBLE | WS_CHILD, leftMargin + 2 * (buttonWidth + buttonSpacing) + 2, 16, buttonWidth, buttonHeight, hwnd, (HMENU)3, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Ryan"), WS_VISIBLE | WS_CHILD, leftMargin + 3 * (buttonWidth + buttonSpacing) + 3, 16, buttonWidth, buttonHeight, hwnd, (HMENU)4, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Cube"), WS_VISIBLE | WS_CHILD, leftMargin + 4 * (buttonWidth + buttonSpacing) + 4, 16, buttonWidth, buttonHeight, hwnd, (HMENU)5, NULL, NULL);
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}