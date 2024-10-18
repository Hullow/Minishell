/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/10/18 20:06:38 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parsing
struct s_command	*ft_parse(struct s_token *head);
struct s_token		*ft_parse_operators(struct s_token *head);
