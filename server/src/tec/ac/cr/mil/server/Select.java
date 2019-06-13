package tec.ac.cr.mil.server;

import tec.ac.cr.mil.logic.Picture;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.ArrayList;

import static tec.ac.cr.mil.logic.Holder.pictureArrayList;

@Path("select")
public class Select {

    @GET
    @Path("all")
    @Produces(MediaType.APPLICATION_JSON)
    public ArrayList<Picture> getAllPictures(){
        System.out.println(5);
        Picture picture1 = new Picture("Hola", "kevin", 1298, 100, "dasdasd");
        Picture picture2 = new Picture("Sos", "chsas", 9999, 122, "grea");
        pictureArrayList.add(picture1);
        pictureArrayList.add(picture2);
        //Aqui va para retornar todas las imagenes
        return pictureArrayList;
    }

}
