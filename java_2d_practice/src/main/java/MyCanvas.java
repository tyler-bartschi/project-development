import javax.swing.*;
import java.awt.*;

public class MyCanvas extends JPanel {
    private static final long serialVersionUID = 1L;

    public MyCanvas() {
        // set the canvas size
        setPreferredSize(new Dimension(900, 600));
        // set the canvas background color
        setBackground(Color.white);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // create a paintbrush object
        Paintbrush myBrush = new Paintbrush(g);
        // draw the different graphics that make up our painting
        myBrush.drawSky();
        myBrush.drawMountains();
    }
}
