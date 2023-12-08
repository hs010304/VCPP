#include "yuhanCG.h"

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색 브러시 생성
    RECT rect = { left, top, right, bottom }; // RECT 타입의 변수를 생성하고 값을 설정
    FillRect(hdc, &rect, hBrush); // 파란색 사각형 그리기
    DeleteObject(hBrush); // 브러시 삭제
}

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
    SelectObject(hdc, hBrush);
    DeleteObject(hBrush); // 브러시 삭제
}

void DrawBonoBono(HWND hwnd, HDC hdc, int blink)
{

    if (blink)
    {
        HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검은색
        HBRUSH BlueBrush = CreateSolidBrush(RGB(127, 200, 255)); // 하늘색
        HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 150, 255)); // 분홍색
        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색

        /// 얼굴 그리기
        SelectObject(hdc, BlueBrush); // 하늘색 브러시
        Ellipse(hdc, 250, 110, 550, 410); // 얼굴

        /// 입 그리기
        SelectObject(hdc, PinkBrush); // 분홍색 브러시
        Ellipse(hdc, 377, 244, 424, 322); // 입

        /// 흰색 원 그리기
        SelectObject(hdc, WhiteBrush); // 흰색 브러시
        Ellipse(hdc, 353, 245, 400, 292); // 좌측 흰색 원  
        Ellipse(hdc, 400, 245, 447, 292); // 우측 흰색 원 

        /// 눈 그리기
        SelectObject(hdc, BlackBrush); // 검은색 브러시
        Ellipse(hdc, 275, 225, 284, 242); // 좌측 눈
        Ellipse(hdc, 525, 225, 534, 242); // 우측 눈

        /// 눈동자 그리기
        SelectObject(hdc, WhiteBrush); // 흰색 브러시
        Ellipse(hdc, 278, 228, 281, 236); // 좌측 눈동자
        Ellipse(hdc, 528, 227, 531, 236); // 우측 눈동자

        /// 코 그리기
        SelectObject(hdc, BlackBrush); // 검은색 브러시
        Ellipse(hdc, 383, 234, 417, 265); // 코

        /// 수염 그리기
        MoveToEx(hdc, 340, 255, NULL); // 좌측 상단 수염
        LineTo(hdc, 370, 262);
        MoveToEx(hdc, 340, 285, NULL); // 좌측 하단 수염
        LineTo(hdc, 368, 272);

        MoveToEx(hdc, 465, 255, NULL); // 우측 상단 수염
        LineTo(hdc, 430, 260);
        MoveToEx(hdc, 430, 270, NULL); // 우측 하단 수염
        LineTo(hdc, 468, 290);

        DeleteObject(BlackBrush);
        DeleteObject(BlueBrush);
        DeleteObject(PinkBrush);
        DeleteObject(WhiteBrush);
    }

    else
    {
        HDC hdc = GetDC(hwnd);
        RECT rect;
        GetClientRect(hwnd, &rect);

        HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검은색
        HBRUSH BlueBrush = CreateSolidBrush(RGB(127, 200, 255)); // 하늘색
        HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 150, 255)); // 분홍색
        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색

        /// 얼굴 그리기
        SelectObject(hdc, BlueBrush); // 하늘색 브러시
        Ellipse(hdc, 250, 110, 550, 410);

        /// 입 그리기
        SelectObject(hdc, PinkBrush); // 분홍색 브러시
        Ellipse(hdc, 377, 244, 424, 322);

        /// 흰색 원 그리기
        SelectObject(hdc, WhiteBrush); // 흰색 브러시
        Ellipse(hdc, 353, 245, 400, 292); // 좌측 흰색 원  
        Ellipse(hdc, 400, 245, 447, 292); // 우측 흰색 원 

        /// 눈 그리기
        MoveToEx(hdc, 275, 225, NULL); // 좌측 상단 눈
        LineTo(hdc, 295, 230);
        MoveToEx(hdc, 292, 230, NULL); // 좌측 하단 눈
        LineTo(hdc, 275, 250);

        MoveToEx(hdc, 510, 230, NULL); // 우측 상단 눈
        LineTo(hdc, 529, 220);
        MoveToEx(hdc, 510, 230, NULL); // 우측 하단 눈
        LineTo(hdc, 529, 250);

        /// 코 그리기
        SelectObject(hdc, BlackBrush); // 검은색 브러시
        Ellipse(hdc, 383, 234, 417, 265); // 코

        /// 수염 그리기
        MoveToEx(hdc, 340, 255, NULL); // 좌측 상단 수염
        LineTo(hdc, 370, 262);
        MoveToEx(hdc, 340, 285, NULL); // 좌측 하단 수염
        LineTo(hdc, 368, 272);

        MoveToEx(hdc, 465, 255, NULL); // 우측 상단 수염
        LineTo(hdc, 430, 260);
        MoveToEx(hdc, 430, 270, NULL); // 우측 하단 수염
        LineTo(hdc, 468, 290);

        DeleteObject(BlackBrush);
        DeleteObject(BlueBrush);
        DeleteObject(PinkBrush);
        DeleteObject(WhiteBrush);

        ReleaseDC(hwnd, hdc);
    }
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 200, 15)); // 노란색
    HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));  // 흰색

    /// 귀 그리기
    SelectObject(hdc, YellowBrush); // 노란색 브러시
    Ellipse(hdc, left, top, left + xlength / 3, top + ylength / 3);  // 왼쪽 귀

    SelectObject(hdc, YellowBrush); // 노란색 브러시
    Ellipse(hdc, left + xlength * 2 / 3, top, left + xlength, top + ylength / 3);  // 오른쪽 귀

    /// 얼굴 그리기
    SelectObject(hdc, YellowBrush); // 노란색 브러시
    Ellipse(hdc, left + xlength / 18, top + ylength / 13, left + xlength / 18 * 17, top + ylength); // 얼굴
    DeleteObject(YellowBrush);

    /// 눈썹 그리기
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 40 / 144, NULL); // 좌측 눈썹1
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 41 / 144, NULL); // 좌측 눈썹2
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 42 / 144, NULL); // 좌측 눈썹3
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 42 / 144);

    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 40 / 144, NULL); // 우측 눈썹1
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 41 / 144, NULL); // 우측 눈썹2
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 42 / 144, NULL); // 우측 눈썹3
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 42 / 144);

    /// 눈 그리기
    SelectObject(hdc, GetStockObject(BLACK_BRUSH)); // 눈 그리기 (검정색)
    Ellipse(hdc, left + xlength * 17 / 54, top + ylength * 27 / 72, left + xlength * 20 / 54, top + ylength * 31 / 72); // 좌측 눈
    Ellipse(hdc, left + xlength * 32 / 54, top + ylength * 27 / 72, left + xlength * 35 / 54, top + ylength * 31 / 72); // 우측 눈

    /// 입 그리기
    SelectObject(hdc, WhiteBrush); // 흰색 브러시

    int mouthLeft = left + xlength * 8 / 20;
    int mouthRight = left + xlength / 2;
    int mouthTop = top + ylength * 35 / 72;
    int mouthBottom = top + ylength * 42 / 72;

    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom); // 좌측 입

    mouthLeft = left + xlength / 2 - 1;  // 오른쪽 좌측
    mouthRight = left + xlength * 12 / 20;  // 오른쪽 우측

    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom); // 우측 입

    DeleteObject(WhiteBrush);
}

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    /// 상단 1
    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL);
    LineTo(hdc, left, top + ylength * 9 / 36);

    /// 상단 2
    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL);
    LineTo(hdc, left + xlength, top);

    /// 상단 3
    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36);

    /// 상단 4
    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36);

    /// 세로 1
    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left, top + ylength);

    /// 세로 2
    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength);

    /// 세로 3
    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16);

    /// 하단 1 
    MoveToEx(hdc, left, top + ylength, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength);

    /// 하단 2
    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16);
}