# 建造者模式

简单来说,就是实现链式调用

调用类

```java
package com.seven.designpattern.builder;

public class Course {
    private String name;
    private String ppt;
    private String video;
    private String post;
    public Course(Builder builder) {
        this.name = builder.name;
        this.ppt = builder.ppt;
        this.video = builder.video;
        this.post = builder.post;
    }

    public static class Builder {
        private String name;
        private String ppt;
        private String video;
        private String post;
		// build过程中的链式调用
        public Builder buildName(String name) {
            this.name = name;
            return this;
        }
        public Builder buildPPT(String ppt) {
            this.ppt = ppt;
            return this;
        }
        public Builder buildVideo(String video) {
            this.video = video;
            return this;
        }
        public Builder buildPost(String post) {
            this.name = post;
            return this;
        }
		// 最后进行构建赋值
        public Course build() {
            return new Course(this);
        }
    }

    @Override
    public String toString() {
        return "Course{" +
                "name='" + name + '\'' +
                ", ppt='" + ppt + '\'' +
                ", video='" + video + '\'' +
                ", post='" + post + '\'' +
                '}';
    }
}

```

测试

```java
public class TestClass {
    public static void main(String[] args) {
        Course course = new Course.Builder()
                .buildName("course builder")
                .buildPost("course post")
                .buildPPT("course ppt")
                .buildVideo("course video").build();
        System.out.println(course.toString());
    }
}
```

