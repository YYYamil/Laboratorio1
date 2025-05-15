
#ifndef CONFIG_H
#define CONFIG_H

// Comenta o descomenta la siguiente línea para el tipo de memoria
#define USAR_MEMORIA_ESTATICA

// Definimos el máximo número de alumnos si usamos memoria estática
#ifdef USAR_MEMORIA_ESTATICA
    #define MAX_CANT_ALUMNOS 2
#endif

#endif /* CONFIG_H */