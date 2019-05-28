package tec.ac.cr.mil.RaidLibray;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
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
    public static byte[] Read(int size){
        byte[] FileBytes = new byte[size];

        return FileBytes;
    }
    public static void Seek(){
    }


    private static void fillFile(byte[] byteFiles, int index, String fileName, int currentDisk) throws IOException {
        createFile(index, fileName, currentDisk);
        File file = new File("C:\\Users\\ramir\\IdeaProjects\\MyInvincibleLibrary\\server\\src\\tec\\ac\\cr\\mil\\RaidLibray\\Disks\\d"+currentDisk+"\\"+fileName+index+".pdf");
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(byteFiles);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }
    private static void createFile(int index, String fileName, int currentDisk) throws IOException {
        String path ="C:"+File.pathSeparator+"Users"+File.pathSeparator+"ramir"+File.pathSeparator+"" +
                "IdeaProjects"+File.pathSeparator+"MyInvincibleLibrary"+File.pathSeparator+"server" +
                "src"+File.pathSeparator+"tec"+File.pathSeparator+"ac"+File.pathSeparator+"cr" +
                "mil"+File.pathSeparator+"RaidLibray"+File.pathSeparator+"Disks"+File.pathSeparator+"d"+currentDisk+
                File.pathSeparator+fileName+index+".pdf";
        // Use relative path for Unix systems
        File f = new File(path);

        f.getParentFile().mkdirs();
        f.createNewFile();
    }
}