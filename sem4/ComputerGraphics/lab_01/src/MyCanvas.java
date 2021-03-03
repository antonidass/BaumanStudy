import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.ColorModel;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class MyCanvas extends Canvas {
    private int WIDTH;
    private int HEIGHT;

    MyCanvas(int parentWidth, int parentHeight) {
        this.WIDTH = parentWidth / 3 * 2;
        this.HEIGHT = parentHeight;
        this.setPreferredSize(new Dimension(WIDTH, HEIGHT));
        this.setBackground(Color.white);
    }


    public void printPoint(Double x, Double y, Color color) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setColor(color);

        graphics2D.fillOval((int)Math.floor(x)-8, (int)Math.floor(y)-8, 14,14);
    }


    public void printString(String string, int x, int y, Color color) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();

        graphics2D.setStroke(new BasicStroke(5));
        graphics2D.setColor(color);

        int newFontSize = (int) (graphics2D.getFont().getSize() * 2);

        graphics2D.setFont(new Font(Font.SANS_SERIF, Font.BOLD, newFontSize));
        graphics2D.drawString(string, x, y);
    }


    public void printTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(4));
        graphics2D.setColor(Color.cyan);
        graphics2D.drawLine(x1, y1, x2, y2);
        graphics2D.drawLine(x1, y1, x3, y3);
        graphics2D.drawLine(x3, y3, x2, y2);
    }


    public void printCircle(int x, int y, int width, int height, Color color) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();

        x = x - width;
        y = y - height;

        graphics2D.setStroke(new BasicStroke(5));
        graphics2D.setColor(color);

        graphics2D.drawOval(x, y, width * 2, height * 2);
    }


    public void printGraph(Graphics2D graphics2D) {
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.setStroke(new BasicStroke(5));
        graphics2D.drawLine(10, 2, 10, HEIGHT);

        graphics2D.setStroke(new BasicStroke(5));
    }


    public void clearCanvas() {
        Graphics2D graphics2D =  (Graphics2D) this.getGraphics();
        graphics2D.setColor(Color.WHITE);
        graphics2D.fillRect(13, 0, WIDTH, HEIGHT);
    }


    public void paint(Graphics graphics) {
        Graphics2D graphics2D = (Graphics2D) graphics;
        printGraph(graphics2D);
    }
}