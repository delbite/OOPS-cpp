#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int num;
    long longNum;
    char ch;
    float floatNum;
    double doubleNum;

    scanf("%d %ld %c %f %lf", &num, &longNum, &ch, &floatNum, &doubleNum);

    printf("%d\n", num);
    printf("%ld\n", longNum);
    printf("%c\n", ch);
    printf("%.3f\n", floatNum);
    printf("%.9lf\n", doubleNum);

    return 0;
}