# Optimizations
photo proccesing optimizations in C

heads up! this code is not a clean one, but it very very efficient!
as part of an exercise done in computer structure course in BIU, I have been given a code that procces image - 
sharpen it or apllying some filter on it.
the original code did its job in average time (for 200, 500, 700 pic sizes) in around 200 ms when compiled with -O3 flag in gcc,

using several techniques for checking less conditions, unrolling loops, use stack memory instead of heap etc -
I have managed to improve its speed all the way to around 6 ms !

you are welcome to check out the code and try it yourself.

during my work i have changes only myfunction and myfunction1 files (.c and .h)
