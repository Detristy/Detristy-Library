public class StudentTest2 {
    public static void main(String[] args){
        Exam e = new Exam("Tom",1,100.0);
        e.printInfo();
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
        return name;
    }
    public int getNumber(){
        return number;
    }
    public abstract void printInfo();
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
    public void printInfo(){
        System.out.println(super.getName() + " " + super.getNumber() + " " + examScore);
    }
}