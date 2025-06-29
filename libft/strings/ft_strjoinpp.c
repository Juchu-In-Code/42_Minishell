#include "../libft.h"
char *ft_strjoinpp(char **arr)
{
	size_t	total_len;
	char	*return_str;
	char	**tmp;

	if (!arr)
		return(NULL);
	tmp = arr;
	total_len = 1;
	while(*tmp != NULL)
	{
		total_len += ft_strlen(*tmp);
		tmp++;
	}
	return_str = ft_calloc(total_len, sizeof(char));
	tmp = arr;
	while (*tmp != NULL)
	{
		ft_strlcat(return_str, *tmp, total_len);		
		tmp++;
	}
	return (return_str);
}
