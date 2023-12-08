#pragma once

#include <windows.h>
#include <cmath>

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);	// ���簢���� �׸��� �Լ�

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center);						// ���� �׸��� �Լ�

void DrawBonoBono(HWND hWnd, HDC hdc, int blink);									// ���뺸�븦 �׸��� �Լ�

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);		// ���̾��� �׸��� �Լ�

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);		// ť�긦 �׸��� �Լ�