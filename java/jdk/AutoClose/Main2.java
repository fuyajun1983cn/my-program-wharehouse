
class ResourceSome implements AutoCloseable {
    void doSome() {
        System.out.println("do something");
    }

    public void close() throws Exception {
        System.out.println("close resources");
    }
}

class ResourceOther implements AutoCloseable {
    void doOther() {
        System.out.println("do something other");
    }

    public void close() throws Exception {
        System.out.println("close other resources");
    }
}

public class Main {
    public static void main(String args[]) {
        //�Զ��ر����ϵ����﷨�� Java 7����
        //�����Զ��رն����Դ���м��÷ֺŸ���
        //��try�������棬Խ����д�Ķ�����Դ��Խ�类�ر�
        try (ResourceSome some = new ResourceSome(); 
                ResourceOther other = new ResourceOther()) {
            some.doSome();
            other.doOther();
        } catch(Exception ex) {
            ex.printStackTrace();
        }
    }
}
