import javax.swing.*;
import java.awt.*;

public class Paintbrush {

    private static final Color ALIZARIN_CRIMSON = new Color(78, 21, 0);
    private static final Color BRIGHT_RED = new Color(219, 0 ,0);
    private static final Color CADMIUM_YELLOW = new Color(255, 236, 0);
    private static final Color DARK_SIENNA = new Color(95, 46, 31);
    private static final Color INDIAN_YELLOW = new Color(255, 184, 0);
    private static final Color MIDNIGHT_BLACK = new Color(0, 0, 0);
    private static final Color PHTHALO_BLUE = new Color(12, 0, 64);
    private static final Color PHTHALO_GREEN = new Color(16, 46, 60);
    private static final Color PRUSSIAN_BLUE = new Color(2, 30, 68);
    private static final Color SAP_GREEN = new Color(10, 52, 16);
    private static final Color TITANIUM_WHITE = new Color(255, 255, 255);
    private static final Color VAN_DYKE_BROWN = new Color(34, 27, 21);
    private static final Color YELLOW_OCHRE = new Color(199, 155, 0);

    private Graphics g;

    public Paintbrush(Graphics graphics) {
        g = graphics;
    }

    public void drawSky(){
        // make a light blue sky
        g.setColor(new Color(157, 233, 245));
        g.fillRect(0, 0,900, 220);
        // with a yellow sun
        g.setColor(Color.yellow);
        g.fillOval(680, 30, 60, 60);
    }

    public void drawMountains() {
        //draw a mountain
        g.setColor(VAN_DYKE_BROWN);
        Polygon triangle = new Polygon();
        triangle.addPoint(15, 450); // bottom-left
        triangle.addPoint(390, 60); // top
        triangle.addPoint(550, 450); // bottom-right
        g.fillPolygon(triangle);

        Color mountainMix = blend(VAN_DYKE_BROWN, YELLOW_OCHRE, 0.15f);
        g.setColor(mountainMix);
        Polygon jagged = new Polygon();
        jagged.addPoint(280, 445);
        jagged.addPoint(435, 170);
        jagged.addPoint(475, 280);
        jagged.addPoint(580, 120);
        jagged.addPoint(755, 520);
        g.fillPolygon(jagged);
    }

    private Color blend(Color c1, Color c2, float ratio) {
        if (ratio > 1f) ratio = 1f;
        else if (ratio < 0f) ratio = 0f;
        float iRatio = 1.0f - ratio;

        int i1 = c1.getRGB();
        int i2 = c2.getRGB();

        int a1 = (i1 >> 24 & 0xff);
        int r1 = ((i1 & 0xff0000) >> 16);
        int g1 = ((i1 & 0xff00) >> 8);
        int b1 = (i1 & 0xff);

        int a2 = (i2 >> 24 & 0xff);
        int r2 = ((i2 & 0xff0000) >> 16);
        int g2 = ((i2 & 0xff00) >> 8);
        int b2 = (i2 & 0xff);

        int a = (int)((a1 * iRatio) + (a2 * ratio));
        int r = (int)((r1 * iRatio) + (r2 * ratio));
        int g = (int)((g1 * iRatio) + (g2 * ratio));
        int b = (int)((b1 * iRatio) + (b2 * ratio));

        return new Color( a << 24 | r << 16 | g << 8 | b );
    }
}
