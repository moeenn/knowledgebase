```bash
# installation
$ pip3 install jupyter

# start server (default Port 8888)
$ jupyter notebook
```


#### Usage

```
# list magic commands
%lsmagic


# Running system commands
!ls -a


# Embed HTML in notebook
%%HTML
<img src="http://random.site.com/image.png" alt="Photo" />


# Show Matplotlib output inside notebook
%matplotlib inline
plt.show()


# Track time of execution of script
%%timeit
[n*n for n in range(1, 1000)]
```
