package tec.ac.cr.mil.RaidLibray;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;

public class RaidManager {

    private static int parityPosition = 0;

    public static void Write(byte[] ImageBytes, String ImageName) throws IOException {
        checkDisks();
        int length = ImageBytes.length;
        int fileSize = length/4;
        int fileCounter = 0;
        int fileTotal = length/fileSize;
        int currentDisk = 0;
        while (fileCounter < fileTotal+1){
            if(currentDisk != parityPosition) {
                int begin = fileCounter * fileSize;
                int end = (fileCounter + 1) * fileSize;

                if (fileCounter != 0) end++;
                if (fileCounter == fileTotal - 1) end = length;

                byte[] partition = Arrays.copyOfRange(ImageBytes, begin, end);

                fillFile(partition, fileCounter, ImageName, currentDisk);


                if (currentDisk == 5) currentDisk = 0;
            }
            currentDisk++;
            fileCounter++;
        }
        if(parityPosition == 5) parityPosition = 0;
        calcParity(fileSize, ImageName, parityPosition);
        parityPosition++;

    }

    public static byte[] Read(int size, String Name){
        checkDisks();
        byte[] FileBytes = new byte[size];
        int stripSize = size/5;
        int currentDisk = 0;
        int totalPartitions = size/stripSize;
        int counter = 0;

        while (counter < totalPartitions){
            Path path = Paths.get("."+File.separator+"server"+File.separator+"src"+
                    File.separator+"tec"+File.separator+"ac"+File.separator+"cr"
                    +File.separator+"mil"+File.separator+"RaidLibray"+File.separator+
                    "Disks"+File.separator+"d"+currentDisk+File.separator+Name+counter+".pdf");
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

    public static void Seek() {
        checkDisks();
    }

    private static void fillFile(byte[] byteFiles, int index, String fileName, int currentDisk){
        File file = new File("."+File.separator+"server"+File.separator+
                "src"+File.separator+"tec"+File.separator+"ac"+File.separator+
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

    private static void calcParity(int size, String fileName, int disk){
        File file = new File("."+File.separator+"server"+File.separator+
                "src"+File.separator+"tec"+File.separator+"ac"+File.separator+
                "cr"+File.separator+"mil"+File.separator+"RaidLibray"+File.separator+"Disks"+File.separator+
                "d"+parityPosition+File.separator+fileName+"Parity.pdf");

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
        byte sum = 0;
        while(i<size){
            while (y<5 && y!=parityPosition){
                sum += (byte) + BytesMatrix[y][i];
                y++;
            }
            Response[i] = sum;
            y=0;
            i++;
        }



        return Response;
    }

    private static byte[][] calcByteMatrix (int size, String fileName, int disk){
        byte[][] Response = new byte[4][size];
        int counter = 0;
        while (counter<5 && counter!= parityPosition){
            Path path = Paths.get("."+File.separator+"server"+File.separator+"src"+
                    File.separator+"tec"+File.separator+"ac"+File.separator+"cr"
                    +File.separator+"mil"+File.separator+"RaidLibray"+File.separator+
                    "Disks"+File.separator+"d"+counter+File.separator+fileName+counter+".pdf");
            try {
                byte[] bArray = Files.readAllBytes(path);
                Response[counter]=bArray;
                // reading content from byte array
            } catch (IOException e) {
                e.printStackTrace();
            }


            counter++;
        }
        return Response;
    }

    private static void checkDisks(){
        int currentDisk = 0;
        Path path;

        while (currentDisk < 5){
            path = Paths.get("."+File.separator+"server"+File.separator+"src"+
                    File.separator+"tec"+File.separator+"ac"+File.separator+"cr"
                    +File.separator+"mil"+File.separator+"RaidLibray"+File.separator+
                    "Disks"+File.separator+"d"+currentDisk+File.separator+"sec.pdf");
                currentDisk++;
            try {
                Files.readAllBytes(path);
            } catch (IOException e) {
                System.out.println("Needs Recovery");
                Recovery(currentDisk);
            }
        }
    }
    private static void Recovery(int diskToRecover){

    }

}