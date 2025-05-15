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

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Declaraciones del modulo para la gestion de ALUMNO
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

//! Puntero que representa un alumno
typedef struct alumno_s * alumno_t; // para usar directamente "alumno_t" es algo del tipo alumno

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

alumno_t CrearAlumno(char nombre[], char apellido[], int documento);

int SerializarAlumno(alumno_t alumno, char buffer[], uint32_t size);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif
 
#endif /* ALUMNO_H_ */
