# Philosophers
Introduction in threading process

In this project we have to resolve the famous [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in three ways.
You can compile every philo solution with make, and test is with ./philo_one/two/three <number of philosophers> <time to die (in ms)> <time to eat (in ms)> <time to sleep (in ms)> <number_of_times_each_philosopher_must_eat (optionnal)>

## philo_one

In this version the non common rules will be:

- One fork between each philosopher, therefore there will be a fork at the right andat the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with amutex for each of them.
- Each philosopher should be a thread.
- Use only thread and mutex

## philo_two

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented bya semaphore.
- Each philosopher should be a thread.
- Use only thread and semaphore (no mutex)

## philo_three

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented bya semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.
- We can and must use fork and semaphore, thread to but mutex is forbidden