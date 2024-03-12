#include <stdio.h>

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

enum Zodiaks {
    ARIES = 4, TAURUS = 5
};

struct ZNAK {
    int id;
    char name[20], surname[20];
    enum Zodiaks zodiak;
    int birthday[3];
};

void printMenu() {
    printf("Меню:\n1) Ввести новую запись\n2) Печать всех записей\n3) Корректировка данных в записи\n4) Вывод людей по месяцу рождения\n5) Выйти\nВведите ваш выбор: ");
}

char const* getZodiakName(int number) {
    switch (number) {
    case 1:
        return "CAPRICORN";
    case 2:
        return "AQUARIS";
    case 3:
        return "PISCES";
    case 4:
        return "ARIES";
    case 5:
        return "TAURUS";
    case 6:
        return "GEMINI";
    case 7:
        return "CANCER";
    case 8:
        return "LEO";
    case 9:
        return "VIRGI";
    case 10:
        return "LIBRA";
    case 11:
        return "SCORPIO";
    case 12:
        return "SAGITTARIUS";
    }
    return "ert";
}

int generateId() {
    return 0;
}

struct ZNAK* addNewNote(struct ZNAK* buff, struct ZNAK note) {
    int len = sizeof(buff);
    buff[len] = note;
    struct ZNAK* notes = (struct ZNAK*) malloc(sizeof(struct ZNAK) * 100);
    //notes = sortNotes(buff);
    return notes;
}

struct ZNAK* sortNotes(struct ZNAK* notes) {
    for (int i = 0; i < 99; i++) {
        if (notes[i].zodiak > notes[i + 1].zodiak) {
            struct ZNAK temp = notes[i];
            notes[i] = notes[i + 1];
            notes[i + 1] = temp;
        }
    }
    return notes;
}

void enterNewNote(struct ZNAK* buff) {
    int id = generateId();
    char name[20], surname[20];
    int birthday[3];
    printf("Введите имя: ");
    scanf("%s", name);
    printf("Введите фамилию: ");
    scanf("%s", surname);
    printf("Формат даты рождения - xx.xx.xxxx\nВведите дату рождения: ");
    scanf("%d.%d.%d", &birthday[0], &birthday[1], &birthday[2]);
    enum Zodiaks zodiak = (enum Zodiaks)birthday[1];
    //struct ZNAK note = { id, name, surname, zodiak, birthday };
    FILE* file = fopen("structs.txt", "w");
    if (file == NULL) {
        printf("Произошла ошибка записи в файл");
        return;
    }
    struct ZNAK* notes = (struct ZNAK*)malloc(sizeof(struct ZNAK) * 100);
    //notes = addNewNote(buff, note);
    fwrite(notes, sizeof(notes), 100, file);
    fclose(file);
}

void printNotes(struct ZNAK* notes) {
    for (int i = 0; i < 100; i++) {
        struct ZNAK note = notes[i];
        printf("ID: %d\nName: %s\nSurname: %s\nBirthday: %d.%d.%d\nZodiak: %s", note.id, note.name, note.surname, note.birthday[0], note.birthday[1], note.birthday[2], getZodiakName(note.birthday[1]));
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    printMenu();
    int choice = 5;
    scanf("%d", &choice);
    struct ZNAK notes[100];
    while (1) {
        switch (choice) {
        case 1:
            system("cls");
            enterNewNote(notes);
            break;
        case 2:
            system("cls");
            break;
        case 3:
            system("cls");
            break;
        case 4:
            system("cls");
            break;
        case 5:
            system("cls");
            printf("Программа успешно завершена :)");
            exit(0);
            break;
        default:
            printf("Такого варианта нет. Попробуйте еще раз :)\n");
            break;
        }
        printMenu();
        scanf("%d", &choice);
    }
}