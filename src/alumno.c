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
#include <stdio.h>
/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Inserta en un buffer un campo de objeto JSON tipo cadena.
 * @warning Si el valor retornado es mayor a disponibles-1 la cadena fue truncada
 * @param[in] campo Nombre del campo
 * @param[in] valor Valor de la cadena
 * @param[in] buffer Puntero a memoria de destino
 * @param[in] disponibles espacio disponible en buffer
 * @return Cantidad de caracteres de la cadena resultante. La cadena escrita en buffer se trunca si este valor supera
 * `disponibles-1`
 */
static int SerializarCadena(const char campo[], const char valor[], char buffer[], uint32_t disponibles);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarCadena(const char campo[], const char valor[], char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(const char campo[], uint32_t valor, char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%u", campo, valor);
}

/* === Public function definitions ============================================================================== */

int Serializar(const alumno_t alumno, char buffer[], uint32_t size) {
    int escritos = 0; // total de caracteres escritos
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;
    resultado = SerializarCadena("Nombre", alumno->nombre, buffer + escritos, size - escritos);

    if (resultado < 0) {
        return -1; // si no nos alcanza el espacio
    }

    buffer[resultado] = ',';
    buffer++;
    buffer = buffer + resultado;
    escritos = escritos + resultado;
    escritos += SerializarCadena("Apellido", alumno->apellido, buffer, size - escritos);

    if (resultado < 0) {
        return -1; // si no nos alcanza el espacio
    }
    buffer++;
    buffer[resultado] = ',';
    buffer++;
    buffer = buffer + resultado;
    escritos = escritos + resultado;
    escritos = SerializarNumero("Documento", alumno->documento, buffer, size - escritos);

    if (resultado < 0) {
        return -1; // si no nos alcanza el espacio
    }
    buffer++;
    buffer[resultado] = '}';

    return escritos;
}

/* === End of documentation ======================================================================================== */
