                     ____  _                   _     
                    / ___|(_) __ _ _ __   __ _| |___ 
                    \___ \| |/ _` | '_ \ / _` | / __|
                     ___) | | (_| | | | | (_| | \__ \
                    |____/|_|\__, |_| |_|\__,_|_|___/
                             |___/                   

    se determina una int global
    la int global corresponde a diferentes valores de una tabla de señales
    la tabla de señales tiene una serie de punteros a funcs
    al determinarse la señal, se indica la callback func relacionada
    cuando la señal se captura, se ejecuta la func relacionada

    CTRL + C
        sigint

    CTRL + D
        exit

    CTRL + \
        denegar la señal y no hacer nada

    diferenciar "interactive mode" de "noninteractive?"

    usar ([K] & 0x1f) para registrar tecla + ctrl en el buffer?

