import java.awt.*;
import java.util.List;

public class MyCanvas extends Canvas {
    private int WIDTH;
    private int HEIGHT;
    private final int CenterX = 420;
    private final int CenterY = 376;

    Geometry geom;

    MyCanvas(int parentWidth, int parentHeight) {
        this.WIDTH = parentWidth / 3 * 2;
        this.HEIGHT = parentHeight;
        this.setPreferredSize(new Dimension(WIDTH, HEIGHT));
        this.setBackground(Color.white);

        geom = new Geometry();
    }

    public void printAll(Geometry geometry) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setColor(Color.black);
        graphics2D.setStroke(new BasicStroke(2));

        // center point
        printPoint(Double.valueOf(CenterX), Double.valueOf(CenterY), Color.red, 8);
        printString("420;376", CenterX, CenterY, Color.green,14);

        printHouse(geometry.House);
        printWindow(geometry.Window);
        printDoor(geometry.Door);
        printSmallWindow(geometry.SmallWindow);
        printCrossSmallWindow(geometry.CrossSmallWindow);
        printRombDoor(geometry.RombDoor);
        printCrossWindow(geometry.CrossWindow);
    }



    public void printPoint(Double x, Double y, Color color, int width) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setColor(color);

        Double r = width / 2.0;

        graphics2D.fillOval((int) Math.round(x - r), (int) Math.round(y - r), width, width);
    }


    public void printString(String string, int x, int y, Color color, int size) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();

        graphics2D.setStroke(new BasicStroke(5));
        graphics2D.setColor(color);

        graphics2D.setFont(new Font(Font.SANS_SERIF, Font.BOLD, size));
        graphics2D.drawString(string, x, y);
    }



    public void printGraph(Graphics2D graphics2D) {
        graphics2D.setStroke(new BasicStroke(5));
        graphics2D.drawLine(10, 2, 10, HEIGHT);
    }


    public void printBasePicture(Graphics2D graphics2D) {
        graphics2D.setStroke(new BasicStroke(2));

        // center point
        printPoint(Double.valueOf(CenterX), Double.valueOf(CenterY), Color.red, 8);
        printString("420;376", CenterX, CenterY, Color.green,14);

        printHouse(this.geom.getHouse());
        printWindow(this.geom.getWindow());
        printDoor(this.geom.getDoor(50.0, 80.0));
        printSmallWindow(this.geom.getSmallWindow(35.0, 35.0));
        printCrossSmallWindow(this.geom.getSmallWindowCross());
        printRombDoor(this.geom.getRombDoor());
        printCrossWindow(this.geom.getCrossWindow());
    }

    public void printHouse(List<List<Double>> house) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.drawLine(house.get(0).get(0).intValue(), house.get(0).get(1).intValue(), house.get(1).get(0).intValue(), house.get(1).get(1).intValue());
        graphics2D.drawLine(house.get(1).get(0).intValue(), house.get(1).get(1).intValue(), house.get(2).get(0).intValue(), house.get(2).get(1).intValue());
        graphics2D.drawLine(house.get(2).get(0).intValue(), house.get(2).get(1).intValue(), house.get(3).get(0).intValue(), house.get(3).get(1).intValue());
        graphics2D.drawLine(house.get(3).get(0).intValue(), house.get(3).get(1).intValue(), house.get(4).get(0).intValue(), house.get(4).get(1).intValue());
        graphics2D.drawLine(house.get(4).get(0).intValue(), house.get(4).get(1).intValue(), house.get(0).get(0).intValue(), house.get(0).get(1).intValue());
        graphics2D.drawLine(house.get(4).get(0).intValue(), house.get(4).get(1).intValue(), house.get(1).get(0).intValue(), house.get(1).get(1).intValue());
    }

    public void printWindow(List<List<Double>> window) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.drawLine(window.get(0).get(0).intValue(), window.get(0).get(1).intValue(), window.get(1).get(0).intValue(), window.get(1).get(1).intValue());
        graphics2D.drawLine(window.get(1).get(0).intValue(), window.get(1).get(1).intValue(), window.get(2).get(0).intValue(), window.get(2).get(1).intValue());
        graphics2D.drawLine(window.get(2).get(0).intValue(), window.get(2).get(1).intValue(), window.get(3).get(0).intValue(), window.get(3).get(1).intValue());
        graphics2D.drawLine(window.get(3).get(0).intValue(), window.get(3).get(1).intValue(), window.get(0).get(0).intValue(), window.get(0).get(1).intValue());
    }

    public void printDoor(List<List<Double>> door) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        for (int i = 0; i < door.size() - 1; i++) {
            graphics2D.drawLine(door.get(i).get(0).intValue(), door.get(i).get(1).intValue(), door.get(i + 1).get(0).intValue(), door.get(i + 1).get(1).intValue());
        }
    }

    public void printSmallWindow(List<List<Double>> smallWindow) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        for (int i = 0; i < smallWindow.size() - 1; i++) {
            graphics2D.drawLine(smallWindow.get(i).get(0).intValue(), smallWindow.get(i).get(1).intValue(), smallWindow.get(i + 1).get(0).intValue(), smallWindow.get(i + 1).get(1).intValue());
        }
    }

    public void printCrossSmallWindow(List<List<Double>> lines) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.drawLine(lines.get(0).get(0).intValue(), lines.get(0).get(1).intValue(), lines.get(1).get(0).intValue(), lines.get(1).get(1).intValue());
        graphics2D.drawLine(lines.get(2).get(0).intValue(), lines.get(2).get(1).intValue(), lines.get(3).get(0).intValue(), lines.get(3).get(1).intValue());
    }

    public void printRombDoor(List<List<Double>> lines) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.drawLine(lines.get(0).get(0).intValue(), lines.get(0).get(1).intValue(), lines.get(1).get(0).intValue(), lines.get(1).get(1).intValue());
        graphics2D.drawLine(lines.get(2).get(0).intValue(), lines.get(2).get(1).intValue(), lines.get(3).get(0).intValue(), lines.get(3).get(1).intValue());

        graphics2D.drawLine(lines.get(0).get(0).intValue(), lines.get(0).get(1).intValue(), lines.get(2).get(0).intValue(), lines.get(2).get(1).intValue());
        graphics2D.drawLine(lines.get(1).get(0).intValue(), lines.get(1).get(1).intValue(), lines.get(2).get(0).intValue(), lines.get(2).get(1).intValue());

        graphics2D.drawLine(lines.get(0).get(0).intValue(), lines.get(0).get(1).intValue(), lines.get(3).get(0).intValue(), lines.get(3).get(1).intValue());
        graphics2D.drawLine(lines.get(1).get(0).intValue(), lines.get(1).get(1).intValue(), lines.get(3).get(0).intValue(), lines.get(3).get(1).intValue());
    }


    public void printCrossWindow(List<List<Double>> lines) {
        Graphics2D graphics2D = (Graphics2D) this.getGraphics();
        graphics2D.setStroke(new BasicStroke(2));

        graphics2D.drawLine(lines.get(0).get(0).intValue(), lines.get(0).get(1).intValue(), lines.get(1).get(0).intValue(), lines.get(1).get(1).intValue());
        graphics2D.drawLine(lines.get(2).get(0).intValue(), lines.get(2).get(1).intValue(), lines.get(3).get(0).intValue(), lines.get(3).get(1).intValue());
    }

    public void clearCanvas() {
        Graphics2D graphics2D =  (Graphics2D) this.getGraphics();
        graphics2D.setColor(Color.WHITE);
        graphics2D.fillRect(13, 0, WIDTH, HEIGHT);
    }


    public void paint(Graphics graphics) {
        Graphics2D graphics2D = (Graphics2D) graphics;
        printGraph(graphics2D);
        printBasePicture(graphics2D);
    }
}