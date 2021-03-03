import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseMotionListener;

@SuppressWarnings("serial")
public class win extends JPanel {

    private Point lastPoint;

    public win() {
        addMouseListener(new MouseAdapter() {
            public void mousePassed(MouseEvent e) {
                lastPoint = new Point(e.getX(), e.getY());

            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent event) {
                Graphics g = getGraphics();
//                g.draw3DRect(30, 30, 30, 30, true);
                g.drawLine(lastPoint.x, lastPoint.y, event.getX(), event.getY());
                g.dispose();
            }
        });
    }


    public static void main(String[] args) {
        JFrame frame = new JFrame("GGGGG");
        frame.getContentPane().add(new win(), BorderLayout.CENTER);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setVisible(true);
    }




}
