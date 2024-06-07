#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #define INPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/input.txt"
    #define OUTPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/output.txt"
#else 
    #define INPUT "input.txt"
    #define OUTPUT "output.txt"
#endif

int main()
{
    FILE *inp, *out;
    if ((inp = fopen(INPUT, "r")) == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    // ввод
    int n;
    fscanf(inp, "%d", &n);
    fclose(inp);

    // инициализация массива
    int *arr = (int*) malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
    {
        arr[i] = 0;
    }
    arr[0] = 1;

    // arr = [1, 0, 0, ...(n раз)..., 0]

    // Для каждого числа от 1 до n...
    for (int i = 1; i <= n; i++) {
        // ...обновляем количество разбиений для всех чисел от i до n
        for (int j = i; j <= n; j++) {
            arr[j] += arr[j - i];
            arr[j] %= 1000000007;
        }
    }

    // т.е. на выходе получается, что число Н, имеет arr[Н] различных разбиений на слагаемые

    // вывод
    out = fopen(OUTPUT, "w");
    fprintf(out, "%d\n", arr[n]);
    fclose(out);

    free(arr);

    return 0;
}
