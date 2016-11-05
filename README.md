# iterative-avgstd
Iterative calculation of mean and standard deviation

Some time ago I was sick with some fever. The only thing I could do was to lay in bed. I took an electronic thermometer and measured my temperature, say 37.8C. It took so little time that I tried again, 37.4C. I tried a third time and the temperature kept changing. 
I thought to measure a few times and then to calculate the average, to see a more stable result. 

After a few sampling, doing it by heart without a piece of paper starts to be a bit complex. I started thinking that there must be a way to use the latest measured average and update it with the next sample.

I worked out a simple formula:

<T>_N = 1/N * sum_i^N T_i 
<T>_(N+1) = 1/(N+1) * sum_i^(N+1) T_i = 1/(N+1) * ( sum_i^N T_i + T_(N+1))

<T>_(N+1) = N/(N+1) * <T>_N + T_(N+1)/(N+1) 

So the next average can be calculated by keeping in mind only 3 numbers: the average, the number of samplings and the last sample. That's nice!
I worked out also the rule for the standard deviation, or better for the variance. 

var_(N+1) = var_N * ((N-1)/N) + (T_(N+1) - <T>_N)^2 

Here, you need to remember only 4 numbers, the average, the variance, the sample and the number of samplings.

This rules are very useful especially on low resource hardware because they do not require a lot of memory.

I later found that this formulas were already known (guess what??) https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
but it was nice to find them by myself!
