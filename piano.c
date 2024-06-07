#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void draw_piano(int c, int r); // 건반 그리는 함수
void draw_piano2(void); // 건반 위에 숫자와 음계를 출력하는 함수
void cursor(int x, int y); //콘솔 창에서 커서의 위치를 (x, y) 좌표로 이동시키는 함수
void touch_keyboard(int code); // 숫자 키를 누르면 해당 건반에 ▲을 출력하는 함수
void manual(void); // 사용법 설명 작성 함수
void practice_piano(void); // 옥타브와 음의 지연시간을 제어하는 함수
void arrow_key_control(int ocde, int* base_octave, int* time_delay); // 화살표 키 입력 제어 함수
int calc_frequency(int octave, int inx); // 주파수를 계산하는 함수
int play_score(void); // 악보를 실행하는 함수

int main(void) {
    SetConsoleOutputCP(949);
    SetConsoleCP(949);

    manual();
    practice_piano();

    return 0;
}

// 악보를 실행하는 함수
int play_score(void) {
    FILE* file;
    int duration, octave, note;

    fopen_s(&file, "score.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    while (fscanf_s(file, "%d %d %d", &octave, &note, &duration) == 3) {
        int frequency = calc_frequency(octave, note);
        Beep(frequency, duration);
    }

    fclose(file);
    return 0;
}

// 콘솔 창에서 커서의 위치를 (x, y)좌표로 이동시키는 함수
void cursor(int x, int y) {
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 사용법 설명 작성 함수
void manual(void) {
    printf("\n");
    printf(" 키보드의 숫자를 누르면\n");
    printf(" 해당 건반에 음이 표시되고,\n");
    printf(" 키↑: 한 옥타브 위로,     키↓:한 옥타브 아래로\n");
    printf(" 키←: 음의 지연시간 짧게, 키→:음의 지연시간 길게\n");
}

// 옥타브와 음의 지연시간을 제어하는 함수
void practice_piano(void) {
    int index[] = { 0, 2, 4, 5, 7, 9, 11, 12 };
    int freq[8], code, i;
    int base_octave = 4, time_delay = 500;

    draw_piano(8, 2);
    draw_piano2();

    do {
        for (i = 0; i < 8; i++)
            freq[i] = calc_frequency(base_octave, index[i]);
        code = _getch();
        if ('1' <= code && code <= '8') {
            code -= 49;
            touch_keyboard(code);
            Beep(freq[code], time_delay);
            draw_piano2();
        }else if ('9' == code) {
            play_score();
        }else {
            arrow_key_control(code, &base_octave, &time_delay);
        }
        cursor(1, 13);
        printf(" 현재 옥타브:%d, ", base_octave);
        printf("현재 지연시간:%4.2f초", time_delay / 1000.);

    } while (code != 27);
}

// 주파수를 계산하는 함수
int calc_frequency(int octave, int inx) {
    double do_scale = 32.7032;
    double ratio = pow(2., 1 / 12.), temp;
    int i;
    temp = do_scale * pow(2, octave - 1);
    for (i = 0; i < inx; i++) {
        temp = (int)(temp + 0.5);
        temp *= ratio;
    }
    return (int)temp;
}

// 건반 그리는 함수
void draw_piano(int c, int r) {
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[12];
    for (i = 1; i < 12; i++)
        b[i] = 0xa0 + i;
    printf("\n");
    printf("%c%c", a, b[3]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < r - 1; i++) {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++) {
            printf("   ");
            printf("%c%c", a, b[2]);
        }
        printf("\n");
        printf("%c%c", a, b[7]);
        for (j = 0; j < c - 1; j++) {
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[11]);
        }
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }
    printf("%c%c", a, b[2]);
    for (j = 0; j < c; j++) {
        printf("   ");
        printf("%c%c", a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

// 건반 위에 숫자와 음계를 출력하는 함수
void draw_piano2(void) {
    int i;
    char code[8][4] = { "도", "레", "미", "파", "솔", "라", "시", "도" };
    for (i = 0; i < 8; i++) {
        cursor(3 + i * 4, 8);
        printf("%2d", i + 1);
    }
    for (i = 0; i < 8; i++) {
        cursor(3 + i * 4, 10);
        printf("%s", code[i]);
    }
}

// 숫자 키를 누르면 해당 건반에 ▲을 출력하는 함수
void touch_keyboard(int code) {
    cursor(3 + code * 4, 10);
    printf("%c%c", 0xa1, 0xe3);
}

// 화살표 키 입력 제어 함수
void arrow_key_control(int code, int* base_octave, int* time_delay) {
    switch (code) {
    case 72: //위쪽 화살표 옥타브 증가
        *base_octave += 1;
        if (6 < *base_octave)
            *base_octave = 6;
        break;
    case 75: //왼쪽 화살표 지연시간 감소
        *time_delay -= 250;
        if (*time_delay < 250)
            *time_delay = 250;
        break;
    case 77: //오른쪽 화살표 지연시간 증가
        *time_delay += 250;
        if (1000 < *time_delay)
            *time_delay = 1000;
        break;
    case 80: //아래쪽 화살표 옥타브 감소
        *base_octave -= 1;
        if (*base_octave <= 2)
            *base_octave = 2;
        break;
    default:
        break;
    }
}
