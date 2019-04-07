# CSS

### css内容超出部分隐藏



```css
// 单行
overflow: hidden;
text-overflow:ellipsis;
white-space: nowrap;
// 多行
display: -webkit-box;
-webkit-box-orient: vertical;
-webkit-line-clamp: 3;
overflow: hidden;

```

## shadow

- box-shadow
  - box-shadow x y 模糊区域 扩展区域 色值
- text-sadow
- border-radius
- background
- clip-path



```css
E {box-shadow: <length> <length> <length>?<length>?||<color>}
也就是：
E {box-shadow:inset x-offset y-offset blur-radius spread-radius color}
换句说：
对象选择器 {box-shadow:投影方式 X轴偏移量 Y轴偏移量 阴影模糊半径 阴影扩展半径 阴影颜色}
```

