
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

void draw_check02(int c, int r);
void gotoxy(int x, int y);
void display_piano_keyboard(void);
void touch_keyboard(int code);
void display_manual(void);
void practice_piano(void);
int calc_frequency(int octave, int inx);
void arrow_key_control(int ocde, int *base_octave, int *time_delay);
void play_note(int note, int duration);

int main(void){
    SetConsoleOutputCP(949);
    SetConsoleCP(949);
    display_manual();
    practice_piano();

    FILE *file;
    int note, duration;

    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    while (fscanf(file, "%d %d", &note, &duration) == 2) {
        play_note(note, duration);
    }

    fclose(file);
    return 0;
}

//�׽�Ʈ
void play_note(int note, int duration) {
    int frequency = (int)(440 * pow(2, (note - 69) / 12.0)); // MIDI ��Ʈ�� ���ļ��� ��ȯ
    Beep(frequency, duration); // ���ļ��� ���� �ð����� ���� ����
}

//�ܼ� â���� Ŀ���� ��ġ�� (x, y) ��ǥ�� �̵���Ű�� �Լ��Դϴ�.
void gotoxy(int x, int y){
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*�ǹ��� ������ ���踦 ����ϴ� ���α׷��� ���� �Լ� display_manual*/
void display_manual(void){
    printf("Ű������ ���ڸ� ������\n");
    printf("�ش� �ǹݿ� ���� ǥ�õǰ�,\n");
    printf("Ű��: �� ��Ÿ�� ����, Ű��:�� ��Ÿ�� �Ʒ���\n");
    printf("Ű��: ���� �����ð� ª��, Ű��:���� �����ð� ���\n");
}

/*��Ÿ��� ���� �����ð��� �����ϴ� �Լ� practice_piano*/
void practice_piano(void){
    int index[] = { 0, 2, 4, 5, 7, 9, 11, 12 };
    int freq[8], code, i;
    int base_octave = 4,
    time_delay = 500;
    draw_check02(8, 2);
    display_piano_keyboard();
    do {
        for (i = 0; i < 8; i++)
            freq[i] = calc_frequency(base_octave, index[i]);
        code = getch();
        if('1' <= code&&code <= '8') {
            code -= 49;
            touch_keyboard(code);
            Beep(freq[code], time_delay);
            display_piano_keyboard();
        }else
            arrow_key_control(code, &base_octave, &time_delay);
        gotoxy(1, 10);
        printf("���� ��Ÿ��:%d, ", base_octave);
        printf("���� �����ð�:%4.2f��", time_delay / 1000.);
    }while (code != 27);
}

/*��Ÿ�꿡 ���� ���Ժ� ���ļ��� ����Ͽ� ��ȯ�ϴ� �Լ� calc_frequency*/
int calc_frequency(int octave, int inx){
    double do_scale = 32.7032;
    double ratio = pow(2., 1 / 12.), temp;
    int i;
    temp = do_scale*pow(2, octave - 1);
    for (i = 0; i < inx; i++){
        temp = (int)(temp + 0.5);
        temp *= ratio;
    }
    return (int)temp;
}

/*�ǹ� ���� ���ڿ� ���踦 ����ϴ� �Լ� display_piano_keyboard*/
void display_piano_keyboard(void){
    int i;
    char code[8][4] = { "��", "��", "��", "��", "��", "��", "��", "��" };
    for (i = 0; i < 8; i++) {
        gotoxy(3 + i * 4, 6);
        printf("%2d", i + 1);
    }
    for (i = 0; i < 8; i++) {
        gotoxy(3 + i * 4, 8);
        printf("%s", code[i]);
    }
}

/*���� Ű�� ������ �ش� �ǹݿ� ���� ����ϴ� �Լ� touch_keyboard*/
void touch_keyboard(int code){
    gotoxy(3 + code * 4, 8);
    printf("%c%c", 0xa1, 0xe3);
}

/*Ȯ��� �ٵ��� �׸��� �Լ� draw_check02*/
void draw_check02(int c, int r){
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[12];
    for (i = 1; i < 12; i++)
        b[i] = 0xa0 + i;
    printf("%c%c", a, b[3]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < r - 1; i++) {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++) {
            printf("  ");
            printf("%c%c", a, b[2]);
        }
        printf("\n");
        printf("%c%c", a, b[7]);
        for (j = 0; j < c - 1; j++) {
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[11]);
        }
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }
    printf("%c%c", a, b[2]);
    for (j = 0; j < c; j++) {
        printf("  ");
        printf("%c%c", a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

/*ȭ��ǥ Ű�� ��Ÿ��� ���� �����ð� ���� �Լ� arrow_key_control*/
void arrow_key_control(int code, int *base_octave, int *time_delay){
    switch (code) {
        case 72: //���� ȭ��ǥ ��Ÿ�� ����
            *base_octave += 1;
            if (6 < *base_octave)
                *base_octave = 6;
            break;
        case 75: //���� ȭ��ǥ �����ð� ����
            *time_delay -= 250;
            if (*time_delay < 250)
                *time_delay = 250;
            break;
        case 77: //������ ȭ��ǥ �����ð� ����
            *time_delay += 250;
            if (1000 < *time_delay)
                *time_delay = 1000;
            break;
        case 80: //�Ʒ��� ȭ��ǥ ��Ÿ�� ����
            *base_octave -= 1;
            if (*base_octave <= 2)
                *base_octave = 2;
            break;
        default:
            break;
    }
}