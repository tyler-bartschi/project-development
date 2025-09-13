import javax.swing.*;

public class App {
    public static void main(String[] args) {
        JFrame window = new JFrame("Art");
        // when we close the window, stop the app
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        MyCanvas canvas = new MyCanvas();
        // can set canvas.setPreferredSize() here
        window.add(canvas);

        // fit the window size around the components (our canvas)
        window.pack();
        // don't allow the user to resize the window
        window.setResizable(false);
        // open window in the center of the screen
        window.setLocationRelativeTo(null);
        // display the window
        window.setVisible(true);
    }
}
