#include "yuhanCG.h"

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // �Ķ��� �귯�� ����
    RECT rect = { left, top, right, bottom }; // RECT Ÿ���� ������ �����ϰ� ���� ����
    FillRect(hdc, &rect, hBrush); // �Ķ��� �簢�� �׸���
    DeleteObject(hBrush); // �귯�� ����
}

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
    SelectObject(hdc, hBrush);
    DeleteObject(hBrush); // �귯�� ����
}

void DrawBonoBono(HWND hwnd, HDC hdc, int blink)
{

    if (blink)
    {
        HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // ������
        HBRUSH BlueBrush = CreateSolidBrush(RGB(127, 200, 255)); // �ϴû�
        HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 150, 255)); // ��ȫ��
        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // ���

        /// �� �׸���
        SelectObject(hdc, BlueBrush); // �ϴû� �귯��
        Ellipse(hdc, 250, 110, 550, 410); // ��

        /// �� �׸���
        SelectObject(hdc, PinkBrush); // ��ȫ�� �귯��
        Ellipse(hdc, 377, 244, 424, 322); // ��

        /// ��� �� �׸���
        SelectObject(hdc, WhiteBrush); // ��� �귯��
        Ellipse(hdc, 353, 245, 400, 292); // ���� ��� ��  
        Ellipse(hdc, 400, 245, 447, 292); // ���� ��� �� 

        /// �� �׸���
        SelectObject(hdc, BlackBrush); // ������ �귯��
        Ellipse(hdc, 275, 225, 284, 242); // ���� ��
        Ellipse(hdc, 525, 225, 534, 242); // ���� ��

        /// ������ �׸���
        SelectObject(hdc, WhiteBrush); // ��� �귯��
        Ellipse(hdc, 278, 228, 281, 236); // ���� ������
        Ellipse(hdc, 528, 227, 531, 236); // ���� ������

        /// �� �׸���
        SelectObject(hdc, BlackBrush); // ������ �귯��
        Ellipse(hdc, 383, 234, 417, 265); // ��

        /// ���� �׸���
        MoveToEx(hdc, 340, 255, NULL); // ���� ��� ����
        LineTo(hdc, 370, 262);
        MoveToEx(hdc, 340, 285, NULL); // ���� �ϴ� ����
        LineTo(hdc, 368, 272);

        MoveToEx(hdc, 465, 255, NULL); // ���� ��� ����
        LineTo(hdc, 430, 260);
        MoveToEx(hdc, 430, 270, NULL); // ���� �ϴ� ����
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

        HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0)); // ������
        HBRUSH BlueBrush = CreateSolidBrush(RGB(127, 200, 255)); // �ϴû�
        HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 150, 255)); // ��ȫ��
        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // ���

        /// �� �׸���
        SelectObject(hdc, BlueBrush); // �ϴû� �귯��
        Ellipse(hdc, 250, 110, 550, 410);

        /// �� �׸���
        SelectObject(hdc, PinkBrush); // ��ȫ�� �귯��
        Ellipse(hdc, 377, 244, 424, 322);

        /// ��� �� �׸���
        SelectObject(hdc, WhiteBrush); // ��� �귯��
        Ellipse(hdc, 353, 245, 400, 292); // ���� ��� ��  
        Ellipse(hdc, 400, 245, 447, 292); // ���� ��� �� 

        /// �� �׸���
        MoveToEx(hdc, 275, 225, NULL); // ���� ��� ��
        LineTo(hdc, 295, 230);
        MoveToEx(hdc, 292, 230, NULL); // ���� �ϴ� ��
        LineTo(hdc, 275, 250);

        MoveToEx(hdc, 510, 230, NULL); // ���� ��� ��
        LineTo(hdc, 529, 220);
        MoveToEx(hdc, 510, 230, NULL); // ���� �ϴ� ��
        LineTo(hdc, 529, 250);

        /// �� �׸���
        SelectObject(hdc, BlackBrush); // ������ �귯��
        Ellipse(hdc, 383, 234, 417, 265); // ��

        /// ���� �׸���
        MoveToEx(hdc, 340, 255, NULL); // ���� ��� ����
        LineTo(hdc, 370, 262);
        MoveToEx(hdc, 340, 285, NULL); // ���� �ϴ� ����
        LineTo(hdc, 368, 272);

        MoveToEx(hdc, 465, 255, NULL); // ���� ��� ����
        LineTo(hdc, 430, 260);
        MoveToEx(hdc, 430, 270, NULL); // ���� �ϴ� ����
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

    HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 200, 15)); // �����
    HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));  // ���

    /// �� �׸���
    SelectObject(hdc, YellowBrush); // ����� �귯��
    Ellipse(hdc, left, top, left + xlength / 3, top + ylength / 3);  // ���� ��

    SelectObject(hdc, YellowBrush); // ����� �귯��
    Ellipse(hdc, left + xlength * 2 / 3, top, left + xlength, top + ylength / 3);  // ������ ��

    /// �� �׸���
    SelectObject(hdc, YellowBrush); // ����� �귯��
    Ellipse(hdc, left + xlength / 18, top + ylength / 13, left + xlength / 18 * 17, top + ylength); // ��
    DeleteObject(YellowBrush);

    /// ���� �׸���
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 40 / 144, NULL); // ���� ����1
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 41 / 144, NULL); // ���� ����2
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 42 / 144, NULL); // ���� ����3
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 42 / 144);

    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 40 / 144, NULL); // ���� ����1
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 41 / 144, NULL); // ���� ����2
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 42 / 144, NULL); // ���� ����3
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 42 / 144);

    /// �� �׸���
    SelectObject(hdc, GetStockObject(BLACK_BRUSH)); // �� �׸��� (������)
    Ellipse(hdc, left + xlength * 17 / 54, top + ylength * 27 / 72, left + xlength * 20 / 54, top + ylength * 31 / 72); // ���� ��
    Ellipse(hdc, left + xlength * 32 / 54, top + ylength * 27 / 72, left + xlength * 35 / 54, top + ylength * 31 / 72); // ���� ��

    /// �� �׸���
    SelectObject(hdc, WhiteBrush); // ��� �귯��

    int mouthLeft = left + xlength * 8 / 20;
    int mouthRight = left + xlength / 2;
    int mouthTop = top + ylength * 35 / 72;
    int mouthBottom = top + ylength * 42 / 72;

    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom); // ���� ��

    mouthLeft = left + xlength / 2 - 1;  // ������ ����
    mouthRight = left + xlength * 12 / 20;  // ������ ����

    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom); // ���� ��

    DeleteObject(WhiteBrush);
}

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    /// ��� 1
    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL);
    LineTo(hdc, left, top + ylength * 9 / 36);

    /// ��� 2
    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL);
    LineTo(hdc, left + xlength, top);

    /// ��� 3
    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36);

    /// ��� 4
    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36);

    /// ���� 1
    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left, top + ylength);

    /// ���� 2
    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength);

    /// ���� 3
    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16);

    /// �ϴ� 1 
    MoveToEx(hdc, left, top + ylength, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength);

    /// �ϴ� 2
    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16);
}