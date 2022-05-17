package cn.lidan.start;

import cn.lidan.util.Const;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

public class Carculator extends JFrame implements ActionListener{
    /*********************北面的控件****************************/
    private final JPanel jp_north = new JPanel();//北面的面板
    private final JTextField input_text = new JTextField();//一个输入框
    private final JButton c_Btn = new JButton("C");//名字为C的button按钮

    /***********************中间的控件**************************/
    private final JPanel jp_center = new JPanel();//中间的面板

    public Carculator() throws HeadlessException {  //声明异常抛出
        this.init();
        this.addNorthComponent();
        this.addCenterButton();
    }
    //初始化的方法
    public void init(){
        this.setTitle(Const.TITLE);//标题
        this.setSize(Const.FRAME_W,Const.FRAME_H);//设置窗口大小
        this.setLayout(new BorderLayout());//设置一个流布局管理器的边界布局
        this.setResizable(false);//固定大小不让其改变
        this.setLocation(Const.FRAME_X,Const.FRAME_Y);//将窗口移动这个位置
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭窗口时退出程序
    }
    //添加北面的部件
    public void addNorthComponent(){
        this.input_text.setPreferredSize(new Dimension(330,30));//北面面板的输入框大小设置
        jp_north.add(input_text);//实现输入框
        this.c_Btn.setForeground(Color.RED);//设置C按钮颜色
        jp_north.add(c_Btn);//实现C按钮

        c_Btn.addActionListener(e -> {//处理事件监听的方法
            input_text.setText("");
        });

        this.add(jp_north,BorderLayout.NORTH);//实现北面的面板
    }
    //添加中间的按钮
    public void addCenterButton(){
        String btn_text = "123+456-789×0.=÷";
        this.jp_center.setLayout(new GridLayout(4,4));//网格布局
        for(int i=0;i<16;i++){
            String temp = btn_text.substring(i,i+1);//substring截取字符：将字符串依次写到button上，i是下标，i+1是对应的字符串数
            JButton btn = new JButton();
            btn.setText(temp);
            if(temp.equals("+")||temp.equals("-")||temp.equals("×")||temp.equals("÷")||temp.equals(".")||temp.equals("=")){//如果接收到的是加减乘除点
                // 等于就进行加粗与增大
                btn.setFont(new Font("粗体",Font.BOLD,16));
                btn.setForeground(Color.RED);
            }
            btn.addActionListener(this);//用this来监听赋值
            jp_center.add(btn);//实现按钮
        }
        this.add(jp_center,BorderLayout.CENTER);//在中间构造一个组件之间没有间距的新边框布局
    }
    /*********************main函数部分*************************************/
    public static void main(String[] args) {
        Carculator carculator=new Carculator();//new一个新窗体
        carculator.setVisible(true);
    }

    private String firstInput = null;
    private String operator =null;//运算符
    @Override
    public void actionPerformed(ActionEvent e) {
        String clickStr = e.getActionCommand();
        if(".0123456789".contains(clickStr)){//如果输入的值包含
            this.input_text.setText(input_text.getText()+clickStr);//将值赋传到文本框里面去
            this.input_text.setHorizontalAlignment(JTextField.RIGHT);//将值从右开始进行赋值;setHorizontalAlignment设置文本水平方式
        }else if(clickStr.matches("[+×÷-]")){
            operator = clickStr;
            firstInput = this.input_text.getText();//写入第一次的值
            this.input_text.setText("");//将第一次的值进行一个清空
        }else if(clickStr.equals("=")){
                 Double a = Double.valueOf(firstInput);
                 Double b = Double.valueOf(this.input_text.getText());
                 Double result = null;
                 switch (operator){
                     case "+":result = a + b;break;
                     case "-":result = a - b;break;
                     case "×":result = a * b;break;
                     case "÷":if(b!=0){result = a / b;}break;
                 }
                 this.input_text.setText(Objects.requireNonNull(result).toString());//返回值到input_text
            }

    }
}