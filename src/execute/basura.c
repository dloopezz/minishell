			/* if ((tmp)->type == GT || (tmp)->type == GGT)
			{
				if ((tmp)->type == GT)
				{
					data->gt = ft_calloc(sizeof(t_data), 1);
					data->gt = tmp->args[0];
					file = open_file(*(tmp)->next->args, 1);
				}
				else if ((tmp)->type == GGT)
				{
					data->ggt = ft_calloc(sizeof(t_data), 1);
					data->ggt = tmp->args[0];
					file = open_file(*(tmp)->next->args, 2);
				}
				close(file);
			}
			else if ((tmp)->type == LT || (tmp)->type == LLT)
			{
				if ((tmp)->type == LT)
				{
					data->lt = ft_calloc(sizeof(t_data), 1);
					data->lt = tmp->args[0];
					if (tmp->next->type == INFILE)
						(data)->infile = (tmp)->next->args[0];
					if (access(data->infile, F_OK) == -1)
						exec_exit_error(5, "No such file or directory");
				}
				else if (tmp->type == LLT)
				{
					data->llt = ft_calloc(sizeof(t_data), 1);
					data->llt = tmp->args[0];
					data->del = tmp->next->args;
				}
			} */