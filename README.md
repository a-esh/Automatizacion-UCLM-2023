## Funcionamiento del Código

### Librerías Utilizadas
- `Servo.h`: Esta librería permite controlar los servomotores conectados a los pines digitales del Arduino. Los servomotores son dispositivos que pueden girar a un ángulo específico dentro de un rango determinado.
- `NewPing.h`: Se emplea para utilizar el sensor ultrasónico. Este sensor emite una señal ultrasónica y mide el tiempo que tarda en recibir el eco de esa señal, lo que permite calcular la distancia a un objeto.

### Configuración de Pines
- El pin 12 se utiliza como pin de activación (trigger) del sensor ultrasónico.
- El pin 11 se utiliza para recibir la señal de eco del sensor ultrasónico.
- Se utiliza el pin 6 para conectar el sensor de infrarrojos.
- Los pines 8 y 13 se utilizan para controlar los servomotores del gripper y el eje de la grúa respectivamente.

### Variables
- `us_value`, `ir_value`: Almacenan los valores leídos por el sensor ultrasónico y el sensor de infrarrojos, respectivamente. Estos valores se utilizan para determinar la distancia al objeto detectado por el sensor ultrasónico y para identificar si se ha encontrado la marca negra por el sensor de infrarrojos.
- `us_blocker`, `ir_blocker`: Son variables booleanas que evitan la detección repetida. Se utilizan para bloquear la detección hasta que se cumplan ciertas condiciones, como evitar que la grúa intente recoger el mismo objeto varias veces o que la marca negra se detecte repetidamente.
- `direction_s`, `horario`, `a_horario`: Estas variables controlan la dirección de los servomotores. Determinan los ángulos a los que deben girar los servomotores para mover la grúa y la pinza en la dirección deseada.
- `time_us`, `time_ir`: Se utilizan para medir el tiempo desde la última detección. Estos tiempos se utilizan para controlar los intervalos entre detecciones y realizar acciones específicas en ciertas condiciones.
- `correction`: Variable utilizada para corregir la detección de la marca negra. Una vez que se detecta la marca negra, esta variable se activa para ajustar la dirección de la grúa y completar la tarea de transporte del bloque.

### Configuración Inicial
- En la función `setup()`, se inicializan los pines de los servomotores y del sensor de infrarrojos, se establecen las posiciones iniciales de los servomotores, se inicia la comunicación serial para la depuración y se establece la dirección inicial de la grúa.

### Bucle Principal (`loop()`)
- En el bucle principal, primero se obtiene la lectura del sensor ultrasónico para detectar la presencia de un objeto cercano (el bloque).
- Si se detecta un objeto dentro del rango especificado y no se ha bloqueado la detección, la grúa se mueve hacia el objeto para recogerlo.
- Luego, se obtiene la lectura del sensor de infrarrojos para detectar la marca negra que indica la zona de destino del bloque.
- Si se detecta la marca negra y se ha realizado la corrección necesaria, la grúa completa el movimiento hacia la zona de destino y se reinician los bloqueadores de detección.

### Notas Adicionales
- El código está diseñado para controlar una grúa que recoge un objeto detectado por un sensor ultrasónico y lo transporta hacia una zona de destino detectada por un sensor de infrarrojos. Este proceso se repite en un bucle continuo, lo que permite que la grúa funcione de manera autónoma una vez que se inicia el programa en el Arduino.
