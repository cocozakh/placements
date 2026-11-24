
#include <stdio.h>

unsigned long long arrangements(int n, int k)
{
    unsigned long long result = 1;

    for (int i = 0; i < k; i++)
    {
        result *= (n - i);
    }

    return result;
}

unsigned long long direct_number(int n, int k, int placement[])
{
    int used[21] = {0};

    unsigned long long number = 0;

    for (int i = 0; i < k; i++)
    {
        int smaller = 0;

        for (int j = 1; j < placement[i]; j++)
        {
            if (used[j] == 0)
            {
                smaller++;
            }
        }

        number += smaller * arrangements(n - i - 1, k - i - 1);

        used[placement[i]] = 1;
    }

    return number;
}

void inverse_number(int n, int k,
                    unsigned long long number,
                    int placement[])
{
    int used[21] = {0};

    for (int i = 0; i < k; i++)
    {
        unsigned long long block_size =
            arrangements(n - i - 1, k - i - 1);

        unsigned long long choice = number / block_size;

        number = number % block_size;

        int selected = 0;

        for (int j = 1; j <= n; j++)
        {
            if (used[j] == 0)
            {
                if (choice == 0)
                {
                    selected = j;
                    break;
                }

                choice--;
            }
        }

        placement[i] = selected;
        used[selected] = 1;
    }
}

int main(void)
{
    int mode;
    int n, k;

    printf("=== ПРОГРАММА РАЗМЕЩЕНИЙ ===\n");
    printf("1. Прямой ход\n");
    printf("2. Обратный ход\n");

    printf("Выберите режим: ");
    scanf("%d", &mode);

    if (mode != 1 && mode != 2)
    {
        printf("Некорректный режим!\n");
        return 1;
    }

    printf("Введите количество элементов n: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Ошибка ввода n!\n");
        return 1;
    }

    printf("Введите длину размещения k: ");

    if (scanf("%d", &k) != 1)
    {
        printf("Ошибка ввода k!\n");
        return 1;
    }

    if (n < 1 || n > 20 || k < 1 || k > n)
    {
        printf("Некорректные значения n и k! (соглашение: n < 20)\n");
        return 1;
    }

    int placement[20];
    int check[21] = {0};

    if (mode == 1)
    {
        printf("Введите элементы размещения:\n");

        for (int i = 0; i < k; i++)
        {
            printf("Элемент %d: ", i + 1);

            if (scanf("%d", &placement[i]) != 1)
            {
                printf("Ошибка ввода!\n");
                return 1;
            }

            if (placement[i] < 1 || placement[i] > n)
            {
                printf("Элемент должен находиться от 1 до n!\n");
                return 1;
            }

            if (check[placement[i]] == 1)
            {
                printf("Повторяющиеся элементы запрещены!\n");
                return 1;
            }

            check[placement[i]] = 1;
        }

        unsigned long long result = direct_number(n, k, placement);

        printf("Номер размещения: %llu\n", result);
    }

    else if (mode == 2)
    {
        unsigned long long number;
        int recovered[20];

        printf("Введите номер размещения: ");

        if (scanf("%llu", &number) != 1)
        {
            printf("Ошибка ввода!\n");
            return 1;
        }

        unsigned long long total = arrangements(n, k);

        if (number >= total)
        {
            printf("Такого номера размещения не существует!\n");
            return 1;
        }

        inverse_number(n, k, number, recovered);

        printf("Восстановленное размещение: ");

        for (int i = 0; i < k; i++)
        {
            printf("%d ", recovered[i]);
        }

        printf("\n");
    }

    return 0;
}
