
             _____            
            | ____|_ ____   __
            |  _| | '_ \ \ / /
            | |___| | | \ V / 
            |_____|_| |_|\_/  

    ENV
        crear env vars

        funcs de:
            [x] - clonar envs
            [x] - linea a dict
            [x] - create dict entry
            [x] - matchear un env con su val
            [x] - get env matching

            [x] - modificar val de un item
            [x] - hacer append al val de un item

            [x] - print path
            [ ] - print a matching env
            [ ] - print a matching env (multiple? variadic?)

            [ ] - env sanitization!
                    - verify input, values, state, etc
                    - lowercase / uppercase
                    - backslash...?
                    - unfinished quoting

            [ ] - eliminar un item del env

            [ ] - add special envs
                    + mod / add some envs

            [ ] - setup quickaccess
                    - path
                    - PWD / OLDPWD
                    - HOME
                    - otros?

            [x] - line to env entry
                - modify it if exists!
                - append it if append mode!

            - verificaciones, expansiones, etc?
            - ordenar lista alfabeticamente?
            - cornercases.

        agregar warns / asserts?
        
        diferenciar entre vars setupeadas locales y exportadas
        

                 _     _       _
             ___| |__ | |_   _| |
            / __| '_ \| \ \ / / |
            \__ \ | | | |\ V /| |
            |___/_| |_|_| \_/ |_|
        comienza en 1
        si el num se cambia, suma 1 deszde ahi en el siguiente
        (incluso si es negativo)
        tal parece que usa atoi, habría que probar con otros inputs
        y nums pasados del max o min
        si unset SHLVL, la siguiente shell aparece con SHLVL = 1


                     ___ ___ 
                    |__ \__ \
                      / / / /
                     |_| |_| 
                     (_) (_) 

    EDGE CASES
        variables con variables adentro
            se expanden en el momento de la asignación
            incluso si están vacías

        que pasa si no hay path?
        variables de shell especiales?
        variable _ ??
        env vars con comillas? guardar o trimmear?
        como sacar bien el pid?
        comportamiento extraño eliminando pwd o oldpwd
        comportamiento extraño
                env -i bash no incluye path
                 pero al hacer unset path o PATH= deja de ejecutar
                tal vez haya que hacer un path provisorio?
        readonly vars?

    no se planea soporte para crear variables locales

         _____                       _   
        | ____|_  ___ __   ___  _ __| |_ 
        |  _| \ \/ / '_ \ / _ \| '__| __| 
        | |___ >  <| |_) | (_) | |  | |_ 
        |_____/_/\_\ .__/ \___/|_|   \__|
                   |_|                   

        key
            puede ser minuscula o combinación
            se expanden las envs
            ignora "" e integra lo que hay adentro y expande vars
            comillas simples igual, pero no expande

            key no puede ser nums o comenzar con nums
            key no puede contener ciertos caracteres
                    cuales?

            asignar se permite solo con += (append) o = (truncate)
            si más de un = se incluye, se comienza a asignar desde el 1ro

        el mensaje de error es:
        bash: export: `invalid-key': not a valid identifier

        NO PLANEAR
            comillas sin terminar

export

    while av[i]
        buscar el =
        si existe = ...
         crear variables de la entrada de: key <=> val
        verificaciones
            - verif val
            - verif si hay +
            
        status = verif la key
            - 
        si status erroneo, asignar +1 flag
