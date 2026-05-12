
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINEA 1024
#define MAX_ARGS  64

int main() {
    char  linea[MAX_LINEA];
    char *args[MAX_ARGS];

    /* ── Ciclo principal de la shell ── */
    while (1) {

        /* 
         * Llamada a sistema: NO APLICA.
         * Se usa printf() + fflush() (librería estándar) para mostrar el
         * prompt e inmediatamente vaciar el buffer de salida estándar.
         */
        printf("mi_shell$ ");
        fflush(stdout);

        /*
         * Llamada a sistema: NO APLICA directamente.
         * fgets() lee una línea completa desde stdin (internamente puede
         * invocar la syscall read(), pero no se llama de forma directa).
         * Si fgets() retorna NULL se detecta EOF (Ctrl+D) y se sale.
         */
        if (fgets(linea, MAX_LINEA, stdin) == NULL) {
            printf("\n");
            break; /* EOF: salir de la shell */
        }

        /* 
         * Llamada a sistema: NO APLICA.
         * Se compara la línea leída con "\n". Si el usuario solo presionó
         * Enter, se usa continue para volver al inicio del ciclo e imprimir
         * nuevamente el prompt sin ejecutar nada.
         */
        if (strcmp(linea, "\n") == 0) {
            continue;
        }

        /* Eliminar el '\n' final para que los comandos funcionen correctamente */
        linea[strcspn(linea, "\n")] = '\0';

        /* 
         * Llamada a sistema: _exit() (invocada internamente por exit()).
         * Se compara la entrada con "exit". Al detectarlo, se imprime un
         * mensaje y se termina el proceso principal de la shell con exit(),
         * que internamente invoca la syscall _exit().
         */
        if (strcmp(linea, "exit") == 0) {
            printf("Saliendo de la shell...\n");
            exit(EXIT_SUCCESS);
        }

        /* 
         * Llamada a sistema: NO APLICA.
         * strtok() divide la línea en tokens usando espacios y tabulaciones
         * como delimitadores. El resultado queda en el arreglo args[].
         * El arreglo debe terminar en NULL tal como lo exige execvp().
         */
        int i = 0;
        args[i] = strtok(linea, " \t");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " \t");
        }
        args[i] = NULL; /* Terminador requerido por execvp */

        /* 
         * Llamadas a sistema utilizadas:
         *   1. fork()    → crea un proceso hijo.
         *   2. execvp()  → en el hijo, reemplaza la imagen del proceso con el
         *                  comando indicado; busca el ejecutable en el PATH.
         *   3. waitpid() → el padre espera en foreground a que el hijo
         *                  finalice antes de volver a mostrar el prompt.
         */
        pid_t pid = fork(); /* Syscall: fork() */

        if (pid < 0) {
            /* Error al crear el proceso hijo */
            perror("Error en fork");

        } else if (pid == 0) {
            /* ── Proceso HIJO ── */

            /* Syscall: execvp()
             * Ejecuta el comando. Si tiene éxito, no retorna.
             * ITEM 4: si retorna (-1), el comando no existe → se muestra error. */
            if (execvp(args[0], args) == -1) {
                perror("Error"); /* Imprime el error del sistema */
            }
            exit(EXIT_FAILURE); /* El hijo termina si execvp falló */

        } else {
            /* ── Proceso PADRE (la shell) ── */

            /* Syscall: waitpid()
             * Espera en foreground a que el proceso hijo (pid) termine.
             * Solo entonces se vuelve a mostrar el prompt (Item 6). */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
