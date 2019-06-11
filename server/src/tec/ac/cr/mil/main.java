package tec.ac.cr.mil;

import org.tensorflow.Tensor;
import tec.ac.cr.mil.RaidLibray.RaidManager;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class main {

    public static void main(String[] args) throws IOException {
        //BufferedImage bImage = ImageIO.read(new File("C:\\Users\\ramir\\Pictures\\prueba.jpeg"));
        //ByteArrayOutputStream bos = new ByteArrayOutputStream();
        //ImageIO.write(bImage, "jpeg", bos);
        //byte [] data = bos.toByteArray();
        //RaidManager.Write(data,"prueba");
        byte[] response = RaidManager.Read(92086, "prueba");
        //System.out.println(data[90085]);
        System.out.println(response[9]);

        // Object recognition using Machine Learning

        ObjectRecognizer r = new ObjectRecognizer();
        File loadedImg = new File( "." + File.separator + "server" +
                File.separator + "src" + File.separator + "tec" +
                File.separator + "ac" + File.separator + "cr" +
                File.separator + "mil" + File.separator + "resources" +
                File.separator + "apple.jpeg");
        r.recognize(loadedImg);

    }

}
