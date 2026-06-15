Trabajo Integrador - MAVI II

Este proyecto consiste en una simulación física en C++ utilizando las bibliotecas Raylib y Box2D.

La simulación representa una grúa puente que permite transportar una pelota desde una plataforma de origen hasta una plataforma de destino. 
El jugador debe coordinar el movimiento de la pelota y de la grúa para superar el espacio entre ambas plataformas sin dejar caer la pelota.

Controles
Movimiento de la pelota
A → mover hacia la izquierda
D → mover hacia la derecha
Movimiento de la grúa
Flecha Izquierda → mover la grúa hacia la izquierda
Flecha Derecha → mover la grúa hacia la derecha
Reinicio
R → reiniciar la simulación

Condiciones de juego
Victoria
La victoria se produce cuando la pelota alcanza la plataforma de destino señalizada con un caliz de fuego.

Derrota
La derrota ocurre cuando la pelota cae al suelo.

Cuerpos estáticos:
Suelo
Plataforma inicial
Plataforma de destino
Riel de la grúa

Estos elementos no son afectados por la gravedad ni por fuerzas externas.

Cuerpos dinámicos:

Pelota
Carro de la grúa
Plataforma suspendida

Estos cuerpos interactúan con la gravedad y las colisiones del sistema físico.

Joints utilizados
Prismatic Joint

Se utiliza un Joint Prismático para conectar el carro de la grúa con el riel.

Su función es restringir el movimiento del carro a un único eje horizontal, impidiendo desplazamientos verticales o rotaciones no deseadas.

Además utiliza un motor para permitir el movimiento controlado mediante las teclas del usuario.

Distance Joint

Se utilizan dos Distance Joint para suspender la plataforma móvil desde el carro.

Estos joints mantienen una distancia constante entre los puntos conectados, simulando el comportamiento de cables.

La combinación de ambos joints genera una estructura en forma de "V" invertida que mantiene suspendida la plataforma permitiendo un comportamiento físico estable y oscilaciones naturales durante el movimiento.
