# CompileAndLink

## create static lib 
ar rc libmain.a main.o work.o

## create dylib
g++ -shared layer.o conflict.o -o libconflict.so

g++ -s -L. -o main -lmain -lconflict
g++ -Wl,--version-script=export.txt -shared layer.o conflict.o -o libconflict.so


## hidden


g++ -fvisibility=hidden -c ../conflict.cc  -o conflict.o


hidde之后，符号类型为t

```
➜  build git:(main) ✗ nm libconflict.so                                
0000000000003f60 t __Z7DoLayerv
0000000000003f80 t __Z7DoThingv
                 U _printf
```


gcc -Wl, --version-script export.txt -shared layer.o conflict.o -o libconflict.so


clang 不支持 --version-script



nm中
T是公开而且实现的函数
t则是hide的接口


执行以下命令
```
➜  build git:(main) ✗ g++ -c ../main.cc -o main.o
➜  build git:(main) ✗ g++ -c ../work.cc -o work.o 
➜  build git:(main) ✗ g++ -c ../conflict.cc -o conflict.o
➜  build git:(main) ✗ g++ -c ../layer.cc -o layer.o    
➜  build git:(main) ✗ ar rc libmain.a main.o work.o
➜  build git:(main) ✗ g++ -shared layer.o conflict.o -o libconflict.so
➜  build git:(main) ✗ g++ -s -L. -o main -lmain -lconflict

```

## linux的表现


```
start
work
layer
work
finished
```


```
// 隐藏符号后
ubuntu@VM-0-2-ubuntu:~/workspace/CompileAndLink/sample1/build$ g++ -fPIC -fvisibility=hidden -c ../conflict.cc -o conflict.o
ubuntu@VM-0-2-ubuntu:~/workspace/CompileAndLink/sample1/build$ g++ -shared layer.o conflict.o -o libconflict.so
ubuntu@VM-0-2-ubuntu:~/workspace/CompileAndLink/sample1/build$ g++ -s -L. -o main -lmain -lconflict
ubuntu@VM-0-2-ubuntu:~/workspace/CompileAndLink/sample1/build$ ./main
start
work
layer
conflict
finished

```


```
// linux 先修改main和conflict的链接顺序，会报错，Mac则不会

ubuntu@VM-0-2-ubuntu:~/workspace/CompileAndLink/sample1/build$ g++ -s -L. -o main  -lconflict -lmain
./libmain.a(main.o): In function `main':
main.cc:(.text+0x14): undefined reference to `DoLayer()'
collect2: error: ld returned 1 exit status

```




## mac的表现

```
➜  build git:(main) ✗ g++ -s -L. -o main -lmain -lconflict
➜  build git:(main) ✗ ./main
start 
work 
layer 
conflict 
finished 

```

```
➜  build git:(main) ✗ g++ -s -L. -o main -lconflict -lmain
➜  build git:(main) ✗ ./main
start
conflict
layer
conflict
finished
```


```
➜  build git:(main) ✗ g++ -fvisibility=hidden -c ../conflict.cc -o conflict.o
➜  build git:(main) ✗ g++ -shared layer.o conflict.o -o libconflict.so
➜  build git:(main) ✗ g++ -s -L. -o main -lconflict -lmain
ld: warning: option -s is obsolete and being ignored
➜  build git:(main) ✗ ./main
start
work
layer
conflict
finished

```