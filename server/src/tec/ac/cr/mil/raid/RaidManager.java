package tec.ac.cr.mil.raid;
import tec.ac.cr.mil.logic.Holder;
import tec.ac.cr.mil.logic.Picture;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

public class RaidManager {

    private static int parityPosition = 4;
    private static String diskPath = "C:\\Users\\Kevin Cordero Zúñiga\\IdeaProjects\\MyInvincibleLibrary\\server\\src\\tec\\ac\\cr\\mil\\raid\\disks";

    /**
     * Write the bytes of an image in the disks
     * @param ImageBytes ByteArray of image´s bytes
     * @param ImageName Name of the image
     * @throws IOException In case doesn't exist the directory
     */
    public static void Write(byte[] ImageBytes, String ImageName) throws IOException {
        checkDisks();
        int length = ImageBytes.length;
        int fileSize = length/4;
        int fileCounter = 0;
        int fileTotal = 4;
        int currentDisk = 0;
        while (fileCounter < fileTotal){
            int begin = fileCounter * fileSize;
            int end = ((fileCounter + 1) * fileSize)+1;
            if (fileCounter == fileTotal - 1) end = length+1;
            byte[] partition = Arrays.copyOfRange(ImageBytes, begin, end-1);
            fillFile(partition, fileCounter, ImageName, currentDisk);
            if (currentDisk == 5) currentDisk = 0;
            currentDisk++;
            fileCounter++;
        }
        calcParity(fileSize, ImageName, parityPosition);

    }

    /**
     * Reads the bytes of an image from the dataBase
     * @param size Size in bytes of the image
     * @param Name Name of the image
     * @return ByteArray of the image
     * @throws IOException In case doesn't exist the directory
     */
    public static byte[] Read(int size, String Name) throws IOException {
        checkDisks();
        byte[] FileBytes = new byte[size];
        int stripSize = size/4;
        int currentDisk = 0;
        int totalPartitions = 4;
        int counter = 0;

        while (counter < totalPartitions){
            Path path = Paths.get(diskPath + "\\d" + currentDisk + "\\" + Name + counter + ".pdf");
            try {
                byte[] bArray = Files.readAllBytes(path);
                System.arraycopy(bArray, 0, FileBytes, (stripSize * counter), bArray.length);
                // reading content from byte array
            } catch (IOException e) {
                e.printStackTrace();
            }
            counter++;
            currentDisk++;
            if(currentDisk==5) currentDisk=0;
        }
        return FileBytes;
    }

    /**
     * Fill a File with the bytes of a strip and save it in the disk
     * @param byteFiles ByteArray with bytes of a strip
     * @param index Identifier of the file
     * @param fileName Name of the file
     * @param currentDisk Disk where the file will be saved
     */
    private static void fillFile(byte[] byteFiles, int index, String fileName, int currentDisk){
        File file = new File(diskPath + "\\d" + currentDisk + "\\" + fileName + index + ".pdf");
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(byteFiles);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }

    /**
     * Calculate the parity file of an image
     * @param size Size of the byte array
     * @param fileName Name of the file
     * @param disk Disk where the file will be saved
     */
    private static void calcParity(int size, String fileName, int disk){
        File file = new File(diskPath + "\\d" + parityPosition + "\\"  + fileName + "Parity.pdf");

        byte[] parity = calcByteArrayParity(size, fileName, disk);
        try (FileOutputStream newFile = new FileOutputStream(file)) {
            newFile.write(parity);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }

    /**
     * Makes the addition of the parity.
     * @param size Size of the byte array
     * @param fileName Name of the file
     * @param disk Disk where the file will be saved
     * @return result of the addition
     */
    private static byte[] calcByteArrayParity(int size, String fileName, int disk){
        byte[] Response = new byte[size];
        byte[][] BytesMatrix = calcByteMatrix(size, fileName, disk);
        int i = 0;
        int y = 0;
        int sum = 0;
        while(i<size){
            while (y<4){
                sum = sum + BytesMatrix[y][i];
                y++;
            }
            Response[i] = (byte)sum;
            y++;
            if(y==5)y=0;
            i++;
            sum = 0;
        }



        return Response;
    }

    /**
     * Unify the strip in a matrix
     * @param size Size of the byte Array
     * @param fileName Name of the file
     * @param disk Disk where the file will be saved
     * @return Matrix of strip
     */
    private static byte[][] calcByteMatrix (int size, String fileName, int disk){
        byte[][] Response = new byte[4][size];
        int counter = 0;
        if(counter == parityPosition)counter++;
        int index = 0;
        while (counter<4 && counter!= parityPosition){
            Path path = Paths.get(diskPath + "\\d" + counter + "\\" + fileName +counter + ".pdf");
            try {
                byte[] bArray = Files.readAllBytes(path);
                Response[index]=bArray;
                index++;
                // reading content from byte array
            } catch (IOException e) {
                e.printStackTrace();
            }
            counter++;

        }
        return Response;
    }

    /**
     * Checks the state of the disk thanks to security files
     * @throws IOException In case doesn't exist the directory
     */
    private static void checkDisks() throws IOException {
        int currentDisk = 0;
        Path path;

        while (currentDisk < 5){
            path = Paths.get( diskPath + "\\d" + currentDisk + "\\sec.pdf");
            try {
                Files.readAllBytes(path);
            } catch (IOException e) {
                System.out.println("Disk "+currentDisk+" needs recovery");
                Recovery(currentDisk);
            }
            currentDisk++;
        }
    }

    /**
     * Recover the disk with missing data
     * @param diskToRecover id of the disk with missing data
     * @throws IOException In case doesn't exist the directory
     */
    private static void Recovery(int diskToRecover) throws IOException {
        if(diskToRecover == 4){
            recoverParity();
        }else{
            recoverDisk(diskToRecover);
        }
    }

    /**
     * Makes the math part of the data restoration
     * @param diskToRecover id of the disk with missing data
     * @throws IOException In case doesn't exist the directory
     */
    private static void recoverDisk(int diskToRecover) throws IOException {
        Path path = Paths.get(diskPath + "\\d" + diskToRecover);
        createSecurityFile(path);
        ArrayList<Picture> Images = Holder.pictureArrayList;
        for (Picture image:Images) {
            int fileSize = image.getSize()/4;
            byte[] parityBytes = loadFile(diskPath+"\\d4\\"+image.getName()+"Parity.pdf");
            byte[] bytesToRecover = new byte[fileSize];
            byte[][] recoverMatrix = createRecoverMatrix(diskToRecover, image.getName(), image.getSize()/4);
            for(int i=0; i<fileSize; i++){
                byte ecuation = (byte)(parityBytes[i]-recoverMatrix[0][i]-recoverMatrix[1][i]-recoverMatrix[2][i]);
                bytesToRecover[i] = ecuation;
            }
            fillFile(bytesToRecover,diskToRecover,image.getName(),diskToRecover);
        }
    }

    /**
     * Unify the strip in a matrix
     * @param diskToRecover id of the disk with missing data
     * @param imageName Name of the image that will be recovered
     * @param fileSize Size of the image that will be recovered
     * @return Matrix of strips
     */
    private static byte[][] createRecoverMatrix(int diskToRecover, String imageName, int fileSize){
        byte[][] Response = new byte[3][fileSize];
        int matrixCounter = 0;

        for(int i=0; i<4; i++){
            if(i==diskToRecover)i++;
            Path path = Paths.get(diskPath + "\\d" + i + "\\" + imageName +i + ".pdf");
            try {
                byte[] bArray = Files.readAllBytes(path);
                Response[matrixCounter]=bArray;
                // reading content from byte array
            } catch (IOException e) {
                e.printStackTrace();
            }
            matrixCounter++;
        }
        return Response;
    }

    /**
     * Recover the parity of the image, in case it lose
     */
    private static void recoverParity() {
        ArrayList<Picture> Images = Holder.pictureArrayList;
        Path path = Paths.get(diskPath + "\\d4\\");
        createSecurityFile(path);
        for (Picture Image : Images) {
            calcParity(Image.getSize() / 4, Image.getName(), 4);
        }
    }

    /**
     * Create Security file, in case it´s miss
     * @param path Directory where it will be created
     */
    private static void createSecurityFile(Path path){
        File file = new File(String.valueOf(path) + "\\sec.pdf");
        byte[] bytes = new byte[1];
        bytes[0] = 1;
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Delete an image from the dataBase
     * @param imageName Name of image to be deleted
     */
    public static void deleteImage(String imageName){
        int currentDisk = 0;
        try {
            while (currentDisk < 4) {
                File file = new File(diskPath + "\\d" + currentDisk + "\\" + imageName + currentDisk + ".pdf");
                file.delete();
                currentDisk++;
            }
            File file = new File(diskPath + "\\d" + currentDisk + "\\" + imageName + "Parity.pdf");
            file.delete();
        }catch (Exception e){
            System.out.println("File not Found");
            e.printStackTrace();
        }
    }

    /**
     * Reads all the bytes from a .pdf file
     * @param stream .pdf File
     * @return Bytes of the file
     * @throws IOException IOException In case doesn't exist the directory
     */
    private static byte[] readFully(InputStream stream) throws IOException
    {
        byte[] buffer = new byte[8192];
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        int bytesRead;
        while ((bytesRead = stream.read(buffer)) != -1)
        {
            baos.write(buffer, 0, bytesRead);
        }
        return baos.toByteArray();
    }

    /**
     * Loads the bytes of the file to be read
     * @param sourcePath Path of the file
     * @return bytes of the file
     * @throws IOException IOException In case doesn't exist the directory
     */
    private static byte[] loadFile(String sourcePath) throws IOException
    {
        InputStream inputStream = null;
        try
        {
            inputStream = new FileInputStream(sourcePath);
            return readFully(inputStream);
        }
        finally
        {
            if (inputStream != null)
            {
                inputStream.close();
            }
        }
    }

}