# Timba-Test
El codigo del programa se encuentra en la ruta: Timba Test\Timba Test\x64\Debug\Main.cpp
![image](https://user-images.githubusercontent.com/90017045/150735335-fa0f89dd-5935-412c-891f-826497d96201.png)

# Diseño Interno
El programa fue desarrollado con SDL, con el fin de facilirtar el uso de graficos.

 Para tener un mayor control del programa, se determino que las funciones de la ventana emergente tendrian que estar separadas con su respectiva información.
 
 ![image](https://user-images.githubusercontent.com/90017045/150735765-5460eafe-2d3b-49c0-b41c-b6f21b50da70.png)

Cada metodo de dibujado utiliza las funciones predeterminadas de SDL, y en el caso del circulo se utilizo el algoritmo de "Midpoint circle".

![image](https://user-images.githubusercontent.com/90017045/150736748-f0790e18-6999-4efc-bec3-3b9bffbf60bb.png)

Para determinar los movimientos de las figuras, se utilizaron instrucciones especificas para cada figura, y con las funciones con las cuales se crean, se diseño un ciclo que permitiera dichos comportamientos.

![image](https://user-images.githubusercontent.com/90017045/150737154-9b32616f-e61a-4184-879b-1c02eda31424.png)
