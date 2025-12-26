/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:47:18 by squinn            #+#    #+#             */
/*   Updated: 2025/12/25 18:47:26 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"
#include "libft.h"
#include "object_list.h"
#include "parse.h"
#include "parse_line.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

static bool	is_rt_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

static void	validate_arguments(int argc, char *argv[])
{
	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	if (!is_rt_extension(argv[1]))
		error_exit("The file extension must be .rt");
}

static bool	is_valid_setting(t_elements_count count)
{
	if (count.num_ambient != 1)
	{
		print_error("Ambient lighting (A) must be declared exactly once.");
		return (false);
	}
	if (count.num_cameras != 1)
	{
		print_error("Camera (C) must be declared exactly once.");
		return (false);
	}
	if (count.num_lights != 1)
	{
		print_error("Light (L) must be declared exactly once.");
		return (false);
	}
	return (true);
}

static void	read_from_rt_file(int fd, t_program *data)
{
	t_elements_count	elements_count;
	char				*line;
	int					result;

	ft_memset(&elements_count, 0, sizeof(elements_count));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		result = parse_line(line, &elements_count, data);
		free(line);
		if (result == PARSE_FAILED)
		{
			destroy_object_list(&data->head);
			exit(EXIT_FAILURE);
		}
	}
	if (!is_valid_setting(elements_count))
	{
		destroy_object_list(&data->head);
		exit(EXIT_FAILURE);
	}
}

void	parse(int argc, char *argv[], t_program *data)
{
	int	fd;

	validate_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("File not found");
	init_dummy_head(&data->head);
	read_from_rt_file(fd, data);
}
