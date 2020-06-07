# 文件上传

搜到了一篇国外的文章，写的简介不简单，比csdn上的优秀多了,

原文地址：https://codeboje.de/spring-mvc-fileupload/

# Uploading a File(s) with Spring MVC and Spring Boot

23.05.2017 by Jens in [Spring Boot](https://codeboje.de/tag/spring-boot/) | [Spring MVC](https://codeboje.de/tag/spring-mvc/)

Uploading a file with Spring MVC is pretty easy, and it gets even easier when running in Spring Boot. However, it’s one of the tasks a developer does once in a while and therefore is pretty easy to forget. The page is a reminder for all of us.

## Uploading File

For uploading a file, you must use *multipart/form-data* as the form encoding and usually files are uploaded with a POST request.

On the Spring MVC *@Controller* we only need to add a *@RequestParam* with the name of your form field and map it to a *MultipartFile* class.

The *MultipartFile* class provides access to the file, file name, file type, etc.

```java
@RequestMapping(value = "/upload", method = RequestMethod.POST)
@ResponseStatus(HttpStatus.OK)
public void upload(@RequestParam("file") MultipartFile file, @RequestParam String additionalField) {

    System.out.println(String.format("File name %s", file.getName()));
    System.out.println(String.format("File original name %s", file.getOriginalFilename()));
    System.out.println(String.format("File size %s", file.getSize()));

    //do whatever you want with the MultipartFile
    file.getInputStream();
}
```

## Uploading Multiple Files

For uploading multiple files together, we only need to add all the files to the form.

In your form will have multiple instances of file inputs using the same *name*attribute. The browser will include them all in the request.

```html
<input type="file" name="files" />
<input type="file" name="files" />
<input type="file" name="files" />
```

In the *@Controller*, we can simply switch from a single *MultipartFile*parameter to using a *MultipartFile* array.

```java
@RequestMapping(value = "/upload", method = RequestMethod.POST)
@ResponseStatus(HttpStatus.OK)
public void upload(@RequestParam("file") MultipartFile[] file, @RequestParam String additionalField) {
    //do whatever you want with the files

}
```

## Configuring Multipart File Uploads in Spring Boot

In Spring Boot the Multipart file upload is configured automatically and set up with defaults. It will also use the Servlet 3 API for Multiparts.

If you need to adjust the max file size or similar, you can do so by setting the following properties in your *application.properties*.

The most used properties are:

- **spring.http.multipart.file-size-threshold** A threshold after which the files are written to disk. Supports *MB* or *KB* as suffixes to indicate size in Megabyte or Kilobyte
- **spring.http.multipart.location** location of the temporary files
- **spring.http.multipart.max-file-size** Max size per file the upload supports; also supports the *MB* or *KB* suffixes; by **default 1MB**
- **spring.http.multipart.max-request-size** max size of the whole request; also supports the *MB* or *KB* suffixes

## Conclusion

Uploading files with Spring MVC is straight forward, and with Spring Boot you get zero configuration too. And, in case you must change the file size or other, you can do so easily with the properties.

------