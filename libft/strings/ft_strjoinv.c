/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/28 15:31:38 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"
#include <stdarg.h>

char *strjoinv(char *str, ...)
{
        char    *return_str;
        char    *tmp_str;
        size_t  size;
        va_list args;
        va_list tmp_args;

        va_start(args, str);
        va_copy(tmp_args, args);
        size = ft_strlen(str) + 1; 
        tmp_str = va_arg(tmp_args, char *);
        while(tmp_str)
        {
                size += ft_strlen(tmp_str);
                tmp_str = va_arg(tmp_args, char *);
        }
        return_str = ft_calloc(size, sizeof(char));
        ft_strlcpy(return_str, str, size);
        tmp_str = va_arg(args, char *);
        while(tmp_str)
        {
                ft_strlcat(return_str, tmp_str, size);
                tmp_str = va_arg(args, char *);
        }
        va_end(args);
        va_end(tmp_args);
        return(return_str);
}
