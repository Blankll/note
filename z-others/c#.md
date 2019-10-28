用Json.NET类库需要引入的命名空间
```c#
using Newtonsoft.Json;


//Json.NET序列化
string jsonData = JsonConvert.SerializeObject(lstStuModel);

//Json.NET反序列化
Student descJsonStu = JsonConvert.DeserializeObject<Student>(json);
```
