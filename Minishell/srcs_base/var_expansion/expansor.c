/*split the line with ' '.
Look for a line that starts with $.
if $ found -> get the key.
if key found -> replace the $key for value.
else replace the string with nothing.*/
int ft_strarrlen(char **arr)
{
        int len;

        len = 0;
        while(arr[len])
                len++;
        return(len);
}

char** expand_lines(int ac, char** av, t_list *env)
{
        char    **raw_lines;
        char    **expansed_lines;
        int     i;

        if (ac > 2)
        {
                printf("too many args");
                return(NULL);
        }
//      lines = ft_split(av[1], ' '); //NOTE:debug
        raw_lines = av;
        expansed_lines = ft_calloc(ft_strarrlen(raw_lines) + 1, sizeof(char *));
                           //NOTE: ^^^^^^^^^^^^ -> using ac is prefered 
        i = -1;
        while(raw_lines[++i]) 
        {
                if(raw_lines[i][0] == '$')
                {
                        char* test_val = get_env_val(env, raw_lines[i] + 1);
                        char* test_val1 = ft_strdup(test_val);
                        expansed_lines[i] =     test_val1 ;
                                                            //NOTE:    raw_lines[i]++ modifies the ptr.
                        raw_lines[i]--;
                        //NOTE:so i turn it back to the orig value.
                        if(!expansed_lines)
                                expansed_lines[i] = ft_strdup("");
                }
                else
                        expansed_lines[i] = ft_strdup(raw_lines[i]);
        }
        expansed_lines[i] = NULL;
        //NOTE: in case of raw_lines being malloc-ed -> free(it);
        //ft_free_matrix((void **)raw_lines);
        return(expansed_lines);
}

void print_char_array(char **arr) {
    if (!arr)
        return;

    for (int i = 0; arr[i] != NULL; i++) {
        printf("%s\n", arr[i]);
    }
}

