//用于测试抽象类的声明和实现。
public class StudentTest {
    public static void main(String[] args){
        Exam e = new Exam("Tom",1,100.0);
        System.out.println(e.getName() + " " + e.getNumber() + " " + e.getScore());
    }
}

abstract class Student{
    private String name;
    private int number;
    public Student(){}
    public Student(String name, int number){
        this.name = name;
        this.number = number;
    }
    public String getName(){
        return this.name;
    }
    public int getNumber(){
        return this.number;
    }
}

class Exam extends Student{
    private double examScore;
    public Exam(String name,int number,double score){
        super(name,number);
        setScore(score);
    }
    private void setScore(double score){
        examScore = score;
    }
    public double getScore(){
        return examScore;
    }
    public String getName(){
        return super.getName();
    }
    public int getNumber(){
        return super.getNumber();
    }
}