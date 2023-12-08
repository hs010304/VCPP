#pragma once

#include <windows.h>
#include <cmath>

void DrawRectangle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);	// 직사각형을 그리는 함수

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center);						// 원을 그리는 함수

void DrawBonoBono(HWND hWnd, HDC hdc, int blink);									// 보노보노를 그리는 함수

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);		// 라이언을 그리는 함수

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);		// 큐브를 그리는 함수