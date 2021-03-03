import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.sql.Time;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;


public class GInterface extends JFrame implements ActionListener {
    public static final int WIDTH = 1280;
    public static final int HEIGHT = WIDTH / 16 * 10;
    public JPanel jPanel;
    public JButton addPointBtn;
    public JButton changePointBtn;
    public JButton delPointBtn;
    public JButton delAllPointsBtn;
    public JButton solveBtn;
    public JButton addButton;
    public JTextArea inputX;
    public JTextArea inputY;
    public JTextArea area;

    public JTextArea newY;
    public JTextArea newX;
    public JTextArea numPoint;
    public JButton changeButton;

    public JTextArea solveArea;

    public JButton delButton;

    public Geometry geometry;
    public MyCanvas myCanvas;

    public Double k;
    public Double minXValue, minYValue;
    public Double maxXValue, maxYValue;

    public int CANVAS_WIDTH = 600;
    public int y0 = 60;
    public int x0 = 100;

    public int x1 = 760;
    public int y1 = 720;

    GInterface() {
        jPanel = new JPanel();
        jPanel.setPreferredSize(new Dimension(WIDTH / 3, HEIGHT));
        jPanel.setLayout(new BorderLayout(5, 5));
        jPanel.setBackground(Color.white);

        JLabel jLabel = new JLabel("Список точек");
        int newFontSize = (int) (jLabel.getFont().getSize() * 2);
        jLabel.setFont(new Font(jLabel.getName(), Font.BOLD, newFontSize));
        jLabel.setVerticalAlignment(SwingConstants.CENTER);
        jLabel.setHorizontalAlignment(SwingConstants.CENTER);
        newFontSize = (int) (newFontSize * 0.8);
        area = new JTextArea(50, 20);
        area.setBackground(Color.WHITE);
        area.setFont(new Font(area.getName(), Font.BOLD, newFontSize));
        area.setText(" №          X                       Y\n");
        area.setPreferredSize(new Dimension(WIDTH / 3, HEIGHT / 10));
        area.setMaximumSize(new Dimension(WIDTH / 3, HEIGHT / 10));
        area.setLineWrap(true);
        area.setWrapStyleWord(true);
        area.setEditable(false);

        newFontSize = (int) (jLabel.getFont().getSize());

        addPointBtn = new JButton("Добавить точку");
        addPointBtn.setMinimumSize(new Dimension(50, 60));
        addPointBtn.setFont(new Font(addPointBtn.getName(), Font.BOLD, newFontSize));
        addPointBtn.setBackground(Color.pink);
        addPointBtn.addActionListener(this);

        changePointBtn = new JButton("Изменить точку");
        changePointBtn.setPreferredSize(new Dimension(50, 60));
        changePointBtn.setFont(new Font(changePointBtn.getName(), Font.BOLD, newFontSize));
        changePointBtn.setBackground(Color.pink);
        changePointBtn.addActionListener(this);

        delPointBtn = new JButton("Удалить точку");
        delPointBtn.setPreferredSize(new Dimension(50, 60));
        delPointBtn.setFont(new Font(delPointBtn.getName(), Font.BOLD, newFontSize));
        delPointBtn.setBackground(Color.pink);
        delPointBtn.addActionListener(this);

        delAllPointsBtn = new JButton("Удалить все точки");
        delAllPointsBtn.setPreferredSize(new Dimension(50, 60));
        delAllPointsBtn.setFont(new Font(delAllPointsBtn.getName(), Font.BOLD, newFontSize));
        delAllPointsBtn.setBackground(Color.pink);
        delAllPointsBtn.addActionListener(this);

        solveBtn = new JButton("Решить задачу");
        solveBtn.setPreferredSize(new Dimension(50, 60));
        solveBtn.setFont(new Font(solveBtn.getName(), Font.BOLD, newFontSize));
        solveBtn.setBackground(Color.pink);
        solveBtn.addActionListener(this);

        JPanel labelPannel = new JPanel();
        labelPannel.setLayout(new FlowLayout());
        labelPannel.setPreferredSize(new Dimension(WIDTH / 3, HEIGHT / 2 / 8));
        labelPannel.setBackground(Color.pink);
        labelPannel.add(jLabel);


        JPanel textPannel = new JPanel();
        textPannel.setLayout(new GridLayout(1, 1));
        textPannel.setPreferredSize(new Dimension(WIDTH / 3, HEIGHT / 10));
        textPannel.add(new JScrollPane(area));
        textPannel.setBackground(Color.white);


        JPanel btnPannel = new JPanel();
        btnPannel.setLayout(new GridLayout(5, 1, 5, 5));
        btnPannel.setBackground(Color.white);

        btnPannel.add(addPointBtn);
        btnPannel.add(changePointBtn);
        btnPannel.add(delPointBtn);
        btnPannel.add(delAllPointsBtn);
        btnPannel.add(solveBtn);

        jPanel.add(labelPannel, BorderLayout.NORTH);
        jPanel.add(textPannel, BorderLayout.CENTER);
        jPanel.add(btnPannel, BorderLayout.SOUTH);

        myCanvas = new MyCanvas(WIDTH, HEIGHT);

        this.setTitle("Главное окно");
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(this.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(250, 150);
        this.getRootPane().setBorder(new LineBorder(Color.BLACK, 5));
        this.setSize(WIDTH, HEIGHT);
        this.setVisible(true);

        this.add(jPanel, BorderLayout.WEST);
        this.add(myCanvas, BorderLayout.EAST);
    }



    public static void main(String[] args) {
        GInterface gInterface = new GInterface();

        gInterface.geometry = new Geometry();
        TaskFrame taskFrame = new TaskFrame();
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

        Timer timer = new Timer(3000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                errorFrame.dispose();
            }
        });

        timer.start();
    }

    public String getFormatString(Double x, Double y, int index) {
        String line = "";
        int width_first = 0, width_second = 0;

        y = Math.round(y * 100.0) / 100.0;
        x = Math.round(x * 100.0) / 100.0;

        if (Math.abs(x) >= 10000 && Math.abs(y) >= 10000) {
            width_first += 10 - String.valueOf(index).length();
            width_second += 10;

            if (x < 0 && y < 0) {
                width_first--;
                width_second--;
            } else if (x < 0) {
                width_first--;
            } else if (y < 0) {
                width_second--;
            }

            line = String.format("%2s", index) + String.valueOf(new char[width_first]).replace('\0', ' ') +
                    String.format("%.2e", x) + String.valueOf(new char[width_second]).replace('\0', ' ') +
                    String.format("%.2e\n", y);
        }
        else if (Math.abs(x) >= 10000) {
            width_first += 10 - String.valueOf(index).length();
            width_second += 10;

            if (x < 0 && y < 0) {
                width_first--;
                width_second--;
            } else if (x < 0) {
                width_first--;
            } else if (y < 0) {
                width_second--;
            }

            line = String.format("%2s", index) + String.valueOf(new char[width_first]).replace('\0', ' ') +
                    String.format("%.2e", x) + String.valueOf(new char[width_second]).replace('\0', ' ') +
                    String.format("%.2f\n", y);
        }
        else if (Math.abs(y) >= 10000) {
            width_first += 10 - String.valueOf(index).length();
            width_second += 24 - String.valueOf(x).length() * 2;

            if (x < 0 && y < 0) {
                width_first--;
                width_second ++;
            } else if (x < 0) {
                width_first--;
                width_second += 2;
            } else if (y < 0) {
                width_second--;
            }

            line = String.format("%2s", index) + String.valueOf(new char[width_first]).replace('\0', ' ') +
                    String.format("%.2f", x) + String.valueOf(new char[width_second]).replace('\0', ' ') +
                    String.format("%.2e\n", y);
        }
        else {
            width_first += 10 - String.valueOf(index).length();
            width_second += 24 - String.valueOf(x).length() * 2;

            if (x < 0 && y < 0) {
                width_first--;
                width_second ++;
            } else if (x < 0) {
                width_first--;
                width_second += 2;
            } else if (y < 0) {
                width_second--;
            }

            line = String.format("%2s", index) + String.valueOf(new char[width_first]).replace('\0', ' ') +
                    String.format("%.2f", x) + String.valueOf(new char[width_second]).replace('\0', ' ') +
                    String.format("%.2f\n", y);
        }

        line = line.replaceAll(",", ".");
        return line;
    }

    public int UnfocusInterface(boolean flag) {
        this.addPointBtn.setEnabled(flag);
        this.delAllPointsBtn.setEnabled(flag);
        this.delPointBtn.setEnabled(flag);
        this.changePointBtn.setEnabled(flag);
        this.solveBtn.setEnabled(flag);

        return HIDE_ON_CLOSE;
    }


    public void addNewPoint() {
        JFrame frame = new JFrame();

        JLabel xLabel = new JLabel(" X");
        xLabel.setFont(new Font(xLabel.getName(), Font.BOLD, 30));
        xLabel.setPreferredSize(new Dimension(100, 100));

        JLabel yLabel = new JLabel(" Y");
        yLabel.setFont(new Font(xLabel.getName(), Font.BOLD, 30));
        yLabel.setPreferredSize(new Dimension(100, 100));


        JPanel xyPanel = new JPanel();
        xyPanel.setLayout(new GridLayout(2, 2, 10, 10));
        xyPanel.setPreferredSize(new Dimension(250, 250));
        xyPanel.setBorder(new LineBorder(Color.black, 2));

        inputX = new JTextArea();
        inputX.setLineWrap(true);
        inputX.setMargin(new Insets(10, 10, 10, 10));
        inputX.setFont(new Font(inputX.getName(), Font.BOLD, 30));

        inputY = new JTextArea();
        inputY.setFont(new Font(inputY.getName(), Font.BOLD, 30));
        inputY.setMargin(new Insets(10, 10, 10, 10));
        inputY.setLineWrap(true);

        xyPanel.add(xLabel);
        xyPanel.add(yLabel);
        xyPanel.add(inputX);
        xyPanel.add(inputY);

        JPanel butPanel = new JPanel();
        butPanel.setLayout(new FlowLayout());
        addButton = new JButton("Добавить координату");
        addButton.setFont(new Font(butPanel.getName(), Font.BOLD, 25));
        addButton.setPreferredSize(new Dimension(400, 100));
        addButton.setBorder(new LineBorder(Color.black, 4));
        addButton.addActionListener(this);
        butPanel.add(addButton);
        butPanel.setBorder(new LineBorder(Color.black, 2));

        frame.setTitle("Добавление новой точки");
        frame.setLayout(new BorderLayout(5, 5));
        frame.setResizable(false);
        frame.setLocation(350, 350);
        frame.getRootPane().setBorder(new LineBorder(Color.BLACK, 3));
        frame.setSize(400, 400);
        frame.setVisible(true);

        frame.add(xyPanel, BorderLayout.NORTH);
        frame.add(butPanel, BorderLayout.SOUTH);

        frame.setAlwaysOnTop(true);

        // Переопределяем нажатие на "выход"
        frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        WindowListener exitListener = new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                UnfocusInterface(true); // включаем остальной интерфейс
                frame.dispose();
            }
        };
        frame.addWindowListener(exitListener);

        UnfocusInterface(false); // отключаем остальной интерфейс при открытии
    }


    public void addPointToList(Double x, Double y) {
        this.geometry.addPoint(x, y);
        String line = getFormatString(x, y, this.geometry.countPoints);
        area.append(line);
    }

    public void getNewPoint() {
        Double x = 0.0, y = 0.0;
        try {
            x = Double.valueOf(inputX.getText());
            y = Double.valueOf(inputY.getText());
        } catch (NumberFormatException exception) {
            printError("Ошибка при вводе координаты точки. Повторите попытку.");
            return;
        }

        addPointToList(x, y);
    }



    public void changePoint() {
        JFrame changeFrame = new JFrame("Изменение точки");


        JTextArea nLabel = new JTextArea(" Ввведите номер изменяемой точки: ");
        nLabel.setLineWrap(true);
        nLabel.setWrapStyleWord(true);
        nLabel.setEditable(false);
        nLabel.setFont(new Font(nLabel.getName(), Font.BOLD, 20));
        nLabel.setPreferredSize(new Dimension(100, 80));

        numPoint = new JTextArea();
        numPoint.setLineWrap(true);
        numPoint.setMargin(new Insets(10, 10, 10, 10));
        numPoint.setFont(new Font(numPoint.getName(), Font.BOLD, 30));


        JLabel xLabel = new JLabel("Новая координата X");
        xLabel.setFont(new Font(xLabel.getName(), Font.BOLD, 20));
        xLabel.setPreferredSize(new Dimension(100, 100));


        JLabel yLabel = new JLabel("Новая координата Y");
        yLabel.setFont(new Font(yLabel.getName(), Font.BOLD, 20));
        yLabel.setPreferredSize(new Dimension(100, 100));


        JPanel xyPanel = new JPanel();
        xyPanel.setLayout(new GridLayout(3, 2, 10, 10));
        xyPanel.setPreferredSize(new Dimension(400, 250));


        newX = new JTextArea();
        newX.setLineWrap(true);
        newX.setMargin(new Insets(10, 10, 10, 10));
        newX.setFont(new Font(newX.getName(), Font.BOLD, 30));

        newY = new JTextArea();
        newY.setFont(new Font(newY.getName(), Font.BOLD, 30));
        newY.setMargin(new Insets(10, 10, 10, 10));
        newY.setLineWrap(true);


        xyPanel.add(nLabel);
        xyPanel.add(numPoint);
        xyPanel.add(xLabel);
        xyPanel.add(yLabel);
        xyPanel.add(newX);
        xyPanel.add(newY);

        JPanel butPanel = new JPanel();
        butPanel.setLayout(new FlowLayout());


        changeButton = new JButton("Изменить координату");
        changeButton.setFont(new Font(changeButton.getName(), Font.BOLD, 25));
        changeButton.setPreferredSize(new Dimension(400, 90));
        changeButton.setBorder(new LineBorder(Color.black, 4));
        changeButton.addActionListener(this);
        butPanel.add(changeButton);

        changeFrame.setLayout(new BorderLayout(5, 5));
        changeFrame.setResizable(false);
        changeFrame.setLocation(350, 350);
        changeFrame.getRootPane().setBorder(new LineBorder(Color.BLACK, 4));
        changeFrame.setSize(600, 400);
        changeFrame.setVisible(true);

        changeFrame.add(xyPanel, BorderLayout.NORTH);
        changeFrame.add(butPanel, BorderLayout.SOUTH);

        changeFrame.setAlwaysOnTop(true);

        // Переопределяем нажатие на "выход"
        changeFrame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        WindowListener exitListener = new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                UnfocusInterface(true); // включаем остальной интерфейс
                changeFrame.dispose();
            }
        };
        changeFrame.addWindowListener(exitListener);

        UnfocusInterface(false); // отключаем остальной интерфейс при открытии
    }

    public void changePointProcess() {
        int newNum;
        Double newXcoord, newYcoord;

        try {
            newNum = Integer.valueOf(numPoint.getText());

        } catch (NumberFormatException exception) {
            printError("Некорректный ввод номера точки. Номер должен быть целочисленным");
            return;
        }

        try {
            newXcoord = Double.valueOf(newX.getText());
            newYcoord = Double.valueOf(newY.getText());
        } catch (NumberFormatException exception) {
            printError("Некорректный ввод координат точки!");
            return;
        }

        String[] lines = area.getText().split("\n");

        if (newNum <= 0 || newNum > lines.length - 1) {
            printError("Невозможно изменить точку с данным номером. Точки с данным номером не существует!");
            return;
        }

        lines[newNum] = getFormatString(newXcoord, newYcoord, newNum);
        this.geometry.Points.get(newNum - 1).set(0, newXcoord);
        this.geometry.Points.get(newNum - 1).set(1, newYcoord);

        area.setText("");
        int i = 0;
        for (String line : lines) {
            if (i == newNum) {
                area.append(line);
            } else {
                area.append(line + "\n");
            }
            i++;
        }
    }


    public void delPoint() {
        JFrame changeFrame = new JFrame("Удаление точки");

        JTextArea nLabel = new JTextArea(" Ввведите номер удаляемой точки: ");
        nLabel.setLineWrap(true);
        nLabel.setWrapStyleWord(true);
        nLabel.setFont(new Font(nLabel.getName(), Font.BOLD, 20));
        nLabel.setPreferredSize(new Dimension(100, 80));
        nLabel.setEditable(false);
        nLabel.setBorder(new LineBorder( Color.BLACK, 2));

        numPoint = new JTextArea();
        numPoint.setLineWrap(true);
        numPoint.setPreferredSize(new Dimension(100, 100));
        numPoint.setBorder(new LineBorder(Color.BLACK, 2));
        numPoint.setMargin(new Insets(10, 10, 10, 10));
        numPoint.setFont(new Font(numPoint.getName(), Font.BOLD, 30));

        delButton = new JButton("Удалить точку");
        delButton.setFont(new Font(delPointBtn.getName(), Font.BOLD, 25));
        delButton.setPreferredSize(new Dimension(100, 50));
        delButton.setBorder(new LineBorder(Color.black, 2));
        delButton.addActionListener(this);


        changeFrame.setLayout(new BorderLayout());
        changeFrame.setResizable(false);
        changeFrame.setLocation(350, 350);
        changeFrame.getRootPane().setBorder(new LineBorder(Color.BLACK, 3));
        changeFrame.setSize(400, 400);
        changeFrame.setVisible(true);

        changeFrame.add(nLabel, BorderLayout.NORTH);
        changeFrame.add(numPoint, BorderLayout.CENTER);
        changeFrame.add(delButton, BorderLayout.SOUTH);

        changeFrame.setAlwaysOnTop(true);

        // Переопределяем нажатие на "выход"
        changeFrame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        WindowListener exitListener = new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                UnfocusInterface(true); // включаем остальной интерфейс
                changeFrame.dispose();
            }
        };
        changeFrame.addWindowListener(exitListener);

        UnfocusInterface(false); // отключаем остальной интерфейс при открытии
    }

    public void delButtonProcess() {
        int numDot;

        try {
            numDot = Integer.valueOf(numPoint.getText());
        } catch (NumberFormatException exception) {
            printError("Некорректный ввод номера точки! Повторите попытку!");
            return;
        }

        String[] lines = area.getText().split("\n");

        if (numDot <= 0 || numDot > lines.length - 1) {
            printError("Невозможно удалить точку с данным номером. Точки с данным номером не существует!");
            return;
        }

        area.setText(lines[0] + "\n");

        this.geometry.Points.remove(numDot - 1);

        if (this.geometry.xNewCoords.size() > 0) {
            this.geometry.xNewCoords.remove(numDot - 1);
            this.geometry.yNewCoords.remove(numDot - 1);
        }

        this.geometry.countPoints = 0;

        for (ArrayList<Double> arrayList : geometry.Points) {
            this.geometry.countPoints++;
            area.append(getFormatString(arrayList.get(0), arrayList.get(1), this.geometry.countPoints));
        }
    }


    public void delAllPointsBtn() {
        area.setText(" №          X                       Y\n");
        this.geometry.Points.clear();
        this.geometry.xNewCoords.clear();
        this.geometry.yNewCoords.clear();
        this.geometry.countPoints = 0;
        return;
    }


    public void displaySolveFrame() {
        JFrame solveFrame = new JFrame();

        solveArea = new JTextArea(5, 30);
        solveArea.setFont(new Font(solveArea.getName(), Font.BOLD, 22));
        solveArea.setMargin(new Insets(30, 30, 30, 30));
        solveArea.setForeground(Color.BLACK);
        solveArea.setWrapStyleWord(true);
        solveArea.setLineWrap(true);
        solveArea.setOpaque(false);
        solveArea.setEditable(false);
        solveArea.setFocusable(false);

        solveFrame.setTitle("Ответ");
        solveFrame.setResizable(false);
        solveFrame.setLocation(400, 400);
        solveFrame.setSize(600, 400);
        solveFrame.setVisible(true);
        solveFrame.add(solveArea);
    }


    public void drawSolve(int n1, int n2, int n3) {
        Double x1 = this.geometry.xNewCoords.get(0);
        Double y1 = this.geometry.yNewCoords.get(0);

        Double x2 = this.geometry.xNewCoords.get(1);
        Double y2 = this.geometry.yNewCoords.get(1);

        Double x3 = this.geometry.xNewCoords.get(2);
        Double y3 = this.geometry.yNewCoords.get(2);

        Double[] circle = this.geometry.getCircle(x1, y1, x2, y2, x3, y3);
        this.myCanvas.printCircle((int)Math.round(circle[0]), (int)Math.round(circle[1]), (int)Math.round(circle[2]), (int) Math.round(circle[2]), Color.green);
        this.myCanvas.printPoint(circle[0], circle[1], Color.green);

        this.myCanvas.printTriangle((int)Math.round(x1), (int)Math.round(y1), (int)Math.round(x2), (int)Math.round(y2),(int)Math.round(x3), (int)Math.round(y3));

        this.myCanvas.printPoint(this.geometry.xNewCoords.get(0), this.geometry.yNewCoords.get(0), Color.RED);

        if (this.geometry.xNewCoords.get(0).intValue() > circle[0] && this.geometry.yNewCoords.get(0).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n1 + 1), this.geometry.xNewCoords.get(0).intValue() + 10, this.geometry.yNewCoords.get(0).intValue() + 10, Color.black);
        } else if (this.geometry.xNewCoords.get(0).intValue() < circle[0] && this.geometry.yNewCoords.get(0).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n1 + 1), this.geometry.xNewCoords.get(0).intValue() - 20, this.geometry.yNewCoords.get(0).intValue() + 20, Color.black);
        } else if (this.geometry.xNewCoords.get(0).intValue() < circle[0] && this.geometry.yNewCoords.get(0).intValue() < circle[1]) {
            this.myCanvas.printString(String.valueOf(n1 + 1), this.geometry.xNewCoords.get(0).intValue() - 10, this.geometry.yNewCoords.get(0).intValue() - 10, Color.black);
        } else {
            this.myCanvas.printString(String.valueOf(n1 + 1), this.geometry.xNewCoords.get(0).intValue() + 10, this.geometry.yNewCoords.get(0).intValue() - 10, Color.black);
        }

        this.myCanvas.printPoint(this.geometry.xNewCoords.get(1), this.geometry.yNewCoords.get(1), Color.RED);

        if (this.geometry.xNewCoords.get(1).intValue() > circle[0] && this.geometry.yNewCoords.get(1).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n2 + 1), this.geometry.xNewCoords.get(1).intValue() + 10, this.geometry.yNewCoords.get(1).intValue() + 10, Color.black);
        } else if (this.geometry.xNewCoords.get(1).intValue() < circle[0] && this.geometry.yNewCoords.get(1).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n2 + 1), this.geometry.xNewCoords.get(1).intValue() - 20, this.geometry.yNewCoords.get(1).intValue() + 20, Color.black);
        } else if (this.geometry.xNewCoords.get(1).intValue() < circle[0] && this.geometry.yNewCoords.get(1).intValue() < circle[1]) {
            this.myCanvas.printString(String.valueOf(n2 + 1), this.geometry.xNewCoords.get(1).intValue() - 10, this.geometry.yNewCoords.get(1).intValue() - 10, Color.black);
        } else {
            this.myCanvas.printString(String.valueOf(n2 + 1), this.geometry.xNewCoords.get(1).intValue() + 10, this.geometry.yNewCoords.get(1).intValue() - 10, Color.black);
        }

        this.myCanvas.printPoint(this.geometry.xNewCoords.get(2), this.geometry.yNewCoords.get(2), Color.RED);

        if (this.geometry.xNewCoords.get(2).intValue() > circle[0] && this.geometry.yNewCoords.get(2).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n3 + 1), this.geometry.xNewCoords.get(2).intValue() + 10, this.geometry.yNewCoords.get(2).intValue() + 10, Color.black);
        } else if (this.geometry.xNewCoords.get(2).intValue() < circle[0] && this.geometry.yNewCoords.get(2).intValue() > circle[1]) {
            this.myCanvas.printString(String.valueOf(n3 + 1), this.geometry.xNewCoords.get(2).intValue() - 20, this.geometry.yNewCoords.get(2).intValue() + 20, Color.black);
        } else if (this.geometry.xNewCoords.get(2).intValue() < circle[0] && this.geometry.yNewCoords.get(2).intValue() < circle[1]) {
            this.myCanvas.printString(String.valueOf(n3 + 1), this.geometry.xNewCoords.get(2).intValue() - 10, this.geometry.yNewCoords.get(2).intValue() - 10, Color.black);
        } else {
            this.myCanvas.printString(String.valueOf(n3 + 1), this.geometry.xNewCoords.get(2).intValue() + 10, this.geometry.yNewCoords.get(2).intValue() - 10, Color.black);
        }
    }


    public void getScalePoints(Double[] answer) {
        Double[] circle = this.geometry.getCircle(answer[1], answer[2], answer[3], answer[4], answer[5], answer[6]);
        Double[] xCord = {answer[1], answer[3], answer[5]};
        Double[] yCord = {answer[2], answer[4], answer[6]};

        this.geometry.Rad = circle[2];

        minXValue = circle[0] - circle[2];
        minYValue = circle[1] - circle[2];

        maxXValue = circle[0] + circle[2];
        maxYValue = circle[1] + circle[2];

        k = CANVAS_WIDTH /  Math.abs(Math.max(Math.abs(maxXValue - minXValue), Math.abs(maxYValue - minYValue)));

        Double newX, newY;

        for (int i = 0; i < 3; i++) {
            newX = x0 + (xCord[i] - minXValue) * k;
            newY = y1 - (y0 + (yCord[i] - minYValue) * k);

            this.geometry.xNewCoords.add(i, newX);
            this.geometry.yNewCoords.add(i, newY);
        }
    }


    public void solve() {
        if (this.geometry.Points.size() < 3) {
            printError("Ошибка! Для решения задачи необходимо ввести как минимум три точки!");
            return;
        }
        this.myCanvas.clearCanvas();

        Double[] answer = this.geometry.getMaxDiff();

        if (answer[7].equals(-1.0)) {
            printError("Ошибка! Невозможно построить треугольник по заданным координатам. Точки не должны лежать на одной прямой!");
            return;
        }

        displaySolveFrame();

        BigDecimal bigDecimal1 = new BigDecimal(this.geometry.squareT);
        this.geometry.squareT =  bigDecimal1.setScale(6, RoundingMode.HALF_UP).doubleValue();
        BigDecimal bigDecimal2 = new BigDecimal(this.geometry.squareC);
        this.geometry.squareC =  bigDecimal2.setScale(6, RoundingMode.HALF_UP).doubleValue();

        BigDecimal bigDecimal3 = new BigDecimal(answer[0]);

        getScalePoints(answer);

        BigDecimal radDecimal = new BigDecimal(this.geometry.Rad);

        solveArea.setText("Площадь треугольника = " + this.geometry.squareT + "\nПлощадь описанного круга = " + this.geometry.squareC + "\n" +
        "\nРазность площадей (максимальная) = " + bigDecimal3.setScale(6, RoundingMode.HALF_UP).doubleValue()
                + "\n\nТочки : \n" + (answer[7].intValue() + 1) + " (" + answer[1] + "; " + answer[2] + ")" + "\n" +
                (answer[8].intValue() + 1) + " (" + answer[3] + "; " + answer[4] +")"+ "\n" +
                (answer[9].intValue() + 1) + " (" + answer[5] + "; " + answer[6] +")"+ "\n" +
                "Радиус окружности = " + radDecimal.setScale(6, RoundingMode.HALF_UP).doubleValue());


        drawSolve(answer[7].intValue(), answer[8].intValue(), answer[9].intValue());
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == addPointBtn) {
            addNewPoint();
        }

        else if (e.getSource() == addButton) {
            getNewPoint();
        }

        else if (e.getSource() == changePointBtn) {
            changePoint();
        }
        else if (e.getSource() == changeButton) {
            changePointProcess();
        }
        else if (e.getSource() == delPointBtn) {
            delPoint();
        }
        else if (e.getSource() == delButton) {
            delButtonProcess();
        }
        else if (e.getSource() == delAllPointsBtn) {
            delAllPointsBtn();
        }
        else if (e.getSource() == solveBtn) {
            solve();
        }
    }
}


class TaskFrame extends JFrame{
    TaskFrame() {
        JTextArea textArea = new JTextArea(5, 30);
        textArea.setForeground(Color.BLACK);
        textArea.setText("На плоскости дано множество точек.\nНайти такой треугольник с вершинами в этих точках," +
                " у которого разность площадей описанного круга и треугольника максимальна.");
        textArea.setWrapStyleWord(true);
        textArea.setLineWrap(true);
        textArea.setOpaque(false);
        textArea.setEditable(false);
        textArea.setFocusable(false);
        textArea.setFont(new Font(textArea.getName(), Font.ITALIC, 20));
        textArea.setMargin(new Insets(15, 15, 15, 15));

        this.setTitle("Условие задачи");
        this.setResizable(false);
        this.setLocation(400, 400);
        this.setSize(600, 400);
        this.setVisible(true);
        this.add(textArea);
    }
}





