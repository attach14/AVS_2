#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

int compute(char* buf, char* ans, int str_leng, int times){

    int cur = 0;

    int cnt = 0;

    for(int j = 0; j < times; j ++){

        cur = 0;

    for(int i = 0;i<str_leng;i++){

        if(buf[i] >= 'A' && buf[i] <'Z' && buf[i] != 'A' && buf[i] != 'O' && buf[i] != 'E' && buf[i] != 'U' && buf[i] != 'I'){

            cnt = buf[i];

            ans[cur] = ('0' + cnt / 10);

            cur++;

            ans[cur] = ('0' + cnt % 10);

            cur++;

            continue;

        }

        if(buf[i] == 'b' || buf [i] == 'c'){

            cnt = buf[i];

            ans[cur] = ('0' + cnt / 10);

            cur++;

            ans[cur] = ('0' + cnt % 10);

            cur++;

            continue;

        }

        if(buf[i] >= 'd' && buf[i] <='z' && buf[i] != 'o' && buf[i] != 'e' && buf[i] != 'u' && buf[i] != 'i'){

            cnt = buf[i];

            ans[cur] = ('0' + cnt / 100);

            cur++;

            ans[cur] = ('0' + (cnt / 10) % 10);

            cur++;

            ans[cur] = ('0' + cnt % 10);

            cur++;

            continue;

        }

        ans[cur] = buf[i];

        cur++;

    }

    ans[cur] = '\0';

    }

    return cur;

}

void write(char* ans, int arr_size, FILE* stream){

    for(int i = 0; i < arr_size; i++){

        fputc(ans[i], stream);

    }

}

int main(int argc, char* argv[]){

    char buf[1000000];

    char ans[3000000];

    int i = 0;

    int ch;

    if (argc != 4){

        printf("Wrong number of arguments - %d instead of 2\n", argc - 1);

        return 0;

    } 

    if(strcmp(argv[1], "--random") == 0){

        i = rand()%1000000;

        if(i == 0)

        i++;

        for(int y = 0;y < i; y++){

            ch = rand()%95;

            ch += 32;

            buf[y] = ch;

        }

        buf[i] = '\0';

    }

    else {

        FILE* in = fopen(argv[1], "r");

        if(in == NULL){

            printf("Wrong input file path\n");

            return 0;

        }

        while(ch != -1 && i < 1000000) {

            ch = fgetc(in);

            buf[i++] = ch;

        }

        if(i == 1000000 && buf[i - 1] != -1){

            printf("The text is too long\n");

            return 0;

        } 

        buf[i-1] = '\0';

        i--;

        fclose(in);

    }

    int times = atoi(argv[2]);

    if(times == 0){

        printf("Wrong number of repeats");

    }

    clock_t start = clock();

    i = compute(buf, ans, i, times);

    clock_t finish = clock();

    double res = (double) finish - start;

    res /= CLOCKS_PER_SEC;

    FILE* out = fopen(argv[3], "w");

    if(out == NULL){

        printf("Wrong output file path");

        return 0;

    }

    fprintf(out, "Execution time is %2.3f seconds\n", res);

    write(ans, i, out);

    return 0;

}
