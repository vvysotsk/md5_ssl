#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include <sys/stat.h>

size_t	read_from_fd(int fd, unsigned char **line)
{
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;

 	fstat(fd, &st);
	temp = ft_str_unsigned_new(st.st_size);
	ret = 0;
	while ((i = read(fd, temp, st.st_size)) > 0)
	{
		ret += i;
		ft_str_unsigned_concat(line, temp, ret - i, i);
		(temp) ? ft_str_unsigned_del(&temp) : 0;
		temp = ft_str_unsigned_new(st.st_size);
	}
	(temp) ? ft_str_unsigned_del(&temp) : 0;
	return (ret);
}