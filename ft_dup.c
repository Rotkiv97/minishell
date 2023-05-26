#include "minishell.h"

/*
	Voglio fare l'output di dati in altri file
	Un fd e' univoco nel processo. Quando avvio un processo linux avvia dei fd standard : 0, 1 e 2

		file descriptor			file
			0					STDIN
			1					STDOUT
			2					STDERR
	Voglio sostituire l'output con il nuovo file descriptor del file file_output
			3					file_output
	dup:	4					file_output
	dup2(file, 1) chiude lo stream associato a 1 e mette il file

			0					STDIN
			1					file_output
			2					STDERR
			3					file_output
	close(file)
			0					STDIN
			1					file_output
			2					STDERR
	Quando avvio una funzione della famiglia exec non viene modificato il PID e
	non vengono sovrascritti i fd.
	Quindi se cambio i fd prima di eseguire un programma con exec essi rimangono
	"memorizzati" anche all'interno del programma appena avviato.
*/

int	main()
{
	int	fd[2];
	int	file = open("file_output", O_WRONLY | O_CREAT, 0777);

	printf("%d\n", getpid());
	printf("CIAO");
	if (pipe(fd) == -1)
		return (3);
	sleep(1);
	int	id = fork();
	if (file == -1)
		return (2);
	int	file2 = dup2(file, STDOUT_FILENO); // Duplico file nel nuovo fd 1
	//int	file2 = dup(file);
	printf("The duplicated fd is %d\n", file2);
	if (id == 0)
	{
	}
	else if (pid > 0)
	{
	}
	else
		return (4);
	close(file); // chiudo il file perche adesso e' duplicato nello STDIN
}