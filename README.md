
## Sistema de Gestión de Pacientes en Hospital
## Descripción:

Este sistema permite a los usuarios gestionar la atención de pacientes diarios en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera y mostrar la información necesaria. El sistema está diseñado para ayudar en el procedimiento diario de atención del hospital y poder acceder con un par de opciones a la información necesaria.

## Cómo compilar y ejecutar
Para mayor simplicidad al momento de probar y ejecutar el codigo se utilizará la plataforma [Repl.it](http://repl.it/), los pasos a seguir son:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/YeahBro5/Tarea-1`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Configure el comando de compilacion con gcc tdas/*.c main.c -Wno-unused-result -o main y el comando run no se modifica (./main)
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades
## Funcionando correctamente:
* `Registrar paciente`: Registra al paciente junto con todos sus datos (Nombre, Edad, Sintomas, Hora de llegada).
* `Asignar prioridad a paciente`: Cambia la prioridad del paciente seleccionado.
* `Mostrar lista de espera`: Muestra la lista de espera ordenada por nivel de prioridad y hora de llegada.
* `Atender al siguiente paciente`: Muestra la información del paciente a ser atendido.
* `Mostrar pacientes por prioridad`: Muestra la lista de espera de un nivel de prioridad en específico.

## Problemas conocidos:
* En caso de que se introduzca la hora de llegada en un formato distinto al especificado, no se ordenará correctamente.
* En caso de que el usuario introduzca una edad no válida, por ejemplo, "veinte años", en vez de 20, no se podrán guardar correctamente los datos.
  
## A mejorar:
* Implementar aún más funciones que se encarguen de mitigar los errores producidos por el usuario al momento de no realizar las solicitudes con el formato especificado.
  
## Ejemplo de uso:
**Paso 1: Registrar un Nuevo Paciente**
Se comienza registrando un nuevo paciente que acaba de llegar al hospital.
````
Opción seleccionada: 1) Registrar paciente
Nombre del paciente: Diego Zerene
Edad del paciente: 25
Síntomas del paciente: Dolor de cabeza severo
Hora de ingreso del paciente (HH:MM): 15:00

Paciente registrado con éxito.
````
El sistema registra a Diego Zerene con una prioridad inicial "Baja". La prioridad inicial será ajustada en caso de ser necesario tras la evaluación médica.

**Paso 2: Asignar Prioridad a un Paciente**

Tras una evaluación inicial, el médico determina que el estado de Diego Zerene requiere atención prioritaria.
````
Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el nombre del paciente: Diego Zerene
Ingrese la prioridad del paciente (Baja/Media/Alta): Alta
````
El sistema actualiza la prioridad de Diego Zerene a "Alta", asegurando que será una de las próximas pacientes en ser atendida.

**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades. 
````
Opción seleccionada: 3) Mostrar lista de espera

Prioridad Alta:

Diego Zerene

Prioridad Media:


Prioridad Baja:



````
La lista muestra a Diego Zerene en la parte superior, indicando su prioridad alta y que es el siguiente a ser atendido.

**Paso 4: Atender al Siguiente Paciente**

Ya que Diego Zerene es el próximo a ser atendido, se desplegará toda su información.
````
Opción seleccionada: 4) Atender al siguiente paciente

Nombre: DIEGO ZERENE
Edad: 25
Sintoma: Dolor de cabeza severo
Hora de llegada: 15:00
Prioridad: ALTA
````
**Paso 5 (bonus): Mostrar pacientes por prioridad**
Una vez atendido Diego Zerene, el doctor decide que quiere revisar si es que queda alguien mas en prioridad alta.
````
Opción seleccionada: 5) Mostrar pacientes por prioridad

Ingrese la prioridad (Baja/Media/Alta): Alta

Pacientes con prioridad Alta:

Lista vacia.

````
Ya que Diego Zerene era el único paciente que faltaba atender, la lista de prioridad alta se mostrará vacía.
