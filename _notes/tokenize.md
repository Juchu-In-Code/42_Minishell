
                         _        _              _
                        | |_ ___ | | _____ _ __ (_)_______
                        | __/ _ \| |/ / _ \ '_ \| |_  / _ \
                        | || (_) |   <  __/ | | | |/ /  __/
                         \__\___/|_|\_\___|_| |_|_/___\___|

    [x] - FASE I -> identificar
        a) separar linea en segmentos
        b) a cada segmento se le asigna:
            - un id
            - la info de a donde empieza en la linea
            - cuanto mide

    [ ] - FASE II -> interpretar
        a) revisar que la sintaxis sea correcta
        b) juntar los tokens con su contexto correspondiente
        c)

    [ ] - FASE II -> definir
        a) construir los tokens finales para ser consumidos
        b) establecer funcionalidad y relaciones
        c) establecer orden


    hacer q tokenize sea una func con su propio "main"
        lexer           - segmentar
        interpreter     - agrupar y analizar sintaxis
        tokenizer       - generar la lista de tokens en orden, con su func
        
        utilidades:
            
            [x] - extraer funcs de debug para usar con una flag
            [x] - extraer funcs de debug para uso de errores
                - mostrar mensajes de error mostrando la pos
    mejorar como se gestionan los toks
        el tokt de todos los tipos no corresponde al mismo mapeo de valores
        se justifica hacer un enum o mejor hacer defs? 
        
        



    

    el contexto se inicia desde el comienzo del input
            termina:
                 - en un pipe
                 - al final del input
    el primer string del contexto es tomado como comando
    si no hay comandos en el contexto, el contexto se acepta

    al iniciar el contexto:
        aceptables: string, redirs, quotes

    redirs:
        acpetables: string, quotes
        si en el contexto hay multipes redirs, se ejecutan todos pero solo el último toma relevancia
        si un > o >> está previo un | entonces el input del pipe se cierra

    quotes y strings:
        la primera en encontrarse al iniciar un contexto, es tomada como un comando
        al seguir una redir, se asigna a esta

    al encontrar un pipe:
        se cierra el contexto anterior, inicia un nuevo contexto de pipe
        al iniciar un pipe debe existir un comando en el contexto anterior

    context pipeline:
        se activa al encontrar un pipe, de modo que se pueda gestionar

    context subshell:
        luego de terminar de tokenizar el contexto de subshell se ejecuta primero
        enviando la linea completa a un fork con sus propiedades individuales

    establecer cada contexto en orden:
        pipes, heredocs, otras redirs, y finalmente ejecución

     check if the resulting tokens have expansions
            mark them for expansion

    expansion:
            quotes -
            envars -

     a string starting a job becomes a command (which can be either an executable
     of after a pipe asks where to read and send information to

                             ___ ___
                            |__ \__ \
                              / / / /
                             |_| |_|
                             (_) (_)

    EDGE CASES



