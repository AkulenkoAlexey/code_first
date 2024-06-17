#include <stdio.h>
#include <math.h>
#include <locale.h>

#define PI 3.14159265358979323846

int main() {
    // Локализация русского языка
    setlocale(LC_ALL, "RUS");
    
    // Создание и открытие файлов .cfg и .dat
    FILE* cfgFile = fopen("test.cfg", "w");
    FILE* datFile = fopen("test.dat", "w");

    // Проверка успешного открытия файлов
    if (cfgFile == NULL || datFile == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    // Запись заголовка файла .cfg
    fprintf(cfgFile, "Stanciya 110/35/6,BINOM337 N10000208,12.04.2024\n");
    fprintf(cfgFile, "6,6A,6D\n");
    fprintf(cfgFile, "1,Ia,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "2,Ib,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "3,Ic,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "4,Ua,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "5,Ub,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "6,Uc,,0,A,1,0,0,-11000,11000,57.735,57.735,S\n");
    fprintf(cfgFile, "1,Pysk MTZ1,,,1\n");
    fprintf(cfgFile, "2,Pysk MTZ2,,,1\n");
    fprintf(cfgFile, "3,Pysk TO,,,1\n");
    fprintf(cfgFile, "50.000000\n");
    fprintf(cfgFile, "1\n");
    fprintf(cfgFile, "-80000,80000\n");
    fprintf(cfgFile, "17/06/2024,10:21:49.151830\n");
    fprintf(cfgFile, "17/06/2024,10:21:51.154545\n");
    fprintf(cfgFile, "ASCII\n");
    fprintf(cfgFile, "1\n");

    // Моделирование данных в файле .dat
    int numSamples = 10000; // Общее количество выборок
    int normalModeSamples = 1000; // Количество выборок в нормальном режиме (1000 мс)
    int Ia; // Аналоговые сигналы

    for (int i = 0; i < numSamples; ++i) {
        // Моделирование аналоговых сигналов (синусоида в нормальном режиме, короткое замыкание в аварийном)
        if (i < normalModeSamples) {
            Ia = 1000.0 * sin(2 * PI * i / 180) + 10000 - i * 10; // Аварийный режим: скачек сигнала
            Ib = 1000.0 * sin(2 * PI * (i + 120) / 180) + 10000 - i * 10; // Аварийный режим: скачек сигнала 
            Ic = 1000.0 * sin(2 * PI * (i + 240) / 180) + 10000 - i * 10; // Аварийный режим: скачек сигнала
            Ua = 110000.0 * sin(2 * PI * i / 180); // Аварийный режим: скачек сигнала
            Ub = 1100.0 * sin(2 * PI * (i + 120) / 180); // Аварийный режим: скачек сигнала 
            Uc = 110000.0 * sin(2 * PI * (i + 240) / 180); // Аварийный режим: скачек сигнала


        }
        else {
            Ia = 1000.0 * sin(2 * PI * i / 180); // Нормальный режим: синусоидальный сигнал
            Ib = 1000.0 * sin(2 * PI * (i + 120) / 180); // Нормальный режим: синусоидальный сигнал
            Ic = 1000.0 * sin(2 * PI * (i + 240) / 180); // Нормальный режим: синусоидальный сигнал
            Ua = 110000.0 * sin(2 * PI * i / 180); // Аварийный режим: скачек сигнала
            Ub = 110000.0 * sin(2 * PI * (i + 120) / 180); // Аварийный режим: скачек сигнала 
            Uc = 110000.0 * sin(2 * PI * (i + 240) / 180); // Аварийный режим: скачек сигнала
        }

        // Запись данных в файл .dat
        fprintf(datFile, "%d,%d,%d\r\n", i + 1, i, Ia);
    }

    // Закрытие файлов
    fclose(cfgFile);
    fclose(datFile);

    printf("Файлы COMTRADE успешно созданы.\n");
    return 0;
}
