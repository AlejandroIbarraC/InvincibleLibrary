package tec.ac.cr.mil.raid;

import java.io.IOException;
import java.util.Arrays;

public class RaidFacade {

    /**
     * Adds an image to Raid System and to database
     * @param imageString String of bytes
     * @param name name of the Image
     * @throws IOException In case doesn't exist the directory
     */
    public static void addImage(String imageString, String name) throws IOException {
        byte[] bytes = imageString.getBytes();
        RaidManager.Write(bytes, name);
    }

    /**
     * Delete a Image from dataBase
     * @param imageName Name of image erase.
     */
    public static void deleteImage(String imageName){
        RaidManager.deleteImage(imageName);
    }

    public static String readImage(int imageSize, String imageName) throws IOException {
        byte[] bytes = RaidManager.Read(imageSize, imageName);
        String imageString = new String(bytes);
        return imageString;
    }

}
