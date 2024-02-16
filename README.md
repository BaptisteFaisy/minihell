![image](https://github.com/BaptisteFaisy/minihell/assets/119856854/d3c81e2e-f238-406a-9349-e60b263d34a7)

liens utiles :

https://segfault42.github.io/posts/minishell/

http://i.paysdu42.fr/?page=minishell.c

https://github.com/appinha/42cursus-03-minishell

~~EXEC~~

pipe

if args->next exist, do pipe

pipefd[0] : le bout de lecture
pipefd[1] : le bout d’écriture
https://tldp.org/LDP/lpg/node11.html
faut ouvrir tous les redirects et peter tous les contenues, et prendre que le dernier

Builtin list:
echo *
cd *
pwd *
export
unset
env
exit *?