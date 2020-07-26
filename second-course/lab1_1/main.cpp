#include <iostream>
#include <conio.h>

#include <ctime>

using namespace std;

const int count = 4;
const int sizeUniversum = 26;

struct Set {
    char c = '\0';
    Set *next = NULL;
};

bool checkSetList(Set *set, char c) {
    for (Set *p = set; p; p = p->next) {
        if (p->c == c)
            return true;
    }
    return false;
}

bool checkSetArray(const char *set, int size, char c) {
    for (int i = 0; i < size; i++) {
        if (set[i] == c)
            return true;
    }
    return false;
}

void addList(Set *set, char c) {
    if (checkSetList(set, c)) return;

    for (Set *p = set; p; p = p->next) {
        if (p->c == '\0') {
            p->c = c;
        } else if (p->next == nullptr) {
            Set *current = new Set;
            current->c = c;
            p->next = current;
            break;
        }
    }
}

char **getRandomSet(int sizeCount) {
    char **collections = new char *[count];
    for (int i = 0; i < count; i++) {
        collections[i] = new char[sizeCount];
        for (int j = 0; j < sizeCount; j++) {
            char c;
            do {
                c = 'a' + (rand() % sizeUniversum);
            } while (checkSetArray(collections[i], sizeCount, c));
            collections[i][j] = c;
        }
    }
    return collections;
}

void printSets(char **collections, int size) {
    cout << "Size of set: " << size << endl;
    char set = 'A';
    for (int i = 0; i < count; i++) {
        cout << set << ": ";
        for (int j = 0; j < size; ++j) {
            cout << collections[i][j];
        }
        cout << endl;
        set++;
    }
}

void printList(Set *set) {
    for (Set *p = set; p; p = p->next) {
        cout << p->c;
    }
}

Set *convertToList(char **collections, int size) {
    Set *listCollections = new Set[count];
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < size; ++j) {
            addList(&listCollections[i], collections[i][j]);
        }
    }
    return listCollections;
}

bool **convertToBinary(char *universum, char **collections, int size) {
    bool **binaryCollections = new bool *[count];
    for (int i = 0; i < count; i++) {
        binaryCollections[i] = new bool[sizeUniversum];
        for (int j = 0; j < sizeUniversum; ++j) {
            binaryCollections[i][j] = false;
        }
    }
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < size; ++j) {
            int k;
            for (k = 0; collections[i][j] != universum[k]; ++k) {}
            binaryCollections[i][k] = true;
        }
    }
    return binaryCollections;
}

long *convertToMachine(char *universum, char **collections, int size) {
    long *machineCollections = new long[count];
    for (int i = 0; i < count; i++) {
        machineCollections[i] = 0;
    }
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < size; ++j) {
            int k;
            for (k = 0; collections[i][j] != universum[k]; ++k) {}
            machineCollections[i] ^= (1 << k);
        }
    }
    return machineCollections;
}

double getArrayTime(char **collections, int size, bool writeAnswer) {
    auto start = clock();
    int k = 0;

    char *answer = new char[count * size];

    // Use case
    for (int i = 0; i < size; i++) {
        if (!(checkSetArray(collections[1], size, collections[0][i]) &&
              checkSetArray(collections[2], size, collections[0][i]))) {
            if (!checkSetArray(answer, k, collections[0][i])) {
                answer[k] = collections[0][i];
                k++;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (!checkSetArray(answer, k, collections[3][i])) {
            answer[k] = collections[3][i];
            k++;
        }
    }

    if (writeAnswer) {
        cout << "Answer of array: ";
        for (int i = 0; i < k; i++) {
            cout << answer[i];
        }
        cout << endl;
    }
    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getListTime(Set *collections, bool writeAnswer) {
    auto start = clock();

    Set answer;
    for (Set *p = &collections[0]; p; p = p->next) {
        if (!(checkSetList(&collections[1], p->c) && checkSetList(&collections[2], p->c))) {
            if (!checkSetList(&answer, p->c)) {
                addList(&answer, p->c);
            }
        }
    }

    for (Set *p = &collections[3]; p; p = p->next) {
        if (!checkSetList(&answer, p->c)) {
            addList(&answer, p->c);
        }
    }

    if (writeAnswer) {
        cout << "Answer of list: ";
        printList(&answer);
        cout << endl;
    }

    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getBinaryTime(char *universum, bool **collections, bool writeAnswer) {
    auto start = clock();

    bool answer[sizeUniversum];

    for (int i = 0; i < sizeUniversum; i++) {
        answer[i] = false;
        answer[i] |= collections[0][i] & !(collections[1][i] & collections[2][i]);
    }

    for (int i = 0; i < sizeUniversum; i++) {
        answer[i] |= collections[3][i];
    }

    if (writeAnswer) {
        cout << "Answer of binary: ";
        for (int i = 0; i < sizeUniversum; i++) {
            if (answer[i]) {
                cout << universum[i];
            }
        }
        cout << endl;
    }

    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

double getMachineTime(char *universum, long *collections, bool writeAnswer) {
    auto start = clock();

    long answer = 0;

    answer |= collections[0] & ~(collections[1] & collections[2]);
    answer |= collections[3];

    if (writeAnswer) {
        cout << "Answer of machine: ";
        for (int i = 0; i < sizeUniversum; i++) {
            if ((answer >> i & 1)) {
                cout << universum[i];
            }
        }
        cout << endl;
    }

    auto stop = clock();
    return (stop - start) / (double) CLOCKS_PER_SEC;
}

int main() {
    srand(time(nullptr));

    const int testCount = 1000000;
    int setSizeCount[] = {1, 2, 4, 8};

    char universum[sizeUniversum];
    for (int i = 0, j = 'a'; j <= 'z'; ++i, ++j) {
        universum[i] = j;
    }

    for (auto i : setSizeCount) {
        double timeArray = 0;
        double timeList = 0;
        double timeBinary = 0;
        double timeMachine = 0;

        char **collections = getRandomSet(i);
        Set *listCollections = convertToList(collections, i);
        bool **binaryCollections = convertToBinary(universum, collections, i);
        long *machineCollections = convertToMachine(universum, collections, i);

        printSets(collections, i);

        for (int j = 0; j < testCount; j++) {
            timeArray += getArrayTime(collections, i, j == 0);
            timeList += getListTime(listCollections, j == 0);
            timeBinary += getBinaryTime(universum, binaryCollections, j == 0);
            timeMachine += getMachineTime(universum, machineCollections, j == 0);
        }

        //timeArray /= testCount;
        //timeList /= testCount;
        //timeBinary /= testCount;
        //timeMachine /= testCount;

        cout << "Time of array: " << timeArray << endl;
        cout << "Time of list: " << timeList << endl;
        cout << "Time of binary: " << timeBinary << endl;
        cout << "Time of machine: " << timeMachine << endl << endl;
    }

    _getch();

    return 0;
}
