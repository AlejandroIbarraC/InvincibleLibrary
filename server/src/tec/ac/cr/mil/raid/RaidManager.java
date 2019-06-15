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
    private static String diskPath = "C:\\Users\\ramir\\IdeaProjects\\MyInvincibleLibrary\\server\\src\\tec\\ac\\cr\\mil\\raid\\disks";

    public static void Write(byte[] ImageBytes, String ImageName) throws IOException {
        checkDisks();
        int length = ImageBytes.length;
        int fileSize = length/4;
        int fileCounter = 0;
        int fileTotal = length/fileSize;
        int currentDisk = 0;
        while (fileCounter < fileTotal){
            int begin = fileCounter * fileSize;
            int end = (fileCounter + 1) * fileSize;
            if (fileCounter != 0) end++;
            if (fileCounter == fileTotal - 1) end = length;
            byte[] partition = Arrays.copyOfRange(ImageBytes, begin, end);
            fillFile(partition, fileCounter, ImageName, currentDisk);
            if (currentDisk == 5) currentDisk = 0;
            currentDisk++;
            fileCounter++;
        }
        calcParity(fileSize, ImageName, parityPosition);

    }

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

    public static void Seek() throws IOException {
        checkDisks();
    }

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
        }



        return Response;
    }

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

    public static void checkDisks() throws IOException {
        int currentDisk = 0;
        Path path;

        while (currentDisk < 5){
            path = Paths.get( diskPath + "\\d" + currentDisk + "\\sec.pdf");
            try {
                Files.readAllBytes(path);
            } catch (IOException e) {
                System.out.println("Needs Recovery");
                Recovery(currentDisk);
            }
            currentDisk++;
        }
    }

    private static void Recovery(int diskToRecover) throws IOException {
        if(diskToRecover == 4){
            recoverParity();
        }else{
            recoverDisk(diskToRecover);
        }
    }

    private static void recoverDisk(int diskToRecover){
        Path path = Paths.get(diskPath + "\\d" + diskToRecover);
        createSecurityFile(path);
    }

    private static void recoverParity() {
        ArrayList<Picture> Images = new ArrayList<>();
        Path path = Paths.get(diskPath + "\\d4\\");
        createSecurityFile(path);
        for (Picture Image : Images) {
            calcParity(Image.getSize() / 4, Image.getName(), 4);
        }
    }

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

    private static void createParityFillRecovery(byte[] bytes, String fileName){
        File file = new File(diskPath + "\\d4\\"  + fileName + "Parity.pdf");

        try (FileOutputStream newFile = new FileOutputStream(file)) {
            newFile.write(bytes);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }

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