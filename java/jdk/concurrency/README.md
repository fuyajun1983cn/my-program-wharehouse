##����API  
ʹ��Thread�������̳߳��򣬱������Դ���synchronized,��������,wait(), notify(), notifyAll()��ϸ�ڡ������Ҫ�����̳߳أ���д���ȸ߼���������JDK5֮���ṩ��java.util.concurrent����

1. ʹ��Lock  
Lock�ӿڵ���Ҫ������֮һΪ`ReentrantLock`�����Դﵽsynchronized�����á�
����һЩ�ض������ʹ�õ�����`ReadWriteLock`, `ReentrantReadWriteLock`

2. ʹ��Condition  
Condition�ӿڴ���Lock����������÷����ǴﵽObject��wait(),notify(),notifyAll()���������á�
```java

Lock lock = new ReentrantLock();
Condition condition = lock.newCondition();

...
try {
    lock.locl();

     while(...) {
         condition.await();
     }

     ...
     condition.signal();

     ...

}
finally {

    lock.unlock();

}
```

3. Executors
```java
Executor excutor;

...

executor.execute(new Runnable() {

    ...


});

```

4. Future API

5. ScheduledExecutorService


