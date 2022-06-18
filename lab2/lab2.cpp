#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

// структура списка
struct list {
    int data; // информационные данные
    list* next; //служебные данные
    list(int val = 0, list* p = nullptr) { //конструктор
        data = val;
        next = p;
    }
};

char bufRus[256];

// функция очистки строки
void clearStr(char* str) {
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            str[i] = '\n';
        else
            str[i] = 0;
    }
}

// функция пополнения списка на el с начала
list* push_front(list* head, int el) {
    list* member = new list(el, head);
    return member;
}

// функция пополнения списка на el с конца
list* push_back(list* head, int el) {
    list* p = head;
    list* member = new list(el, nullptr);
    if (head == nullptr) {
        return member;
    }
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = member;
    return head;
}

// функция удаления элемента с начала
list* pop_front(list* head) {
    if (head == nullptr) {
        printf("\nСписок пуст!");
        return head;
    }
    list* p = head;
    list* n = head->next;
    if (n == nullptr) {
        free(p);
        return nullptr;
    }

    head = new list(n->data, n->next);
    free(p);
    return head;
}

// функция удаления элемента с конца
list* pop_back(list* head) {
    if (head == nullptr) {
        printf("\nСписок пуст!");
        return head;
    }
    list* p = head;
    list* prev = head;
    while (p->next != nullptr) {
        if ((p->next)->next == nullptr) prev = p;
        p = p->next;
    }
    if (p == prev) {
        free(p);
        return nullptr;
    }
    prev->next = nullptr;
    return head;
}

// функция вывода списка в консоль
void printfList(list* head) {
    printf("\n");

    list* p = head;
    if (head == nullptr) {
        printf("Список пуст!");
        return;
    }

    while (p != nullptr) {
        printf("%d ", p->data);
        p = p->next;
    }
}

// функция получения длинны списка ~ количества элементов
int getLen(list* head) {
    int count = 0;
    list* p = head;
    if (head == nullptr)
        return 0;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

// функция получения указателя на элемент по индексу в списке
list* getElByInd(list* head, int ind) {
    list* p = head;
    int i = 0;
    while (i != ind) {
        i++;
        p = p->next;
    }
    return p;
}

// функция сортировки списка по убыванию
list* listSort(list* head) {
    int listSize = getLen(head);

    for (int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize - 1; j++) {
            list* first = getElByInd(head, j);
            list* second = getElByInd(head, j + 1);
            if (first->data < second->data) {

                int swap12 = first->data;
                first->data = second->data;
                second->data = swap12;

            }
        }
    }

    return head;
}

// функция функция получения убывающей последовательности минимальный элементов
list* minsequence(list* head) {
    list* sequence = nullptr;
    int listSize = getLen(head);
    bool uniqEl = true;
    for (int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize; j++) {
            if (getElByInd(head, i)->data == getElByInd(head, j)->data && i != j)
                uniqEl = false;
        }
        if (uniqEl == true)
            sequence = push_back(sequence, getElByInd(head, i)->data);
        uniqEl = true;
    }
    sequence = listSort(sequence);
    return sequence;
}

// функция создания списка
list* enterList() {

    char str[100];
    list* head = nullptr;
    puts("Создание списка. Вводите числа через Enter. Для окончания нажмите Enter дважды.");
    while (1) {
        gets_s(str);
        if (!head) {
            head = new list;
            head->data = atoi(str);
            continue;
        }
        if (!str[0]) break;
        head = push_back(head, atoi(str));
    }
    return head;


}

//открытие и чтение файла
list* inputFile() {
    printf("\nПрежде чем начинать чтение из файла убедитесь, что файл 'listData.txt' находится в папке с проектом и нажмите enter:");
    char c;
    scanf_s("%c", &c);

    FILE* fp;
    list* head = nullptr;
    char name[] = "listData.txt";
    int inpt = 1;
    while (fopen_s(&fp, name, "r") != 0) {
        printf("\nНе удалось открыть файл. Введите: \n0 - Выход\n1 - Повторная попытка \nВвод команды: ");
        if (inpt == 0)
            return(0);
        int chekInput = scanf_s("%d", &inpt);
        while (chekInput < 0 || (inpt < 0 && inpt > 1)) {
            printf("\nОшибка ввода. Попробуйте снова.\nВвод команды: ");
            int chekInput = scanf_s("%d", &inpt);
            if (inpt == 0) {
                return nullptr;
            }
            if (inpt == 1) {
                printf("Поместите файл с данными и нажмите enter:");
                scanf_s("%c", &c);
            }
        }
    }

    char str[100];
    while (1) {
        fgets(str, 100, fp);
        if (!head) {
            head = new list;
            head->data = atoi(str);
            continue;
        }
        if (feof(fp)) break;
        head = push_back(head, atoi(str));
    }
    //head = push_back(head, atoi(str));

    return head;

}

//Создание файла формата .txt
void plusTXT(char* str) {

    char bin[] = ".txt";
    strcat_s(str, 50, bin);
}


//добавление в файл списка напрямую с консоли
void consoleToFile(char* name) {
    FILE* fp;
    printf("\n%s", name);
    if (!fopen_s(&fp, name, "wb+")) {
        printf("\nЗаписываем данные, введите число:\n");
        char str[100] = {};
        while (1) {
            int num = 0;
            str[0] = 0;
            gets_s(str);
            if (!str[0]) break;
            num = atoi(str);
            fprintf(fp, "%d", num);
            fprintf(fp, "%s", "\n");
        }
        printf("\nФайл создан, данные записаны");
        fclose(fp);
    }
    else
        printf("Ошибка создания файла!");
}

//экспорт списка в файл
void exportToFile(list* head, char* name) {
    FILE* fp;
    list* p = head;
    printf("\n%s", name);

    if (!fopen_s(&fp, name, "wb+")) {
        char str[100] = {};
        int num = 0;
        while (p != nullptr) {
            //num = atoi(p);
            fprintf(fp, "%d", p->data);
            fprintf(fp, "%s", "\n");
            p = p->next;
        }
        printf("\nФайл создан, данные записаны");
        fclose(fp);
    }
    else
        printf("Ошибка создания файла!");
}

//главное меню программы
void Menu()
{
    int i, k, n, num, numnew;
    int inpt;
    const char* ss[] = { " 0 - Импорт списка из файла", " 1 - Создание списка с консоли", " 2 - Добавление элемента в конец списка",\
    " 3 - Добавление элемента в начало списка", " 4 - Удаление элемента из конца", \
    " 5 - Удаление элемента из начала"," 6 - Вывод размера списка", " 7 - Вывод списка", \
    " 8 - Вывод элемента по индексу", " 9 - Вывод убывающей последовательности уникальных элементов" , \
    "10 - Создание файла со списком, введённого с консоли", "11 - Экспорт списка в файл", "12 - Выход", "-------------------- ВЫБЕРИТЕ ЖЕЛАЕМУЮ ОПЦИЮ ---------------------" };
    k = sizeof(ss) / sizeof(ss[0]);

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    list* head = nullptr;
    list* subseq = nullptr;
    int checkInpt = -1;
    int ind;
    char name[50];

    while (1)
    {
        puts("\n------------------ РАБОТА С ОДНОСВЯЗНЫМ СПИСКОМ ------------------");
        for (i = 0; i < k; i++) puts(ss[i]);
        scanf_s("%d", &inpt);
        getchar();
        switch (inpt)
        {
        case 0: head = inputFile();             break;
        case 1: head = enterList();            break;
        case 2: printf("Число: "); scanf_s("%d", &num); head = push_back(head, num);      break;
        case 3: printf("Число: "); scanf_s("%d", &num); head = push_front(head, num);     break;
        case 4: head = pop_back(head);         break;
        case 5: head = pop_front(head);        break;
        case 6: printf("Размер списка = %d", getLen(head));          break;
        case 7: printf("Список: "); printfList(head);                break;
        case 8:
            if (head == nullptr) {
                printf("Список пуст!");
                break;
            }
            printf("Введите индекс: ");

            checkInpt = scanf_s("%d", &ind);
            while (checkInpt == 0) {
                printf("\nОшибка ввода, попробуйте снова: ");
                getchar();
                checkInpt = scanf_s("%d", &ind);
            }

            if (ind < 0) {
                printf("В списке нет отрицательных индексов у элементов!");
                break;
            }


            printf("Элемент = %d", getElByInd(head, ind)->data);  break;
        case 9: subseq = minsequence(head);
            printf("Последовательность уникальных элементов по убыванию:\n ");
            printfList(subseq);
            break;
        case 10:printf("При вводе имени создаваемого файла не нужно указывать бинарный формат файла! (Можно и на русском!)");
            printf("\nВведите имя файла для создания и записи данных: ");
            name[0] = 0;

            gets_s(name);
            plusTXT(name);
            consoleToFile(name);
            break;
        case 11:
            if (head == nullptr) {
                printf("Список пуст, экспортировать нечего!");
                break;
            }
            printf("При вводе имени создаваемого файла не нужно указывать бинарный формат файла! (Можно и на русском!)");
            printf("\nВведите имя файла для создания и записи данных: ");
            name[0] = 0;
            gets_s(name);
            plusTXT(name);
            exportToFile(head, name);
            break;
        case 12: printf("До свидания!"); free(head); free(subseq); return;
        default: printf("Неизвестная команда!");
        }
    }

}


int main()
{
    setlocale(LC_ALL, "Rus");
    Menu();

}