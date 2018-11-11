# ThinkPHP ORM[^1]模型

##基本认知

1. TP5的模型是ORM[^1]的具体实现， 同时， 模型还会包含相关的业务逻辑

### 模型与模型关联

模型不仅仅只是操作数据库，还会包含相关的业务逻辑，用来处理相对复杂的业务逻辑，模型可以作为业务的集合；

##常见的模型方法

1. find(\$primary_key),get($primary_key): 查询一条数据，get只能用于模型；
2. select(\$primary_key),all($primary_key):查询多条数据，all只能用于模型；

==在模型查询中优先使用静态调用==

# 数据表关系分析

主表-从表

1. 一对一关系 ``belongsTo()``
2. 一对多的关系  ``hasMany()``
3. 多对多的关系  ``belongsToMany``

# ThinkPHP模型关联

## 步骤

1. 确定表的关系[模型与模型之间的关系]

2. 通过创建方法建立模型关联

   ```php
   /**
    * 一对一的关系且表中包含外键字段
    *
    * $this 当前模型
    * Image 关联模型名称
    * topic_img_id 关联模型外键
    * id 当前模型的组件id [primarykey]
    */
   public function topImg()
   {
     //对于表中不包含外键字段的关联用hasOne() [就是反过来]
     return $this->belongsTo('Image','topic_img_id','id');
   }

   /**
     * 一对多的关系
     *
     * $this: 当前模型
     * BannerItem: 关联模型名称
     * banner_id: 关联模型外键名
     * id: 当前模型的id组件[primarykey]
     */
    public function items()
    {
      return $this->hasMany('BannerItem','banner_id','id');
    }

      /**
       * 建立多对多的模型关联
       *
       * ProductModel 关联模型名
       * theme_product 中间表名[是表名，不是模型名]
       * product_id 中间表关联从表外键名
       * theme_id 关联表关联主表外键名
       */
      public function products()
      {
          return $this->belongsToMany('ProductModel', 'theme_product', 'product_id', 'theme_id');
      }
   ```

3. 调用模型获取关联数据

   ```php
   /**
    * items:在模型中创建的关联方法
    * $id:查找的primarykey
    */
   $banner = BannerModel::with('items')->find($id);
   ```

   ### 嵌套关联查询

   1. 确定模型与模型之间的关系

   2. 建立模型关联

      ```php
          /**
           * 建立模型关联
           * $this 当前模型
           * ImageModel 关联模型名称
           * img_id 关联模型外键名
           * id 当前模型的id组件[primarykey]
           */
          public function image()
          {
              return $this->belongsTo('ImageModel','img_id','id');
          }
      ```

   3. 调用模型方法获取数据

      ```php
      /**
       * items 关联方法
       * items.image 当前模型(BannerModel)关联的模型(BannerItemModel)关联模型(ImageModel)的方法
       * $id 当前模型的id组件[primarykey]
       */

      $banner = BannerModel::with(['items','items.image'])->find($id);
      ```

      ​

      ### 通过闭包对关联模型的子模型进行排序

      ```php
          /**
           * 获取产品的详情
           *
           * @param int $id 产品id
           *@return object $product 产品详情集合
           */
           public static function getDetail($id)
           {
               /***************************************************
               |
               + 通过闭包对关联模型的子模型进行排序
               |
               ***************************************************/
               $product = self::with(['imgs'])
                   ->with(['imgs' => function($query){
                       $query->with(['imageUrl'])
                          ->order('order','asc');
                   }])
                   ->with(['properties'])
                   ->find($id);

               return $product;
           }
      ```

      ​

      ##模型关联的数据的CRUD 操作

      一对多时建议分开的形式保存，先保存一，再保存多

      ## TP5启用事务

      ```php
               try{
                   //启用事务
                   Db::startTrans();
                   //生成订单编号
                   $order_code = $this->makeOrderNo();
                   //保存订单数据到数据库
                   $order = new OrderModel();
                   $order->user_id = $this->u_id;
                   $order->order_no = $order_code;
                   $order->total_price = $snap['order_price'];
                   $order->total_count = $snap['total_count'];
                   $order->snap_img = $snap['snap_image'];
                   $order->snap_name = $snap['snap_name'];
                   $order->snap_address = $snap['snap_address'];
                   $order->snap_items = json_encode($snap['snap_items']);
                   $order->save();

                   //向中间表插入数据
                   $order_id = $order->id;
                   $create_time = $order->create_time;
                   $products = $this->product_client;

                   foreach($products as &$item) $item['order_id'] = $order_id;
                   //ORM插入数据
                   $order_product = new OrderProductModel();
                   $order_product->saveAll($products);
                   Db::commit();

               }catch(Exception $e){
                   //出现异常启用事务回滚
                   Db::rollback();
                   //抛出异常
                   throw $e;
               }

      ```

      ​

      ## TP5自动写入时间戳及自定义时间戳字段

      在模型下添加字段

      ```php
      //开启自动写入时间戳
      protected $autoWriteTimestamp = true;
      //自定义时间戳字段名
      protected $createTime = 'create_timestamp';
      ```

      ​

      ### 隐藏模型字段[^2]

      ####$this和self的区别

      ``$this``是指向当前对象的指针（可以看成C里面的指针），``self``是指向当前类的指针。

      self是引用静态类的类名，而$this是引用非静态类的实例名。

      #### 隐藏字段

      1. 通过ORM来隐藏字段

      ```php
      $banner = BannerModel::with(['items','items.image'])->find($id);
      /**
       * update_time ,delete_time 要隐藏的字段名
       */
      $banner->hidden(['update_time','delete_time']);
      ```

      2. 通过数据集临时隐藏数据

      ```php
      //使用数据集临时隐藏数据
      $products = collection($products)->hidden(['summary']);
      ```

      ​

      #### 仅显示指定字段名

      ```php
      $banner = BannerModel::with(['items', 'items.image']);
      /**
       * 仅仅显示查询结果中的id和update_time字段
       */
      $banner->visible(['id','update_time']);
      ```

      ### TP5读取器

      ``每次执行ORM操作时都会运行读取器的方法``

      运用读取器可以巧妙的解决灵活配置图片地址前缀的问题

      ```php
      /**
       * getUrlAttr($value, $data) 读取器的特定格式，获取url字段的值
       * $value 读取器获取的目标字段的值保存在该变量中
       * $data 模型对应的表的所有字段的值以数组的形式保存在$data中
       * $data['from'] 通过该字段确定图片保存的地址是在服务器本地还是专有图片服务器上
       */
      public function getUrlAttr($value, $data)
      { 
        $final_url = $value;
        $prefix = \think\Env::get('img_url_prefix');
        if($data['from'] == 1) $final_url = $prefix.$value;
        return $final_url;
      }
      ```

      ## API版本管理

      业务是不可能一成不变的，版本管理可以更好的应对业务的变更

      ==**开闭原则[^3]**==**对扩展开放，对修改封闭**

      分版本的意义： 保证新版本推出之后，旧版本也可以继续使用，提供多版本支持

      动态生成路由地址从而转换不同的版本

      ```php
      //version 通过不同的地址传入而区分不同的版本从而得到不同的response
      Route::get('api/:version/banner/:id', 'api/:version.Bnner/getBanner');
      ```

      ## TP5开启路由完全匹配

      将config.php下的route_complete_match值改为true

      ```php
      // 路由使用完整匹配
          'route_complete_match'   => true,
      ```

      ## 数据冗余

      适当的数据冗余设计可以减缓数据库查询的压力

      在数据量不可控时应当尽量减少数据库的压力

      数据冗余是违反数据库库设计原理

      数据冗余会产生数据不一致的隐患

      ## #TP5时间字段

      只有通过模型进行数据库操作才能自动更新数据库中的delete_time,update_time,create_time



[^1]: object relational mapping 对象关系映射[可以l理解为表在面向对象中的一种体现]
[^2]: 有时并不需要数据表中的所有字段
[^3]: 如果要修改代码，最好通过扩展的形式 