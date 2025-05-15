/*********************************************************************************************************************
Copyright (c) 2025, Yamil Tolaba <yamiltolaba@gmail.com>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 ** @brief Codigo fuente para la gestion de alumno
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"

#include "config.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */


//! Estuctura con los datos de alumno
struct alumno_s {   //debe ser el mismo struct de alumno.h
    char nombre[20];        //!< Nombre del alumno
    char apellido [20];     //!< Apellido del alumno
    int documento;          //!< Documento del alumno
#ifdef USAR_MEMORIA_ESTATICA
    bool ocupado;           //!< Para Memoria Estatica indica si una instancia está ocupada
#endif
};

/* === Private function declarations =============================================================================== */

static alumno_t CrearAlumnoEstatico();

/**
 * @brief Inserta en un buffer un campo de objeto JSON tipo cadena.
 *
 * @param[in] campo Nombre del campo
 * @param[in] valor Valor de la cadena
 * @param[in] buffer Puntero a memoria de destino
 * @param[in] size espacio disponible en buffer
 * @return Cantidad de caracteres de la cadena resultante. La cadena escrita en buffer se trunca si este valor supera
 * `size-1`
 */
static int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t size);

/**
 * @brief Devuelve un json de cadena valor
 * 
 * @param campo Cadena de caracteres
 * @param valor Entero que recibe el valor
 * @param buffer Cadena donde se escribe la serializacion
 * @param size Lugares disponibles en la cadena
 * @return int Devolvera -1 si no hay espacios suficientes
 */
static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t size);


/* === Private variable definitions ================================================================================ */


#ifdef USAR_MEMORIA_ESTATICA
//! Arreglo de alumnos para cuando se usa Memoria Estática
static struct alumno_s arreglo_alumnos[MAX_CANT_ALUMNOS] = {0}; //! Comienza en 0
#endif

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
static int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":%i", campo, valor);
}

#ifdef USAR_MEMORIA_ESTATICA
static alumno_t CrearAlumnoEstatico(){
    alumno_t self = NULL;
    int i;

    for(i = 0; i < MAX_CANT_ALUMNOS; i++){
        if(arreglo_alumnos[i].ocupado == false){
            arreglo_alumnos[i].ocupado = true;
            self = &arreglo_alumnos[i];
            break;
        }
    }

    return self;
}
#endif
    


/* === Public function definitions ============================================================================== */

alumno_t CrearAlumno(char nombre[], char apellido[], int documento){

    #ifdef USAR_MEMORIA_ESTATICA
        alumno_t self = CrearAlumnoEstatico();
    #else
        alumno_t self = malloc(sizeof(struct alumno_s));
    #endif

    if(self != NULL){
        strncpy(self->nombre, nombre, sizeof(self->nombre)-1);
        strncpy(self->apellido, apellido, sizeof(self->apellido)-1);
        self->documento = documento;
    }

    return self;
}

int SerializarAlumno(alumno_t alumno, char buffer[], uint32_t size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer = buffer + 1;
    escritos = 1;

    resultado = SerializarCadena("nombre", alumno->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }

    buffer = buffer + resultado;
    escritos = escritos + resultado;
    resultado = escritos;

    escritos = escritos + SerializarCadena("apellido", alumno->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);
    resultado = escritos;

    escritos = escritos + SerializarEntero("documento", alumno->documento, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);

    if (escritos >= (size - 1)) {
        return -1;
    } else {
        *buffer = '}';
        buffer++;
        *buffer = '\0';

        escritos = escritos + 2;
    }

    return escritos;
}


 /*=== End of documentation ======================================================================================== */
 