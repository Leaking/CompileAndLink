# CompileAndLink


## create dylib
g++ -shared layer.o conflict.o -o libconflict.so
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

