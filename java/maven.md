# maven





## maven多模块项目

创建一个父工程，选择普通maven项目，不需要模板







 <scope>的值的含义：
compile，缺省值，适用于所有阶段，会随着项目一起发布。 
provided，类似compile，期望JDK、容器或使用者会提供这个依赖。如servlet.jar。 
runtime，只在运行时使用，如JDBC驱动，适用运行和测试阶段。 
test，只在测试时使用，用于编译和运行测试代码。不会随项目发布。 
system，类似provided，需要显式提供包含依赖的jar，Maven不会在Repository中查找它。 





