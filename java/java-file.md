# java文件

## File Class

### 文件的创建，重命名，删除
```java
package ynnu.corejava.file;

import java.io.File;
import java.io.IOException;

public class HelloFile {
	public static void main(String[] args) {
		//文件操作
		File file = new File("hello2.txt");//创建文件对象
		File file2 = new File("hello2.txt");//创建文件对象
		System.out.println("当前文件是否存在："+file.exists());
		if(file.exists()) {
			System.out.println("当前文件对象是否为文件："+file.isFile());
			System.out.println("当前文件对象是否为目录："+file.isDirectory());
		}else {
			try {
				file.createNewFile();//创建文件
				System.out.println("创建文件成功，文件目录为："+file.getAbsolutePath());
			}catch(IOException e) {
				System.out.println("创建文件失败");
			}
			
		}
		if(file2.exists()) {
			file2.delete();
			System.out.println("文件删除成功");
		}
		//文件夹操作
		File floder = new File("floder");//创建文件对象
		System.out.println(floder.mkdir());//创建文件目录
	}

}

```

### 文件属性的读取
```java
package ynnu.corejava.file;

import java.io.File;

public class FileProperty {

	public static void main(String[] args) {
		File file = new File("hello.txt");
		//判断文件是房价存在
		System.out.println("判断文件是否存在:"+file.exists());
		//读取文件名称
		System.out.println("读取文件名称:"+file.getName());
		//读取相对文件路径
		System.out.println("读取相对文件路径:"+file.getPath());
		//读取绝对文件路径etAbsolutePath()
		System.out.println("读取绝对文件路径:"+file.getAbsolutePath());
		//读取父级文件路径
		System.out.println("读取父级文件路径:"+new File(file.getAbsolutePath()).getParent());
		//读取文件大小
		System.out.println("读取文件大小:"+file.length()+"byte");
		//判断文件是否被隐藏
		System.out.println("判断文件是否被隐藏:"+file.isHidden());
		//判断文件是否可读
		System.out.println("判断文件是否可读:"+file.canRead());
		//判断文件是否可写
		System.out.println("判断文件是否可写:"+file.canWrite());
		//判断文件是否为文件夹
		System.out.println("判断文件是否为文件夹:"+file.isDirectory());
	}

}

```

## maven项目下path

```bash
File file = new File("reddit");
// 获取项目根目录下reddit目录地址
String courseFile = file.getCanonicalPath();
String absFile = file.getAbsolutePath();
// 项目根目录地址
String rootPath = System.getProperty("user.dir");
// 获取编译后target下classes/reddit目录
ClassLoader classLoader = getClass().getClassLoader();
String path = classLoader.getResource("reddit").getPath();
```

