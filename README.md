# Minishell

Minishell est un projet de l'école 42 visant à recréer un shell minimaliste inspiré de bash.

## Fonctionnalités

- Exécution de commandes simples ou enchaînées avec des pipes (`|`).
- Gestion des redirections (`>`, `>>`, `<`).
- built-ins (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`).
- Gestion des signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\\`).
- Appels Système (ls, ps, ...)

## Installation

Pour compiler le projet, exécutez la commande suivante dans le répertoire racine :

```bash
make
```

Cela générera l'exécutable `minishell`.

## Utilisation

```bash
./minishell
```
