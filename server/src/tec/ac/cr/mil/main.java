package tec.ac.cr.mil;

import tec.ac.cr.mil.RaidLibray.RaidManager;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

public class main {

    public static void main(String[] args) throws IOException {
        BufferedImage bImage = ImageIO.read(new File("C:\\Users\\ramir\\Pictures\\prueba.jpeg"));
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ImageIO.write(bImage, "jpeg", bos);
        byte [] data = bos.toByteArray();
   //     RaidManager.Write(data,"prueba");
        byte[] response = RaidManager.Read(data.length, "prueba");
        System.out.println(data[90085]);
        System.out.println(response[90085]);
    }

}
