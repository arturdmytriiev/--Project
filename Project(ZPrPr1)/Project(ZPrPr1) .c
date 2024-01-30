#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

#define siz_lin 10000
#define N 255
#define LAPSIZE 5
#define true 1 //присвоения альтернативных имен существующим типам данных.  true a false // priradiť alternatívne názvy existujúcim dátovým typom. pravda nepravda   https://www.studytonight.com/c/typedef.php true = 1, false = 0
#define false 0
#define filePath "C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv"

// Глобальная переменная которая принимает в себя кол-во записей в файле, необходимо для того чтоб знать сколько эдементов в массиве Драйверов
// Globálna premenná, ktorá akceptuje počet záznamov v súbore, je potrebné aby ste vedeli, koľko prvkov je v poli Drivers
int driversListSize = 0; //Размер списка драйверов // Veľkosť zoznamu ovládačov

struct driver {// Структура для Драйвера (она описывает все основные данн  для 1 драйвера) // Štruktúra pre vodiča (popisuje všetky základné údaje pre 1 vodiča)
    char *fullName; // имя и фамилия через пробел // meno a priezvisko oddelené medzerou
    char *born;// год рождения // rok narodenia
    char gender;// гендер 1 символ // gender 1 znak
    char *carModel;// модель машины // Model auta
    double laps[LAPSIZE];// массив с временем кругов на 5 элементов // pole s časmi na kolo o 5 prvkov
};

// Open file
FILE* openFile() {
    FILE *subor = fopen("C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv", "r");
    if (subor == NULL) {
        printf("Can not read file.");
        exit(false);
    }
    return subor;
}

// Close file
void closeFile(FILE *subor) {
    fclose(subor);
}

// Функция для добавления символов в массив // Funkcia pre pridanie symbolov do poľa
void append(char* s, char c) {
    int len /*riadok*/ = (int)strlen(s); //Функция strlen () вычисляет длину заданной строки. //Funkcia strlen () počíta dĺžku daného reťazca.
    s[len] = c;
    s[len+1] = '\0'; /*riadok +1 dalej*/
}

// Функция для добавления символов в массив // Funkcia pre pridanie symbolov do poľa
int contains(const double source[], const double value, const int size) { //size == LAPSIZE (5 cisel)
    for (int i = 0; i < size; i++) {
        if (source[i] == value) {
            return true;
        }
    }
    return false;
}

void freeDrivers(struct driver* drivers) {
    for (int i = 0; i < driversListSize; i++) {// очищаем память которую мы выделили ранее // vymaže pamäť, ktorú sme predtým pridelili
        free(drivers[i].fullName);
        free(drivers[i].born);
        free(drivers[i].carModel);
    }
    free(drivers);
}

struct driver* driver_d1(char *source) {// функция которая преобразовывает строку из файла в структуру Driver // funkcia, ktorá prevádza reťazec zo súboru na štruktúru ovládača
    int cPosition = 0;// Позиция курсора начинаеться на 0 // Pozícia kurzora začína na 0
    char lapBuffer[N] = {};// Специальный буфер для считывания времени кругов из файла // Špeciálna vyrovnávacia pamäť na čítanie časov okruhov zo súboru
    char fullName[N] = {};// переменная для считывания полного имени гонщика // premenná na prečítanie celého názvu ovládača
    char born[N] = {};// переменная для считывания года рождения гонщика // premenná na čítanie roku narodenia jazdca
    char gender = '\0';// символ с нулевым значением // znak s nulovou hodnotou // переменная для считывания пола гонщика // premenná na čítanie gender jazdca
    char carModel[N] = {};// переменная для считывания модели автомобиля // premenná na načítanie modelu automobilu
    double laps[5] = {};// переменная для считывания времени кругов гонщика // premenná na čítanie časov na kolo jazdca

    for (int v = 0; v < 9; v++) { // 9 - кол-во переменных в строке, которые нам необходимо считать // 9 - počet premenných v riadku, ktoré musíme prečítať
        while (source[cPosition] != '\n') { // конец линии (ряд) // koniec riadku (riadok)
            if (source[cPosition] == ';') { // переход на другое слово дальше в одном рядку //presun na ďalšie slovo ďalej v jednom riadku
                cPosition++;
                memset(lapBuffer, 0, sizeof(lapBuffer));
                break;
            } else {
                switch (v) {
                    case 0:
                        append(fullName, source[cPosition]);
                        break;
                    case 1:
                        gender = source[cPosition];
                        break;
                    case 2:
                        append(born, source[cPosition]);
                        break;
                    case 3:
                        append(carModel, source[cPosition]);
                        break;
                    case 4:
                        append(lapBuffer, source[cPosition]);
                        laps[0] = atof(lapBuffer); // atof  возвращает преобразованное значение // atof vráti prevedenú hodnotu
                        break;
                    case 5:
                        append(lapBuffer, source[cPosition]);
                        laps[1] = atof(lapBuffer); // atof  возвращает преобразованное значение // atof vráti prevedenú hodnotu
                        break;
                    case 6:
                        append(lapBuffer, source[cPosition]);
                        laps[2] = atof(lapBuffer); //atof преобразует строку в число с плавающей запятой (double).
                        break;
                    case 7:
                        append(lapBuffer, source[cPosition]);
                        laps[3] = atof(lapBuffer);
                        break;
                    case 8:
                        append(lapBuffer, source[cPosition]);
                        laps[4] = atof(lapBuffer);
                        break;
                    default: break;
                }
            }
            cPosition++;
        }
    }
    struct driver *driver = malloc(sizeof(struct driver));// Создаем структуру данных для драйвера. malloc - выделяет память под эту структуру // Vytvorte dátovú štruktúru pre ovládač. malloc - vytvori pamäť pre túto štruktúru
    driver->fullName = malloc(strlen(fullName)+1); // выделяем память в размере strlen(fullName)+1 в структуре для массива символов // pridelíme pamäť strlen (fullName) +1 v štruktúre pre pole znakov
    driver->born = malloc(strlen(born)+1);// выделяем память в размере strlen(born)+1 в структуре для массива символов // pridelíme pamäť strlen (fullName) +1 v štruktúre pre pole znakov
    driver->carModel = malloc(strlen(carModel)+1);    // выделяем память в размере strlen(car)+1 в структуре для массива символов // pridelíme pamäť strlen (fullName) +1 v štruktúre pre pole znakov
    strcpy(driver->fullName, fullName);// Копируем данные из переменной fullName в  переменную driver->fullName // Skopírujte údaje z premennej fullName do premennej driver-> fullName
    strcpy(driver->born, born);// Копируем данные из переменной born в  переменную driver->born
    driver->gender = gender;// так как это не поинтер, мы просто присваеваем значение gender в driver->gender // pretože to nie je ukazovateľ, iba priradíme hodnotu rodu k driver-> gender
    strcpy(driver->carModel, carModel);// Копируем данные из переменной fullName в переменную carModel->carModel

    for (int i = 0; i < 5; i++) {// делаем цикл и присваеваем все значения из laps в driver->laps //
        driver->laps[i] = laps[i];
    }

    //free(driver);
    // возвращаем структуру драйвера
    return driver;
}


int compareDouble(const void *lhs, const void *rhs) { // compare функция для сравнения чисел // funkcia porovnania na porovnanie čísel
    if (*(double*)lhs > *(double*)rhs) {
        return 1;
    }else if
            (*(double*)lhs < *(double*)rhs) return -1;// const void тип с которым можно создать указатель // typ s ktorým je možné vytvoriť ukazovate
    else {
        return 0;
    }
}

int compareString(char *lhs, char *rhs) { // сравнить строку //porovnat line //BRAND
    if (strcmp(lhs, rhs)) {//Функция strcmp () сравнивает две строки и возвращает 0 //  strcmp () Porovná
        return 1; //Сравнивает две строки посимвольно.  // Porovná dva reťazce znak po znaku.   https://www.programiz.com/c-programming/library-function/string.h/strcmp
    }
    else {
        return 0;
    }
}

int compare(const void *lhs, const void *rhs) {//сравнить //porovnat   char int double
    if (*(double*)lhs > *(double*)rhs)   // const void это для сравнения любого значения char int double // pre porovnanie vsetkeho char int double je const void
        return 1;
    else if (*(double*)lhs < *(double*)rhs)
        return -1;
    else
        return 0;
}

void bestResultForGn(const struct driver *drivers, const int size) {
    // создаем массив для лучших результатов драйверов // vytvorí pole pre lepšie výsledky ovládača
    double laps[sizeof(*drivers)] = {};

    for (int i = 0; i < size; i++) {

        struct driver driver = drivers[i];

        //  массив для времени кругов //  pole pre časy na kolo
        double cLaps[5] = {};

        // копируем данные // skopírovanie údajov
        for (int j = 0; j < 5; j++) {
            cLaps[j] = driver.laps[j];
        }

        // сортируем по возрастанию и берем элемент по индкесу 0 // zoradiť vzostupne a zobrať prvok indexom 0
        qsort(cLaps, LAPSIZE, sizeof(cLaps[5]), compareDouble);  //porovnaj Double
        // Сохраняем лучший результат для каждого драйвера // Uložte najlepšie cislo pre každého vodiča
        laps[i] = cLaps[0];
    }

    // сортируем наш массив, чтоб получить лучший результат из всех драйверов // zoraďte naše pole, aby ste dosiahli najlepší výsledok zo všetkých ovládačov
    qsort(laps, size, sizeof(laps[5]), compareDouble);

    for (int i = 0; i < size; i++) {
        struct driver driver = drivers[i];

        // Находим драйвера которому принадлежит лучший результат // Nájdite vodica, ktorý ma najlepší výsledok
        if (contains(driver.laps, laps[0], LAPSIZE)) { //содержит //obsahuje

            int index = 0;
            // Находим индекс в массике по которому находится лучший результат // Nájdite index v pole, kde sa nachadza najlepší výsledok
            for (int i = 0; i < LAPSIZE; i++) {
                if (driver.laps[i] == laps[0]) {
                    index = i + 1;
                    break;
                }
            }

            // Печатаем все это в консоль
            printf("Najlepsie kolo: %.3f;\n", laps[0]);
            printf("Jazdec: %s\n", driver.fullName);
            printf("Cislo kola: %i\n", index);
        }
    }
}

struct driver *getDataSourcesFrom() { //получить источники данных из фаила //získať zdroje údajov z file
    FILE *subor = openFile();
    char symbols[N] = {};
    driversListSize = 0;


    while (fgets(symbols, N, subor) != NULL) {//  сколько всего строк в файле (1 строка = 1 структура) // koľko riadkov je v súbore (1 riadok = 1 štruktúra)
        driversListSize++;
    }

    struct driver* drivers = calloc(driversListSize, sizeof(struct driver)); // выделяем память для массива структур рамером в index // caloc - выделяет запрошенную память  // pridelenie pamäte pre rad štruktúr veľkosti v indexe // výhrevnosť - pridelenie požadovanej pamäte

    rewind(subor);  // переводим курсор в FILE  на начало файла // presunie kurzor na SÚBOR na začiatok súboru

    int i = 0;// создаем переменную для индексации

    while (fgets(symbols, N, subor) != NULL) {// преобразовываем строки в структуры и записываем их в массив структур
        drivers[i] = *driver_d1(symbols);
        i++;
    }
    closeFile(subor);
    return drivers;// возвращаем массив структур
}

void timeforDriver(double *source, double *worstTime, double *averageTime, double *bestTime) { // source источник. zdroj
    double a[LAPSIZE] = {};
    for (int i = 0; i < LAPSIZE; i++) {
        a[i] = source[i];
    }
    qsort(a, LAPSIZE, sizeof(a[0]), compare); // сортировка. Самое маленькое число на позиции 0 и идем вверх. А на позиции 4 самое большое //Zoradiť vzostupne// Najmenšie číslo je na pozícii 0 a ideme hore. A na pozícii 4 najväčšia
    *bestTime = a[0];
    int simbol = sizeof(a)/sizeof(double );
    *worstTime = a[4];
    double timeforall[]={};
    double sum = 0.0;
    for (int q = 0; q < LAPSIZE; q++) {
        sum += timeforall[q];
    }
    *averageTime = sum/simbol;
}
//------------------------------------
//---------------DRIVER---------------
//------------------------------------
void driver() {
    char input[N] = {};

    printf("Function: driver() \n");
    printf("Write driver name:");
    scanf("%s", input);
    struct driver* drivers = getDataSourcesFrom();
    struct driver* driver = NULL;

    for (int w=0; w<driversListSize; w++) {
        if (strstr(drivers[w].fullName, input) != NULL) {
            driver = &drivers[w];
        }
    }
    if (driver != NULL) {
        double worstTime = 0.0;
        double averageTime = 0.0;
        double bestTime = 0.0;

        timeforDriver(driver->laps, &worstTime, &averageTime, &bestTime);

        printf("\n");
        printf("%s\n", driver->fullName);
        printf("nar. %s, %s\n", driver->born, driver->gender == 'f' ? "zena" : "muz");
        printf("Automobil: %s\n", driver->carModel);
        printf("\n");
        printf("Casy okruhov: ");
        for (int i = 0; i < 5; i++) {
            printf("%.3f;", driver->laps[i]);
        }
        printf("\n");
        printf("\nNajlepsie kolo: %.3f", bestTime);
        printf("\nNajhorsie kolo: %.3f", worstTime);
        printf("\nPriemerne kolo: %.3f", averageTime);
    } else {
        printf("Dont work");
    }
    freeDrivers(drivers);
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------SUM------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void sum() {
    printf("Function: sum() \n");
    // получаем массив данных из файла в виде структур // získa pole údajov zo súboru vo forme štruktúr
    struct driver* drivers = getDataSourcesFrom();
    // пробигаемся по массиву структур и печатаем все инфу в консоль // prejsť radom štruktúr a vytlačiť všetky informácie do konzoly
    for (int i = 0; i < driversListSize; i++) {
        struct driver driver = drivers[i];
        printf("\n");
        printf("%s, nar. %s, %s, Automobil: %s \nCasy okruhov: ", driver.fullName, driver.born, driver.gender == 'm' ? "muz" : "zena", driver.carModel);
        for (int i = 0; i < 5; i++) {
            printf("%.3f;", driver.laps[i]);
        }
        printf("\n");
    }
    // запускаем очистку памяти
    freeDrivers(drivers);
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------LAP------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void lap() {
    printf("Function: lap() \n");

    // получаем массив данных из файла в виде структур // získa pole údajov zo súboru vo forme štruktúr
    struct driver *drivers = getDataSourcesFrom();
    bestResultForGn(drivers, driversListSize); // mam este void pre Lap aj Gender (spolu)

    // запускаем очистку памяти
    freeDrivers(drivers);
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------Gender---------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void gender() {

    struct driver* drivers = getDataSourcesFrom();
    char input[N] = {};

    printf("Write gender: \n");
    scanf("%s", input);
    int genderCount = 0;
    for (int r=0; r<driversListSize; r++) {
        if (strstr(&drivers[r].gender, input) !=NULL) {
            genderCount++;
        }
    }
    if (genderCount <= 0) {
        printf("Gender dont exist");
    }
    else{
        struct driver* filterbygender = calloc(genderCount, sizeof(struct driver));
        for (int y=0, p=0;y < driversListSize; y++) {
            if (strstr(&drivers[y].gender, input) !=NULL){
                filterbygender[p]= drivers[y];
                p++;
            }
        }
        bestResultForGn(filterbygender, genderCount);
        free(filterbygender);
    }
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------YEAR-----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void year() {
    int input;
    printf("Write year: \n");
    scanf("%d", &input);

    struct driver *drivers = getDataSourcesFrom();

    for (int a = 0; a < driversListSize; ++a) {
        if (atoi(drivers[a].born) < input) { //atoi prerobi char v int //https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm

            double lap[LAPSIZE] = {0.0};
            int index = 0;
            double bestLapResult = 0.0;
            for (int q = 0; q < LAPSIZE; q++) {
                lap[q] = drivers[a].laps[q];
            }
            qsort(lap, LAPSIZE, sizeof(lap[5]), compareDouble);
            bestLapResult = lap[0];
            // Находим индекс в массике по которому находится лучший результат // Nájdite index v pole, kde sa nachadza najlepší výsledok
            for (int i = 0; i < LAPSIZE; i++) {
                if (drivers[a].laps[i] == lap[0]) {
                    index = i + 1;
                    break;
                }
            }
            printf("\n");
            printf("%s\n", drivers[a].fullName);
            printf("Nar. %s\n", drivers[a].born);
            printf("Najlepsie kolo: %.3f;\n", bestLapResult);
            printf("Cislo kola: %i\n", index);
            printf("\n");
        }

    }
    freeDrivers(drivers);
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------BRAND----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void brand() {
    printf("Function: brand() \n");

    // получаем массив данных из файла в виде структур
    struct driver* drivers = getDataSourcesFrom();
    // создаем массив для торговых марок авто (без повторов) // vytvorenе poľa pre auto značky (bez opakovaní)
    char carMark[N][N] = {{}};// массив для всех автомобилей наездников //pole bez opakovania

    for (int i = 0; i < driversListSize; i++) {
        // получить массив марок авто
        strcpy(carMark[i], drivers[i].carModel);//функция копирует информацию которую я указал в нутри скобок // funkcia skopíruje informácie, ktoré som uviedol v zátvorkách
    }

    char TrMark[N][N] = {{}};  //массив уже для уникальных авто //pole pre auto bez opakovanie unikatne
    int index = 0;

    // удаляем дубликаты марок авто в массиве и копируем все уникальные марки в отдельный массив// vymazem auto ktore ma rovanke meno
    for (int i=0; i < driversListSize; i++) {
        int j;
        for (j=0; j < driversListSize; j++)
            if (compareString(carMark[i], carMark[j]) == 0) // 0 - означает что две строки одинаковые //2 line sa rovna
                break;

        if (j == i)
            strcpy(TrMark[index++], carMark[i]);
    }

    for (int i = 0; i < index; i++) { // пробигаемся по массиву структур и печатаем все инфу в консоль
        printf("%s", TrMark[i]);
        printf("\n");

        int Onecaronep = 0; // кол-во авто для 1 марки //počet automobilov pre 1 značku

        // Находим сколько записей соответствует 1 марке авто // Nájdite, koľko záznamov sa nachadza s 1 značkou automobilu
        for (int f = 0; f < driversListSize; f++) {
            if (compareString(TrMark[i], drivers[f].carModel) == 0) {
                Onecaronep++;
            }
        }

        // Создаем массив для хранения всех записей для 1 марки авто // vytvoryme pole pre vsetci udaje o 1 aute (Car Mark)
        struct driver* AllDriversForOneCar = calloc(Onecaronep, sizeof(struct driver)); // выделяет запрошенную память и возвращает указатель на нее // pridelí požadovanú pamäť a vráti do nej ukazovateľ
        //onecaronep - это количество выделяемых элементов. //toto je počet položiek, ktoré sa majú prideliť.
        // sizeof(struct driver) - это размер элементов. //toto je veľkosť položiek.
        // Заполняем массив // Vyplniť pole
        int carIndex = 0;
        for (int s = 0; s < driversListSize; s++) {
            if (compareString(TrMark[i], drivers[s].carModel) == 0) {
                AllDriversForOneCar[carIndex] = drivers[s];
                carIndex++;
            }
        }

        double bestResult = 1000000;  //это наибольшее значение, которое может содержать двойное значение .  //maximálny konečný počet reprezentovateľných pohyblivých čísel.
        int driverIndex = 0;
        int lapIndex = 0;
        for (int q = 0; q < carIndex; q++) {
            for (int g = 0; g < 5; g++) {

                if (AllDriversForOneCar[q].laps[g] < bestResult) {
                    bestResult = AllDriversForOneCar[q].laps[g];
                    driverIndex = q;
                    lapIndex = g;
                }
            }
        }

        // печатаем лучший результат для 1 марки авто
        printf("Znacka: %s\n", AllDriversForOneCar[driverIndex].carModel);
        printf("Najlepsie kolo: %.3f\n", AllDriversForOneCar[driverIndex].laps[lapIndex]);
        printf("Jazdec: %s\n", AllDriversForOneCar[driverIndex].fullName);
        printf("Cislo kola: %d\n", lapIndex + 1);

        printf("\n\n\n");
        free(AllDriversForOneCar);
    }
    // запускаем очистку памяти
    freeDrivers(drivers);
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------AVERAGE--------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void average() {
    printf("Function: average() \n");

    struct driver* drivers = getDataSourcesFrom();
    double averageforDriver[N] = {};

    for (int q = 0; q < driversListSize; q++) {

        struct driver driver = drivers[q];
        double lap[LAPSIZE] = {0.0};

        for (int w = 0; w < LAPSIZE; w++) {
            lap[w] = driver.laps[w];
        }

        qsort(lap, LAPSIZE, sizeof(double), compareDouble);
        double worstTime = 0.0;
        double averageTime = 0.0;
        double bestTime = 0.0;

        timeforDriver(driver.laps, &worstTime, &averageTime, &bestTime);


        printf("%s - %.3f\n", driver.fullName, averageTime);
        averageforDriver[q] = lap[2];
    }
    printf("\n");
    qsort(averageforDriver, driversListSize, sizeof(double), compareDouble);
    for (int z = 0; z < driversListSize; z++) {
        if (contains(drivers[z].laps, averageforDriver[0], LAPSIZE)) {
            struct driver driver = drivers[z];
            double lap[LAPSIZE] = {0.0};
            double worstTime = 0.0;
            double averageTime = 0.0;
            double bestTime = 0.0;
            timeforDriver(driver.laps, &worstTime, &averageTime, &bestTime);
            printf("Best: \n");
            printf("%s - %.3f\n", drivers[z].fullName, averageTime);
        }
    }
    freeDrivers(drivers);// запускаем очистку памяти
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------DRIVER--------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
void newDR() {
    printf("Function: newdriver()\n");

    FILE *fileso = fopen("C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv", "a+");

    char firstName[N] = {};
    char lastName[N] = {};
    int year;
    char gen[30];
    char bran[30];
    double lp[5];

    if (fileso == NULL)
    {
        printf("File does not exist.\n");
        return;
    }
    // Cast kodu precital z internetu ale pisal dalej sam
    printf("Enter the first and last name:\n");
    https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/

    scanf(" %[^\n]%*c", firstName); // позволяет вводить строки с пробелами // переходами на новую строку -> подробнее
    fprintf(fileso, "\n%s", firstName);
    fprintf(fileso, "%s", lastName);
    fprintf(fileso, "%s", ";");

    printf("Enter the gender:\n");
    scanf("%s", gen);
    fprintf(fileso, "%s;", gen);

    printf("Enter the age:\n");
    scanf("%d", &year);
    fprintf(fileso, "%d;", year);

    printf("Enter the brand:\n");
    scanf("%s", bran);
    fprintf(fileso, "%s;", bran);

    printf("Enter the time:\n");
    scanf("%lf", &lp[0]);
    scanf("%lf", &lp[1]);
    scanf("%lf", &lp[2]);
    scanf("%lf", &lp[3]);
    scanf("%lf", &lp[4]);
    fprintf(fileso, "%.3f;%.3f;%.3f;%.3f;%.3f", lp[0],  lp[1],  lp[2],  lp[3],  lp[4]);

    fclose(fileso);
    sum();
}
//---------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------rmdriver-------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//https://codeforwin.org/2018/02/c-program-remove-specific-line-from-file.html?fbclid=IwAR11SbFbGODlL3MGcaSjnPuVNqNP7ycK_H8JeHORuTul0fufeHqyUELMW_E
void rmdriver() {
    FILE *File_nas;
    int line;
    FILE *Fiel_tmp;


    File_nas  = fopen("C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv", "r");
    Fiel_tmp = fopen("delete.tmp", "w");

    if (File_nas == NULL || Fiel_tmp == NULL)
    {
        printf("File can not open");

        exit(false);
    }

    printf("File before delete line.\n");
    printf("\n");
    char c;

    while((c = fgetc(File_nas)) != EOF) {
        putchar(c);
    }
    printf("\n");
    printf("\n");
    printf("Enter line number delete (start line 1......): ");
    scanf("%d", &line);
    printf("\n");
    rewind(File_nas);

    char bf[siz_lin];
    int nt = 1;

    while ((fgets(bf, siz_lin, File_nas)) != NULL)
    {
        if (line != nt)
            fputs(bf, Fiel_tmp);

        nt++;
    }

    fclose(File_nas);
    fclose(Fiel_tmp);


    remove("C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv");
    rename("delete.tmp", "C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv");
    printf("\n");
    printf("\n");
    printf("File after delete line.\n");
    printf("\n");

    File_nas = fopen("C:\\Users\\softd\\Clion project\\Projek1\\jazdci.csv", "r");
    printf("\n");
    while((c = fgetc(File_nas)) != EOF) {
        putchar(c);
    }
    fclose(File_nas);
}
//------------------------------------------
//-----------------MENU---------------------
//------------------------------------------
void menu() {

    char a;
    int e = 1;

    do {
        printf("\n\n");
        printf("Select operation: \n\n");
        printf("s - sum() \n");
        printf("d - driver() \n");
        printf("l - lap() \n");
        printf("g - gender() \n");
        printf("b - brand() \n");
        printf("y - year() \n");
        printf("a - average() \n");
        printf("u - under() \n");
        printf("c - change() \n");
        printf("n - newdriver() \n");
        printf("r - rmdriver() \n");
        printf("x - exit\n");
        scanf(" %c", &a);
        printf("\n");

        switch (a) {
            case 's':
                sum();
                break;
            case 'd':
                driver();
                break;
            case 'l':
                lap();
                break;
            case 'g':
                gender();
                break;
            case 'b':
                brand();
                break;
            case 'y':
                year();
                break;
            case 'a':
                average();
                break;
            case 'u':
                break;
            case 'c':
                break;
            case 'n':
                newDR();
                break;
            case 'r':
                rmdriver();
                break;
            case 'x':
                e = 0;
                break;
            default:
                printf("Wrong operation. Enter again.");
                break;
        }
    } while(e);
}

int main() {
    menu();
    return 0;
}