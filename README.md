![image](https://github.com/BaptisteFaisy/minihell/assets/119856854/d3c81e2e-f238-406a-9349-e60b263d34a7)

liens utiles :

https://segfault42.github.io/posts/minishell/

http://i.paysdu42.fr/?page=minishell.c

https://github.com/appinha/42cursus-03-minishell

### Execution command with leak suppression caused by readline
valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=readline.supp --track-origins=yes ./minishell

### Todo

- Pass evaluations to validate the project

### Justifications
- https://stackoverflow.com/questions/66898092/how-do-i-make-readline-exit-on-ctrlc