public class A {
    public int a = 2;

    public static void setA(int a) {
        System.out.println("huuu");
    }
}

class B extends A {
    public void getA() {
        System.out.println(a);
    }
}
