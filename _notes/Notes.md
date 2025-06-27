
=================================================
             __  __ _       _     _          _ _
            |  \/  (_)_ __ (_)___| |__   ___| | |
            | |\/| | | '_ \| / __| '_ \ / _ \ | |
            | |  | | | | | | \__ \ | | |  __/ | |
            |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|
                                                 

    Shell loop
        REPL - Read - Execute - Print - Loop
        Error handling
            errno and ft_errno
        Input parsing
            tokenizer
        Manage env vars, manage path
        Command exec
        Builtins
            func de exec builtins para determinar que builtin
                y con que args, etc
        gestionar history
            que cosas se podrían lograr si no se usa RL?

---------------

organización de archivos
    a - main
    b - setup (verificaciones e inicializaciones y preparativos)
    c - procesamiento o ejecución de módulos principales
    + - (en adelante)
    u - utilidades, si se ve la necesidad de segregar, usar ub, uc, ud, etc
    z - debug

    MAIN
    -->     declaración de variables
    -->     verificar cosas / inicializar
                limpiar y retornar si error
    -->     main minishell loop
                limpiar y retornar si error
    -->     limpiar y retornar 0

---------------

    func para comp una string y ejecutar algo
    func para hacer split en whitespace + una string opcional de chars

---------------

    agregar una struct de propiedades de shell para guardar cosas

    SETUP
        [ ] - agregar envs adicionales / modificar las existentes
        [ ] - setup quickenv y path
        [ ] - vars con expansiones?
        [ ] - var sanitization

        [ ] - shell properties
        [ ] - backups y tcgetattr
                investigar más de todo eso

    PROMPT
            - tomar cwd...
            - hacer join con user
            - colores?
            - podría capturar el código del $? y mostrarlo.

    SIGNALS
        [ ] - crear var global
        [ ] - crear funcs de señales

    LOOP
            - signal
            - prompt
        [x] - capturar linea
        [x] - add hist
            - histfile?
        [ ] - tokenize
        [ ] - expand
        [ ] - process
        [ ] - execute

    CLEANUP
        [ ] - establecer como se limpian las listas
        [ ] - limpiar cadenas de texto
        [ ] - crear func para guardar * a liberar?

---------------

    redirecciones
    expansiones

---------------

--    [ ]   revisar funcs de readline / history
            investigar como funciona la manipulación de la linea

--    [ ] organizar funcs externas de acuerdo a la funcionalidad

    como se declara y usa la global? (respecto a la norma)
    se pueden globales const?

----------------

    casos a testear
        << en el medio de la ejecución y no al principio?

        cd y otros builtins en pipes
        multiples variables encadenadas y multiples signos de dolar encadenados

    documentar casos comparando con BASH y ZSH

-- notas para reordenar luego
----------------------------

    la minishell debería poder tomar las variables creadas?
    puede crear variables?

    func de exit: exit code, alguna opt, cosas a limpiar(a modo func variadica)

    habría que hacerse algo especial con el prompt?

    idea de builtin de debug: dado el contenido de una linea como arg
    (o la siguiente linea)
    separa el input organizado en los tokens y su significado
    quizás similar a como nush hace cosas o la pag de explainshell

    redirs pueden estar en cualquier parte,
                --> incluso en el medio de args
                --> incluso en el medio de builtins

    quotes " '$$' " las comillas dobles hacen que las comillas
                    simples no importen, las $$ se expanden

    el token puede tener un modo "expandible" y un modo literal

    para hacer funcionar el hist file entre sesiones 
        abrir un archivo para guardar las cosas
        cargar el contenido en una lista y alimentarla a rl hist
    
    heredoc debería ser ejecutado antes que cualquier otra redir
            o cmd
            y si el EOF tiene comillas, hay que expandir las vars
            y las vars en el EOF no tienen que expandirse

    syntax errors -> hay que cerrar todo sin ejecutar
    

============================================
                          _____  _____  ___ 
                         / _ \ \/ / _ \/ __|
                        |  __/>  <  __/ (__ 
                         \___/_/\_\___|\___|
                                            
    
    hacer un ft_fork que gestione el potencial error del fork y retorne el pid.
        posiblemente se pueda pasarle un arg
            para que escriba el pid antes de retornarlo,
            en caso de que se necesite guardar el pid (para waitpid, etc)



                                 _           _ _ _   _           
                                | |__  _   _(_) | |_(_)_ __  ___ 
                                | '_ \| | | | | | __| | '_ \/ __|
                                | |_) | |_| | | | |_| | | | \__ \
                                |_.__/ \__,_|_|_|\__|_|_| |_|___/
                                                                 

    si se recibe la designación de builtin
        ejecuta lo que tiene que hacer
        pero no ejecuta algo externo?



                                     ____       _
                                    |  _ \  ___| |__  _   _  __ _ 
                                    | | | |/ _ \ '_ \| | | |/ _` |
                                    | |_| |  __/ |_) | |_| | (_| |
                                    |____/ \___|_.__/ \__,_|\__, |
                                                            |___/ 
    separar make de debug, fsanitize, valgrind, etc
    estandarizar una serie de cosas para usar gdb
    ft_assert o similar
    test.sh con diffs de output
    debug snapshot para ver info de
        si los tokens y resultados son los correctos

    interfaz de testeo/debug separada del código principal
    el make debería poder incluir o no esos casos
    tamb se puede hacer con #ifdef DEBUG
    las lineas de debug podrían tener un /* DEBUG */ al comienzo


    para ayudar a debugear,
    armar un modo "headless" o no interactivo,
    con alguna opt o flag activada
    que tal pasandole algo por stdin?

    testear con tmux / zellij de escribir lo mismo en 2 shells en paralelo?
    

                                         ___    _
                                        |_ _|__| | ___  __ _ ___
                                         | |/ _` |/ _ \/ _` / __|
                                         | | (_| |  __/ (_| \__ \
                                        |___\__,_|\___|\__,_|___/
                                                                 
    implementar una arena?
    crear una interfaz que pueda limpiar todos los pts en un arr?
    como se podría usar el programa con un #! (shebang)?


                                          ____
                                         / ___|___   ___  _ __
                                        | |   / _ \ / _ \| '_ \
                                        | |__| (_) | (_) | |_) |
                                         \____\___/ \___/| .__/
                                                         |_|
    
    mejorar y estandarizar como usar git?
        mejoras a gitf?

    
                 _____ ___ _   _ ___ ____  _   _ ___ _   _  ____
                |  ___|_ _| \ | |_ _/ ___|| | | |_ _| \ | |/ ___|
                | |_   | ||  \| || |\___ \| |_| || ||  \| | |  _
                |  _|  | || |\  || | ___) |  _  || || |\  | |_| |
                |_|   |___|_| \_|___|____/|_| |_|___|_| \_|\____|
 
        Testear maníacamente todo
            chequear frees con valgrind y address sanitizer
        
        revisar que todo en la libft esté en condiciones
        revisar la norma y especificaciones del proyecto


------------------------------------------------------------------
                 _______  _______ _____ ____  _   _    _    _
                | ____\ \/ /_   _| ____|  _ \| \ | |  / \  | |
                |  _|  \  /  | | |  _| | |_) |  \| | / _ \ | |
                | |___ /  \  | | | |___|  _ <| |\  |/ ___ \| |___
                |_____/_/\_\ |_| |_____|_| \_\_| \_/_/   \_\_____|
                 _____ _   _ _   _  ____ _____ ___ ___  _   _ ____
                |  ___| | | | \ | |/ ___|_   _|_ _/ _ \| \ | / ___|
                | |_  | | | |  \| | |     | |  | | | | |  \| \___ \
                |  _| | |_| | |\  | |___  | |  | | |_| | |\  |___)
                |_|    \___/|_| \_|\____| |_| |___\___/|_| \_|____/

-- readline
------------
       #include <readline/readline.h>
       #include <readline/history.h>
--    char *readline (const char *prompt);

    DESCRIPTION
       readline will read a line from the terminal and return it, using
       prompt as a prompt.  If prompt is NULL or the empty string, no
       prompt is issued.  The line returned is allocated with malloc(3);
       the caller must free it when finished.  The line returned has the
       final newline removed, so only the text of the line remains.

       readline offers editing capabilities while the user is entering
       the line.  By default, the line editing commands are similar to
       those of emacs.  A vi-style line editing interface is also
       available.

       This manual page describes only the most basic use of readline.
       Much more functionality is available; see The GNU Readline Library
       and The GNU History Library for additional information.

    RETURN VALUE
       readline returns the text of the line read.  A blank line returns
       the empty string.  If EOF is encountered while reading a line, and
       the line is empty, NULL is returned.  If an EOF is read with a
       non-empty line, it is treated as a newline.

    --> void rl_clear_history (void)
    Clear the history list by deleting all of the entries, in the same manner
    as the History library’s clear_history() function. This differs from
    clear_history because it frees private data Readline saves in the history
    list.

    --> int rl_on_new_line (void)
    Tell the update functions that we have moved onto a new (empty) line,
    usually after outputting a newline. 

    --> void rl_replace_line (const char *text, int clear_undo)
    Replace the contents of rl_line_buffer with text. The point and mark are
    preserved, if possible. If clear_undo is non-zero, the undo list associated
    with the current line is cleared.

    --> void rl_redisplay (void)
    Change what’s displayed on the screen to reflect the current contents of
    rl_line_buffer

    --> void add_history (const char *string)
       Place string at the end of the history list.  The associated data
       field (if any) is set to NULL.  If the maximum number of history
       entries has been set using stifle_history(), and the new number of
       history entries would exceed that maximum, the oldest history
       entry is removed.

--------------------------

    pipe,
    dup,
    dup2,
    waitpid,
    wait,
    wait3,
    wait4,
    fork,
    execve,

    signal,
    sigaction,
    sigemptyset,
    sigaddset,
    kill,

    getcwd,
    chdir,
    stat,
    lstat,
    fstat,
    unlink,

    opendir,
    readdir,
    closedir,
    isatty,
    ttyname,
    ttyslot,
    ioctl,

    getenv,
    tcsetattr,
    tcgetattr,
    tgetent,
    tgetflag,
    tgetnum,
    tgetstr,
    tgoto,
    tputs

---------------------------

    access,
    open,
    read,
    close,

    strerror,
    perror,

---------------------------

    exit,
    printf,
    malloc,
    free,
    write,
