# Philosophers

## Description du Projet

Le projet "Philosophers" de l'école 42 est conçu pour introduire les étudiants aux défis de la programmation multithread et de la synchronisation. Inspiré par le problème des philosophes qui dînent, ce projet vise à simuler une situation où plusieurs threads (représentant les philosophes) doivent partager des ressources (les fourchettes) sans provoquer de deadlock (interblocage) ou de famine des threads.

### Objectifs

- Comprendre les concepts de threading et de processus.
- Apprendre la gestion des threads en C.
- Mettre en œuvre des mécanismes de synchronisation comme les mutex.
- Éviter les problèmes de concurrence tels que les deadlocks et la famine.

## Installation

### Prérequis

- Un compilateur C, comme `gcc`.
- Un système d'exploitation Unix ou similaire.

### Compilation

Exécutez la commande suivante dans le répertoire du projet pour compiler le programme :
```bash
make
```

## Utilisation

Pour exécuter le programme, utilisez la commande suivante :
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Le nombre de philosophes et également de fourchettes.
- `time_to_die`: Le temps en millisecondes après lequel un philosophe meurt s'il n'a pas mangé.
- `time_to_eat`: Le temps en millisecondes qu'un philosophe prend pour manger.
- `time_to_sleep`: Le temps en millisecondes qu'un philosophe passe à dormir.
- `number_of_times_each_philosopher_must_eat` (optionnel): Le nombre de fois où chaque philosophe doit manger avant de terminer la simulation.
