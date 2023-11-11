#include "parse.h"

// static bool	check_cub_file(char *arg)
// {
// 	size_t	len;

// 	len = ft_strlen(arg);
// 	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
// 			|| arg[len - 1] != 'b'
// 			|| arg[len - 4] != '.'))
// 		return (false);
// 	return (true);
// }

//needs more fix bruh :(
bool	chk_valid_file(char *str, char *type)//chk for dir and parent .. stuff inside ur slash
{
	bool	dir_chk;

	if (!ft_strncmp("./", str, 2))
		str += 2;
	else if (!ft_strncmp("~/", str, 2))
		str += 2;
	else if (!ft_strncmp("../", str, 3))
		str += 3;
	while (*str && ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')\
	 || *str == '_' || (*str >= '0' && *str <= '9') || *str == '/'))
	{
		if (dir_chk && *str == '/')
			return (true);
		dir_chk = false;
		if (*str == '/')
			dir_chk = true;
		str++;
	}
	if (dir_chk)
		return(true);
	return (ft_strcmp(type, str));
}

bool	chk_cub_and_xmp(char *str, bool cub)
{
	if (cub)
	{
		if (chk_valid_file(str, ".cub"))
			return (print_err(str, "not a .cub file", 1));
	}
	else if (chk_valid_file(str, ".xpm"))
		return (print_err(str, "not a .xpm file", 1));
	return (false);
}

// static bool	check_xmp_file(char *arg)
// {
// 	size_t	len;

// 	len = ft_strlen(arg);
// 	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
// 			|| arg[len - 1] != 'm'
// 			|| arg[len - 4] != '.'))
// 		return (false);
// 	return (true);
// }

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

int	check_mapfile(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (print_err(arg, "is Directory", 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_err(arg, strerror(errno), 1));
	close(fd);
	// if (cub && !check_cub_file(arg))
	// 	return (print_err(arg, "not a .cub file", 1));
	// if (!cub && !check_xmp_file(arg))
	// 	return (print_err(arg, "not a .xmp file", 1));
	if (chk_cub_and_xmp(arg, cub))
		return(1);
	return (0);
}

int	ft_parse(t_parse *parse, char *path)
{
	if (check_mapfile(path, true) == 1)
		return (SUCCESS);
	parse->pdir = '\0';
	initialize_imap(&parse->imap);
	parse_map_file(path, parse);
	if (parse->imap.file == NULL)
		return (SUCCESS);
	initialize_parse_vars(parse);
	if (get_map(parse, parse->imap.file) == 1)
		return (free_double_array(&parse->imap.file), 0);
	if (check_map_ifvalid(parse, parse->map) == FAILURE)
		return (free_parser(parse), 0); 
	if (check_texture(parse) == FAILURE)
		return (free_parser(parse), 0);
	duplicate_parse(parse);
	return (1);
}
