#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    unsigned char val, old_val, mask;
    unsigned int seed;
    int bit1, cont;
    double p; 
    FILE *arch, *archivo, *error;

    if (argc > 1)
    {
        p = (float)atof(argv[1]);
        if (p > 1. || p < 0)
        {
            fprintf (stderr, "La probabilidad debe encontrarse en el intervalo [0,1]\n");
            fflush(stderr);
            exit(1);
        }
    }
    else
    {
        fprintf (stderr, "\nSe tiene que pasar por parámetro una probabilidad.\n\n");
        exit(1);
    }

    if (!(archivo=fopen("Entrada.bin","rb")))
    {
        fprintf (stderr, "No se pudo abrir el archivo 'Entrada.bin'\n");
        exit(1);
    }

    if (!(error=fopen("Salida.bin","wb")))
    {
        fprintf (stderr, "No se pudo abrir el archivo 'Salida.bin'\n");
        exit(1);
    }

    seed = (unsigned int)time(NULL);
    srand(seed);
    arch = fopen ("ReporteErrores.txt","w");
    fprintf (arch, "Valor de la semilla utilizada para inicializar generador de numeros aleatorios:\n%d\n\n", seed);
    fprintf (arch, "Probabilidad para la injección de errores:\n%f\n\n", p);
    cont = 0;
    size_t foo;
    while (1)
    {
        foo = fread(&val, 1, 1, archivo);//Leemos un byte del archivo.
        if (foo != 0)
        {
            old_val = val;
            bit1 = rand() % 8;

            if (drand48() <= p)
            {   
               mask = 1 << bit1; 
               if (val & mask)
                    val &= ~mask;
                else
                    val |= mask;
               fprintf (arch, "Se inyecta un error en el bit: %d del byte %06d ", bit1, cont);
            }
            fwrite((void*)&val , 1, 1, error);
            if (val != old_val)
            {
                char buffer1[16], buffer2[16];
                unsigned char n;
                int i;

                n = old_val;
                for (i = 7; i >=0; --i, n >>= 1)
                    if (n & 1)
                        buffer1[i]='1';
                    else
                        buffer1[i]='0';
                buffer1[8]=0;
                n = val;
                for (i = 7; i >=0; --i, n >>= 1)
                    if (n & 1)
                        buffer2[i]='1';
                    else
                        buffer2[i]='0';
                buffer2[8]=0;
                fprintf (arch, ": %s vs %s\n",  buffer1, buffer2);
                fflush(arch);
            }
            cont++;
        }
        else
            break;
    }
    fclose(archivo);
    fclose(arch);
    fclose(error);
    return 0;
}
