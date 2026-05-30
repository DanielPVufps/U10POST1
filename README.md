# U10 POST1 - Benchmark de Caché

## Estudiante

- Nombre: Daniel Pacheco Villamizar
- Asignatura: Arquitectura de Computadores

## Objetivo

Analizar el comportamiento de la jerarquía de memoria caché mediante un benchmark que mide la latencia promedio de acceso secuencial y aleatorio para diferentes tamaños de memoria.

## Hardware Utilizado

### Caché detectada

| Nivel | Tamaño |
|---------|---------|
| L1 Datos | 288 KiB |
| L1 Instrucciones | 192 KiB |
| L2 | 7.5 MiB |
| L3 | 12 MiB |

Comando utilizado:

```bash
lscpu | grep cache
```

## Resultados Experimentales

| Tamaño (KB) | Secuencial (ns) | Aleatorio (ns) |
|------------|----------------|---------------|
| 4 | 0.71 | 4.56 |
| 16 | 0.62 | 4.47 |
| 64 | 0.99 | 4.60 |
| 256 | 0.59 | 3.37 |
| 1024 | 0.55 | 3.74 |
| 4096 | 0.60 | 4.84 |
| 16384 | 0.84 | 15.96 |
| 65536 | 0.72 | 16.71 |

## Análisis

Los accesos secuenciales presentan una latencia muy baja debido a la localidad espacial y al mecanismo de prefetch implementado por el procesador.

Los accesos aleatorios mantienen una latencia relativamente estable para tamaños pequeños, pero aumentan significativamente cuando el conjunto de datos supera la capacidad de la caché L3.

Se observa un incremento de aproximadamente 4 ns a más de 16 ns al pasar de tamaños que caben en caché a tamaños superiores a 16 MB.

Este comportamiento evidencia la diferencia entre acceder a datos almacenados en caché y acceder a datos ubicados en memoria principal.

## Checkpoints

### Checkpoint 1

Ejecución del benchmark:

```bash
./cache_bench
```

### Checkpoint 2

Consulta de la jerarquía de caché:

```bash
lscpu | grep cache
```

### Checkpoint 3

Resultados almacenados:

```bash
cat resultados.txt
```

## Archivos Entregados

- cache_bench.c
- resultados.txt
- README.md

## Conclusión

La prueba demuestra que el rendimiento de acceso a memoria depende fuertemente de la jerarquía de caché. Los accesos secuenciales aprovechan mejor los mecanismos de optimización del procesador, mientras que los accesos aleatorios sufren penalizaciones importantes cuando los datos exceden la capacidad de las memorias caché disponibles.
