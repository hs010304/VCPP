#include <windows.h>

#define WINDOW_TITLE TEXT("202007032 윤형식")
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

POINT startPoint;
BOOL Draw = FALSE;
BOOL Move = FALSE;
HWND hwnd;                       //핸들러
HBRUSH PinkBrush, WhiteBrush;

int Move_X, Move_Y; // 이전 마우스 위치, 현재 마우스 위치 차이로 사각형 이동시 필요한 값 구하기
int DrawStart_X, DrawStart_Y, DrawEnd_X, DrawEnd_Y; // 이전 사각형 시작점, 끝점을 저장후 사각형 삭제후 새로운 사각형 그리기 위함

void Cleanup() {    // 리소스 해제 함수 (메모리 누수 방지)
    if (PinkBrush) {
        DeleteObject(PinkBrush);
        PinkBrush = NULL;
    }
    if (WhiteBrush) {
        DeleteObject(WhiteBrush);
        WhiteBrush = NULL;
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        // 브러쉬 생성 및 Draw, Move 변수 초기화
    case WM_CREATE:
        WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        PinkBrush = CreateSolidBrush(RGB(255, 0, 255));
        Move = FALSE;
        Draw = FALSE;
        Move_X = 0;
        Move_Y = 0;
        DrawStart_X = 0;
        DrawStart_Y = 0;
        DrawEnd_X = 0;
        DrawEnd_Y = 0;
        break;

    case WM_LBUTTONDOWN:    // 왼쪽 버튼 눌렀을시 Draw 활성화, 현재 마우스 좌표 저장
        Draw = TRUE;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP:
        if (Draw) {
            Draw = FALSE;
            int end_X = LOWORD(lParam);
            int end_Y = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);          //  hdc 가져오기
            SelectObject(hdc, WhiteBrush);
            SetROP2(hdc, R2_WHITE);         //  흰색 사용 하도록 설정 덮어씌우기
            Rectangle(hdc, DrawStart_X, DrawStart_Y, DrawEnd_X, DrawEnd_Y); //  함수 호출하여 흰색 사각형을 그림 (덮어씌우기)
            SetROP2(hdc, R2_COPYPEN);       // 픽셀 지정색으로 칠하기
            SelectObject(hdc, PinkBrush);
            Rectangle(hdc, startPoint.x, startPoint.y, end_X, end_Y); //  함수 호출하여 분홍색 사각형 그림 
            ReleaseDC(hwnd, hdc);           // dc 해제 메모리 누수 방지 
            DrawStart_X = startPoint.x;     // 이전 사각형의 x,y 좌표를 현재 좌표로 변경
            DrawStart_Y = startPoint.y;
            DrawEnd_X = end_X;
            DrawEnd_Y = end_Y;
        }
        break;

    case WM_RBUTTONDOWN:    //  오른쪽 버튼 눌렀을시 현재 마우스 위치가 이전에 그려진 사각형 위에 있는지 확인,
        //  조건 충족시 Move 활성화 현재 마우스 위치와 이전 사각형 시작점 사이의 X, Y 좌표 저장
        if (LOWORD(lParam) >= DrawStart_X && LOWORD(lParam) <= DrawEnd_X &&
            HIWORD(lParam) >= DrawStart_Y && HIWORD(lParam) <= DrawEnd_Y) {
            Move = TRUE;
            Move_X = LOWORD(lParam) - DrawStart_X;
            Move_Y = HIWORD(lParam) - DrawStart_Y;
        }
        break;

    case WM_RBUTTONUP:      // 오른쪽 버튼 땟을시 비활성화
        Move = FALSE;
        break;

    case WM_MOUSEMOVE:
        if (Draw) {         // draw 활성화시 현재좌표를 가져와서 이전 시작점부터 현재좌표까지 사각형 그리기 
            int Now_X = LOWORD(lParam);
            int Now_Y = HIWORD(lParam);
            HDC hdc = GetDC(hwnd);
            SetROP2(hdc, R2_COPYPEN);       // 사각형 색 채워서 만들기
            Rectangle(hdc, startPoint.x, startPoint.y, Now_X, Now_Y);
            SetROP2(hdc, R2_NOTXORPEN);     // 이전 사각형 지우기
            SelectObject(hdc, PinkBrush);
            Rectangle(hdc, startPoint.x, startPoint.y, Now_X, Now_Y);
            ReleaseDC(hwnd, hdc);
        }

        else if (Move && (wParam & MK_RBUTTON)) {   // move 활성화 오른쪽 버튼이 눌려있는 상태에서만 
            int newX = LOWORD(lParam) - Move_X;     // 현재 마우스 좌표에서 이동 시 시작 지점과의 차이 계산 
            int newY = HIWORD(lParam) - Move_Y;
            int width = DrawEnd_X - DrawStart_X;    // 이동중인 사각형의 너비 높이 계산 
            int height = DrawEnd_Y - DrawStart_Y;
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, WhiteBrush);
            SetROP2(hdc, R2_WHITE);                 // 이전 사각형을 지우고 백그라운드 흰색 처리 
            Rectangle(hdc, DrawStart_X, DrawStart_Y, DrawEnd_X, DrawEnd_Y);
            SetROP2(hdc, R2_COPYPEN);               // 현재 위치에 사각형 그리기
            SelectObject(hdc, PinkBrush);
            Rectangle(hdc, newX, newY, newX + width, newY + height);
            ReleaseDC(hwnd, hdc);
            DrawStart_X = newX;
            DrawStart_Y = newY;
            DrawEnd_X = newX + width;
            DrawEnd_Y = newY + height;
        }
        break;

    case WM_DESTROY:    // 윈도우 종료시 프로그램 종료
        PostQuitMessage(0);
        break;

    default:            // 사용자 정의한 메시지 처리가 아닌 경우, 기본 창 프로시저를 호출
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return S_OK;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {    // winmain 함수 부분
    WNDCLASS wc = { 0 };
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("윈도우 클래스 등록 실패"), TEXT("에러"), MB_ICONERROR | MB_OK);
        return -1;
    }

    hwnd = CreateWindow(
        wc.lpszClassName,   // 윈도우 클래스 이름 지정 
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),    // MAX 최대화 버튼 비활성화, THICK 크기 조절 프레임 비활성화
        0, 0,   // 초기 시작위치
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, // 부모 윈도우 및 메뉴 NULL 처리
        hInstance,  // 인스턴스 핸들 전달
        NULL        // 추가적인 데이터 전달할 포인터, 일반적으로 사용 x
    );

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("윈도우 생성 실패"), TEXT("에러"), MB_ICONERROR | MB_OK);
        return -1;
    }

    ShowWindow(hwnd, nCmdShow); //  윈도우창 화면에 표시
    UpdateWindow(hwnd);

    MSG msg;    // 사용자 입력, 시스템 이벤트 감지 
    while (GetMessage(&msg, hwnd, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

