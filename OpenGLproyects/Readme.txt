Nombre de integrantes: Rodrigo Soto/ Ian Pereira

Como ejecutar el programa.

paso 1 : abra la terminal de ubuntu.

paso 2 : ingresar en el archivo en donde tiene el programa.

paso 3 : verifique que en el archivo "ENTRADA.TXT" contenga solo un numero, si desea cambiar el numero de circulos, escriba su numero deseado.

Paso 3 : Compile utilizando el "make", si resultara a fallar, utilice la siguiente linea:

"g++ main.cpp Circle.cpp OpenGlShadder.cpp glad/glad.c -lGL -lglfw -ldl -o main"

Paso 4 : ejecute el programa con "./main", si resultara a fallar, utilice este "LIBGL_ALWAYS_SOFTWARE=1 ./main".
