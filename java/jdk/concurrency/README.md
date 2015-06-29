##�̰߳�ȫ  
��д�̰߳�ȫ�Ĵ����ʵ�ʾ��ǹ����*״̬*���ر���*�����*��*�ɸı��״̬*�ķ��ʡ�
������̷߳���һ��״̬������������һ�����������д�������������ʹ��ͬ��������Э���Ը�״̬�����ķ��ʡ�
������з��ʵ��µ�����ķ������£�  
* ��Ҫ���̹߳���״̬������  
* ��״̬��������Ϊ�����޸ĵġ�
* ���κ�ʱ�����״̬����ʱ��ʹ��ͬ����  
**�̰߳�ȫ**�����װ���κ���Ҫͬ�����ʵĵط���ʹ��ʹ���������ṩ�Լ���ͬ��������  
**��״̬�Ķ��������̰߳�ȫ��**    
Ϊ�˱�֤״̬��һ���ԣ��ڵ���ԭ�Ӳ����ڸ�����ص�״̬������  

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

6. �����̰߳�ȫ��  
  ��AtomicLong, AtomicBoolean�ȡ�

7. intrinsic lock  
  Java�е�ÿ�����󶼿�����Ϊintrinsic
  lock��ÿ��intrinsic���ǿ�����ġ�����������ÿ-�߳�����������ÿ-������(��pthread)����ζ�ţ���Java�У�
  ��synchronized���������Ĵ���ֻ����ֹ�̼߳�Ķ�η��ʣ����ǲ�����ֹ�߳��ڵĶ�η��ʡ�  


�������ʾ����  
* NoVisibility ���������ݲ�ʹ��ͬ��ʱ����������ݲ�һ���ԡ� 
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;synchronized����򷽷�����ȷ������ԭ���ԣ����ң���������һ��
  ��Ҫ�����壺�ڴ�ɼ��ԣ���һ���̶߳Թ������ݵ��޸��ܷ���һ���̸߳�֪��

**The Java Memory
modelҪ��fetch��store����������ԭ�Ӳ�����**���ǣ�����64λ��long ��
double�ķ�volatile���͵ı����������Ա����Ĵ�ȡ������Ϊ���������Ĳ��������У��ڶ��̳߳����У�
���ڹ����long��double���͵ı�������������Ϊ`volatile`���͡�  

Locking�ܹ���֤ԭ���ԺͿɼ��ԣ���volatileֻ�ܱ�֤�ɼ��ԡ� 

* ThreadLocal example  
```java
private static ThreadLocal<Connection> connectionHolder
    = new ThreadLocal<Connection>() {
    public Connection initialValue() {
        return DriverManager.getConnection(DB_URL);
    }
};

public static Connection getConnection() {
    return connectionHolder.get();
}
```

