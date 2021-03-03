import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;


public class Ginterface extends JFrame implements ActionListener {
    public static final int WIDTH = 1280;
    public static final int HEIGHT = WIDTH / 16 * 10;

    public ArrayList<Geometry> states;

    public JPanel mainPanel, firstPanel, secondPanel, thirdPanel, fourthPanel;
    public JTextArea moveAreaX, moveAreaY, rotateAreaX, rotateAreaY, rotateAlpha, MxArea, MyArea, kxArea, kyArea;
    public JButton moveButton, rotateButton, scaleButton, resetButton, backButton;
    public JLabel dxLabel, dyLabel, RxLabel, RyLabel, alphaLabel, MxLabel, MyLabel, kxLabel, kyLabel;

    public Geometry geometry;
    public MyCanvas myCanvas;

    Ginterface() {
        mainPanel = new JPanel();
        mainPanel.setPreferredSize(new Dimension(WIDTH / 3, HEIGHT));
        mainPanel.setLayout(new GridLayout(4, 1));
        mainPanel.setBackground(Color.white);

        firstPanel = new JPanel();
        secondPanel = new JPanel();
        thirdPanel = new JPanel();
        fourthPanel = new JPanel();

        firstPanel.setBackground(Color.white);
        secondPanel.setBackground(Color.white);
        thirdPanel.setBackground(Color.white);
        fourthPanel.setBackground(Color.white);

        JLabel firstLabel = new JLabel("Перемещение");
        firstLabel.setBorder(new LineBorder(Color.BLACK, 1));
        JLabel secondLabel = new JLabel("Поворот");
        JLabel thirdLabel = new JLabel("Масштабирование");

        firstLabel.setFont(new Font(firstLabel.getName(), Font.BOLD, 20));
        secondLabel.setFont(new Font(secondLabel.getName(), Font.BOLD, 20));
        thirdLabel.setFont(new Font(thirdLabel.getName(), Font.BOLD, 20));
        firstLabel.setHorizontalAlignment(SwingConstants.CENTER);
        secondLabel.setHorizontalAlignment(SwingConstants.CENTER);
        thirdLabel.setHorizontalAlignment(SwingConstants.CENTER);
        firstLabel.setVerticalAlignment(SwingConstants.CENTER);
        secondLabel.setVerticalAlignment(SwingConstants.CENTER);
        thirdLabel.setVerticalAlignment(SwingConstants.CENTER);

        firstLabel.setBorder(new EmptyBorder(35, 0, 0, 0));
        secondLabel.setBorder(new EmptyBorder(35, 0, 0, 0));
        thirdLabel.setBorder(new EmptyBorder(35, 0, 0, 0));


        moveAreaX = new JTextArea(1, 10);
        moveAreaY = new JTextArea(1, 10);
        rotateAreaX = new JTextArea(1, 1);
        rotateAreaY = new JTextArea(1, 1);
        rotateAlpha = new JTextArea(1, 1);
        MxArea = new JTextArea(1, 1);
        MyArea = new JTextArea(1, 1);
        kxArea = new JTextArea(1, 1);
        kyArea = new JTextArea(1, 1);

        moveAreaY.setBackground(Color.white);
        moveAreaX.setBackground(Color.white);
        rotateAreaX.setBackground(Color.white);
        rotateAreaY.setBackground(Color.white);
        rotateAlpha.setBackground(Color.white);
        MxArea.setBackground(Color.white);
        MyArea.setBackground(Color.white);
        kxArea.setBackground(Color.white);
        kyArea.setBackground(Color.white);

        moveAreaY.setBorder(new LineBorder(Color.green));
        moveAreaX.setBorder(new LineBorder(Color.green));
        rotateAreaX.setBorder(new LineBorder(Color.green));
        rotateAreaY.setBorder(new LineBorder(Color.green));
        rotateAlpha.setBorder(new LineBorder(Color.green));
        MxArea.setBorder(new LineBorder(Color.green));
        MyArea.setBorder(new LineBorder(Color.green));
        kxArea.setBorder(new LineBorder(Color.green));
        kyArea.setBorder(new LineBorder(Color.green));

        moveAreaY.setText("0");
        moveAreaX.setText("0");
        rotateAreaX.setText("420");
        rotateAreaY.setText("376");
        rotateAlpha.setText("0");
        MxArea.setText("420");
        MyArea.setText("376");
        kxArea.setText("1");
        kyArea.setText("1");

        moveAreaY.setFont(new Font(moveAreaX.getName(), Font.BOLD, 20));
        moveAreaX.setFont(new Font(moveAreaX.getName(), Font.BOLD, 20));
        rotateAreaX.setFont(new Font(moveAreaX.getName(), Font.BOLD, 20));
        rotateAreaY.setFont(new Font(moveAreaX.getName(), Font.BOLD, 20));
        rotateAlpha.setFont(new Font(moveAreaX.getName(), Font.BOLD, 20));
        MxArea.setFont(new Font(moveAreaX.getName(), Font.BOLD, 18));
        MyArea.setFont(new Font(moveAreaX.getName(), Font.BOLD, 18));
        kxArea.setFont(new Font(moveAreaX.getName(), Font.BOLD, 18));
        kyArea.setFont(new Font(moveAreaX.getName(), Font.BOLD, 18));
        // TODO бордеры и цвет

        moveAreaY.setLineWrap(false);
        moveAreaX.setLineWrap(false);
        rotateAreaX.setLineWrap(false);
        rotateAreaY.setLineWrap(false);
        rotateAlpha.setLineWrap(false);
        MxArea.setLineWrap(false);
        MyArea.setLineWrap(false);
        kxArea.setLineWrap(false);
        kyArea.setLineWrap(false);

        moveAreaY.setWrapStyleWord(true);
        moveAreaX.setWrapStyleWord(true);
        rotateAreaX.setWrapStyleWord(true);
        rotateAreaY.setWrapStyleWord(true);
        rotateAlpha.setWrapStyleWord(true);
        MxArea.setWrapStyleWord(true);
        MyArea.setWrapStyleWord(true);
        kxArea.setWrapStyleWord(true);
        kyArea.setWrapStyleWord(true);


        moveButton = new JButton("Переместить");
        rotateButton = new JButton("Повернуть");
        scaleButton = new JButton("Масштабировать");
        backButton = new JButton("Шаг назад");
        resetButton = new JButton("Сброс");

        backButton.setPreferredSize(new Dimension(235, 34));
        resetButton.setPreferredSize(new Dimension(235, 34));
        scaleButton.setPreferredSize(new Dimension(235, 34));
        moveButton.setPreferredSize(new Dimension(235, 34));
        rotateButton.setPreferredSize(new Dimension(235, 34));

        moveButton.setBackground(Color.pink);
        rotateButton.setBackground(Color.pink);
        scaleButton.setBackground(Color.pink);
        backButton.setBackground(Color.pink);
        resetButton.setBackground(Color.pink);

        moveButton.addActionListener(this);
        rotateButton.addActionListener(this);
        scaleButton.addActionListener(this);
        backButton.addActionListener(this);
        resetButton.addActionListener(this);

        moveButton.setFont(new Font(moveButton.getName(), Font.BOLD, 20));
        rotateButton.setFont(new Font(moveButton.getName(), Font.BOLD, 20));
        scaleButton.setFont(new Font(moveButton.getName(), Font.BOLD, 20));
        backButton.setFont(new Font(moveButton.getName(), Font.BOLD, 20));
        resetButton.setFont(new Font(moveButton.getName(), Font.BOLD, 20));


        dxLabel = new JLabel("dx");
        dyLabel = new JLabel("dy");

        RxLabel = new JLabel("Rx");
        RyLabel = new JLabel("Ry");
        alphaLabel = new JLabel("Угол");
        MxLabel = new JLabel("Mx");
        MyLabel = new JLabel("My");
        kxLabel = new JLabel("kx");
        kyLabel = new JLabel("ky");

        dxLabel.setVerticalAlignment(SwingConstants.CENTER);
        dyLabel.setVerticalAlignment(SwingConstants.CENTER);
        RxLabel.setVerticalAlignment(SwingConstants.CENTER);
        RyLabel.setVerticalAlignment(SwingConstants.CENTER);
        MxLabel.setVerticalAlignment(SwingConstants.CENTER);
        MyLabel.setVerticalAlignment(SwingConstants.CENTER);
        alphaLabel.setVerticalAlignment(SwingConstants.CENTER);
        kxLabel.setVerticalAlignment(SwingConstants.CENTER);
        kyLabel.setVerticalAlignment(SwingConstants.CENTER);

        dxLabel.setHorizontalAlignment(SwingConstants.CENTER);
        dyLabel.setHorizontalAlignment(SwingConstants.CENTER);
        RxLabel.setHorizontalAlignment(SwingConstants.CENTER);
        RyLabel.setHorizontalAlignment(SwingConstants.CENTER);
        MxLabel.setHorizontalAlignment(SwingConstants.CENTER);
        MyLabel.setHorizontalAlignment(SwingConstants.CENTER);
        alphaLabel.setHorizontalAlignment(SwingConstants.CENTER);
        kxLabel.setHorizontalAlignment(SwingConstants.CENTER);
        kyLabel.setHorizontalAlignment(SwingConstants.CENTER);

        dxLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        dyLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        RxLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        RyLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        MxLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        MyLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        alphaLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        kxLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));
        kyLabel.setFont(new Font(dxLabel.getName(), Font.BOLD, 20));


        firstPanel = new JPanel(new BorderLayout());
        secondPanel = new JPanel(new BorderLayout());
        thirdPanel = new JPanel(new BorderLayout());
        fourthPanel = new JPanel(new BorderLayout());


        JPanel firstUpPanel = new JPanel(new FlowLayout());
        JPanel firstMidPanel = new JPanel(new GridLayout(2, 2));
        JPanel firstDownPanel = new JPanel(new FlowLayout());

        firstUpPanel.setBackground(Color.decode("#DCDCDC"));
        firstMidPanel.setBackground(Color.decode("#DCDCDC"));
        firstDownPanel.setBackground(Color.decode("#DCDCDC"));

        firstUpPanel.add(firstLabel);

        firstMidPanel.add(dxLabel);
        firstMidPanel.add(dyLabel);
        firstMidPanel.add(moveAreaX);
        firstMidPanel.add(moveAreaY);
        firstDownPanel.add(moveButton);

        firstPanel.add(firstUpPanel, BorderLayout.NORTH);
        firstPanel.add(firstMidPanel, BorderLayout.CENTER);
        firstPanel.add(firstDownPanel, BorderLayout.SOUTH);


        JPanel secondUpPanel = new JPanel(new FlowLayout());
        JPanel secondMidPanel = new JPanel(new GridLayout(2, 3));
        JPanel secondDownPanel = new JPanel(new FlowLayout());

        secondUpPanel.setBackground(Color.decode("#DCDCDC"));
        secondMidPanel.setBackground(Color.decode("#DCDCDC"));
        secondDownPanel.setBackground(Color.decode("#DCDCDC"));

        secondUpPanel.add(secondLabel);


        secondMidPanel.add(RxLabel);
        secondMidPanel.add(RyLabel);
        secondMidPanel.add(alphaLabel);
        secondMidPanel.add(rotateAreaX);
        secondMidPanel.add(rotateAreaY);
        secondMidPanel.add(rotateAlpha);

        secondDownPanel.add(rotateButton);

        secondPanel.add(secondUpPanel, BorderLayout.NORTH);
        secondPanel.add(secondMidPanel, BorderLayout.CENTER);
        secondPanel.add(secondDownPanel, BorderLayout.SOUTH);


        JPanel thirdUpPanel = new JPanel(new FlowLayout());
        JPanel thirdMidPanel = new JPanel(new GridLayout(2, 4));
        JPanel thirdDownPanel = new JPanel(new FlowLayout());

        thirdUpPanel.setBackground(Color.decode("#DCDCDC"));
        thirdMidPanel.setBackground(Color.decode("#DCDCDC"));
        thirdDownPanel.setBackground(Color.decode("#DCDCDC"));

        thirdUpPanel.add(thirdLabel);

        thirdMidPanel.add(MxLabel);
        thirdMidPanel.add(MyLabel);
        thirdMidPanel.add(kxLabel);
        thirdMidPanel.add(kyLabel);
        thirdMidPanel.add(MxArea);
        thirdMidPanel.add(MyArea);
        thirdMidPanel.add(kxArea);
        thirdMidPanel.add(kyArea);

        thirdDownPanel.add(scaleButton);

        thirdPanel.add(thirdUpPanel, BorderLayout.NORTH);
        thirdPanel.add(thirdMidPanel, BorderLayout.CENTER);
        thirdPanel.add(thirdDownPanel, BorderLayout.SOUTH);


        JPanel fourthPanel = new JPanel(new FlowLayout());
        fourthPanel.setPreferredSize(new Dimension(WIDTH / 3, 20));
        fourthPanel.setBorder(new EmptyBorder(50, 0, 0, 0));
        fourthPanel.setBackground(Color.decode("#DCDCDC"));


        fourthPanel.add(backButton);
        fourthPanel.add(resetButton);

        firstPanel.setBorder(new LineBorder(Color.black, 2));
        secondPanel.setBorder(new LineBorder(Color.black, 1));
        thirdPanel.setBorder(new LineBorder(Color.black, 2));

        mainPanel.add(firstPanel);
        mainPanel.add(secondPanel);
        mainPanel.add(thirdPanel);
        mainPanel.add(fourthPanel);

        myCanvas = new MyCanvas(WIDTH, HEIGHT);

        this.setTitle("Главное окно");
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(this.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(250, 150);
        this.getRootPane().setBorder(new LineBorder(Color.BLACK, 5));
        this.setSize(WIDTH, HEIGHT);
        this.setVisible(true);

        this.add(mainPanel, BorderLayout.WEST);
        this.add(myCanvas, BorderLayout.EAST);
    }


    public static void main(String[] args) {
        Ginterface gInterface = new Ginterface();
        gInterface.geometry = new Geometry();

        gInterface.states = new ArrayList<>(10);
        gInterface.states.add(gInterface.geometry.Clone());
    }


    public void printError(String errorMsg) {
        JFrame errorFrame = new JFrame("Ошибка");
        errorFrame.setResizable(false);
        errorFrame.setLocation(970, 350);
        errorFrame.getRootPane().setBorder(new LineBorder(Color.BLACK, 3));
        errorFrame.setSize(400, 300);
        errorFrame.setVisible(true);

        JTextArea errorMSG = new JTextArea();
        errorMSG.setFont(new Font(errorMSG.getName(), Font.BOLD, 25));
        errorMSG.setText(errorMsg);
        errorMSG.setWrapStyleWord(true);
        errorMSG.setLineWrap(true);
        errorMSG.setEditable(false);
        errorMSG.setMargin(new Insets(30, 30, 30, 30));

        errorFrame.add(errorMSG);
    }





    public void moveProcess() {
        Double dx = 0.0, dy = 0.0;
        try {
            dx = Double.valueOf(moveAreaX.getText());
            dy = Double.valueOf(moveAreaY.getText());
        } catch (Exception exception) {
            printError("Некорректные данные для перемещения точки!");
            return;
        }

        this.geometry.UpdateMoveAll(dx, dy);
        this.states.add(this.geometry.Clone());
        this.myCanvas.clearCanvas();
        this.myCanvas.printAll(this.geometry);
    }

    public void rotateProcess() {
        Double rx = 0.0, ry = 0.0, alpha = 0.0;

        try {
            rx = Double.valueOf(rotateAreaX.getText());
            ry = Double.valueOf(rotateAreaY.getText());
            alpha = Double.valueOf(rotateAlpha.getText());
        } catch (Exception exception) {
            printError("Ошибка в данных для поворота!");
            return;
        }

        this.geometry.rotateAll(rx, ry, alpha);
        this.states.add(this.geometry.Clone());
        this.myCanvas.clearCanvas();
        this.myCanvas.printAll(this.geometry);
    }

    public void scaleProcess() {
        Double mx = 0.0, my = 0.0, kx = 0.0, ky = 0.0;

        // TODO фокус кнопки назад
        // TODO подготовить текст для сообщений
        // TODO функцию изменить для одног ообъекта
        try {
            mx = Double.valueOf(MxArea.getText());
            my = Double.valueOf(MyArea.getText());
            kx = Double.valueOf(kxArea.getText());
            ky = Double.valueOf(kyArea.getText());
        } catch (Exception exception) {
            printError("Ошибка в данных для поворота!");
            return;
        }

        this.geometry.scaleAll(mx, my, kx, ky);
        this.states.add(this.geometry.Clone());
        this.myCanvas.clearCanvas();
        this.myCanvas.printAll(this.geometry);
    }



    public void backProcess() {
        if (this.states.size() <= 1) {
            return;
        }

        this.geometry = states.get(states.size() - 2).Clone();
        this.myCanvas.clearCanvas();
        this.myCanvas.printAll(this.geometry);
        this.states.remove(states.size() - 1);
    }

    public void beginStateProcess() {
        this.geometry = states.get(0).Clone();
        this.myCanvas.clearCanvas();
        this.myCanvas.printAll(this.geometry);
        this.states.clear();
        this.states.add(this.geometry.Clone());
    }


    @Override
    public void actionPerformed(ActionEvent e){
        if (e.getSource() == moveButton) {
            moveProcess();
        }
        else if (e.getSource() == rotateButton) {
            rotateProcess();
        }
        else if (e.getSource() == scaleButton) {
            scaleProcess();
        }
        else if (e.getSource() == backButton) {
            backProcess();
        }
        else if (e.getSource() == resetButton) {
            beginStateProcess();
        }
    }
}




