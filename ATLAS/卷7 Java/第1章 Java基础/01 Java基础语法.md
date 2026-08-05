---
tags:
  - Java
---
Java中大小写是严格的，除了定义外其余部分不允许使用逗号分隔。

# 1. 数据类型 常量和变量
## 1.1 char
Java中char使用Unicode编码。
## 1.2 boolean
布尔类型，其值仅有 true 和 false。
Java中整数类型不能和布尔类型相互转换。
## 1.3 变量
声明变量时必须要显示初始化，不可使用未初始化的变量值。
## 1.4 常量
#### 常量指示
使用 final 来指示常量：
```java
public class Main {  
    public static void main(String[] args){  
        final int SampleNumber = 2;  
        System.out.println("Sample Number: " + SampleNumber);  
    }  
}
```
#### 类常量
类常量可以在类的多个方法中使用，使用 static final 声明。
```java
public class Main {  
  
    public static final double PI = 3.14;  
  
    public static void main(String[] args){  
        final int SampleNumber = 2;  
        double OutputNumber = SampleNumber + PI;  
        System.out.println("New Number: " + OutputNumber);  
    }  
}
```

## 1.5 枚举
和C++的枚举差不多，对应枚举类型的变量仅存储声明中的某个给定枚举值。
```java
public class Main {  
    public static void main(String[] args){  
        enum Color{RED,BLUE,YELLOW};  
        Color c = Color.RED;  
        System.out.println(c);  
    }  
}
```

# 2. 基本运算
除了 `+ - * / %` 外，可以通过使用 Math 类来进行更复杂的运算。
Java 支持赋值运算 `+= -=` 和自增运算 `++ --` 。
此外还有位运算符 `& | ^ ~ >> <<` 和三元运算符 `?:`。使用方法和C++一样。
## 2.1 有关除法的说明
`/` 表示整除当且仅当该运算符的两个操作数均为整数，
否则，表示浮点除法。
## 2.2 Math
使用 Math 类需要进行导入，或者使用前缀。
```java
import static java.lang.Math.*;
```
此后可以使用该类中的对应方法，例如开根 `Math.sqrt(x)` ，幂运算 `Math.pow(x,a)` ，三角函数，指数函数，对数。
Math 类提供了两个常量 `Math.PI` ，`Math.E` 。
```java
import static java.lang.Math.*;  
  
public class Main {  
    public static void main(String[] args){  
        int n = 2;  
        System.out.println(pow(2, n));  
    }  
}
```
## 2.3 类型转换
#### 普通数值类型转换
可以使用下面的语句进行类型转换：
```java
public class Main {  
    public static void main(String[] args){  
        int N = 123456789;  
        double ChangeN = N;  
        System.out.println("Now N = " + ChangeN);  
    }  
}
```
此时输出的结果会变为：
```java
Now N = 1.23456789E8
```
即科学计数法，即发生了类型的转换。
不难发现这样转换类型会造成信息的修改或丢失，我们讨论这个情况。
#### 类型转换造成的信息丢失
会造成精度损失的转换有下列三种：
1. int -> float
2. long -> float
3. long -> double
#### 运算中的类型转换
只要运算符的两个操作数中有一个是 double/long/float ，两个数都会被转换成对应的数据类型，
否则均转换为 int 类型。
#### 强制类型转换
强制类型转换（cast）通过添加括号实现：
```java
public class Main {  
    public static void main(String[] args){  
        double Test = 12.34;  
        int NewTest = (int) Test;  
        System.out.println(NewTest);  
    }  
}
```
这样的类型转换默认直接截取整数部分，如果要四舍五入，可以使用 `Math.round(x)` 来实现。
# 3. 字符串
这里仅介绍和C++不同的内容。
## 3.1 String
Java的字符串实际上是一个 String 类。

1. 求子串 `substring(l,r)` 
2. 拼接 `+` ，对于非字符串类型的，会转变为字符串后进行拼接。
3. 检查是否相等 `s1.equals(s2)`

字符串不是字符数组，不能修改某个特定字符，因此 String 是不可变的。
## 3.2 StringBuilder
StringBuilder 是可变字符串，支持直接修改特定位置的字符。
StringBuilder 的字符串对象声明如下：
```java
StringBuilder Test = new StringBuilder();
```
下面是几种方法的使用：
```java
public class Main {  
    public static void main(String[] args){  
        StringBuilder Test = new StringBuilder();  
        Test.append("hello World!"); //字符串扩展 ""->"hello World!"       
        Test.setCharAt(0,'H'); //字符串位置修改 "hello World!"->"Hello World!"        
        Test.delete(5,12); //删除特定范围 "Hello World!" -> "Hello"        
        //删除特定字符用 deleteCharAt(index)        
        Test.replace(0,2,"hE"); //替换特定范围 "Hello"->"hEllo"        
        Test.reverse(); //反转  
        System.out.println(Test);  
    }  
}
```
如果要将 StringBuilder 类对象转换为 String 类对象，可以使用 `s.toString()` 方法。
## 3.3 StringBuffer
StringBuffer 类和 StringBuilder 类基本一样。
StringBuffer 具有线程安全的特性，但是会慢一些。
# 4. 输入输出
## 4.1 System

## 4.2 Scanner
Scanner 是一个类，能够用于获取用户的输入，通常情况下需要导入这个库。
```java
import java.util.Scanner;
```
可以通过下面的语法创建 Scanner 对象：
```java
Scanner s = new Scanner(System.in);
```
Scanner 的构造提供了从文件创建，从输入流创建，从字符串创建三种方法。
#### next & nextLine
上文中 s 对象获取输入内容之后，我们需要获取这些内容，可以使用方法 `next()` 或者 `nextLine()` ，为了防止出现无内容仍获取和有内容未被获取的情形，通常在获取前进行检查。
```java
import java.util.Scanner;  
  
public class ScannerTrial {  
    public static void main(String[] args) {  
        Scanner s = new Scanner(System.in);  
        System.out.print("Input something : ");  
        String input = s.next();  
        System.out.print(input);  
    }  
}
```

对于 `next()` 而言，一定要获取到有效字符后才停止输入，对于获取到有效字符前获得到的空白字符，会自动省略，而有效字符后的空白会被视为分割或结束符，因此 `next()` 不能获得带有空格的字符串。

而对于 `nextLine()` ，其以 Enter 作为结束符，读取的是一整行的内容，类似于 C++ 里的 getline。

#### nextX
`nextX()` 可以获取到类型为 X 的数据，例如这里的类型为整形，方法名就为 `nextInt()` 。