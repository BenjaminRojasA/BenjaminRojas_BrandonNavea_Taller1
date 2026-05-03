# :musical_note: C-Player | Reproductor de Consola (Taller 01 EDD)

## :pencil: De qué trata esto
Este es nuestro proyecto para el Taller 1 de Estructuras de Datos (UCN). La idea es armar un reproductor de música desde cero usando C++ puro, **sin usar las librerías fáciles como std::list o std::vector (cero STL)**. Todo el control de los datos lo estamos manejando a mano con memoria dinámica y punteros.

---

## :busts_in_silhouette: El Equipo

| Integrante | RUT | Carrera | GitHub |
| :--- | :--- | :--- | :--- |
| **Benjamín Rojas** | 22.086.016-7 | ICCI | [@BenjaminRojasA](https://github.com/BenjaminRojasA) |
| **Brandon Navea** | 22.042.679-3 | ICCI | [@brandonnavea](https://github.com/tu_usuario) |

* **Profesor:** Bastian Ruiz Garay
* **Ayudante:** Pablo Guzmán Vargas

---

## :construction: Estado Actual del Proyecto (Lo que funciona hasta ahora)
El reproductor está en pleno desarrollo. Hasta este commit, el código base ya logra hacer lo siguiente:
* **Cargar las canciones:** Lee correctamente el archivo `music_source.txt` al arrancar el programa, separando los datos con `stringstream`.
* **Interfaz base:** El menú principal ya se despliega limpio en la consola.
* **Lista General (Opción L):** Al presionar 'L', el programa recorre nuestra lista enlazada y muestra todas las canciones que se cargaron exitosamente en la memoria.
* **Salir (Opción X):** Cierra el ciclo del menú correctamente.

*(Nota: Las opciones de reproducir (W), avanzar (E), retroceder (Q) y la persistencia de estado con `status.cfg` están en proceso de construcción para los próximos commits).*

---

## :brain: Estructuras que armamos
Por el momento tenemos implementado nuestro "esqueleto" principal:
* **Nodos y Lista Doblemente Enlazada:** Hechos a mano utilizando *Templates* (`<T>`) para poder guardar cualquier tipo de objeto (en este caso, estamos guardando punteros a la clase `cancion`). 

---

## :rocket: Cómo probarlo (Instrucciones)

El proyecto está configurado con **CMake**, así que es súper fácil de levantar en CLion:

1. **Clonar el repo:**
   
```bash
   git clone [https://github.com/BenjaminRojasA/BenjaminRojas_BrandonNavea_Taller1.git](https://github.com/BenjaminRojasA/BenjaminRojas_BrandonNavea_Taller1.git)
