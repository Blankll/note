# java异常体系

Throwable

- Error [非检查异常]
  - VirtualMachineError
    - StackOverflowError
    - ...
    - OutOfMemoryError
  - ...
  - AWTError
- Exception
  - RuntimeException[非检查异常]
    - ArithmeticException
    - ...
    - NullpointException
    - IndexOutOfBoundsException
  - ...
  - IOException[受检查异常]
    - EOFException
    - ...
    - FileNotFindException



![java-exceptions](../statics/java/java-exception.png)