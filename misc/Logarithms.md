Consider the following equation


$S = r^t$


Where $S$ is size (relative to current size), $r$ is rate, and $t$ is time. The above equation can also be inverted to isolate time.


$t = \log_{r} S$


Q. If we are doubling every 1 year, what will be our relative size after 5 years?

$S = 2^5 = 32$


Q. If we are doubling every 1 time period (e.g. year), after how many time periods will our size be 32?

$t = \log_{2} 32 = 5$


#### Logarithmic Laws
There are five basic log laws.  

##### Law # 1

> $log_{a} 1 = 0$

Writing the law in index form

> $a^0 = 1$

The questions this is asking is: If I am growing at the rate $a$, how long will it take for me to grow by factor of 1. Answer is zero because we are already $(current size \cdot 1)$.


##### Law # 2

> $log_{a} a = 1$

Writing the law in index form

> $a^1 = a$

The question this is asking is: If I am growing at the rate $a$, how long will it take for me to grow a factor of $a$ relative to my current size. The answer is 1 meaning, it will take me one time period.


##### Law # 3

> $log_{a} (\frac{1} a) = -1$

Writing in index form

>  $a^{-1} = \frac{1} a$

This is the question: If I am growing at the rate of $a$, how long before I am $\frac{1} a$ times my current size?
The answer is -1, meaning I would have to go back one time period, to be the size I am now.


##### Law # 4

> $log_{a} m + log_{a} n = log_{a} m \cdot n$

Writing this in index form

> $a^m \cdot a^n = a^{m+n}$

This makes more sense with numbers

> $log_{2} 8 + log_{a} 32 = log_{2} 256$

In the above equation, think of $log_{a} m$ as unit of time. 

From the above law, this one can be derived.

> $log_{a} m - log_{a} n = log_{a} (\frac{m} n)$

Writing this in index form

> $a^m \div a^n = a^{m-n}$


##### Law # 5
From Law # 4 we can also derive the following law

> $\log_{a} (m^n) = n\log_{a} m$

E.g.

> $\log_{a} (m\cdot m\cdot m) = \log_{a} m + \log_{a} m + \log_{a} m$

> $\log_{a} (m^3) = 3 (\log_{a} m)$


##### Law # 6 - Change of Base

> $\log_{a} b = \frac{\log_{c} b} {\log_{c} a}$

Using this law, we can go from base $a$ to $c$ where $c$ being any rational number.

We can also derive this law as follows

> $x = \log_{a} b$

> $a^x = b$

> $\log_{c} (a^x) = \log_{c} b$

> $x(\log_{c} a) = \log_{c} b$

> $x = \frac{\log_{c} b} {\log_{c} a}$


There is a special case for this law where $b=c$

> $\log_{b} (a^x) = \log_{b} b$

> $x(\log_{b} a) = 1$

> $x = \frac{1} {\log_{b} a}$


#### Euler's Number

Euler's number, also denoted as $e$ is frequently used as base of log. It is defined as the maximum compounding at 100% growth rate, for one time period.

$e$ is an irrational number (like $\pi$) which keeps going and the numbers never repeat themselves.

> $e = 2.7182818...$


#### Where does $e$ come from?

Here is the formula for calculating compouding growth.

> $(1 + \frac{1}{n})^n = S$

Consider we grow at 100% rate per year.

> $(1 + 1)^1 = 2$

Consider we grow at 100% rate every 6 months.

> $(1 + \frac{1}{2})^2 = 2.25$

This improves our returns from the previous example. Could it be that if we keep shortening our time period, our return also keeps increasing indefinitely?

Consider we grow at 100% rate every day.

> $(1 + \frac{1}{365})^365 = 2.71457$

This is higher from the last example, but not by much. Now consider if we double every minute.

> $(1 + \frac{1}{365 \cdot 24 \cdot 60})^{365 \cdot 24 \cdot 60} = 2.71828$

This is approximately the value of $e$.

The conclusion is, even if we compound at 100% rate (i.e. double) $∞$ times in a time period, the max rate of return that we can achieve is $e$.   


#### What about other rates and time periods?

Think of the value of $e$ as follows, where $S$ is size, $r$ is rate and $t$ is time.

> $S = e^{rt}$

If we compound at 30% growth rate for 2 time periods, the max growth we can achieve is as follows

> $S = e^{0.3 \cdot 2} = 1.822$
