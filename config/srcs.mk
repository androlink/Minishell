
SRCS += main.c

#----env----

SRCS += env/ms_env_add.c
SRCS += env/ms_env_collapse.c
SRCS += env/ms_env_init.c
SRCS += env/ms_env_new.c
SRCS += env/ms_env_remove.c
SRCS += env/ms_env_to_strs.c
SRCS += env/ms_env_get.c
SRCS += env/ms_env_gen.c
SRCS += env/ms_env_complete.c
SRCS += env/ms_env_exist.c


#----parser----



SRCS += parser/heredoc/ms_heredoc.c
SRCS += parser/syntax/ms_syntax_error.c
SRCS += parser/syntax/ms_syntax_rule.c


#----prompt----

SRCS += prompt/ms_prompt.c