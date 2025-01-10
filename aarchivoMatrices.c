#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_ORDENES 50
#define NOMBRE_MAX 50

typedef struct {
    char nombre[NOMBRE_MAX];
    int cantidad;
    float tiempoFabricacion;
    int recursos;
} Producto;

typedef struct {
    char nombreProducto[NOMBRE_MAX];
    int cantidadSolicitada;
    float tiempoTotal;
    int recursosTotales;
} OrdenTrabajo;

Producto productos[MAX_PRODUCTOS];
OrdenTrabajo ordenes[MAX_ORDENES];
int totalProductos = 0;
int totalOrdenes = 0;
int archivoGuardado = 1;


void menu();
void ingresarProducto();
void consultarProducto();
void mostrarProductos();
void eliminarProducto();
void comprarProducto();
void ingresarOrdenTrabajo();
void mostrarOrdenes();
void buscarOrdenTrabajo();
void guardarArchivos();
void cargarArchivos();

int main() {
    cargarArchivos();
    menu();
    printf("-R-> DESARROLLADO POR JOSO -K-> ");
    return 0;
}

void menu() {
    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Ingresar productos\n");
        printf("2. Comprar productos\n");
        printf("3. Consultar un producto\n");
        printf("4. Mostrar todos los productos\n");
        printf("5. Ingresar orden de trabajo\n");
        printf("6. Mostrar todas las ordenes de trabajo\n");
        printf("7. Buscar una orden de trabajo\n");
        printf("8. Eliminar producto\n");
        printf("9. Guardar archivo\n");
        printf("10. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1: ingresarProducto(); break;
            case 2: comprarProducto(); break;
            case 3: consultarProducto(); break;
            case 4: mostrarProductos(); break;
            case 5: ingresarOrdenTrabajo(); break;
            case 6: mostrarOrdenes(); break;
            case 7: buscarOrdenTrabajo(); break;
            case 8: eliminarProducto(); break;
            case 9: guardarArchivos(); break;
            case 10:
                if (!archivoGuardado) {
                    printf("\nNo ha guardado los cambios. Desea salir de todas formas? (s/n): ");
                    char confirmacion;
                    scanf(" %c", &confirmacion);
                    if (confirmacion == 'n' || confirmacion == 'N') {
                        opcion = 0; // Volver al menu
                    }
                }
                break;
            default: printf("\nOpcion no valida.\n");
        }
    } while (opcion != 10);
}

void ingresarProducto() {
    if (totalProductos >= MAX_PRODUCTOS) {
        printf("\nNo se pueden agregar mas productos.\n");
        return;
    }
    Producto nuevoProducto;
    printf("\nIngrese el nombre del producto: ");
    fgets(nuevoProducto.nombre, NOMBRE_MAX, stdin);
    nuevoProducto.nombre[strcspn(nuevoProducto.nombre, "\n")] = '\0';

    printf("Ingrese la cantidad inicial: ");
    scanf("%d", &nuevoProducto.cantidad);

    printf("Ingrese el tiempo de fabricacion (en horas): ");
    scanf("%f", &nuevoProducto.tiempoFabricacion);

    printf("Ingrese la cantidad de recursos necesarios: ");
    scanf("%d", &nuevoProducto.recursos);

    productos[totalProductos++] = nuevoProducto;
    archivoGuardado = 0;
    printf("\nProducto agregado exitosamente.\n");
}

void consultarProducto() {
    char nombreBusqueda[NOMBRE_MAX];
    printf("\nIngrese el nombre del producto a consultar: ");
    fgets(nombreBusqueda, NOMBRE_MAX, stdin);
    nombreBusqueda[strcspn(nombreBusqueda, "\n")] = '\0';

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreBusqueda) == 0) {
            printf("\nProducto encontrado:\n");
            printf("Nombre: %s\nCantidad: %d\nTiempo de Fabricacion: %.2f horas\nRecursos: %d\n",
                   productos[i].nombre, productos[i].cantidad, productos[i].tiempoFabricacion, productos[i].recursos);
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

void mostrarProductos() {
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < totalProductos; i++) {
        printf("%d. Nombre: %s\nCantidad: %d\nTiempo de Fabricacion: %.2f horas\nRecursos: %d\n\n",
               i + 1, productos[i].nombre, productos[i].cantidad, productos[i].tiempoFabricacion, productos[i].recursos);
    }
}

void eliminarProducto() {
    char nombreEliminar[NOMBRE_MAX];
    printf("\nIngrese el nombre del producto a eliminar: ");
    fgets(nombreEliminar, NOMBRE_MAX, stdin);
    nombreEliminar[strcspn(nombreEliminar, "\n")] = '\0';

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreEliminar) == 0) {
            for (int j = i; j < totalProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            totalProductos--;
            archivoGuardado = 0;
            printf("\nProducto eliminado exitosamente.\n");
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

void comprarProducto() {
    char nombreCompra[NOMBRE_MAX];
    int cantidadCompra;
    printf("\nIngrese el nombre del producto a comprar: ");
    fgets(nombreCompra, NOMBRE_MAX, stdin);
    nombreCompra[strcspn(nombreCompra, "\n")] = '\0';

    printf("Ingrese la cantidad a comprar: ");
    scanf("%d", &cantidadCompra);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreCompra) == 0) {
            productos[i].cantidad += cantidadCompra;
            archivoGuardado = 0;
            printf("\nCompra realizada exitosamente.\n");
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

void ingresarOrdenTrabajo() {
    if (totalOrdenes >= MAX_ORDENES) {
        printf("\nNo se pueden agregar mas ordenes de trabajo.\n");
        return;
    }

    OrdenTrabajo nuevaOrden;
    printf("\nIngrese el nombre del producto: ");
    fgets(nuevaOrden.nombreProducto, NOMBRE_MAX, stdin);
    nuevaOrden.nombreProducto[strcspn(nuevaOrden.nombreProducto, "\n")] = '\0';

    printf("Ingrese la cantidad solicitada: ");
    scanf("%d", &nuevaOrden.cantidadSolicitada);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nuevaOrden.nombreProducto) == 0) {
            nuevaOrden.tiempoTotal = productos[i].tiempoFabricacion * nuevaOrden.cantidadSolicitada;
            nuevaOrden.recursosTotales = productos[i].recursos * nuevaOrden.cantidadSolicitada;

            if (productos[i].cantidad >= nuevaOrden.cantidadSolicitada) {
                productos[i].cantidad -= nuevaOrden.cantidadSolicitada;
                ordenes[totalOrdenes++] = nuevaOrden;
                archivoGuardado = 0;
                printf("\nOrden de trabajo ingresada exitosamente.\n");
            } else {
                printf("\nNo hay suficientes unidades disponibles para completar la orden.\n");
            }
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

void mostrarOrdenes() {
    printf("\n--- Lista de Ordenes de Trabajo ---\n");
    for (int i = 0; i < totalOrdenes; i++) {
        printf("%d. Nombre del Producto: %s\nCantidad Solicitada: %d\nTiempo Total: %.2f horas\nRecursos Totales: %d\n\n",
               i + 1, ordenes[i].nombreProducto, ordenes[i].cantidadSolicitada, ordenes[i].tiempoTotal, ordenes[i].recursosTotales);
    }
}

void buscarOrdenTrabajo() {
    char nombreOrden[NOMBRE_MAX];
    printf("\nIngrese el nombre del producto de la orden a buscar: ");
    fgets(nombreOrden, NOMBRE_MAX, stdin);
    nombreOrden[strcspn(nombreOrden, "\n")] = '\0';

    for (int i = 0; i < totalOrdenes; i++) {
        if (strcmp(ordenes[i].nombreProducto, nombreOrden) == 0) {
            printf("\nOrden de trabajo encontrada:\n");
            printf("Nombre del Producto: %s\nCantidad Solicitada: %d\nTiempo Total: %.2f horas\nRecursos Totales: %d\n",
                   ordenes[i].nombreProducto, ordenes[i].cantidadSolicitada, ordenes[i].tiempoTotal, ordenes[i].recursosTotales);
            return;
        }
    }
    printf("\nOrden de trabajo no encontrada.\n");
}

void guardarArchivos() {
    FILE *archivoProductos = fopen("productos.txt", "w");
    FILE *archivoOrdenes = fopen("ordenes.txt", "w");

    if (!archivoProductos || !archivoOrdenes) {
        printf("\nError al guardar los archivos.\n");
        return;
    }

   
    for (int i = 0; i < totalProductos; i++) {
        fprintf(archivoProductos, "%s,%d,%.2f,%d\n",
                productos[i].nombre, productos[i].cantidad, productos[i].tiempoFabricacion, productos[i].recursos);
    }
    fclose(archivoProductos);

    
    for (int i = 0; i < totalOrdenes; i++) {
        fprintf(archivoOrdenes, "%s,%d,%.2f,%d\n",
                ordenes[i].nombreProducto, ordenes[i].cantidadSolicitada, ordenes[i].tiempoTotal, ordenes[i].recursosTotales);
    }
    fclose(archivoOrdenes);

    archivoGuardado = 1;
    printf("\nArchivos guardados exitosamente.\n");
}

void cargarArchivos() {
    FILE *archivoProductos = fopen("productos.txt", "r");
    FILE *archivoOrdenes = fopen("ordenes.txt", "r");

    if (archivoProductos) {
        while (fscanf(archivoProductos, "%[^,],%d,%f,%d\n",
                      productos[totalProductos].nombre, &productos[totalProductos].cantidad,
                      &productos[totalProductos].tiempoFabricacion, &productos[totalProductos].recursos) != EOF) {
            totalProductos++;
        }
        fclose(archivoProductos);
    }

    if (archivoOrdenes) {
        while (fscanf(archivoOrdenes, "%[^,],%d,%f,%d\n",
                      ordenes[totalOrdenes].nombreProducto, &ordenes[totalOrdenes].cantidadSolicitada,
                      &ordenes[totalOrdenes].tiempoTotal, &ordenes[totalOrdenes].recursosTotales) != EOF) {
            totalOrdenes++;
        }
        fclose(archivoOrdenes);
    }
}
