package tec.ac.cr.mil.raid;

import java.io.IOException;
import java.util.Arrays;

public class RaidFacade {

    public static void addImage(String imageString, String name) throws IOException {
        byte[] bytes = imageString.getBytes();
        RaidManager.Write(bytes, name);
    }

    public static void deleteImage(String imageName){
        RaidManager.deleteImage(imageName);
    }

    public static String readImage(int imageSize, String imageName){
        byte[] bytes = RaidManager.Read(imageSize, imageName);
        String imageString = new String(bytes);
        return imageString;
    }

    public static void readAllImages(){
        //recursive method
    }

    public static void deleteAllImages(){
        //recursive method
    }
}
