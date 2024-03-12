#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

enum Zodiaks {
	ARIES = 4, TAURUS = 5, GEMINI = 6, CANCER = 7, LEO = 8, VIRGO = 9, LIBRA = 10, SCORPIO = 11, SAGITTARIUS = 12, CAPRICORN = 1, AQUARIUS = 2, PISCES = 3
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
			return "AQUARIUS";
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
			return "VIRGO";
		case 10:
			return "LIBRA";
		case 11:
			return "SCORPIO";
		case 12:
			return "SAGITTARIUS";
	}
	return "";
}

enum Zodiaks getZodiak(int number) {
	switch (number) {
		case 1:
			return CAPRICORN;
		case 2:
			return AQUARIUS;
		case 3:
			return PISCES;
		case 4:
			return ARIES;
		case 5:
			return TAURUS;
		case 6:
			return GEMINI;
		case 7:
			return CANCER;
		case 8:
			return LEO;
		case 9:
			return VIRGO;
		case 10:
			return LIBRA;
		case 11:
			return SCORPIO;
		case 12:
			return SAGITTARIUS;
	}
}

int getMaxId(struct ZNAK* notes) {
	int maxId = -1;
	for (int i = 0; i < 100; i++) {
		struct ZNAK note = notes[i];
		maxId = note.id > maxId ? note.id : maxId;
	}
	return maxId;
}

int generateId(struct ZNAK* notes) {
	return getMaxId(notes) + 1;
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

struct ZNAK* addNewNote(struct ZNAK* notes, struct ZNAK note) {
	int len = sizeof(notes);
	notes[len] = note;
	struct ZNAK* buff = (struct ZNAK*)malloc(sizeof(struct ZNAK) * 100);
	notes = sortNotes(notes);
	return buff;
}

void enterNewNote(struct ZNAK* notes) {
	int id = generateId(notes);
	char name[20], surname[20];
	int birthday[3];
	printf("Введите имя: ");
	scanf("%s", name);
	printf("Введите фамилию: ");
	scanf("%s", surname);
	printf("Формат даты рождения - xx.xx.xxxx\nВведите дату рождения: ");
	scanf("%d.%d.%d", &birthday[0], &birthday[1], &birthday[2]);
	enum Zodiaks zodiak = (enum Zodiaks) birthday[1];
	struct ZNAK note = { id, name, surname, zodiak, birthday };
	FILE* file = fopen("structs.txt", "w");
	if (file == NULL) {
		printf("Произошла ошибка записи в файл");
		return;
	}
	struct ZNAK *buff = (struct ZNAK*)malloc(sizeof(struct ZNAK) * 100);
	buff = addNewNote(notes, note);
	fwrite(buff, sizeof(buff), 100, file);
	fclose(file);
}

void printNotes(struct ZNAK* notes) {
	for (int i = 0; i < 100; i++) {
		struct ZNAK note = notes[i];
		if (note.id == -842150451) continue;
		printf("ID: %d\nName: %s\nSurname: %s\nBirthday: %d.%d.%d\nZodiak: %s", note.id, note.name, note.surname, note.birthday[0], note.birthday[1], note.birthday[2], getZodiakName(note.birthday[1]));
	}
}

void printNotesByMonth(struct ZNAK* notes) {
	int month;
	int isWas = 0;
	printf("Введите номер месяца: ");
	scanf("%d", &month);
	for (int i = 0; i < 100; i++) {
		struct ZNAK note = notes[i];
		if (note.birthday[1] == month) {
			printf("ID: %d\nName: %s\nSurname: %s\nBirthday: %d.%d.%d\nZodiak: %s", note.id, note.name, note.surname, note.birthday[0], note.birthday[1], note.birthday[2], getZodiakName(note.birthday[1]));
			isWas = 1;
		}
	}
	if (isWas == 0) {
		printf("Извините, но людей, родившихся в указанный месяц нет в записях :(\n");
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	printMenu();
	int choice = 5;
	scanf("%d", &choice);
	struct ZNAK* notes = (struct ZNAK*) malloc(sizeof(struct ZNAK) * 100);
	FILE* file = fopen("structs.txt", "rb");
	if (file == NULL) {
		printf("Ошибка доступа к файлу :(");
		exit(-1);
	}
	fread(notes, sizeof(struct ZNAK), 64, file);
	fclose(file);
	while (1) {
		switch (choice) {
			case 1:
				system("cls");
				enterNewNote(notes);
				break;
			case 2:
				system("cls");
				printNotes(notes);
				break;
			case 3:
				system("cls");
				break;
			case 4:
				system("cls");
				printNotesByMonth(notes);
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