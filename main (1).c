#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

// Función para colocar las mayúsculas a todas las letras.
void mayusculas(char *cadena)
{
  for(int i = 0; cadena[i] != '\0'; i++)
    {
      cadena[i] = toupper(cadena[i]); // Cada carácter se pasa a mayúsculas.
    }
}


// Función comparar (o más bien, 'lower than') para la función list_sortedInsert.
int comparar(void *data1, void *data2) {
    Paciente *paciente1 = (Paciente *)data1;
    Paciente *paciente2 = (Paciente *)data2;
  
    return strcmp(paciente1->hora, paciente2->hora) < 0; // Retorna true en caso de que la hora del paciente1 sea menor a la del paciente2.
}

// Función encargada de encontrar al paciente en una lista.
Paciente* encontrarPaciente(List *ListaPacientes, char *nombre)
{
  Paciente *paciente = list_first(ListaPacientes);
  while (paciente != NULL)
    {
      if (strcmp(paciente->nombre, nombre) == 0)
      {
        paciente = list_popCurrent(ListaPacientes); // Se elimina el paciente de la lista.
        return paciente; // Se retorna el paciente encontrado.
      }
      paciente = list_next(ListaPacientes); // En caso de no encontrarlo, se pasa al siguiente paciente.
    }

  return NULL;

}

// Función encargada de mostrar los nombres de los pacientes en una lista.
void mostrarPacientes(List *listaPacientes)
{
  Paciente *paciente = list_first(listaPacientes);
  if (paciente == NULL)
  {
    printf("Lista vacia.\n");
  }
  while(paciente != NULL) // Recorre toda la lista mostrando los nombres de los pacientes.
    {
      printf("%s\n", paciente->nombre);
      paciente = list_next(listaPacientes);
    }
}

// Función encargada del primer menú "Registrar paciente".
void registrar_paciente(List *pacientesPrioridadBaja) {
  unsigned short edad;
  Paciente *paciente = malloc(sizeof(Paciente)); // Asignación memoria para el paciente.	
  if (paciente == NULL) {
      printf("\nNo se pudo registrar al paciente\n\n");
      return;
  }
  getchar();    
  
  printf("\n=======================================\n");
  printf("          Datos del paciente\n");
  printf("=======================================\n\n");
  // Nombre del paciente
  printf("Nombre del paciente: ");
  scanf("%[^\n]", paciente->nombre);
  mayusculas(paciente->nombre);
  // Edad del paciente
  printf("Edad del paciente: ");
  // Bucle para la edad
  while((scanf("%hu", &edad)) != 1) // Hasta que no se realice una entrada valida (número entero)
    {
      printf("Ingrese una edad válida: ");
      while (getchar() != '\n'); // Para limpiar el buffer
    }
  getchar();
  paciente->edad = edad;
  // Síntoma del paciente.
  printf("Síntomas del paciente: ");
  scanf("%[^\n]", paciente->sintoma);
  // Hora de ingreso del paciente
  printf("Hora de ingreso del paciente (HH:MM): ");
  getchar();
  scanf("%[^\n]", paciente->hora);
  
  // Se asigna automáticamente la prioridad Baja.
  strcpy(paciente->prioridad, "BAJA");
  
  
  // Se agrega el paciente a la lista de prioridad baja.
  list_sortedInsert(pacientesPrioridadBaja, paciente, comparar);

  printf("\nPaciente registrado con éxito.\n\n");
}


// Función encargada de agregar a cada paciente en su lista correspondiente.
void asignarPacienteALista(Paciente *paciente, List *pacientesPrioridadBaja, List *pacientesPrioridadMedia, List *pacientesPrioridadAlta)
{
  if (strcmp(paciente->prioridad, "BAJA") == 0) 
  {
      list_sortedInsert(pacientesPrioridadBaja, paciente, comparar); // Agrega el paciente en la lista de prioridad baja.
  } 
  else if (strcmp(paciente->prioridad, "MEDIA") == 0) 
  {
      list_sortedInsert(pacientesPrioridadMedia, paciente, comparar); // Agrega el paciente en la lista de prioridad media.
  } 
  else if (strcmp(paciente->prioridad, "ALTA") == 0)
  {
      list_sortedInsert(pacientesPrioridadAlta, paciente, comparar); // Agrega el paciente en la lista de prioridad alta.
  }
}

// Función encargada de registrar la nueva prioridad de un paciente.
void asignar_prioridad(List *pacientesPrioridadBaja, List *pacientesPrioridadMedia, List *pacientesPrioridadAlta)
{
  printf("\n=======================================\n");
  printf("        Asignación de prioridad\n");
  printf("=======================================\n\n");
  Paciente *paciente;
  char nombre[50];
  char prioridad[6];
  int flag;
  
  printf("Ingrese el nombre del paciente: ");
  getchar();
  scanf("%[^\n]", nombre);
  mayusculas(nombre);
  
  getchar();
  // Bucle hasta que se ingrese una prioridad válida.
  while(1)
    {
      printf("Ingrese la prioridad del paciente (Baja/Media/Alta): ");
      scanf("%[^\n]", prioridad);
      mayusculas(prioridad);
      if (strcmp(prioridad, "BAJA") == 0 || strcmp(prioridad, "MEDIA") == 0 || strcmp(prioridad, "ALTA") == 0)
      {
        break;
      }
      getchar();
    }
  // Fín del bucle.
  

  // Se busca al paciente en la lista prioridad baja
  if ((paciente = encontrarPaciente(pacientesPrioridadBaja, nombre)) != NULL)
  {
    strcpy(paciente->prioridad, prioridad); // Se actualiza la prioridad del paciente.
    asignarPacienteALista(paciente, pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Asignacion a la priordad correspondiente.
    printf("\nEl paciente ahora se encuentra en la prioridad %s\n\n", paciente->prioridad);
  }
    
  // Se busca al paciente en la lista prioridad media
  else if ((paciente = encontrarPaciente(pacientesPrioridadMedia, nombre)) != NULL)
  {
      strcpy(paciente->prioridad, prioridad); // Se actualiza la prioridad del paciente.
      asignarPacienteALista(paciente, pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Asignacion a la priordad correspondiente.
      printf("\nEl paciente ahora se encuentra en la prioridad %s\n\n", paciente->prioridad);
  }
    
  // Se busca al paciente en la lista prioridad alta  
  else if ((paciente = encontrarPaciente(pacientesPrioridadAlta, nombre)) != NULL)
  {
      strcpy(paciente->prioridad, prioridad); // Se actualiza la prioridad del paciente.
      asignarPacienteALista(paciente, pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Asignacion a la priordad correspondiente.
      printf("\nEl paciente ahora se encuentra en la prioridad %s\n\n", paciente->prioridad);
  }
    
  else
  {
    printf("\nPaciente no se encuentra en el sistema\n\n");
  }
}

// Función encargada del menú 3 "Mostrar lista de espera"
void mostrar_lista_pacientes(List *pacientesPrioridadBaja, List *pacientesPrioridadMedia, List *pacientesPrioridadAlta) 
{
  printf("\n=======================================\n");
  printf("           Lista de espera\n");
  printf("=======================================\n\n");

  // Se muestra cada paciente de las distintas listas: prioridad baja, media y alta.
  printf("Pacientes prioridad Alta:\n\n");
  mostrarPacientes(pacientesPrioridadAlta);
  printf("\n");
  
  printf("Pacientes prioridad Media:\n\n");
  mostrarPacientes(pacientesPrioridadMedia);
  printf("\n");
  
  printf("Pacientes prioridad Baja:\n\n");
  mostrarPacientes(pacientesPrioridadBaja);
  printf("\n");
}

// Función encargada del menú 4 "Atender al siguiente paciente"
void atenderSiguientePaciente(List *pacientesPrioridadBaja, List *pacientesPrioridadMedia, List *pacientesPrioridadAlta)
{
  // Se inicializan las variables
  Paciente *pacientesBaja = list_first(pacientesPrioridadBaja);
  Paciente *pacientesMedia = list_first(pacientesPrioridadMedia);
  Paciente *pacientesAlta = list_first(pacientesPrioridadAlta);
  int flag = 0; // Esta variable se utiliza para verificar si ya se encontró un paciente para ser atendido.
                // 1 para que ya se encontró, 0 para que no se encontro.

  printf("\n=======================================\n");
  printf("           Atención paciente\n");
  printf("=======================================\n\n");

  // Se busca en cada lista el siguiente paciente a ser atendido y se muestra.
  // En caso de ya haberlo encontrado, no se sigue buscando.
  while (pacientesAlta != NULL && flag == 0) // Búsqueda en lista prioridad ALTA
    {
      flag = 1;
      printf("Nombre: %s \nEdad: %hu\nSíntomas: %s\nHora de llegada: %s\nPrioridad: %s", pacientesAlta->nombre, pacientesAlta->edad, pacientesAlta->sintoma, pacientesAlta->hora, pacientesAlta->prioridad);
      list_popFront(pacientesPrioridadAlta);
    }
    
    while (pacientesMedia != NULL && flag == 0) // Búsqueda en lista prioridad MEDIA
    {
      printf("Nombre: %s \nEdad: %hu\nSíntomas: %s\nHora de llegada: %s\nPrioridad: %s", pacientesMedia->nombre, pacientesMedia->edad, pacientesMedia->sintoma, pacientesMedia->hora, pacientesMedia->prioridad);
      list_popFront(pacientesPrioridadMedia);
      flag = 1;
    }
  
    while (pacientesBaja != NULL && flag == 0) // Búsqueda en lista prioridad BAJA
    {
      printf("Nombre: %s \nEdad: %hu\nSíntomas: %s\nHora de llegada: %s\nPrioridad: %s", pacientesBaja->nombre, pacientesBaja->edad, pacientesBaja->sintoma, pacientesBaja->hora, pacientesBaja->prioridad);
      list_popFront(pacientesPrioridadBaja);
      flag = 1;
    }
  // Si el flag es igual a 0, significa que no se encontró ningún paciente en la lista.
  if (flag == 0)
  {
    printf("No hay pacientes en espera");
  }
    printf("\n\n");
}

// Función encargada del menú 5 "Mostrar pacientes por prioridad"
void mostrarPorPrioridad(List *pacientesPrioridadBaja, List *pacientesPrioridadMedia, List *pacientesPrioridadAlta)
{
  printf("\n=======================================\n");
  printf("            Lista prioridad\n");
  printf("=======================================\n\n");
  getchar();
  char prioridad[6];
  // Bucle hasta que se ingrese una prioridad válida.
  while(1)
    {
      printf("Ingrese la prioridad (Baja/Media/Alta): ");
      scanf("%[^\n]", prioridad);
      printf("\n");
      mayusculas(prioridad);
      if (strcmp(prioridad, "BAJA") == 0 || strcmp(prioridad, "MEDIA") == 0 || strcmp(prioridad, "ALTA") == 0)
      {
        break;
      }
      getchar();
    }
  // Fín del bucle.

  // Dependiendo de la prioridad elegida, se muestra la lista correspodiente.
  if (strcmp(prioridad, "BAJA") == 0) // Prioridad BAJA
  {
    printf("Pacientes con prioridad baja: \n\n");
    mostrarPacientes(pacientesPrioridadBaja);
  }
  else if (strcmp(prioridad, "MEDIA") == 0) // Prioridad MEDIA
  {
    printf("Pacientes con prioridad media: \n\n");
    mostrarPacientes(pacientesPrioridadMedia);
  }
  else // Prioridad Alta
  {
    printf("Pacientes con prioridad alta: \n\n");
    mostrarPacientes(pacientesPrioridadAlta);
  }
  printf("\n");
}

int main() {
  char opcion;
  List *pacientesPrioridadBaja = list_create(); // puedes usar una lista para gestionar los pacientes
  List *pacientesPrioridadMedia = list_create();
  List *pacientesPrioridadAlta = list_create();

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientesPrioridadBaja); // Registrar paciente.
      break;
    case '2':
      asignar_prioridad(pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Asignar prioridad.
      break;
    case '3':
      mostrar_lista_pacientes(pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Mostrar lista de espera.
      break;
    case '4':
      atenderSiguientePaciente(pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Atender al siguiente paciente.
      break;
      break;
    case '5':
      mostrarPorPrioridad(pacientesPrioridadBaja, pacientesPrioridadMedia, pacientesPrioridadAlta); // Mostrar pacientes por prioridad.
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria..."); // Salir
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos.
  list_clean(pacientesPrioridadBaja);

  return 0;
}