package tec.ac.cr.mil.RaidLibray;

import java.io.IOException;
import java.util.Arrays;

public class RaidFacade {
    public static void addImage(String imageString, String name) throws IOException {
        byte[] bytes = imageString.getBytes();
        RaidManager.Write(bytes, name);
        //Add to DataBase
    }
    public static void deleteImage(String imageName){
        RaidManager.deleteImage(imageName);
        //Delete dataBase
    }
    public static void readImage(int imageSize, String imageName){
        byte[] bytes = RaidManager.Read(imageSize, imageName);
        String imageString = Arrays.toString(bytes);
    }
    public static void readAllImages(){
        //recursive method
    }
    public static void deleteAllImages(){
        //recursive method
    }
}
