package tec.ac.cr.mil.logic;

import tec.ac.cr.mil.ml.ObjectRecognizer;
import tec.ac.cr.mil.raid.RaidFacade;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Base64;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

public class DatabaseFacade {

    public static void INSERT(Picture picture) throws IOException {
        Serializer.deserialize();
        picture.setId(getFreeID());
        byte[] decodedString = Base64.getDecoder().decode(new String(picture.getPictureData()).getBytes("UTF-8"));
        byte[] pictureBytes = picture.getPictureData().getBytes();
        picture.setDescription(ObjectRecognizer.getInstance().getDescription(decodedString));
        picture.setSize(pictureBytes.length);
        RaidFacade.addImage(picture.getPictureData(), picture.getName());
        picture.setPictureData("");
        pictureArrayList.add(picture);
        Serializer.serialize();
    }

    public static void DELETE(Picture picture){
        Serializer.deserialize();
        Picture toRMPicture = getOldPicture(picture.getId());
        if (toRMPicture != null){
            pictureArrayList.remove(toRMPicture);
        }
        RaidFacade.deleteImage(picture.getName());
        Serializer.serialize();
    }

    public static void UPDATE(Picture picture) throws IOException {
        Serializer.deserialize();
        Picture toRMPicture = getOldPicture(picture.getId());
        if (toRMPicture != null){
            picture.setPictureData(RaidFacade.readImage(toRMPicture.getSize(), toRMPicture.getName()));
            RaidFacade.deleteImage(toRMPicture.getName());
            RaidFacade.addImage(picture.getPictureData(), picture.getName());
            pictureArrayList.remove(toRMPicture);
            picture.setPictureData("");
            pictureArrayList.add(picture);
        }
        Serializer.serialize();
    }

    public static ArrayList<Picture> SELECT() throws IOException {
        Serializer.deserialize();
        getAllPicturesData();
        return pictureArrayList;
    }

    private static int getFreeID(){
        int i = 0;
        int id = 0;
        while (i < pictureArrayList.size()){
            if (pictureArrayList.get(i).getId() == id){
                id++;
                i = 0;
            }else{
                i++;
            }
        }
        return id;
    }

    private static Picture getOldPicture(int id){
        for (int i = 0; i < pictureArrayList.size(); i++){
            if (pictureArrayList.get(i).getId() == id){
                return pictureArrayList.get(i);
            }
        }
        return null;
    }

    private static void getAllPicturesData() throws IOException {
        for (int i = 0; i < pictureArrayList.size(); i++){
            Picture picture = pictureArrayList.get(i);
            String name = picture.getName();
            int size = picture.getSize();
            picture.setPictureData(RaidFacade.readImage(size, name));
        }
    }

}
