# javaIO

标签（空格分隔）： 未分
javaI/O：int 和out，即java的输入与输出，io体系的基本功能是读和写；

##IO流：  
- [ ] 作用：读写设备上的数据，硬盘文件，内存，键盘，网络.....
- [ ] 根据数据的走向，可分为：输入流，输出流；
- [ ] 根据处理的数据类型，可分为：字节流，字符流；
 -  字节流：可以处理所有类型的数据，mp3，图片，文字，视频等，在读取时，读到一个字节就返回一个字节；**在java中对应的类都以Stream结尾**
 -  字符流：仅能够处理纯文本数据，如txt文本等。读到一个或多个字节，先查找指定的编码表，然后将查到的字符返回；**在java中对应的类都以Reader或Writer结尾**


 ##使用字节流读写数据
 1，流的打开->流的操作->流的关闭；
 - [ ] 在程序中所有的数据都是以流的方式进行传输或保存的，程序需要数据的时候要使用输入流读取数据，而当程序需要将一些数据保存起来的时候，就要使用输出流完成。
##字节流
字节流主要是操作byte类型数据，以byte数组为准，主要操作类就是OutputStream、InputStream
###字节输出流：OutputStream
OutputStream是整个IO包中字节输出流的最大父类，此类的定义如下：
```java
public abstract class OutputStream extends Object implements Closeable,Flushable
```
从以上的定义可以发现，此类是一个抽象类，如果想要使用此类的话，则首先必须通过子类实例化对象，那么如果现在要操作的是一个文件，则可以使用：FileOutputStream类。通过向上转型之后，可以为OutputStream实例化
```
Closeable表示可以关闭的操作，因为程序运行到最后肯定要关闭
Flushable：表示刷新，清空内存中的数据
FileOutputStream类的构造方法如下：
public FileOutputStream(File file)throws FileNotFoundException 
```
```java
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class Test11 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        OutputStream out=new FileOutputStream(f);//如果文件不存在会自动创建
        String str="Hello World";
        byte[] b=str.getBytes();
        out.write(b);//因为是字节流，所以要转化成字节数组进行输出
        out.close();
    }
}
```
```java
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
//如果将append的值设置为true，则表示在文件的末尾追加内容。
public class Test11 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        OutputStream out=new FileOutputStream(f,true);//追加内容
        String str="\r\nHello World";
        byte[] b=str.getBytes();
        for(int i=0;i<b.length;i++){
            out.write(b[i]);
        }
        out.close();
    }
}
```

###字节输入流：InputStream
既然程序可以向文件中写入内容，则就可以通过InputStream从文件中把内容读取进来，首先来看InputStream类的定义：
```java
public abstract class InputStream extends Object implements Closeable
```
与OutputStream类一样，InputStream本身也是一个抽象类，必须依靠其子类，如果现在是从文件中读取，就用FileInputStream来实现。
观察FileInputStream类的构造方法：
```java
public FileInputStream(File file)throws FileNotFoundException
```
```java
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

public class Test13 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        InputStream in=new FileInputStream(f);
        byte[] b=new byte[(int) f.length()];
        in.read(b);
        in.close();
        System.out.println(new String(b));
    }
}
```
```java
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
//不知道输入文件大小时
public class Test15 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        InputStream in=new FileInputStream(f);
        byte[] b=new byte[1024];
        int temp=0;
        int len=0;
        while((temp=in.read())!=-1){//-1为文件读完的标志
            b[len]=(byte) temp;
            len++;
        }
        in.close();
        System.out.println(new String(b,0,len));
    }
}
```
```java
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
//不知道输入文件大小时
public class Test15 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        InputStream in=new FileInputStream(f);
        byte[] b=new byte[1024];
        int temp=0;
        int len=0;
        while((temp=in.read())!=-1){//-1为文件读完的标志
            b[len]=(byte) temp;
            len++;
        }
        in.close();
        System.out.println(new String(b,0,len));
    }
}
```
##字符流
在程序中一个字符等于两个字节，那么java提供了Reader、Writer两个专门操作字符流的类。
###字符输出流：Writer
Writer本身是一个字符流的输出类，此类的定义如下：
```java
public abstract class Writer extends Object implements Appendable，Closeable，Flushable
```
此类本身也是一个抽象类，如果要使用此类，则肯定要使用其子类，此时如果是向文件中写入内容，所以应该使用FileWriter的子类。
FileWriter类的构造方法定义如下：
```java
public FileWriter(File file)throws IOException
```
字符流的操作比字节流操作好在一点，就是可以直接输出字符串了，不用再像之前那样进行转换操作了。
```java
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

public class Test17 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        Writer out=new FileWriter(f,true);//追加
        String str="\r\nHello World";
        out.write(str);
        out.close();
    }
}
```
###字符输入流：Reader

Reader是使用字符的方式从文件中取出数据，Reader类的定义如下：
```java
public abstract class Reader extends Objects implements Readable，Closeable
```
Reader本身也是抽象类，如果现在要从文件中读取内容，则可以直接使用FileReader子类。
FileReader的构造方法定义如下：
```java
public FileReader(File file)throws FileNotFoundException
```
```java
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;

public class Test19 {
    public static void main(String[] args) throws IOException {
        File f = new File("d:" + File.separator+"test.txt");
        Reader input=new FileReader(f);
        char[] c=new char[1024];
        int temp=0;
        int len=0;
        while((temp=input.read())!=-1){
            c[len]=(char) temp;
            len++;
        }
        input.close();
        System.out.println(new String(c,0,len));
    }
}
```
##字节流与字符流的区别
- 字节流在操作的时候本身是不会用到缓冲区（内存）的，是与文件本身直接操作的，而字符流在操作的时候是使用到缓冲区的
- 字节流在操作文件时，即使不关闭资源（close方法），文件也能输出，但是如果字符流不使用close方法的话，则不会输出任何内容，说明字符流用的是缓冲区，并且可以使用flush方法强制进行刷新缓冲区，这时才能在不close的情况下输出内容
- 在所有的硬盘上保存文件或进行传输的时候都是以字节的方法进行的，包括图片也是按字节完成，而字符是只有在内存中才会形成的，所以**使用字节的操作是最多的**。
