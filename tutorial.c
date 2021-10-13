#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* 3 main things in a lifetime of a shell.
 * 1. Initialize: A typical shell would read and execute its configurations
 *    files. These change aspects of the shell's behavior.
 * 2. Interpret: Next, the shell reads commands from stdin (which could be
 *    interactive, or a file) and executes them.
 * 3. Terminate: After its commands are executed, the shell executes any
 *    shutdown commands, frees up any memory, and terminates. */

char	*lsh_read_line(void)
{
	char	*line;
	ssize_t	bufsize;

	line = NULL;
	bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) {
		if (feof(stdin)) {
			exit(EXIT_SUCCESS);
		} else {
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

char	**lsh_split_line(char *line)
{
	int		bufsize;
	int		position;
	char	**tokens;
	char	*token;

	bufsize = LSH_TOK_BUFSIZE;
	position = 0;
	tokens = malloc(bufsize * sizeof(char *));

	if (!tokens) {
		fprintf(stderr, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens) {
				fprintf(stderr, "minishell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/* Function declarations for builtin shell commands: */

int	lsh_cd(char **args);
int	lsh_help(char **args);
int	lsh_exit(char **args);

/* List of builtin commands, followed by their corresponding functions. */

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int	(*builtin_func[]) (char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit
};

int	lsh_num_builtins() {
	return (sizeof(builtin_str) / sizeof(char *));
}

int	lsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "minishell: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("minishell");
		}
	}
	return (1);
}

int lsh_help(char **args)
{
	int	i;

	printf("kyumlee, mishin's minishell\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < lsh_num_builtins(); i++) {
		printf("   %s\n", builtin_str[i]);
	}

	printf("Use the man command for informantion on other programs.\n");
	return (1);
}

int	lsh_exit(char **args)
{
	return (0);
}

int		lsh_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0) {
		// Child process
		if (execvp(args[0], args) == -1) {
			perror("minishelll");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("minishell");
	} else {
		// Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

int	lsh_execute(char **args)
{
	int	i;

	if (args[0] == NULL) {
		return (1);
	}

	for (i = 0; i < lsh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}
	return (lsh_launch(args));
}

void	lsh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	do {
		printf("minishell> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while (status);
}

int	main(int argc, char **argv)
{
	// Load config files, if any.

	// Run command loop.
	lsh_loop();

	// Perform any shutdown/cleanup
	
	return EXIT_SUCCESS;
}
