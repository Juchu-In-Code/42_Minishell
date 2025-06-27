         ____        _ _ _   _
        | __ ) _   _(_) | |_(_)_ __  ___
        |  _ \| | | | | | __| | '_ \/ __|
        | |_) | |_| | | | |_| | | | \__ \
        |____/ \__,_|_|_|\__|_|_| |_|___/

        ◦ echo with option -n
        ◦ cd with only a relative or absolute path
        ◦ pwd with no options
        ◦ export with no options
        ◦ unset with no options
        ◦ env with no options or arguments
        ◦ exit with no options

        [ ] - func para reconocer builtins
        [ ] - gestionar posibles codigos de salida / error
        [ ] -


                  ___ _ ____   __
                 / _ \ '_ \ \ / /
                |  __/ | | \ V /
                 \___|_| |_|\_/


        [x] - func para print env vars
        [ ] -


                 _____     _
                | ____|___| |__   ___
                |  _| / __| '_ \ / _ \
                | |__| (__| | | | (_) |
                |_____\___|_| |_|\___/


        [ ] - func básica de echo
        [ ] - opt de '-n'
              (( -n do not output the trailing newline ))




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

        NO PLANEAR SOPORTE PARA:
            - export [key] sin =
            (que podría causar que una env local se promueva a env global)
            ?? - a menos que sencillamente pase de largo y no haga nada?
                    (excepto quejarse de malos inputs)

        NO PLANEAR
            comillas sin terminar

                 _   _                _
                | | | |_ __  ___  ___| |_
                | | | | '_ \/ __|/ _ \ __|
                | |_| | | | \__ \  __/ |_
                 \___/|_| |_|___/\___|\__|



=============================
                  ____ ____
                 / ___|  _ \
                | |   | | | |
                | |___| |_| |
                 \____|____/

