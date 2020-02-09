# Fragment

1. Android3.0引入的api,为了适配大型平板电脑

2. 一个fragment可以在多个activity中使用,一个activity可以包含多个activity
3. fragment也拥有自己的布局,自己的响应事件和生命周期,但他的生命周期受到宿主activity的影响

### fragment的使用

1. 写一个类,继承fragment

2. 重写onCreateView()方法,连接布局和代码,返回fragment对应的布局的view

3. 把fragment加载到activity中 有静态加载和动态加载

   静态加载

   ```java
   public class LeftFragment extends Fragment {
   
   
       @Override
       public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                Bundle savedInstanceState) {
           // Inflate the layout for this fragment
           return inflater.inflate(R.layout.fragment_left, container, false);
       }
   }
   ```

   ```xml
   <fragment
             android:id="@+id/fragment_left"
             android:layout_width="0dp"
             android:layout_weight="1"
             android:layout_height="wrap_content" android:name="com.example.seven.myapplicationtest.fragments.LeftFragment"/>
   <fragment
             android:id="@+id/fragment_right"
             android:layout_width="0dp"
             android:layout_weight="1"
             android:layout_height="match_parent"        	`					         android:name="com.example.seven.myapplicationtest.fragments.RightFragment"/>
   ```

   动态加载



### Fragment的生命周期

1. 宿主activity执行了onCreate之后对应的fragment回调的生命周期
   - onAttach(): fragment首次挂载到activity时被执行,用于连接宿主activity
   - onCreate():创建fragment,进行初始化时创建fragment对象
   - onCreateView():创建fragment对应的视图对象
   - onActivityCreate(): 当宿主activity被创建之后会调用
2. 桶activity生命周期对应的方法
   - onStart(): 使fragment可见
   - onResume(): 使fragment获得焦点,可以与用户进行交互
   - onPause(): 使fragment失去焦点,不能交互
   - onStop(): 使fragment不可见
3. 当activity被销毁时fragment执行的方法
   - onDestroyView(): 销毁fragment对应的视图对象
   - onDestroy(): 销毁fragment对象
   - onDetach(): 解除宿主activity与fragment的绑定