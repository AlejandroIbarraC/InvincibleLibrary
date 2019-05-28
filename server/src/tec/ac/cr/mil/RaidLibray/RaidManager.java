package tec.ac.cr.mil.RaidLibray;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;

public class RaidManager {
    public static void Write(byte[] ImageBytes, String ImageName) throws IOException {
        int fileSize = 10000;
        int length = ImageBytes.length;
        int fileCounter = 0;
        int fileTotal = length/fileSize;
        int currentDisk = 0;
        while (fileCounter < fileTotal){
            int begin = fileCounter*fileSize;
            int end = (fileCounter+1)*fileSize;

            if(fileCounter != 0) end++;
            if(fileCounter == fileTotal-1) end = length;

            byte[] partition = Arrays.copyOfRange(ImageBytes, begin, end);

            fillFile(partition, fileCounter, ImageName, currentDisk);

            fileCounter++;

            currentDisk++;
            if (currentDisk == 5) currentDisk = 0;
        }


    }
    public static byte[] Read(int size, String Name){
        byte[] FileBytes = new byte[size];
        int currentDisk = 0;
        int totalPartitions = size/10000;
        int counter = 0;

        while (counter < totalPartitions){
            Path path = Paths.get("."+File.separator+"server"+File.separator+"src"+
                    File.separator+"tec"+File.separator+"ac"+File.separator+"cr"
                    +File.separator+"mil"+File.separator+"RaidLibray"+File.separator+
                    "Disks"+File.separator+"d"+currentDisk+File.separator+Name+counter+".pdf");
            try {
                byte[] bArray = Files.readAllBytes(path);
                System.arraycopy(bArray, 0, FileBytes, (10000 * counter), bArray.length);
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

    public static void Seek(){
    }


    private static void fillFile(byte[] byteFiles, int index, String fileName, int currentDisk){
        File file = new File("."+File.separator+"server"+File.separator+
                "src"+File.separator+"tec"+File.separator+"ac+File.pathSeparator"+File.separator+
                "cr"+File.separator+"mil"+File.separator+"RaidLibray"+File.separator+"Disks"+File.separator+
                "d"+currentDisk+File.separator+fileName+index+".pdf");
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(byteFiles);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }

}