# sistemas_op_taller1

nombres:
Florencia Castillo
Felipe Caro
Maximiliano alvarez
Juan Pablo Cardenas

Guía de Compilación y Ejecución para mi_shell.c :)

1. Requisitos:
   - Un sistema operativo basado en Unix/Linux o un entorno de compilación (como MinGW/Cygwin/WSL en Windows).
   - El compilador GCC instalado en el sistema.

2. Compilar el código fuente:
   Abre una terminal (o consola de comandos) en el directorio donde se encuentra el archivo 'mi_shell.c' y ejecuta el siguiente comando:
   
   gcc mi_shell.c -o mi_shell (este es el nombbre que le pusimos a la shell)

   Este comando compilará el código fuente y generará un archivo ejecutable llamado 'mi_shell' (o 'mi_shell.exe' si estás en Windows).

3. Ejecutar la shell:
   Para iniciar tu shell básica, ejecuta el archivo binario recién compilado con el siguiente comando en la terminal:
   
   ./mi_shell
   
4. Uso de los comandos:
   Una vez que se inicie, verás el prompt "mi_shell$ ". A partir de aquí, se pueden ingresar comandos:
   - Ejecutar comandos estándar del sistema (ej. ls, pwd, echo hola, whoami).
   - Si presionas Enter sin ingresar nada, la shell volverá a mostrar el prompt.
   - Si ingresas un comando que no existe, la shell mostrará un error ("Error: No such file or directory") y continuará funcionando.
   
5. Salir de la shell:
   Para terminar la ejecución y cerrar la shell, se escribe el siguiente comando:
   
   exit
   
