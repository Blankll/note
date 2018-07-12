# AJAX

异步js和XML



```javascript
var trigger = $('#trigger');
var card = $('#card');
var loaded = false;

trigger.on('click', function() {
    if(card.is(':visible')){
        card.slideUp();
    }else {
        if(!loaded){
            card.load('card.html');
            loaded = true;
        }
        card.slideDown();
    }
    //状态反转
    //card.toggle();
});
```

## JQuery 下的AJAX

```javascript
var url = '';
var httpMethod = 'get|post';
$.ajax(url, {
    method: httpMethod,
    data: {
        //post data
    },
}).done(function(data) {
    
});
```

格式

```javascript
var url = '';
var httpMethod = 'get|post';
$.ajax({
    url: url,
    datatype: jsinp,
    method: httpMethod,
    data: {
        //post data
    },
    success: function(data) {
        //成功回调函数
    },
    error: function() {
        //失败回调函数
    }
})
```

简写的post

```javascript
$.get(url)
```

简写的post

```javascript
$.post(url, {
    //data
    username: '',
    password: ''
});
$.getJson(url);
$.getScript(url);
```

