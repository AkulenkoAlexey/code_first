#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
	// Локализация русского языка
	setlocale(LC_ALL, "RUS");

	// Создание и открытие файлов .csv, .cfg и .dat
	char buffer[1024];
	FILE* datFile = fopen("prog1.dat", "r");
	FILE* csvFile = fopen("prog2.csv", "w");
	FILE* cfgFile = fopen("prog1.cfg", "r");

	// Проверка успешного открытия файлов
	if (datFile == NULL || csvFile == NULL || cfgFile == NULL) {
		printf("Ошибка открытия файла.\n");
		return 1;
	}

	// Количество сигналов и частота сети
	int numChan, freq;

	fgets(buffer, sizeof(buffer), cfgFile); // Первая строка
	fgets(buffer, sizeof(buffer), cfgFile); // Вторая строка, содержащая количество сигналов
	sscanf(buffer, "%d", &numChan);
	
	// Пропуск строк, содержащих информацию о сигналах
	for (int i = 0; i < numChan; i ++) {
		fgets(buffer, sizeof(buffer), cfgFile);
	} 
	// Чтение строки содержащей частоту
	fgets(buffer, sizeof(buffer), cfgFile); 
	sscanf(buffer, "%d", &freq);
	
	// Запись данных в файл .csv 
	if (datFile) {
		while ((fgets(buffer, sizeof(buffer), datFile)) != NULL) {
			fprintf(csvFile, "%s", buffer);
		}
	}
        
        // Закрытие файлов
	fclose(datFile);
	fclose(csvFile);
	fclose(cfgFile);

	printf("Файл .cfg успешно создан.\n");
	printf("Частота сети: %d\n", freq);

	return 0;

}

