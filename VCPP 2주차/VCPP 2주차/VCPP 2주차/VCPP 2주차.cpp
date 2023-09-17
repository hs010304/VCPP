#include <stdio.h>
#include <conio.h>

int main() {
    printf("202007032 윤형식 VC++\n\n");

    while (1) {
        printf("command>");
        char input;
        char buffer[100];
        int bufferIndex = 0;

        while (1) {
            input = _getch();

            if (input == '\r') {
                buffer[bufferIndex] = '\0';
                break;
            }
            else if (input == 27) {
                return 0;
            }
            else {
                putchar(input);
                buffer[bufferIndex++] = input;
            }
        }

        printf("\n");

        if (buffer[0] != '\0') {
            switch (buffer[0]) {
            case 'q':
                printf("qwer 화이팅\n");
                break;
            case 'w':
                printf("과제 너무 좋다\n");
                break;
            case 'e':
                printf("담주부턴 과제량 3배다\n");
                break;
            case 'r':
                printf("행복합니다\n");
                break;
            default:
                printf("오류: 다른 글자를 입력하셨습니다.\n");
                break;
            }
        }
    }

    return 0;
}
