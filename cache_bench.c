#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX_SIZE (64 * 1024 * 1024)

double tiempo_actual() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {

    printf("========================================\n");
    printf(" CACHE BENCHMARK - U10 POST1\n");
    printf(" Daniel Pacheco Villamizar\n");
    printf("========================================\n\n");

    size_t tamanos[] = {
        4*1024,
        16*1024,
        64*1024,
        256*1024,
        1024*1024,
        4*1024*1024,
        16*1024*1024,
        64*1024*1024
    };

    int num_tamanos = sizeof(tamanos)/sizeof(tamanos[0]);

    printf("Tamano(KB)\tSecuencial(ns)\tAleatorio(ns)\n");

    for(int t=0; t<num_tamanos; t++) {

        size_t bytes = tamanos[t];
        size_t elementos = bytes / sizeof(int);

        int *array = malloc(bytes);

        if(array == NULL) {
            printf("Error reservando memoria\n");
            return 1;
        }

        for(size_t i=0; i<elementos; i++) {
            array[i] = i;
        }

        volatile long long suma = 0;

        double inicio = tiempo_actual();

        for(int r=0; r<100; r++) {
            for(size_t i=0; i<elementos; i++) {
                suma += array[i];
            }
        }

        double fin = tiempo_actual();

        double secuencial =
            ((fin - inicio) * 1e9) /
            (elementos * 100);

        inicio = tiempo_actual();

        for(int r=0; r<100; r++) {
            for(size_t i=0; i<elementos; i++) {

                size_t idx =
                    ((i * 1103515245u) + 12345u)
                    % elementos;

                suma += array[idx];
            }
        }

        fin = tiempo_actual();

        double aleatorio =
            ((fin - inicio) * 1e9) /
            (elementos * 100);

        printf("%8zu\t%12.2f\t%12.2f\n",
               bytes/1024,
               secuencial,
               aleatorio);

        free(array);
    }

    return 0;
}
