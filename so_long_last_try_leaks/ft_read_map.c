/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmorale <crmorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:20:07 by crmorale          #+#    #+#             */
/*   Updated: 2024/11/30 21:52:31 by crmorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_failed_malloc(t_game *game)
{
	perror("Error: malloc failed.");
	ft_free_map_and_texts(game);
	exit (EXIT_FAILURE);
}

void	ft_map_size(t_game *game)
{
	char	*line;
	int		fd;

	fd = open (game->txt, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: unable to open file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		perror("Error: couldnt read map.");
		close(fd);
		exit (EXIT_FAILURE);
	}
	game->width = ft_strlen(line) - 1;
	game->height = 0;
	while (line)
	{
		if ((int)ft_strlen(line) - 1 != game->width)
		{
			free(line);
			perror("Error: wrong map size.");
			close(fd);
			exit (EXIT_FAILURE);
		}
		game->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

void	ft_malloc_map(t_game *game)
{
	int		fd;
	int		i;

	fd = open(game->txt, O_RDONLY);
	if (fd == -1)
		ft_failed_malloc(game);
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		ft_failed_malloc(game);
	i = 0;
	while (i < game->height)
	{
		ft_loop(fd, i, game);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
}

void ft_loop(int fd, int i, t_game *game)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		ft_failed_malloc(game);
	}
	game->map[i] = ft_strdup(line);
	free(line);
	if (!game->map)
		ft_failed_malloc(game);
	game->map[i][game->width] = '\0';
}