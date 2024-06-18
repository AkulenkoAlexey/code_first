#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define PI 3.14159265358979323846

int main() {
    // Локализация русского языка
    setlocale(LC_ALL, "RUS");
    
    // Создание и открытие файлов .cfg и .dat
    FILE* cfgFile = fopen("prog1.cfg", "w");
    FILE* datFile = fopen("prog1.dat", "w");

    // Проверка успешного открытия файлов
    if (cfgFile == NULL || datFile == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    // Запись заголовка файла .cfg
    fprintf(cfgFile, "Stanciya 110/35/6,BINOM,17.06.2024\n");
    fprintf(cfgFile, "9,6A,3D\n");
    fprintf(cfgFile, "1,Ia,,,A,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "2,Ib,,,A,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "3,Ic,,,A,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "4,Ua,,,V,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "5,Ub,,,V,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "6,Uc,,,V,1,0,0,-10000,10000,1,1,S\n");
    fprintf(cfgFile, "1,Pysk MTZ,,,0\n");
    fprintf(cfgFile, "2,RPO,,,0\n");
    fprintf(cfgFile, "3,RPV,,,1\n");
    fprintf(cfgFile, "50\n");
    fprintf(cfgFile, "1\n");
    fprintf(cfgFile, "1000,15000\n");
    fprintf(cfgFile, "17/06/2024,10:21:43.151830\n");
    fprintf(cfgFile, "17/06/2024,10:21:58.151830\n");
    fprintf(cfgFile, "ASCII\n");
    fprintf(cfgFile, "1\n");

    // Моделирование данных в файле .dat
    int numSamp = 15000; // Общее количество выборок
    int normSamp = 5000; // Последняя выборка в нормальном режиме (5000 мс)
    int avarSamp = 10000; // Последняя выборка в аварийном режиме (10000 мс)
    int Ia, Ib, Ic, Ua, Ub, Uc; // Аналоговые сигналы
    int PyskMTZ, RPO, RPV; // Дискретные сигналы

    for (int i = 0; i < numSamp; ++i) {
        // Моделирование сигналов 
        if (i < normSamp) {
            // Нормальный режим
            Ia = 1000 * sin(2 * PI * i / 180);
            Ib = 1000 * sin(2 * PI * (i + 120) / 180); 
            Ic = 1000 * sin(2 * PI * (i + 240) / 180);
            Ua = 6000 * sin(2 * PI * i / 180);
            Ub = 6000 * sin(2 * PI * (i + 120) / 180); 
            Uc = 6000 * sin(2 * PI * (i + 240) / 180); 
            PyskMTZ = 0;
            RPO = 0;
            RPV = 1;

        }
        else if (i < avarSamp) {
            // Аварийный режим
            Ia = rand() % 70 - 35;
            Ib = 1000 * sin(2 * PI * (i + 120) / 180) + 1000 - (i - 5000) / 50;
            Ic = 1000 * sin(2 * PI * (i + 240) / 180) + 1000 - (i - 5000) / 5;
            Ua = 900 * sin(2 * PI * (i + 120) / 180);
            Ub = 450 * sin(2 * PI * (i + 120) / 180);
            Uc = 450 * sin(2 * PI * (i + 240) / 180);
            PyskMTZ = 1;
            RPO = 0;
            RPV = 1;

        }
        else {
            // Послеаварийный режим
            Ia = 0;
            Ib = 0;
            Ic = 0;
            Ua = 0;
            Ub = 0;
            Uc = 0;
            PyskMTZ = 0;
            RPO = 1;
            RPV = 0;

        }

        // Запись данных в файл .dat
        fprintf(datFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", i + 1, i, Ia, Ib, Ic, Ua, Ub, Uc, PyskMTZ, RPO, RPV);
    }

    // Закрытие файлов
    fclose(cfgFile);
    fclose(datFile);

    printf("Файлы COMTRADE успешно созданы.\n");
    return 0;
}
