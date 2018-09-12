/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:38:40 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:38:41 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include "../includes/wolf3d.h"

void		ft_flag_argv(int i, AR argv, t_arg *arg)
{
	if (argv[i][1] == 'm')
	{
		if (arg->flag & MAPN && ++arg->error)
			ft_putendl("Warning! You set the m_t a second time");
		arg->map_name = argv[i + 1];
		arg->flag |= MAPN;
	}
	else if (argv[i][1] == 'w')
	{
		arg->screen_w = (Uint16)ft_atoi(argv[i + 1]);
		arg->flag |= MAPW;
	}
	else if (argv[i][1] == 'h')
	{
		arg->screen_h = (uint16_t)ft_atoi(argv[i + 1]);
		arg->flag |= MAPH;
	}
	else
		ft_putendl("Uncorrected argument");
}

int8_t		ft_read_argv(int argc, AR argv, t_arg *arg)
{
	int		i;

	i = 1;
	arg->flag = 0x000000;
	arg->error = 0;
	if ((argc == 1 || (argc - 1) % 2 != 0) && ++arg->error)
		ft_putendl_fd("Wrong arguments!", 2);
	else
	{
		while (i < argc)
		{
			if (argv[i][0] == '-' && ft_strlen(argv[i]) == 2 && i + 2 <= argc)
			{
				ft_flag_argv(i, argv, arg);
			}
			i += 2;
		}
	}
	if (arg->error)
		return (1);
	return (0);
}

int8_t		ft_mapping(t_map *map_t, t_spr *sprite, t_sdl *sdl)
{
	map_t->map_w = (int16_t)ft_splitter(map_t->head->content, ' ');
	map_t->map_h = (int16_t)ft_count_list(map_t->head);
	if (ft_check_w_map(map_t->head, map_t->map_w) != 1)
	{
		ft_list_del(&map_t->head);
		return (0);
	}
	ft_remap(map_t);
	ft_fix_map(map_t, sprite, sdl);
	return (1);
}

t_list		*ft_pars_file(int16_t fd)
{
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd(&head, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	return (head);
}
