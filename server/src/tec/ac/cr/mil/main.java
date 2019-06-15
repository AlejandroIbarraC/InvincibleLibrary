package tec.ac.cr.mil;

import tec.ac.cr.mil.logic.DatabaseFacace;
import tec.ac.cr.mil.logic.Picture;
import tec.ac.cr.mil.raid.RaidManager;
import tec.ac.cr.mil.ml.ObjectRecognizer;

import javax.xml.crypto.Data;
import java.io.File;
import java.io.IOException;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

public class main {

    public static void main(String[] args) throws IOException {

        // RAID Stuff:

        //BufferedImage bImage = ImageIO.read(new File("C:\\Users\\ramir\\Pictures\\prueba.jpeg"));
        //ByteArrayOutputStream bos = new ByteArrayOutputStream();
        //ImageIO.write(bImage, "jpeg", bos);
        //byte [] data = bos.toByteArray();
        //RaidManager.Write(data,"prueba");
       // byte[] response = RaidManager.Read(92086, "prueba");
        //System.out.println(data[90085]);
       /// System.out.println(response[9]);

        // Object recognition using Machine Learning:


    }

}
