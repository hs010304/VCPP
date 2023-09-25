#include <stdio.h> // 표준 입 출력
#include <conio.h> // _getch()
#include <chrono> // 시간 측정 
#define _CRT_SECURE_NO_WARNINGS // 경고 메시지 무시
#define ESC 27  // 아스키코드 정의
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
using namespace std; // C++ 표준 라이브러리 요소 사용 printf, chrono 등 (std:: 생략하기 위해)


int main() {
    chrono::system_clock::time_point Start = chrono::system_clock::now(); // 시간 측정을 시작하는 지점을 기록 (현재 시간을 Start 에 저장)

    printf("기술 목록 :\n↓→a  : 아도겐!=o\n→↓→s : 아이스볼!\n↑→↓c : 파이어볼!\n");

    while (1) { // 무한 루프
        int a, b = 0; // 변수 선언
        int adogen = 0, iceball = 0, fireball = 0; // 기술 입력 변수 선언
        int cnt = 0, cnt1 = 0, cnt2 = 0; // 입력 길이 카운트 변수 

        while ((a = _getch()) != ESC) { // ESC가 입력될 때까지 사용자의 입력을 받는 무한 루프
            if (a != 224) { // 방향키가 아닐 시
                b = a; // 현재 입력값 b에 저장
                printf("%c", b); // 입력된 문자 출력

                switch (b) {
                case UP:
                    printf("↑");
                    break;
                case DOWN:
                    printf("↓");
                    break;
                case RIGHT:
                    printf("→");
                    break;
                case LEFT:
                    printf("←");
                    break;
                }
                // 입력된 키의 따른 화면 출력 내용

                if ((adogen == 1 && b != RIGHT) || (adogen == 2 && b != 'a')) // 해당 변수에 조건이 충족되지 않을 시 초기화 (아도겐)
                {
                    cnt = 0;
                    adogen = 0;
                }
                if ((iceball == 1 && b != DOWN) || (iceball == 2 && b != RIGHT) || (iceball == 3 && b != 's')) // 해당 변수에 조건이 충족되지 않을 시 초기화 (아이스볼)
                {
                    cnt1 = 0;
                    iceball = 0;
                }
                if ((fireball == 1 && b != RIGHT) || (fireball == 2 && b != DOWN) || (fireball == 3 && b != 'c')) // 해당 변수에 조건이 충족되지 않을 시 초기화 (파이어볼)
                {
                    cnt2 = 0;
                    fireball = 0;
                }
            }
            else { // 입력 값이 방향키인 경우 처리
                b = _getch(); // 추가 입력 받음

                switch (b) {
                case UP:
                    printf("↑");
                    break;
                case DOWN:
                    printf("↓");
                    break;
                case RIGHT:
                    printf("→");
                    break;
                case LEFT:
                    printf("←");
                    break;
                }

                if ((adogen == 1 && b != RIGHT) || (adogen == 2 && b != 'a')) // 아도겐 초기화
                {
                    cnt = 0;
                    adogen = 0;
                }
                if ((iceball == 1 && b != DOWN) || (iceball == 2 && b != RIGHT) || (iceball == 3 && b != 's')) // 아이스볼 초기화
                {
                    cnt1 = 0;
                    iceball = 0;
                }
                if ((fireball == 1 && b != RIGHT) || (fireball == 2 && b != DOWN) || (fireball == 3 && b != 'c')) // 파이어볼 초기화
                {
                    cnt2 = 0;
                    fireball = 0;
                }
                // 첫 번째 조건문에서 방향키 이외의 값이 들어왔을경우 _getch()함수로 추가 입력을 받고 이 때도 방향키 이외의 값을 받을 수 
                // 있으므로, 재검사 실시 조건에 맞지 않을경우 초기화

                if ((b == DOWN)) { // 조건에 맞는 키가 입력되었을 때 카운트 증가 (아도겐)
                    adogen++;
                    cnt++;
                    Start = chrono::system_clock::now(); // 키가 입력된 시점부터 시간 시작
                }
                if ((b == RIGHT) && (cnt == 1)) {
                    adogen++;
                    cnt++;
                }

                if ((b == RIGHT)) { // 조건에 맞는 키가 입력되었을 때 카운트 증가 (아이스볼)
                    iceball++;
                    cnt1++;
                    Start = chrono::system_clock::now(); // 키가 입력된 시점부터 시간 시작
                }
                if ((b == DOWN) && (cnt1 == 1)) {
                    iceball++;
                    cnt1++;
                }
                if ((b == RIGHT) && (cnt1 == 2)) {
                    iceball++;
                    cnt1++;
                }

                if ((b == UP)) { // 조건에 맞는 키가 입력되었을 때 카운트 증가 (파이어볼)
                    fireball++;
                    cnt2++;
                    Start = chrono::system_clock::now(); // 키가 입력된 시점부터 시간 시작
                }
                if ((b == RIGHT) && (cnt2 == 1)) {
                    fireball++;
                    cnt2++;
                }
                if ((b == DOWN) && (cnt2 == 2)) {
                    fireball++;
                    cnt2++;
                }
            }
            if ((b == 'a') && (cnt == 2) && (adogen == 2)) { // 아도겐의 3번째 카운트가 'a'인 경우 탈출
                break;
            }
            if ((b == 's') && (cnt1 == 3) && (iceball == 3)) { // 아이스볼의 4번째 카운트가 's'인 경우 탈출
                break;
            }
            if ((b == 'c') && (cnt2 == 3) && (fireball == 3)) { // 파이어볼의 4번째 카운트가 'c'인 경우 탈출
                break;
            }
        }
        chrono::system_clock::time_point EndTime = chrono::system_clock::now(); // 시간 종료 지점
        chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(EndTime - Start); // 시간 저장
        if ((b == 'a') && (cnt == 2) && (adogen == 2) && (ms.count() <= 300)) { // 아도겐의 3번째 카운트가 'a'이며, 0.3초 이내에 입력된 경우
            printf("\n아도겐!=o\n");
            cnt = 0;
            adogen = 0;
        }
        else if ((b == 's') && (cnt1 == 3) && (iceball == 3) && (ms.count() <= 300)) { // 아이스볼의 4번째 카운트가 's'이며, 0.3초 이내에 입력된 경우
            printf("\n아이스볼!\n");
            cnt1 = 0;
            iceball = 0;
        }
        else if ((b == 'c') && (cnt2 == 3) && (fireball == 3) && (ms.count() <= 300)) { // 파이어볼의 4번째 카운트가 'c'이며, 0.3초 이내에 입력된 경우
            printf("\n파이어볼!\n");
            cnt2 = 0;
            fireball = 0;
        }

        if (a == ESC) break; // a의 입력된 값이 ESC인 경우 탈출
    }

    return 0;
}
