package tec.ac.cr.mil.logic;

import java.util.ArrayList;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

public class DatabaseFacace {

    public static void INSERT(Picture picture){
        Serializer.deserialize();
        picture.setId(getFreeID());
        pictureArrayList.add(picture);
        Serializer.serialize();
    }

    public static void DELETE(Picture picture){
        Serializer.deserialize();
        Picture toRMPicture = getOldPicture(picture.getId());
        if (toRMPicture != null){
            pictureArrayList.remove(toRMPicture);
        }
        Serializer.serialize();
    }

    public static void UPDATE(Picture picture){
        Serializer.deserialize();
        Picture toRMPicture = getOldPicture(picture.getId());
        if (toRMPicture != null){
            pictureArrayList.remove(toRMPicture);
            pictureArrayList.add(picture);
        }
        Serializer.serialize();
    }

    public static ArrayList<Picture> SELECT(){
        Serializer.deserialize();
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

}
