package tec.ac.cr.mil.raid;

import java.io.IOException;
import java.util.Arrays;

public class RaidFacade {

    /**
     * Adds an image to the Raid System
     * @param imageString String of bytes
     * @param name name of the Image
     * @throws IOException In case doesn't exist the directory
     */
    public static void addImage(String imageString, String name) throws IOException {
        byte[] bytes = imageString.getBytes();
        RaidManager.Write(bytes, name);
    }

    /**
     * Delete a Image from the raid
     * @param imageName Name of image erase.
     */
    public static void deleteImage(String imageName){
        RaidManager.deleteImage(imageName);
    }

    /**
     * Reads an image from the raid
     * @param imageSize size of the image to be read
     * @param imageName name of the image to be read
     * @return string with the data of the image
     * @throws IOException in case of an error
     */
    public static String readImage(int imageSize, String imageName) throws IOException {
        byte[] bytes = RaidManager.Read(imageSize, imageName);
        String imageString = new String(bytes);
        return imageString;
    }

}
